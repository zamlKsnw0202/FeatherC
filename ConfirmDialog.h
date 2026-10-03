#pragma once

#include <QDialog>

namespace Ui { class ConfirmDialog; }

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget* parent = nullptr);
    ~ConfirmDialog() override;

    // 设置顶部程序名
    void setAppName(const QString& name);

    // 设置要删除的路径
    void setPaths(const QStringList& paths);

    // 设置文件作用说明
    void setDescription(const QString& desc);

private:
    Ui::ConfirmDialog* ui;
};