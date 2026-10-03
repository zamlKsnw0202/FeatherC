#include "stdafx.h"
#include "ScanHugeFile.h"
#include <QDir>
#include <QDebug>

ScanHugeFile::ScanHugeFile(QObject* parent) : QObject(parent)
{
   
    m_excludeDirs = {
        QStringLiteral("C:\\Windows"),
        QStringLiteral("C:\\$Recycle.Bin"),
        QStringLiteral("C:\\System Volume Information"),
        QStringLiteral("C:\\$WinREAgent"),
    };
}


bool ScanHugeFile::isExcluded(const QString& dir) const
{
    QString d = QDir::toNativeSeparators(dir).toLower();
    while (d.endsWith(QLatin1Char('\\')))
        d.chop(1);

    for (const QString& raw : m_excludeDirs) {
        QString e = QDir::toNativeSeparators(raw).toLower();
        while (e.endsWith(QLatin1Char('\\')))
            e.chop(1);

        if (d == e)
            return true;
        if (d.startsWith(e + QLatin1Char('\\')))
            return true;
    }
    return false;
}


// É¨ÃèÄ¿Â¼

quint64 ScanHugeFile::scanDir(const QString& dir,
    QVector<BigFile>& results,
    int depth)
{
    if (m_canceled.load() || depth > 64)
        return 0;

    if (isExcluded(dir))
        return 0;

    const std::wstring wdir = dir.toStdWString();
    const std::wstring pattern = wdir + L"\\*";

    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(pattern.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;

    quint64 totalSize = 0;

    do {
        if (m_canceled.load())
            break;

        const wchar_t* name = fd.cFileName;
        if (wcscmp(name, L".") == 0 || wcscmp(name, L"..") == 0)
            continue;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
            continue;

        const QString fullPath = dir + QLatin1Char('\\') + QString::fromWCharArray(name);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (isExcluded(fullPath))
                continue;
            totalSize += scanDir(fullPath, results, depth + 1);
        }
        else {
            const quint64 sz = fileSizeOf(fd);
            totalSize += sz;

            if (sz >= kThreshold) {
                BigFile bf{ fullPath, sz };
                results.push_back(bf);
                emit fileFound(bf);
            }
        }

        if (totalSize > (1ULL << 62))
            break;

    } while (FindNextFileW(hFind, &fd));

    FindClose(hFind);
    return totalSize;
}


// ¶¥²ãÉ¨Ãè
void ScanHugeFile::scan(const QString& root)
{
    m_canceled.store(false);

    QVector<BigFile> results;
    QString rootPath = root;
    if (!rootPath.endsWith(QLatin1Char('\\')))
        rootPath += QLatin1Char('\\');

    const std::wstring wroot = rootPath.toStdWString();

    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW((wroot + L"*").c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        emit error(QStringLiteral("ÎÞ·¨·ÃÎÊ %1").arg(rootPath));
        emit finished(results);
        return;
    }

    QStringList subDirs;
    do {
        const wchar_t* name = fd.cFileName;
        if (wcscmp(name, L".") == 0 || wcscmp(name, L"..") == 0)
            continue;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
            continue;

        const QString qname = QString::fromWCharArray(name);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            const QString fullPath = rootPath + qname;

            if (isExcluded(fullPath))
                continue;

            subDirs << fullPath;
        }
        else {
            const quint64 sz = fileSizeOf(fd);
            if (sz >= kThreshold) {
                BigFile bf{ rootPath + qname, sz };
                results.push_back(bf);
                emit fileFound(bf);
            }
        }
    } while (FindNextFileW(hFind, &fd));
    FindClose(hFind);

    const int total = subDirs.size();
    for (int i = 0; i < total; ++i) {
        if (m_canceled.load())
            break;

        emit dirProgress(i + 1, total, subDirs[i]);
        scanDir(subDirs[i], results);
    }

    std::sort(results.begin(), results.end(),
        [](const BigFile& a, const BigFile& b) { return a.size > b.size; });

    emit finished(results);
}