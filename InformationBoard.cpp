#include "stdafx.h"
#include "InformationBoard.h"
#include <QStyle>

InformationBoard::InformationBoard(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.cleanBtn, &QPushButton::clicked, this, [this]() {
        emit cleanRequested(ui.nameLabel->text(), ui.pathLabel->text());
        });
}

void InformationBoard::setAppName(const QString& name)
{
    ui.nameLabel->setText(name);
}

void InformationBoard::setVersion(const QString& version)
{
    ui.versionLabel->setText(version.isEmpty() ? "-" : version);
}

void InformationBoard::setPath(const QString& path)
{
    ui.pathLabel->setText(path.isEmpty() ? "(无路径)" : path);
    ui.pathLabel->setToolTip(path);
}

void InformationBoard::setRegistered(bool registered)
{
    ui.registeredLabel->setText(registered ? "已注册" : "未注册");

    if (registered) {
        ui.registeredLabel->setStyleSheet(
            "color: #2E8B57; font-weight: bold; background: transparent; border: none;");
    }
    else {
        ui.registeredLabel->setStyleSheet(
            "color: #C0392B; font-weight: bold; background: transparent; border: none;");
    }
}