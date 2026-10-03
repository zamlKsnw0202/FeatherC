#include "stdafx.h"
#include "FeatherC.h"
#include "data.h"
#include "CleanCore.h"
#include "InformationBoard.h"
#include "ConfirmDialog.h"
#include "ScanHugeFile.h"
#include <Windows.h>
#include <iostream>
#include <sstream>

#include <QPushButton>



static void LogW(const std::wstring& msg) {
    OutputDebugStringW((msg + L"\n").c_str());

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE && h != nullptr) {
        DWORD written = 0;
        WriteConsoleW(h, msg.c_str(), (DWORD)msg.size(), &written, nullptr);
        WriteConsoleW(h, L"\n", 1, &written, nullptr);
    }
}


template<typename T>
static std::wstring ToW(const T& v) {
    std::wostringstream oss;
    oss << v;
    return oss.str();
}


FeatherC::FeatherC(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.syscleanTempBtn, &QPushButton::clicked, this, &FeatherC::WindowsClean);
    connect(ui.sysToolConfigBtn, &QPushButton::clicked, this, [this]() {
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.fMask = SEE_MASK_NOCLOSEPROCESS;
        sei.lpVerb = L"open";  
        sei.lpFile = L"C:\\Windows\\System32\\cleanmgr.exe";
        sei.lpParameters = L"/sageset:1";
        sei.nShow = SW_SHOWNORMAL;

        if (!ShellExecuteExW(&sei)) {
            DWORD err = GetLastError();
           
        }
		}); 
    connect(ui.MFoldersBtn, &QPushButton::clicked, this, [this]() {
        ShowOnDriveC();
        });
    QTimer::singleShot(0, this, [this]() {
        onScanClicked();
        });
}


struct InstalledApp {
    std::wstring name;
    std::wstring version;
    std::wstring installLocation;
    std::wstring uninstallString;
    std::wstring displayIcon;        // 新增
    std::wstring quietUninstallString; // 新增
};


static std::wstring ExtractDir(const std::wstring& raw) {
    if (raw.empty()) return L"";

    std::wstring s = raw;

   
    while (!s.empty() && (s.front() == L' ' || s.front() == L'\t')) s.erase(0, 1);
    while (!s.empty() && (s.back() == L' ' || s.back() == L'\t')) s.pop_back();

    if (!s.empty() && s.front() == L'"') {
        size_t endQ = s.find(L'"', 1);
        if (endQ != std::wstring::npos)
            s = s.substr(1, endQ - 1);
        else
            s.erase(0, 1); 
    }
    else {
        
        size_t sp = s.find(L' ');
        if (sp != std::wstring::npos)
            s = s.substr(0, sp);
    }

   
    size_t comma = s.find_last_of(L',');
    if (comma != std::wstring::npos) {
       
        bool allDigit = true;
        for (size_t i = comma + 1; i < s.size(); ++i) {
            if (!iswdigit(s[i])) { allDigit = false; break; }
        }
        if (allDigit)
            s = s.substr(0, comma);
    }

   
    size_t pos = s.find_last_of(L"\\/");
    if (pos == std::wstring::npos || pos == 0)
        return L"";

    return s.substr(0, pos);
}


