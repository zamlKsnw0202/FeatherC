#include "stdafx.h"
#include "ConfirmDialog.h"
#include "ui_ConfirmDialog.h"

ConfirmDialog::ConfirmDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);

    connect(ui->okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::setAppName(const QString& name)
{
    ui->appNameLabel->setText(name);
}

void ConfirmDialog::setPaths(const QStringList& paths)
{
    ui->pathEdit->setPlainText(paths.join("\n"));
}

void ConfirmDialog::setDescription(const QString& desc)
{
    ui->descEdit->setPlainText(desc);
}