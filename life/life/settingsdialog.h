#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPainter>

#include "gameview.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(GameView &view, QWidget *parent = nullptr);
    ~SettingsDialog();

protected:
    void showEvent(QShowEvent*);

private slots:

    void on_buttonOK_clicked();

private:
    Ui::SettingsDialog *ui;
    GameView &view;
};

#endif // SETTINGSDIALOG_H
