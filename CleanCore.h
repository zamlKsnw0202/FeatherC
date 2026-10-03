#pragma once
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

namespace CleanUtil {

    
    inline QString ExpandEnv(const QString& input) {
        wchar_t buf[32767];
        DWORD n = ExpandEnvironmentStringsW(
            reinterpret_cast<const wchar_t*>(input.utf16()),
            buf, 32767);
        if (n == 0 || n > 32767) return input;
        return QString::fromWCharArray(buf, n - 1);
    }

 
    inline bool IsProcessRunning(const QString& exeName) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) return false;

        PROCESSENTRY32W pe = {};
        pe.dwSize = sizeof(pe);

        bool found = false;
        if (Process32FirstW(snap, &pe)) {
            do {
                if (_wcsicmp(pe.szExeFile,
                    reinterpret_cast<const wchar_t*>(exeName.utf16())) == 0) {
                    found = true;
                    break;
                }
            } while (Process32NextW(snap, &pe));
        }
        CloseHandle(snap);
        return found;
    }

 
    inline qint64 GetFolderSize(const QString& path) {
        qint64 total = 0;
        QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot,
            QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            total += it.fileInfo().size();
        }
        return total;
    }

  
    inline qint64 RemoveFolder(const QString& path, QString* errorMsg = nullptr) {
        qint64 removed = 0;
        QDir dir(path);
        if (!dir.exists()) return 0;
        removed = GetFolderSize(path);

        if (!dir.removeRecursively()) {
            if (errorMsg) *errorMsg = QStringLiteral("删除失败: %1").arg(path);
            return 0; 
        }
        return removed;
    }

  
    inline QString AppNameToProcess(const QString& appName) {
        static const QHash<QString, QString> map = {
            // ===== 浏览器 =====
            { QStringLiteral("Google Chrome"),        QStringLiteral("chrome.exe") },
            { QStringLiteral("Microsoft Edge"),       QStringLiteral("msedge.exe") },
            { QStringLiteral("Mozilla Firefox"),      QStringLiteral("firefox.exe") },
            { QStringLiteral("Opera"),                QStringLiteral("opera.exe") },
            { QStringLiteral("Vivaldi"),              QStringLiteral("vivaldi.exe") },
            { QStringLiteral("Brave"),                QStringLiteral("brave.exe") },
            { QStringLiteral("360 安全浏览器"),       QStringLiteral("360se.exe") },
            { QStringLiteral("QQ 浏览器"),            QStringLiteral("QQBrowser.exe") },
            { QStringLiteral("搜狗高速浏览器"),       QStringLiteral("SogouExplorer.exe") },

            // ===== 聊天 / 通讯 =====
            { QStringLiteral("Discord"),              QStringLiteral("Discord.exe") },
            { QStringLiteral("Telegram Desktop"),     QStringLiteral("Telegram.exe") },
            { QStringLiteral("钉钉"),                 QStringLiteral("DingTalk.exe") },
            { QStringLiteral("飞书"),                 QStringLiteral("Lark.exe") },
            { QStringLiteral("微信"),                 QStringLiteral("WeChat.exe") },
            { QStringLiteral("QQ"),                   QStringLiteral("QQ.exe") },
            { QStringLiteral("Microsoft Teams"),      QStringLiteral("Teams.exe") },
            { QStringLiteral("Slack"),                QStringLiteral("slack.exe") },
            { QStringLiteral("Zoom"),                 QStringLiteral("Zoom.exe") },
            { QStringLiteral("WhatsApp"),             QStringLiteral("WhatsApp.exe") },
            { QStringLiteral("豆包"),                 QStringLiteral("Doubao.exe") },

            // ===== 影音 =====
            { QStringLiteral("网易云音乐"),           QStringLiteral("cloudmusic.exe") },
            { QStringLiteral("QQ 音乐"),              QStringLiteral("QQMusic.exe") },
            { QStringLiteral("酷狗音乐"),             QStringLiteral("KuGou.exe") },
            { QStringLiteral("PotPlayer"),            QStringLiteral("PotPlayerMini64.exe") },
            { QStringLiteral("VLC"),                  QStringLiteral("vlc.exe") },
            { QStringLiteral("Spotify"),              QStringLiteral("Spotify.exe") },
            { QStringLiteral("OBS Studio"),           QStringLiteral("obs64.exe") },
            { QStringLiteral("Audacity"),             QStringLiteral("Audacity.exe") },
            { QStringLiteral("哔哩哔哩直播姬"),       QStringLiteral("BilibiliLive.exe") },
            { QStringLiteral("TikTok LIVE Studio"),   QStringLiteral("TikTokLiveStudio.exe") },
            { QStringLiteral("剪映"),                 QStringLiteral("JianyingPro.exe") },
            { QStringLiteral("必剪"),                 QStringLiteral("Bcut.exe") },

            // ===== 开发工具 =====
            { QStringLiteral("Visual Studio Code"),   QStringLiteral("Code.exe") },
            { QStringLiteral("PyCharm Community Edition"), QStringLiteral("pycharm64.exe") },
            { QStringLiteral("IntelliJ IDEA"),        QStringLiteral("idea64.exe") },
            { QStringLiteral("Node.js"),              QStringLiteral("node.exe") },
            { QStringLiteral("Python"),               QStringLiteral("python.exe") },
            { QStringLiteral("Cursor"),               QStringLiteral("Cursor.exe") },
            { QStringLiteral("Notion"),               QStringLiteral("Notion.exe") },
            { QStringLiteral("Android Studio"),       QStringLiteral("studio64.exe") },
            { QStringLiteral("GitHub Desktop"),       QStringLiteral("GitHubDesktop.exe") },
            { QStringLiteral("Unity"),                QStringLiteral("Unity.exe") },
            { QStringLiteral("Blender"),              QStringLiteral("blender.exe") },
            { QStringLiteral("Dev-C++"),              QStringLiteral("devcpp.exe") },
            { QStringLiteral("Bootstrap Studio"),     QStringLiteral("Bootstrap Studio.exe") },
            { QStringLiteral("World Creator"),        QStringLiteral("World Creator.exe") },

            // ===== 下载 / 网盘 =====
            { QStringLiteral("迅雷"),                 QStringLiteral("Thunder.exe") },
            { QStringLiteral("Internet Download Manager"), QStringLiteral("IDMan.exe") },
            { QStringLiteral("百度网盘"),             QStringLiteral("BaiduNetdisk.exe") },
            { QStringLiteral("夸克"),                 QStringLiteral("Quark.exe") },

            // ===== 游戏平台 / 启动器 =====
            { QStringLiteral("Steam"),                QStringLiteral("steam.exe") },
            { QStringLiteral("Epic Games Launcher"),  QStringLiteral("EpicGamesLauncher.exe") },
            { QStringLiteral("Riot Client"),          QStringLiteral("RiotClientServices.exe") },
            { QStringLiteral("Rockstar Games Launcher"), QStringLiteral("RockstarService.exe") },
            { QStringLiteral("Ubisoft Connect"),      QStringLiteral("UbisoftConnect.exe") },
            { QStringLiteral("Battle.net"),           QStringLiteral("Battle.net.exe") },
            { QStringLiteral("EA App"),               QStringLiteral("EADesktop.exe") },
            { QStringLiteral("GOG Galaxy"),           QStringLiteral("GalaxyClient.exe") },
            { QStringLiteral("Xbox"),                 QStringLiteral("XboxPcApp.exe") },
            { QStringLiteral("我的世界启动器"),       QStringLiteral("MinecraftLauncher.exe") },
            { QStringLiteral("Minecraft Launcher"),   QStringLiteral("MinecraftLauncher.exe") },
            { QStringLiteral("PCL2 启动器"),          QStringLiteral("PCL2.exe") },
            { QStringLiteral("HMCL 启动器"),          QStringLiteral("HMCL.exe") },
            { QStringLiteral("Paradox Launcher"),     QStringLiteral("paradox-launcher-v2.exe") },
            { QStringLiteral("光·遇"),                QStringLiteral("Sky.exe") },
            { QStringLiteral("超自然行动组"),         QStringLiteral("Preternatural.exe") },
            { QStringLiteral("网易UU加速器"),         QStringLiteral("uu.exe") },

            // ===== Adobe =====
            { QStringLiteral("Adobe Photoshop 2024"), QStringLiteral("Photoshop.exe") },
            { QStringLiteral("Adobe Photoshop 2023"), QStringLiteral("Photoshop.exe") },
            { QStringLiteral("Adobe Photoshop 2022"), QStringLiteral("Photoshop.exe") },
            { QStringLiteral("Adobe Photoshop 2026"), QStringLiteral("Photoshop.exe") },
            { QStringLiteral("Adobe Premiere Pro 2024"), QStringLiteral("Adobe Premiere Pro.exe") },
            { QStringLiteral("Adobe Premiere Pro 2023"), QStringLiteral("Adobe Premiere Pro.exe") },
            { QStringLiteral("Adobe After Effects 2024"), QStringLiteral("AfterFX.exe") },
            { QStringLiteral("Adobe After Effects 2023"), QStringLiteral("AfterFX.exe") },
            { QStringLiteral("Adobe Illustrator 2024"), QStringLiteral("Illustrator.exe") },
            { QStringLiteral("Adobe Illustrator 2023"), QStringLiteral("Illustrator.exe") },
            { QStringLiteral("Adobe InDesign 2024"),  QStringLiteral("InDesign.exe") },
            { QStringLiteral("Adobe Lightroom Classic"), QStringLiteral("Lightroom.exe") },
            { QStringLiteral("Adobe Lightroom"),      QStringLiteral("lightroom.exe") },
            { QStringLiteral("Adobe Audition 2024"),  QStringLiteral("Audition.exe") },
            { QStringLiteral("Adobe Audition 2023"),  QStringLiteral("Audition.exe") },
            { QStringLiteral("Adobe Media Encoder 2024"), QStringLiteral("Adobe Media Encoder.exe") },
            { QStringLiteral("Adobe Premiere Rush"),  QStringLiteral("Rush.exe") },
            { QStringLiteral("Adobe Animate 2024"),   QStringLiteral("Animate.exe") },
            { QStringLiteral("Adobe Dreamweaver 2024"), QStringLiteral("Dreamweaver.exe") },
            { QStringLiteral("Adobe Bridge 2024"),    QStringLiteral("Bridge.exe") },
            { QStringLiteral("Adobe Media Cache"),    QStringLiteral("") },       
            { QStringLiteral("Adobe Common Logs"),    QStringLiteral("") },

            // ===== 办公 =====
            { QStringLiteral("WPS Office"),           QStringLiteral("wps.exe") },
            { QStringLiteral("Microsoft Office"),     QStringLiteral("WINWORD.EXE") },
            { QStringLiteral("OneNote"),              QStringLiteral("ONENOTE.EXE") },
            { QStringLiteral("Outlook"),              QStringLiteral("OUTLOOK.EXE") },
            { QStringLiteral("Process Hacker"),       QStringLiteral("ProcessHacker.exe") },

            // ===== 系统工具 / 通用 =====
            { QStringLiteral("Everything"),           QStringLiteral("Everything.exe") },
            { QStringLiteral("CCleaner"),             QStringLiteral("CCleaner.exe") },
            { QStringLiteral("Windows 临时文件"),     QStringLiteral("") },
            { QStringLiteral("CPU-Z"),                QStringLiteral("cpuz.exe") },
            { QStringLiteral("7-Zip"),                QStringLiteral("7zFM.exe") },
            { QStringLiteral("Cheat Engine"),         QStringLiteral("Cheat Engine.exe") },
            { QStringLiteral("AMD DxcCache"),         QStringLiteral("") },
            { QStringLiteral("Clash Verge"),          QStringLiteral("clash-verge.exe") },
            { QStringLiteral("驱动总裁"),             QStringLiteral("DrvCeo.exe") },
            { QStringLiteral("Bezier Games"),         QStringLiteral("") },
            { QStringLiteral("图吧工具箱"),           QStringLiteral("") },
            { QStringLiteral("WindSoul 软件管家"),    QStringLiteral("winManager.exe") },
            { QStringLiteral("Radmin VPN"),           QStringLiteral("RvControlSvc.exe") },
            { QStringLiteral("WinSCP"),               QStringLiteral("WinSCP.exe") },
            { QStringLiteral("PixPin"),               QStringLiteral("PixPin.exe") },
            { QStringLiteral("BongoCat"),             QStringLiteral("BongoCat.exe") },
        };
        return map.value(appName, QString());
    }

  
    struct CleanResult {
        bool    success = false;      // 是否成功执行
        bool    wasRunning = false;   // 进程是否在运行
        qint64  removedBytes = 0;     // 删除的总字节数
        int     removedFiles = 0;     // 删路径
        int     failedPaths = 0;      // 删失败数量
        QString message;              // 附加信息
    };

  
    inline CleanResult CleanAppCache(const QString& appName,
        const std::vector<std::wstring>& paths,
        QWidget* parent = nullptr)
    {
        CleanResult result;

      
        QString procName = AppNameToProcess(appName);
        if (!procName.isEmpty() && IsProcessRunning(procName)) {
            result.wasRunning = true;
            result.message = QStringLiteral("%1 正在运行，请先关闭后再清理。").arg(appName);
            return result;
        }

       
        qint64 total = 0;
        for (const auto& wp : paths) {
            QString raw = QString::fromStdWString(wp);
            QString real = ExpandEnv(raw);     

            QString err;
            qint64 bytes = RemoveFolder(real, &err);
            if (bytes > 0 || !QDir(real).exists()) {
                total += bytes;
                result.removedFiles++;
            }
            else {
                result.failedPaths++;
                qDebug() << "删除失败:" << real << err;
            }
        }

        result.removedBytes = total;
        result.success = true;
        result.message = QStringLiteral("清理完成");
        return result;
    }

    // ---------- 格式化大小 ----------
    inline QString FormatSize(qint64 bytes) {
        const double KB = 1024.0;
        const double MB = KB * 1024;
        const double GB = MB * 1024;

        if (bytes >= GB) return QStringLiteral("%1 GB").arg(bytes / GB, 0, 'f', 2);
        if (bytes >= MB) return QStringLiteral("%1 MB").arg(bytes / MB, 0, 'f', 2);
        if (bytes >= KB) return QStringLiteral("%1 KB").arg(bytes / KB, 0, 'f', 2);
        return QStringLiteral("%1 B").arg(bytes);
    }

} 