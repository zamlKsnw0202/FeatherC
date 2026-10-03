#include "stdafx.h"
#include "FeatherC.h"
#include "data.h"
#include <Windows.h>
#include <QtWidgets/QApplication>
#include <iostream>
#include <qdebug.h>

void PrintW(const std::wstring& s) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h == INVALID_HANDLE_VALUE || h == nullptr) return;
    DWORD written = 0;
    WriteConsoleW(h, s.c_str(), (DWORD)s.size(), &written, nullptr);
}

void OpenConsole() {
    if (GetConsoleWindow() != nullptr) return;
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
}

static bool isRunAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = nullptr;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(nullptr, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin;
}

static void runAsAdmin()
{
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileNameW(nullptr, szPath, MAX_PATH)) {
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = szPath;
        sei.hwnd = nullptr;
        sei.nShow = SW_NORMAL;
        ShellExecuteExW(&sei);
    }
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

#ifdef Q_OS_WIN
    if (!isRunAsAdmin()) {
        runAsAdmin();
        return 0;
    }
#endif

    FeatherC Fwindow;

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    std::wcout << L"hello console" << std::endl;

    Fwindow.FindAllAPP();
    Fwindow.show();
    Fwindow.InitList();

   

    return app.exec();
}