#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(GameView& view, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    view(view)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->tableSizeX->setMinimum(1);
    ui->tableSizeX->setMaximum(100);
    ui->tableSizeX->setPrec(0);
    ui->tableSizeY->setMinimum(1);
    ui->tableSizeY->setMaximum(100);
    ui->tableSizeY->setPrec(0);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent *)
{
    ui->tableSizeX->setPosition(view.getCellsX());
    ui->tableSizeY->setPosition(view.getCellsY());
}


void SettingsDialog::on_buttonOK_clicked()
{
    view.setFieldSize(round(ui->tableSizeX->getValue()), round(ui->tableSizeY->getValue()));
    close();
}
