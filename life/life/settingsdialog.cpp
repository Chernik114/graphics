#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    drv(nullptr)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->tableSizeX->setRange(1, 100);
    ui->tableSizeX->setPrec(0);
    ui->tableSizeY->setRange(1, 100);
    ui->tableSizeY->setPrec(0);
    ui->valAnimTime->setRange(0, 1000);
    ui->valAnimTime->setPrec(0);
    ui->valCellSize->setRange(6, 100);
    ui->valCellSize->setPrec(0);
    ui->valTimerInt->setRange(50, 5000);
    ui->valTimerInt->setPrec(0);
    ui->valTimerInt->setKoef(0.002);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setDrv(SettingsDriver &drv)
{
    this->drv = &drv;
}

void SettingsDialog::showEvent(QShowEvent *)
{
    ui->tableSizeX->setPosition(drv->gv.getCellsX());
    ui->tableSizeY->setPosition(drv->gv.getCellsY());
    ui->valAnimTime->setPosition(drv->tv.getMsAnimation());
    ui->valCellSize->setPosition(drv->tv.getSizeCell());
    ui->valTimerInt->setPosition(drv->tm.interval());
}


void SettingsDialog::on_buttonOK_clicked()
{
    drv->gv.setFieldSize(round(ui->tableSizeX->getValue()), round(ui->tableSizeY->getValue()));
    drv->tv.setMsAnimation(ui->valAnimTime->getValue());
    drv->tv.setSizeCell(ui->valCellSize->getValue());
    drv->tm.setInterval(ui->valTimerInt->getValue());
    close();
}

void SettingsDialog::on_buttonCancel_clicked()
{
    close();
}
