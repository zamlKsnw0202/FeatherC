#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FeatherC.h"

class FeatherC : public QMainWindow
{
    Q_OBJECT

public:
    FeatherC(QWidget *parent = nullptr);
    void FindAllAPP();
    void InitList();
	void WindowsClean();
    void onScanClicked();
    ~FeatherC();

private:
    struct AppItem {
        std::wstring name;
        std::wstring version;
        std::wstring path;
    };
    std::vector<AppItem> m_apps;
    Ui::FeatherCClass ui;
};