static void ReadUninstallKey(HKEY root, const std::wstring& subKey,
    std::vector<InstalledApp>& out) {

    HKEY hKey = nullptr;
    if (RegOpenKeyExW(root, subKey.c_str(), 0,
        KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS)
        return;

    DWORD index = 0;
    wchar_t subName[256];
    DWORD subNameLen = 256;

    while (RegEnumKeyExW(hKey, index++, subName, &subNameLen,
        nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {

        HKEY hSub = nullptr;
        if (RegOpenKeyExW(hKey, subName, 0, KEY_READ, &hSub) == ERROR_SUCCESS) {

            
            auto readStr = [&](const wchar_t* valueName) -> std::wstring {
                wchar_t buf[1024] = {};
                DWORD size = sizeof(buf);
                DWORD type = 0;
                if (RegQueryValueExW(hSub, valueName, nullptr, &type,
                    (LPBYTE)buf, &size) == ERROR_SUCCESS) {
                    return buf;
                }
                return L"";
                };

            InstalledApp app;
            app.name = readStr(L"DisplayName");
            app.version = readStr(L"DisplayVersion");
            app.installLocation = readStr(L"InstallLocation");
            app.uninstallString = readStr(L"UninstallString");
            app.displayIcon = readStr(L"DisplayIcon");
            app.quietUninstallString = readStr(L"QuietUninstallString");

            
            

            if (app.installLocation.empty())
                app.installLocation = ExtractDir(app.uninstallString);

            if (app.installLocation.empty())
                app.installLocation = ExtractDir(app.quietUninstallString);

            if (app.installLocation.empty())
                app.installLocation = ExtractDir(app.displayIcon);

            
            if (!app.installLocation.empty() && app.installLocation.front() == L'"') {
                if (app.installLocation.back() == L'"')
                    app.installLocation = app.installLocation.substr(1, app.installLocation.size() - 2);
                else
                    app.installLocation.erase(0, 1);
            }
            // ======================================

            if (!app.name.empty())
                out.push_back(std::move(app));

            RegCloseKey(hSub);
        }
        subNameLen = 256;
    }

    RegCloseKey(hKey);
}


void FeatherC::FindAllAPP() {

    std::vector<InstalledApp> apps;
    ReadUninstallKey(HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", apps);
    ReadUninstallKey(HKEY_LOCAL_MACHINE,
        L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall", apps);
    ReadUninstallKey(HKEY_CURRENT_USER,
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", apps);

   
    int withPath = 0, withoutPath = 0;
    for (const auto& app : apps) {
        if (app.installLocation.empty()) withoutPath++;
        else withPath++;
    }

    LogW(L"共找到 " + ToW(apps.size()) + L" 个程序");
    LogW(L"有路径: " + ToW(withPath) + L" | 无路径: " + ToW(withoutPath));

   
    // 清空旧数据
    m_apps.clear();
    m_apps.reserve(apps.size());

    // 存进 m_apps（只保留有路径的）
    for (const auto& app : apps) {
        if (app.installLocation.empty()) continue;

        AppItem item;
        item.name = app.name;
        item.version = app.version;
        item.path = app.installLocation;
        m_apps.push_back(std::move(item));
    }

}
void FeatherC::InitList() {

   
    auto* layout = qobject_cast<QVBoxLayout*>(ui.listContainer->layout());
    if (!layout) {
        LogW(L"[InitList] listContainer 没有 QVBoxLayout");
        return;
    }

   
    while (layout->count() > 1) {
        QLayoutItem* item = layout->takeAt(0);
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }

	
    for (const auto& app : m_apps) {

        auto* board = new InformationBoard(ui.listContainer);


        connect(board, &InformationBoard::cleanRequested,
            this, [this](const QString& name, const QString& path) {
                // 处理清理请求
                qDebug() << "清理请求:" << name << path;

                ConfirmDialog dlg(this);
                dlg.setAppName(name);
                auto& paths = Data.APP_deletePaths[name.toStdWString()].path;

                QStringList Paths;
                for (const auto& p : paths) {
                    Paths.append(QString::fromStdWString(p));
                }
                dlg.setPaths(Paths);

                if (dlg.exec() == QDialog::Accepted) {

                   
                    auto result = CleanUtil::CleanAppCache(
                        name, paths, this);
                    //正在运行
                    if (result.wasRunning) {
                       
                        QMessageBox::warning(this,
                            QStringLiteral("无法清理"),
                            result.message);
                    }
                    else if (!result.success) {
                        QMessageBox::warning(this,
                            QStringLiteral("清理失败"),
                            result.message);
                    }
                    else {
                     
                        QString msg = QStringLiteral("清理完成！\n\n")
                            .arg(name);
                        msg += QStringLiteral("释放空间: %1\n")
                            .arg(CleanUtil::FormatSize(result.removedBytes));
                        msg += QStringLiteral("成功路径: %1 个\n")
                            .arg(result.removedFiles);
                        if (result.failedPaths > 0) {
                            msg += QStringLiteral("失败路径: %1 个\n")
                                .arg(result.failedPaths);
                        }

                        QMessageBox::information(this,
                            QStringLiteral("清理完成"), msg);
                    }
                }
            });


		board->setProperty("appName", QString::fromStdWString(app.name)); 
        if (Data.Reg_names.count(app.name))
        {
            Data.Reg_exist_names.push_back(app.name);
            board->setRegistered(true);
        }
        else
        {
            board->setRegistered(false);
        }
        board->setAppName(QString::fromStdWString(app.name));
        board->setVersion(QString::fromStdWString(app.version));
        board->setPath(QString::fromStdWString(app.path));
        
        layout->insertWidget(layout->count() - 1, board);
    }

    
    ui.statusBar->showMessage(
        QString("共 %1 个程序").arg(static_cast<int>(m_apps.size())));
}
void FeatherC::WindowsClean() {
    ConfirmDialog dlg(this);

    dlg.setAppName("System Temp & Report(Logs)");
    dlg.setPaths({
        // 1. Windows 日志
        "C:/Windows/Logs/CBS",
        "C:/Windows/Logs/DISM",
        "C:/Windows/Logs",

        // 2. Windows 更新下载缓存
        "C:/Windows/SoftwareDistribution/Download",

        // 3. 传递优化缓存
        "C:/Windows/ServiceProfiles/NetworkService/AppData/Local/Microsoft/Windows/DeliveryOptimization",

        // 4. 内核转储 / 蓝屏文件
        "C:/Windows/Minidump",
        "C:/Windows/LiveKernelReports",
        "C:/Windows/MEMORY.DMP",

        // 5. WER 错误报告
        "C:/ProgramData/Microsoft/Windows/WER/ReportQueue",
        "C:/ProgramData/Microsoft/Windows/WER/ReportArchive",
        "C:/Users/<用户>/AppData/Local/Microsoft/Windows/WER/ReportQueue",
        "C:/Users/<用户>/AppData/Local/Microsoft/Windows/WER/ReportArchive",

        // 6. 程序崩溃转储
        "C:/Users/<用户>/AppData/Local/CrashDumps",

        // 7. 用户临时目录
        "C:/Users/<用户>/AppData/Local/Temp",

        //8.Cleanmgr
        "Cleanmgr For Your Config"
        });
    dlg.setDescription({
        "C:/Windows/Logs/CBS\n"
        "   组件安装日志，常达几百 MB，可安全删除。\n\n"

        "C:/Windows/Logs/DISM\n"
        "   DISM 操作日志，排查系统映像问题时用，平时可删。\n\n"

        "C:/Windows/Logs\n"
        "   系统其他日志，仅删大于 5MB 的文件。\n\n"

        "C:/Windows/SoftwareDistribution/Download\n"
        "   Windows 更新下载缓存，通常几十 MB ~ 几 GB。\n\n"

        "C:/Windows/ServiceProfiles/NetworkService/.../DeliveryOptimization\n"
        "   传递优化缓存，P2P 更新分发用，可安全删除。\n\n"

        "C:/Windows/Minidump\n"
        "   蓝屏小内存转储，每份几百 KB ~ 几 MB。\n\n"

        "C:/Windows/LiveKernelReports\n"
        "   内核实时报告，用于诊断硬件/驱动问题。\n\n"

        "C:/Windows/MEMORY.DMP\n"
        "   完整内存转储，单文件可达几 GB，仅蓝屏后生成。\n\n"

        "C:/ProgramData/Microsoft/Windows/WER/ReportQueue\n"
        "   系统级错误报告队列，待发送的报告。\n\n"

        "C:/ProgramData/Microsoft/Windows/WER/ReportArchive\n"
        "   系统级错误报告归档，已发送的报告。\n\n"

        "C:/Users/<用户>/AppData/Local/Microsoft/Windows/WER/ReportQueue\n"
        "   用户级错误报告队列。\n\n"

        "C:/Users/<用户>/AppData/Local/Microsoft/Windows/WER/ReportArchive\n"
        "   用户级错误报告归档。\n\n"

        "C:/Users/<用户>/AppData/Local/CrashDumps\n"
        "   程序崩溃转储，单文件几十 MB ~ 几 GB。\n\n"

        "C:/Users/<用户>/AppData/Local/Temp\n"
        "   用户临时目录，仅删除大于 10MB 的文件。\n"
        });

    if (dlg.exec() == QDialog::Accepted) {
        qint64 freed = cleanSystemCacheFiles();
        if (freed > 0) {
           
            QMessageBox::information(this, "清理完成",
                QString("已释放C盘：%1 MB")
                .arg(freed / 1024.0 / 1024.0, 0, 'f', 2));

            
            statusBar()->showMessage(
                QString("清理完成，释放 %1 MB").arg(freed / 1024.0 / 1024.0, 0, 'f', 2),
                5000);
        }
        else {
            QMessageBox::warning(this, "清理完成",
                "没有可清理的大文件，或文件正在被占用。");
        }
    }
}   

FeatherC::~FeatherC()
{
}

void FeatherC::onScanClicked()
{
    
    auto* dlg = new QProgressDialog(
        QStringLiteral("正在扫描 C 盘..."),
        QStringLiteral("取消"), 0, 100, this);
    dlg->setWindowModality(Qt::WindowModal);
    dlg->setMinimumDuration(0);
    dlg->setAutoClose(false);
    dlg->setAutoReset(false);

   
    auto* thread = new QThread(this);
    auto* scanner = new ScanHugeFile;
    scanner->moveToThread(thread);

    connect(thread, &QThread::started, scanner, [scanner] {
        scanner->scan(QStringLiteral("C:\\"));
        });

   
    connect(scanner, &ScanHugeFile::dirProgress,
        this, [dlg](int cur, int total, const QString& dir) {
            dlg->setLabelText(
                QStringLiteral("(%1/%2) %3").arg(cur).arg(total).arg(dir));
            dlg->setValue(total ? cur * 100 / total : 0);
        });

   
    connect(scanner, &ScanHugeFile::finished,
        this, [this, dlg, thread, scanner](const QVector<BigFile>& results) {
            dlg->close();
            dlg->deleteLater();

           
            QDialog resultDlg(this);
            resultDlg.setWindowTitle(QStringLiteral("扫描完成"));
            resultDlg.resize(860, 620);

            auto* outerLayout = new QVBoxLayout(&resultDlg);
            outerLayout->setContentsMargins(10, 10, 10, 10);
            outerLayout->setSpacing(8);

           
            auto* header = new QLabel(
                QStringLiteral("共找到 <b>%1</b> 个大于 200 MB 的文件")
                .arg(results.size()),
                &resultDlg);
            header->setTextFormat(Qt::RichText);
            outerLayout->addWidget(header);

            auto* scroll = new QScrollArea(&resultDlg);
            scroll->setWidgetResizable(true);
            scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

            auto* content = new QWidget;
            auto* vbox = new QVBoxLayout(content);
            vbox->setContentsMargins(4, 4, 4, 4);
            vbox->setSpacing(4);

            if (results.isEmpty()) {
                auto* empty = new QLabel(
                    QStringLiteral("没有找到超过 200MB 的文件。"), content);
                empty->setAlignment(Qt::AlignCenter);
                empty->setStyleSheet(QStringLiteral("color:#888; padding:20px;"));
                vbox->addWidget(empty);
            }
            else {
                for (const auto& f : results) {
                    
                    auto* row = new QFrame(content);
                    row->setFrameShape(QFrame::StyledPanel);
                    row->setStyleSheet(QStringLiteral(
                        "QFrame {"
                        "  background:#fafafa;"
                        "  border:1px solid #e0e0e0;"
                        "  border-radius:4px;"
                        "}"));

                    auto* h = new QHBoxLayout(row);
                    h->setContentsMargins(8, 5, 8, 5);
                    h->setSpacing(10);

                    // 大小
                    auto* sizeLabel = new QLabel(
                        QStringLiteral("%1 MB").arg(f.size / ScanHugeFile::kMB),
                        row);
                    sizeLabel->setFixedWidth(90);
                    sizeLabel->setStyleSheet(QStringLiteral(
                        "font-weight:bold; color:#c0392b; border:none;"));
                    sizeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

                    // 路径
                    auto* pathLabel = new QLabel(f.path, row);
                    pathLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
                    pathLabel->setToolTip(f.path);
                    pathLabel->setStyleSheet(QStringLiteral("border:none;"));
                    pathLabel->setWordWrap(false);

                    h->addWidget(sizeLabel);
                    h->addWidget(pathLabel, 1);

                    vbox->addWidget(row);
                }
            }

            vbox->addStretch(1);
            scroll->setWidget(content);
            outerLayout->addWidget(scroll, 1);

           
            auto* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok, &resultDlg);
            connect(btnBox, &QDialogButtonBox::accepted,
                &resultDlg, &QDialog::accept);
            outerLayout->addWidget(btnBox);

            resultDlg.exec();

            
            thread->quit();
            thread->wait();
            scanner->deleteLater();
            thread->deleteLater();
        });

    // ==========  出错 ==========
    connect(scanner, &ScanHugeFile::error,
        this, [this](const QString& msg) {
            QMessageBox::warning(this, QStringLiteral("错误"), msg);
        });

    // ========== 取消按钮 ==========
    connect(dlg, &QProgressDialog::canceled, scanner, [scanner] {
        scanner->cancel();
        });

   
    thread->start();
}