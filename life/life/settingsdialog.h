#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QMessageBox>

#include "settingsdriver.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    void setDrv(SettingsDriver &drv);

protected:
    void showEvent(QShowEvent*);

private slots:
    void on_buttonOK_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::SettingsDialog *ui;
    SettingsDriver *drv;
};

#endif // SETTINGSDIALOG_H
