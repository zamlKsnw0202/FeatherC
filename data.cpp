#include "stdafx.h"
#include "data.h"

data::data()
{
    Reg_names = {
        // 浏览器
        L"Google Chrome",
        L"Microsoft Edge",
        L"Mozilla Firefox",
        L"Opera",
        L"Vivaldi",
        L"Brave",
        L"360 安全浏览器",
        L"QQ 浏览器",
        L"搜狗高速浏览器",

        // 聊天 / 通讯
        L"Discord",
        L"Telegram Desktop",
        L"钉钉",
        L"飞书",
        L"微信",
        L"QQ",
        L"Microsoft Teams",
        L"Slack",
        L"Zoom",
        L"WhatsApp",
        L"豆包",

        // 影音
        L"网易云音乐",
        L"QQ 音乐",
        L"酷狗音乐",
        L"PotPlayer",
        L"VLC",
        L"Spotify",
        L"OBS Studio",
        L"Audacity",
        L"哔哩哔哩直播姬",
        L"TikTok LIVE Studio",
        L"剪映",
        L"必剪",

        // 开发工具
        L"Visual Studio Code",
        L"PyCharm Community Edition",
        L"IntelliJ IDEA",
        L"Node.js",
        L"Python",
        L"Cursor",
        L"Notion",
        L"Android Studio",
        L"GitHub Desktop",
        L"Unity",
        L"Blender",
        L"Dev-C++",
        L"Bootstrap Studio",
        L"World Creator",

        // 下载 / 网盘
        L"迅雷",
        L"Internet Download Manager",
        L"百度网盘",
        L"夸克",

        // 游戏平台 / 启动器
        L"Steam",
        L"Epic Games Launcher",
        L"Riot Client",
        L"Rockstar Games Launcher",
        L"Ubisoft Connect",
        L"Battle.net",
        L"EA App",
        L"GOG Galaxy",
        L"Xbox",
        L"我的世界启动器",
        L"Minecraft Launcher",
        L"PCL2 启动器",
        L"HMCL 启动器",
        L"Paradox Launcher",
        L"光·遇",
        L"超自然行动组",
        L"网易UU加速器",

        // 办公 / 设计 / Adobe
        L"Adobe Photoshop 2024",
        L"Adobe Photoshop 2023",
        L"Adobe Photoshop 2022",
        L"Adobe Photoshop 2026",
        L"Adobe Premiere Pro 2024",
        L"Adobe Premiere Pro 2023",
        L"Adobe After Effects 2024",
        L"Adobe After Effects 2023",
        L"Adobe Illustrator 2024",
        L"Adobe Illustrator 2023",
        L"Adobe InDesign 2024",
        L"Adobe Lightroom Classic",
        L"Adobe Lightroom",
        L"Adobe Audition 2024",
        L"Adobe Audition 2023",
        L"Adobe Media Encoder 2024",
        L"Adobe Premiere Rush",
        L"Adobe Animate 2024",
        L"Adobe Dreamweaver 2024",
        L"Adobe Bridge 2024",
        L"Adobe Media Cache",
        L"WPS Office",
        L"Microsoft Office",
        L"OneNote",
        L"Outlook",
        L"Process Hacker",

        // 系统工具 / 通用
        L"Everything",
        L"CCleaner",
        L"Windows 临时文件",
        L"CPU-Z",
        L"7-Zip",
        L"Cheat Engine",
        L"AMD DxcCache",
        L"Clash Verge",
        L"驱动总裁",
        L"Bezier Games",
        L"图吧工具箱",
        L"WindSoul 软件管家",
        L"Radmin VPN",
        L"WinSCP",
        L"PixPin",
        L"BongoCat",
    };

    //============================================================
    // 浏览器
    //============================================================

    APP_deletePaths[L"Google Chrome"] = {
        { L"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Cache",
          L"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Code Cache",
          L"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\GPUCache" }, true
    };

    APP_deletePaths[L"Microsoft Edge"] = {
        { L"%LOCALAPPDATA%\\Microsoft\\Edge\\User Data\\Default\\Cache",
          L"%LOCALAPPDATA%\\Microsoft\\Edge\\User Data\\Default\\Code Cache",
          L"%LOCALAPPDATA%\\Microsoft\\Edge\\User Data\\Default\\GPUCache" }, true
    };

    APP_deletePaths[L"Mozilla Firefox"] = {
        { L"%LOCALAPPDATA%\\Mozilla\\Firefox\\Profiles\\*\\cache2" }, true
    };

    APP_deletePaths[L"Opera"] = {
        { L"%APPDATA%\\Opera Software\\Opera Stable\\Cache",
          L"%APPDATA%\\Opera Software\\Opera Stable\\Code Cache",
          L"%APPDATA%\\Opera Software\\Opera Stable\\GPUCache" }, true
    };

    APP_deletePaths[L"Vivaldi"] = {
        { L"%LOCALAPPDATA%\\Vivaldi\\User Data\\Default\\Cache",
          L"%LOCALAPPDATA%\\Vivaldi\\User Data\\Default\\Code Cache",
          L"%LOCALAPPDATA%\\Vivaldi\\User Data\\Default\\GPUCache" }, true
    };

    APP_deletePaths[L"Brave"] = {
        { L"%LOCALAPPDATA%\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cache",
          L"%LOCALAPPDATA%\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Code Cache",
          L"%LOCALAPPDATA%\\BraveSoftware\\Brave-Browser\\User Data\\Default\\GPUCache" }, true
    };

    APP_deletePaths[L"360 安全浏览器"] = {
        { L"%APPDATA%\\360se6\\User Data\\Default\\Cache",
          L"%APPDATA%\\360se6\\User Data\\Default\\Code Cache" }, true
    };

    APP_deletePaths[L"QQ 浏览器"] = {
        { L"%LOCALAPPDATA%\\Tencent\\QQBrowser\\User Data\\Default\\Cache",
          L"%LOCALAPPDATA%\\Tencent\\QQBrowser\\User Data\\Default\\Code Cache" }, true
    };

    APP_deletePaths[L"搜狗高速浏览器"] = {
        { L"%LOCALAPPDATA%\\SogouExplorer\\User Data\\Default\\Cache" }, true
    };

    //============================================================
    // 聊天 / 通讯
    //============================================================

    APP_deletePaths[L"Discord"] = {
        { L"%APPDATA%\\discord\\Cache",
          L"%APPDATA%\\discord\\Code Cache",
          L"%APPDATA%\\discord\\GPUCache" }, true
    };

    APP_deletePaths[L"Telegram Desktop"] = {
        { L"%APPDATA%\\Telegram Desktop\\tdata\\user_data\\cache" }, true
    };

    APP_deletePaths[L"钉钉"] = {
        { L"%APPDATA%\\DingTalk\\cache" }, true
    };

    APP_deletePaths[L"飞书"] = {
        { L"%APPDATA%\\LarkShell\\Cache",
          L"%APPDATA%\\LarkShell\\GPUCache" }, true
    };

    APP_deletePaths[L"微信"] = {
        { L"%USERPROFILE%\\Documents\\WeChat Files\\*\\FileStorage\\Cache",
          L"%USERPROFILE%\\Documents\\WeChat Files\\*\\FileStorage\\Temp" }, true
    };

    APP_deletePaths[L"QQ"] = {
        { L"%APPDATA%\\Tencent\\QQ\\Temp" }, true
    };

    APP_deletePaths[L"Microsoft Teams"] = {
        { L"%APPDATA%\\Microsoft\\Teams\\Cache",
          L"%APPDATA%\\Microsoft\\Teams\\Code Cache",
          L"%APPDATA%\\Microsoft\\Teams\\GPUCache",
          L"%APPDATA%\\Microsoft\\Teams\\blob_storage" }, true
    };

    APP_deletePaths[L"Slack"] = {
        { L"%APPDATA%\\Slack\\Cache",
          L"%APPDATA%\\Slack\\Code Cache",
          L"%APPDATA%\\Slack\\GPUCache" }, true
    };

    APP_deletePaths[L"Zoom"] = {
        { L"%APPDATA%\\Zoom\\data",
          L"%APPDATA%\\Zoom\\logs" }, true
    };

    APP_deletePaths[L"WhatsApp"] = {
        { L"%APPDATA%\\WhatsApp\\Cache" }, true
    };

    APP_deletePaths[L"豆包"] = {
        { L"%APPDATA%\\Doubao\\Cache",
          L"%APPDATA%\\Doubao\\Code Cache",
          L"%APPDATA%\\Doubao\\GPUCache" }, true
    };

    //============================================================
    // 影音
    //============================================================

    APP_deletePaths[L"网易云音乐"] = {
        { L"%LOCALAPPDATA%\\Netease\\CloudMusic\\Cache" }, true
    };

    APP_deletePaths[L"QQ 音乐"] = {
        { L"%LOCALAPPDATA%\\Tencent\\QQMusic\\Cache" }, true
    };

    APP_deletePaths[L"酷狗音乐"] = {
        { L"%APPDATA%\\Kugou\\Cache" }, true
    };

    APP_deletePaths[L"PotPlayer"] = {
        { L"%TEMP%\\PotPlayerTemp" }, true
    };

    APP_deletePaths[L"VLC"] = {
        { L"%APPDATA%\\vlc\\cache" }, true
    };

    APP_deletePaths[L"Spotify"] = {
        { L"%LOCALAPPDATA%\\Spotify\\Browser\\Cache",
          L"%LOCALAPPDATA%\\Spotify\\Storage" }, true
    };

    APP_deletePaths[L"OBS Studio"] = {
        { L"%APPDATA%\\obs-studio\\plugin_config\\obs-browser\\obs_profile_cookies\\*\\Code Cache" }, true
    };

    APP_deletePaths[L"Audacity"] = {
        { L"%LOCALAPPDATA%\\Audacity\\SessionData" }, true
    };

    APP_deletePaths[L"哔哩哔哩直播姬"] = {
        { L"%APPDATA%\\BilibiliLive\\Cache",
          L"%APPDATA%\\BilibiliLive\\GPUCache" }, true
    };

    APP_deletePaths[L"TikTok LIVE Studio"] = {
        { L"%APPDATA%\\TikTok LIVE Studio\\Cache",
          L"%APPDATA%\\TikTok LIVE Studio\\Code Cache",
          L"%APPDATA%\\TikTok LIVE Studio\\GPUCache" }, true
    };

    APP_deletePaths[L"剪映"] = {
        { L"%LOCALAPPDATA%\\JianyingPro\\User Data\\Cache" }, true
    };

    APP_deletePaths[L"必剪"] = {
        { L"%APPDATA%\\BcutBilibili\\Cache",
          L"%APPDATA%\\BcutBilibili\\GPUCache" }, true
    };

    //============================================================
    // 开发工具
    //============================================================

    APP_deletePaths[L"Visual Studio Code"] = {
        { L"%APPDATA%\\Code\\Cache",
          L"%APPDATA%\\Code\\CachedData",
          L"%APPDATA%\\Code\\GPUCache" }, true
    };

    APP_deletePaths[L"PyCharm Community Edition"] = {
        { L"%LOCALAPPDATA%\\JetBrains\\PyCharmCE*\\caches",
          L"%LOCALAPPDATA%\\JetBrains\\PyCharmCE*\\log" }, true
    };

    APP_deletePaths[L"IntelliJ IDEA"] = {
        { L"%LOCALAPPDATA%\\JetBrains\\IntelliJIdea*\\caches",
          L"%LOCALAPPDATA%\\JetBrains\\IntelliJIdea*\\log" }, true
    };

    APP_deletePaths[L"Node.js"] = {
        { L"%LOCALAPPDATA%\\npm-cache" }, true
    };

    APP_deletePaths[L"Python"] = {
        { L"%LOCALAPPDATA%\\pip\\Cache" }, true
    };

    APP_deletePaths[L"Cursor"] = {
        { L"%APPDATA%\\Cursor\\Cache",
          L"%APPDATA%\\Cursor\\CachedData",
          L"%APPDATA%\\Cursor\\GPUCache" }, true
    };

    APP_deletePaths[L"Notion"] = {
        { L"%APPDATA%\\Notion\\Cache",
          L"%APPDATA%\\Notion\\Code Cache",
          L"%APPDATA%\\Notion\\GPUCache" }, true
    };

    APP_deletePaths[L"Android Studio"] = {
        { L"%LOCALAPPDATA%\\Google\\AndroidStudio*\\caches",
          L"%LOCALAPPDATA%\\Google\\AndroidStudio*\\log" }, true
    };

    APP_deletePaths[L"GitHub Desktop"] = {
        { L"%APPDATA%\\GitHub Desktop\\Cache",
          L"%APPDATA%\\GitHub Desktop\\Code Cache",
          L"%APPDATA%\\GitHub Desktop\\GPUCache" }, true
    };

    APP_deletePaths[L"Unity"] = {
        { L"%LOCALAPPDATA%\\Unity\\Cache",
          L"%LOCALAPPDATA%\\Unity\\Editor\\Cache" }, true
    };

    APP_deletePaths[L"Blender"] = {
        { L"%LOCALAPPDATA%\\Blender Foundation\\Blender\\Cache" }, true
    };

    APP_deletePaths[L"Dev-C++"] = {
        { L"%APPDATA%\\Dev-Cpp\\Templates" }, true
    };

    APP_deletePaths[L"Bootstrap Studio"] = {
        { L"%APPDATA%\\Bootstrap Studio\\Cache" }, true
    };

    APP_deletePaths[L"World Creator"] = {
        { L"%APPDATA%\\World Creator\\Cache" }, true
    };

    //============================================================
    // 下载 / 网盘
    //============================================================

    APP_deletePaths[L"迅雷"] = {
        { L"%APPDATA%\\Thunder Network\\Thunder\\Cache" }, true
    };

    APP_deletePaths[L"Internet Download Manager"] = {
        { L"%APPDATA%\\IDM\\DwnlData" }, true
    };

    APP_deletePaths[L"百度网盘"] = {
        { L"%APPDATA%\\baidu\\BaiduNetdisk\\Cache" }, true
    };

    APP_deletePaths[L"夸克"] = {
        { L"%APPDATA%\\Quark\\Cache" }, true
    };

    //============================================================
    // 游戏平台 / 启动器
    //============================================================

    APP_deletePaths[L"Steam"] = {
        { L"%LOCALAPPDATA%\\Steam\\htmlcache",
          L"%LOCALAPPDATA%\\Steam\\logs",
          L"%LOCALAPPDATA%\\Steam\\appcache" }, true
    };

    APP_deletePaths[L"Epic Games Launcher"] = {
        { L"%LOCALAPPDATA%\\EpicGamesLauncher\\Saved\\webcache",
          L"%LOCALAPPDATA%\\EpicGamesLauncher\\Saved\\Logs" }, true
    };

    APP_deletePaths[L"Riot Client"] = {
        { L"%LOCALAPPDATA%\\Riot Games\\Riot Client\\Cache",
          L"%LOCALAPPDATA%\\Riot Games\\Riot Client\\Logs" }, true
    };

    APP_deletePaths[L"Rockstar Games Launcher"] = {
        { L"%LOCALAPPDATA%\\Rockstar Games\\Launcher\\Cache",
          L"%LOCALAPPDATA%\\Rockstar Games\\Launcher\\logs" }, true
    };

    APP_deletePaths[L"Ubisoft Connect"] = {
        { L"%LOCALAPPDATA%\\Ubisoft Game Launcher\\cache",
          L"%LOCALAPPDATA%\\Ubisoft Game Launcher\\logs" }, true
    };

    APP_deletePaths[L"Battle.net"] = {
        { L"%APPDATA%\\Battle.net\\Cache",
          L"%LOCALAPPDATA%\\Blizzard Entertainment\\Battle.net\\Logs" }, true
    };

    APP_deletePaths[L"EA App"] = {
        { L"%LOCALAPPDATA%\\Electronic Arts\\EA Desktop\\Logs",
          L"%LOCALAPPDATA%\\Electronic Arts\\EA Desktop\\Cache" }, true
    };

    APP_deletePaths[L"GOG Galaxy"] = {
        { L"%PROGRAMDATA%\\GOG.com\\Galaxy\\logs" }, true
    };

    APP_deletePaths[L"Xbox"] = {
        { L"%LOCALAPPDATA%\\Packages\\Microsoft.GamingApp_8wekyb3d8bbwe\\LocalCache" }, true
    };

    APP_deletePaths[L"我的世界启动器"] = {
        { L"%APPDATA%\\.minecraft\\logs",
          L"%APPDATA%\\.minecraft\\crash-reports",
          L"%APPDATA%\\.minecraft\\webcache" }, true
    };

    APP_deletePaths[L"Minecraft Launcher"] = {
        { L"%APPDATA%\\.minecraft\\logs",
          L"%APPDATA%\\.minecraft\\webcache" }, true
    };

    APP_deletePaths[L"PCL2 启动器"] = {
        { L"%APPDATA%\\PCL\\Cache",
          L"%APPDATA%\\PCL\\Logs" }, true
    };

    APP_deletePaths[L"HMCL 启动器"] = {
        { L"%APPDATA%\\.hmcl\\cache",
          L"%APPDATA%\\.hmcl\\logs" }, true
    };

    APP_deletePaths[L"Paradox Launcher"] = {
        { L"%LOCALAPPDATA%\\Paradox Interactive\\launcher-v2\\Cache",
          L"%LOCALAPPDATA%\\Paradox Interactive\\launcher-v2\\logs" }, true
    };

    APP_deletePaths[L"光·遇"] = {
        { L"%APPDATA%\\ThatGameCompany\\com.tgc.sky.win\\cache" }, true
    };

    APP_deletePaths[L"超自然行动组"] = {
        { L"%LOCALAPPDATA%\\Preternatural\\Saved\\Logs",
          L"%LOCALAPPDATA%\\Preternatural\\Saved\\Crashes" }, true
    };

    APP_deletePaths[L"网易UU加速器"] = {
        { L"%APPDATA%\\Netease\\UU\\Cache",
          L"%APPDATA%\\UUGame\\Cache" }, true
    };

    //============================================================
    // Adobe 全家桶
    //============================================================

    APP_deletePaths[L"Adobe Photoshop 2024"] = {
        { L"%APPDATA%\\Adobe\\Adobe Photoshop 2024\\Adobe Photoshop 2024 Settings\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Photoshop 2024\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Photoshop 2023"] = {
        { L"%APPDATA%\\Adobe\\Adobe Photoshop 2023\\Adobe Photoshop 2023 Settings\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Photoshop 2023\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Photoshop 2022"] = {
        { L"%APPDATA%\\Adobe\\Adobe Photoshop 2022\\Adobe Photoshop 2022 Settings\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Photoshop 2022\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Photoshop 2026"] = {
        { L"%APPDATA%\\Adobe\\Adobe Photoshop 2026\\Adobe Photoshop 2026 Settings\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Photoshop 2026\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Premiere Pro 2024"] = {
        { L"%APPDATA%\\Adobe\\Premiere Pro\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Premiere Pro\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Premiere Pro 2023"] = {
        { L"%APPDATA%\\Adobe\\Premiere Pro\\23.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Premiere Pro\\23.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe After Effects 2024"] = {
        { L"%APPDATA%\\Adobe\\After Effects\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\After Effects\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\After Effects\\24.0\\Disk Cache" }, true
    };

    APP_deletePaths[L"Adobe After Effects 2023"] = {
        { L"%APPDATA%\\Adobe\\After Effects\\23.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\After Effects\\23.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\After Effects\\23.0\\Disk Cache" }, true
    };

    APP_deletePaths[L"Adobe Illustrator 2024"] = {
        { L"%APPDATA%\\Adobe\\Adobe Illustrator 2024\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Illustrator 2024\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Illustrator 2023"] = {
        { L"%APPDATA%\\Adobe\\Adobe Illustrator 2023\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Illustrator 2023\\Cache" }, true
    };

    APP_deletePaths[L"Adobe InDesign 2024"] = {
        { L"%APPDATA%\\Adobe\\InDesign\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\InDesign\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Lightroom Classic"] = {
        { L"%APPDATA%\\Adobe\\Lightroom\\Caches",
          L"%LOCALAPPDATA%\\Adobe\\Lightroom\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Lightroom"] = {
        { L"%APPDATA%\\Adobe\\Lightroom CC\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Lightroom CC\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Audition 2024"] = {
        { L"%APPDATA%\\Adobe\\Audition\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Audition\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Audition 2023"] = {
        { L"%APPDATA%\\Adobe\\Audition\\23.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Audition\\23.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Media Encoder 2024"] = {
        { L"%APPDATA%\\Adobe\\Adobe Media Encoder\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Adobe Media Encoder\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Premiere Rush"] = {
        { L"%APPDATA%\\Adobe\\Premiere Rush\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Premiere Rush\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Animate 2024"] = {
        { L"%APPDATA%\\Adobe\\Animate\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Animate\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Dreamweaver 2024"] = {
        { L"%APPDATA%\\Adobe\\Dreamweaver\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Dreamweaver\\24.0\\Cache" }, true
    };

    APP_deletePaths[L"Adobe Bridge 2024"] = {
        { L"%APPDATA%\\Adobe\\Bridge\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Bridge\\24.0\\Cache",
          L"%LOCALAPPDATA%\\Adobe\\Bridge\\24.0\\Thumbnails" }, true
    };

    APP_deletePaths[L"Adobe Media Cache"] = {
        { L"%APPDATA%\\Adobe\\Common\\Media Cache",
          L"%APPDATA%\\Adobe\\Common\\Media Cache Files",
          L"%APPDATA%\\Adobe\\Common\\PTX",
          L"%APPDATA%\\Adobe\\Common\\AME" }, true
    };

    //============================================================
    // 办公
    //============================================================

    APP_deletePaths[L"WPS Office"] = {
        { L"%APPDATA%\\Kingsoft\\office6\\cache" }, true
    };

    APP_deletePaths[L"Microsoft Office"] = {
        { L"%LOCALAPPDATA%\\Microsoft\\Office\\16.0\\OfficeFileCache" }, true
    };

    APP_deletePaths[L"OneNote"] = {
        { L"%LOCALAPPDATA%\\Microsoft\\OneNote\\16.0\\Cache" }, true
    };

    APP_deletePaths[L"Outlook"] = {
        { L"%LOCALAPPDATA%\\Microsoft\\Outlook\\Cache" }, true
    };

    APP_deletePaths[L"Process Hacker"] = {
        { L"%APPDATA%\\Process Hacker\\Logs" }, true
    };

    //============================================================
    // 系统工具 / 通用
    //============================================================

    APP_deletePaths[L"Everything"] = {
        { L"%APPDATA%\\Everything\\Logs" }, true
    };

    APP_deletePaths[L"CCleaner"] = {
        { L"%APPDATA%\\CCleaner\\Logs" }, true
    };

    APP_deletePaths[L"Windows 临时文件"] = {
        { L"%LOCALAPPDATA%\\Temp" }, true
    };

    APP_deletePaths[L"CPU-Z"] = {
        { L"%TEMP%\\cpuz*" }, true
    };

    APP_deletePaths[L"7-Zip"] = {
        { L"%TEMP%\\7z*" }, true
    };

    APP_deletePaths[L"Cheat Engine"] = {
        { L"%LOCALAPPDATA%\\Temp\\Cheat Engine" }, true
    };

    APP_deletePaths[L"AMD DxcCache"] = {
        { L"%LOCALAPPDATA%\\AMD\\DxcCache" }, true
    };

    APP_deletePaths[L"Clash Verge"] = {
        { L"%TEMP%\\clash-verge*" }, true
    };

    APP_deletePaths[L"驱动总裁"] = {
        { L"C:\\Program Files\\DriverMaster\\Download" }, true
    };

    APP_deletePaths[L"Bezier Games"] = {
        { L"%APPDATA%\\Bezier Games\\*\\Cache" }, true
    };

    APP_deletePaths[L"图吧工具箱"] = {
        { L"%TEMP%\\tb*" }, true
    };

    APP_deletePaths[L"WindSoul 软件管家"] = {
        { L"%LOCALAPPDATA%\\winManager\\Cache" }, true
    };

    APP_deletePaths[L"Radmin VPN"] = {
        { L"%APPDATA%\\Radmin VPN\\Logs" }, true
    };

    APP_deletePaths[L"WinSCP"] = {
        { L"%APPDATA%\\WinSCP\\Logs" }, true
    };

    APP_deletePaths[L"PixPin"] = {
        { L"%LOCALAPPDATA%\\PixPin\\Data\\Cache" }, true
    };

    APP_deletePaths[L"BongoCat"] = {
        { L"%LOCALAPPDATA%\\Packages\\vladelaina.bongocat_hnew8t3b8e0t6\\LocalCache\\Local\\BongoCat\\Cache" }, true
    };
}
data::~data() {
}


data Data;

qint64 cleanSystemCacheFiles()
{
    qint64 freed = 0;

#ifdef Q_OS_WIN

    
    auto forceDelete = [](const QString& path) -> bool {
        std::wstring wpath = path.toStdWString();

        
        if (DeleteFileW(wpath.c_str()))
            return true;

     
        HANDLE hToken = nullptr;
        if (OpenProcessToken(GetCurrentProcess(),
            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
            const wchar_t* privs[] = {
                L"SeTakeOwnershipPrivilege",
                L"SeDebugPrivilege",
                L"SeBackupPrivilege",
                L"SeRestorePrivilege"
            };
            for (const wchar_t* priv : privs) {
                LUID luid;
                if (LookupPrivilegeValueW(nullptr, priv, &luid)) {
                    TOKEN_PRIVILEGES tp;
                    tp.PrivilegeCount = 1;
                    tp.Privileges[0].Luid = luid;
                    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
                    AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), nullptr, nullptr);
                }
            }
            CloseHandle(hToken);
        }

        
        PSID pSid = nullptr;
        SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
        if (AllocateAndInitializeSid(&ntAuthority, 2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0, &pSid)) {
            SetNamedSecurityInfoW(const_cast<LPWSTR>(wpath.c_str()),
                SE_FILE_OBJECT,
                OWNER_SECURITY_INFORMATION,
                pSid, nullptr, nullptr, nullptr);
            FreeSid(pSid);
        }

       
        SetFileAttributesW(wpath.c_str(), FILE_ATTRIBUTE_NORMAL);

        if (DeleteFileW(wpath.c_str()))
            return true;


        return MoveFileExW(wpath.c_str(), nullptr,
            MOVEFILE_DELAY_UNTIL_REBOOT) != 0;
        };

    auto cleanDir = [&](const QString& dirPath, qint64 minSize) {
        QDir dir(dirPath);
        if (!dir.exists()) return;

        QDirIterator it(dirPath, QDir::Files | QDir::NoDotAndDotDot,
            QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            QFileInfo fi = it.fileInfo();
            if (fi.size() < minSize) continue;   

            qint64 size = fi.size();
            if (forceDelete(fi.absoluteFilePath()))
                freed += size;
        }


        QDirIterator dirIt(dirPath, QDir::Dirs | QDir::NoDotAndDotDot,
            QDirIterator::Subdirectories);
        QStringList dirs;
        while (dirIt.hasNext()) {
            dirIt.next();
            dirs.prepend(dirIt.filePath());
        }
        for (const QString& d : dirs)
            QDir(d).rmdir(d);
        };

    const qint64 MB = 1024LL * 1024;

    // ---------- 1. 浏览器缓存（阈值 10MB） ----------
    QString localCache = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);

    

    // ---------- 2. Windows 日志（CBS / DISM 阈值 1MB，其他 5MB） ----------
    cleanDir("C:/Windows/Logs/CBS", 1 * MB);
    cleanDir("C:/Windows/Logs/DISM", 1 * MB);
    cleanDir("C:/Windows/Logs", 5 * MB);

    // ---------- 3. Windows 更新下载缓存（阈值 10MB） ----------
    cleanDir("C:/Windows/SoftwareDistribution/Download", 10 * MB);

    // ---------- 4. 传递优化缓存（阈值 10MB） ----------
    cleanDir("C:/Windows/ServiceProfiles/NetworkService/AppData/Local/"
        "Microsoft/Windows/DeliveryOptimization", 10 * MB);

    // ---------- 5. 内核转储 / 蓝屏文件（阈值 1MB） ----------
    cleanDir("C:/Windows/Minidump", 1 * MB);
    cleanDir("C:/Windows/LiveKernelReports", 1 * MB);

   
    QFile memDump("C:/Windows/MEMORY.DMP");
    if (memDump.exists() && memDump.size() >= 10 * MB) {
        qint64 s = memDump.size();
        if (forceDelete("C:/Windows/MEMORY.DMP"))
            freed += s;
    }

    // ---------- 6. WER 错误报告（阈值 1MB） ----------
    
    cleanDir("C:/ProgramData/Microsoft/Windows/WER/ReportQueue", 1 * MB);
    cleanDir("C:/ProgramData/Microsoft/Windows/WER/ReportArchive", 1 * MB);

    
    QString userWer = localCache + "/Microsoft/Windows/WER";
    cleanDir(userWer + "/ReportQueue", 1 * MB);
    cleanDir(userWer + "/ReportArchive", 1 * MB);

    // ---------- 7. 程序崩溃转储（阈值 10MB） ----------
    cleanDir(localCache + "/CrashDumps", 10 * MB);

    // ---------- 8. 用户临时目录大文件（阈值 10MB） ----------
    cleanDir(QDir::tempPath(), 10 * MB);

    //-----------9.Cleanmgr --------------------
    
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.fMask = SEE_MASK_NOCLOSEPROCESS;
        sei.lpVerb = L"open";  
        sei.lpFile = L"C:\\Windows\\System32\\cleanmgr.exe";
        sei.lpParameters = L"/sagerun:1";
        sei.nShow = SW_SHOWNORMAL;
        if (!ShellExecuteExW(&sei)) {
            DWORD err = GetLastError();
           
        }


#endif 

    qDebug() << "释放空间:" << freed << "字节";
    return freed;
}



namespace fs = std::filesystem;



static double GetFolderSizeMB(const QString& folderPath) {
    double total = 0;
    QDir dir(folderPath);
    QDirIterator it(folderPath, QDir::Files | QDir::NoDotAndDotDot,
        QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        total += it.fileInfo().size();
    }
    return total / (1024.0 * 1024.0);
}

static bool IsOnDriveC(const QString& path) {
    return !path.isEmpty() && path[0].toUpper() == QChar('C');
}

QVector<FolderInfo> CheckMigratableFolders(bool calcSize ,
    bool onlyOnC) {
    struct Item { QString name; QStandardPaths::StandardLocation loc; };

    static const QVector<Item> kFolders = {
        { QStringLiteral("下载 (Downloads)"), QStandardPaths::DownloadLocation },
        { QStringLiteral("桌面 (Desktop)"),   QStandardPaths::DesktopLocation },
        { QStringLiteral("文档 (Documents)"), QStandardPaths::DocumentsLocation },
        { QStringLiteral("图片 (Pictures)"),  QStandardPaths::PicturesLocation },
        { QStringLiteral("音乐 (Music)"),     QStandardPaths::MusicLocation },
        { QStringLiteral("视频 (Videos)"),    QStandardPaths::MoviesLocation },
    };

    QVector<FolderInfo> results;

    for (const auto& item : kFolders) {
        QString path = QStandardPaths::writableLocation(item.loc);
        if (path.isEmpty()) continue;


        path = QDir::toNativeSeparators(path);

        FolderInfo info;
        info.name = item.name;
        info.path = path;
        info.exists = QDir(path).exists();
        info.onC = IsOnDriveC(path);
        info.sizeMB = 0.0;

        if (calcSize && info.exists && info.onC) {
            info.sizeMB = GetFolderSizeMB(path);
        }

        if (onlyOnC && !info.onC) continue;
        results.push_back(info);
    }
    return results;
}

void ShowOnDriveC() {
    auto folders = CheckMigratableFolders(true, true);


    QString msg;
    double totalMB = 0;

    if (folders.empty()) {
        msg = QStringLiteral("没有发现可迁移的文件夹。");
    }
    else {
        msg = QStringLiteral("找到 %1 个可迁移的文件夹：\n\n")
            .arg(folders.size());

        int index = 1;
        for (const auto& f : folders) {
            msg += QStringLiteral("[%1] %2\n")
                .arg(index++)
                .arg(f.name);
            msg += QStringLiteral("    路径: %1\n").arg(f.path);
            msg += QStringLiteral("    大小: %1 MB\n\n")
                .arg(f.sizeMB, 0, 'f', 1);
            totalMB += f.sizeMB;
        }

        msg += QStringLiteral("----------------------------\n");
        msg += QStringLiteral("合计: %1 MB (%2 GB)\n\n")
            .arg(totalMB, 0, 'f', 1)
            .arg(totalMB / 1024.0, 0, 'f', 2);
        msg += QStringLiteral("迁移方法：\n"
            "右键文件夹 -> 属性 -> 位置 -> 移动");
    }


    QMessageBox::information(nullptr,
        QStringLiteral("C盘可迁移文件夹"),
        msg);

}