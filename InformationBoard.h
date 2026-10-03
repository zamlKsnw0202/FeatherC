#pragma once

#include <QWidget>
#include "ui_InformationBoard.h"

class InformationBoard : public QWidget
{
    Q_OBJECT

public:
    explicit InformationBoard(QWidget* parent = nullptr);

    void setAppName(const QString& name);
    void setVersion(const QString& version);
    void setPath(const QString& path);
    void setRegistered(bool registered);

signals:
    void cleanRequested(const QString& name, const QString& path);

private:
    Ui::InformationBoard ui;
};