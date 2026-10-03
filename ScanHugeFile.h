#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <atomic>
#include <windows.h>

struct BigFile {
    QString   path;
    quint64   size = 0;   // 字节
};

class ScanHugeFile : public QObject
{
    Q_OBJECT
public:
    // 阈值：200 MB
    static constexpr quint64 kThreshold = 200ULL * 1024 * 1024;
    static constexpr quint64 kMB = 1024ULL * 1024;

    explicit ScanHugeFile(QObject* parent = nullptr);

    // 请求停止
    void cancel() { m_canceled.store(true); }

    // 设置要排除的目录
    void setExcludeDirs(const QStringList& dirs) { m_excludeDirs = dirs; }

public slots:
    // 在工作线程中执行
    void scan(const QString& root = QStringLiteral("C:\\"));

signals:
    void fileFound(const BigFile& file);
    void dirProgress(int current, int total, const QString& dir);
    void finished(const QVector<BigFile>& results);
    void error(const QString& message);

private:
    std::atomic_bool m_canceled{ false };
    QStringList      m_excludeDirs;

    bool isExcluded(const QString& dir) const;

    quint64 scanDir(const QString& dir, QVector<BigFile>& results, int depth = 0);

    static quint64 fileSizeOf(const WIN32_FIND_DATAW& fd) {
        return (static_cast<quint64>(fd.nFileSizeHigh) << 32) | fd.nFileSizeLow;
    }
};