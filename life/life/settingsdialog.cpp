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
    ui->valFstImpact->setRange(0, 2);
    ui->valSndImpact->setRange(0, 2);
    ui->valLiveBegin->setRange(0, 10);
    ui->valLiveEnd->setRange(0, 10);
    ui->valBirthBegin->setRange(0, 10);
    ui->valBirthEnd->setRange(0, 10);
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
    ui->valFstImpact->setPosition(drv->gv.getParam(GameView::FST_IMPACT));
    ui->valSndImpact->setPosition(drv->gv.getParam(GameView::SND_IMPACT));
    ui->valLiveBegin->setPosition(drv->gv.getParam(GameView::LIVE_BEGIN));
    ui->valLiveEnd->setPosition(drv->gv.getParam(GameView::LIVE_END));
    ui->valBirthBegin->setPosition(drv->gv.getParam(GameView::BIRTH_BEGIN));
    ui->valBirthEnd->setPosition(drv->gv.getParam(GameView::BIRTH_END));
}


void SettingsDialog::on_buttonOK_clicked()
{
    double
            fstImpact  = ui->valFstImpact->getValue(),
            sndImpact  = ui->valSndImpact->getValue(),
            liveBegin  = ui->valLiveBegin->getValue(),
            liveEnd    = ui->valLiveEnd  ->getValue(),
            birthBegin = ui->valBirthBegin->getValue(),
            birthEnd   = ui->valBirthEnd->getValue();
    if(!(liveBegin <= birthBegin && birthBegin <= birthEnd && birthEnd <= liveEnd)){
        QMessageBox::warning(this, "Wrond params", "Must be liveBegin <= birthBegin <= birthEnd <= liveEnd");
        return;
    }
    drv->gv.setFieldSize(round(ui->tableSizeX->getValue()), round(ui->tableSizeY->getValue()));
    drv->tv.setMsAnimation(ui->valAnimTime->getValue());
    drv->tv.setSizeCell(ui->valCellSize->getValue());
    drv->tm.setInterval(ui->valTimerInt->getValue());
    drv->gv.setParam(GameView::FST_IMPACT, fstImpact);
    drv->gv.setParam(GameView::SND_IMPACT, sndImpact);
    drv->gv.setParam(GameView::LIVE_BEGIN, liveBegin);
    drv->gv.setParam(GameView::LIVE_END, liveEnd);
    drv->gv.setParam(GameView::BIRTH_BEGIN, birthBegin);
    drv->gv.setParam(GameView::BIRTH_END, birthEnd);
    close();
}

void SettingsDialog::on_buttonCancel_clicked()
{
    close();
}
