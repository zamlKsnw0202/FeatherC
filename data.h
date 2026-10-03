#pragma once
#include <map>
#include <vector>
#include <string>
#include <unordered_set>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>
#include <initguid.h>  
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")

#ifdef Q_OS_WIN
#include <windows.h>
#include <aclapi.h>
#include <shellapi.h>
#endif

struct FolderInfo {
    QString name;
    QString path;
    bool    exists;
    bool    onC;
    double  sizeMB;
};

struct DeletePath {
    std::vector<std::wstring> path;
    bool         safeToDelete = true;
};

class data
{
public:
    data();
    ~data();
    std::unordered_set<std::wstring> Reg_names;
    std::vector <std::wstring> Reg_exist_names;
    std::map<std::wstring, DeletePath> APP_deletePaths;
};

extern data Data;



qint64 cleanSystemCacheFiles();

QVector<FolderInfo> CheckMigratableFolders(bool calcSize = true,
    bool onlyOnC = true);

void ShowOnDriveC();