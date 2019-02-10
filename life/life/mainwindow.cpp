#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(*(new QTimer()))
{
    ui->setupUi(this);
    view.setWidget(*ui->drawWidget);
    timer.setInterval(500);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(on_actionStep_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete &timer;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->scrollArea->setMinimumSize(ui->centralWidget->size());
    ui->scrollArea->setMaximumSize(ui->centralWidget->size());
}

void MainWindow::showEvent(QShowEvent *)
{
    ui->drawWidget->setIView(view);
    ui->drawWidget->setSize(QSize(500, 500));
}

void MainWindow::on_actionColorBorder_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getBorderColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setBorderColor(t.rgb());
}

void MainWindow::on_actionColorText_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getTextColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setTextColor(t.rgb());
}

void MainWindow::on_actionColorCellAlive_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getAliveColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setAliveColor(t.rgb());
}

void MainWindow::on_actionColorCellNAlive_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getNAliveColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setNAliveColor(t.rgb());
}

void MainWindow::on_actionColorCellDead_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getDeadColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setDeadColor(t.rgb());
}

void MainWindow::on_actionColorCellNDead_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    QColor t = QColorDialog::getColor(vv.getNDeadColor(), this, "Choose");
    if(!t.isValid()){
        return;
    }
    vv.setNDeadColor(t.rgb());
}

void MainWindow::on_actionCellSizeUp_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    vv.setSizeCell(vv.getSizeCell() + 5);
}

void MainWindow::on_actionCellSizeDown_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    vv.setSizeCell(vv.getSizeCell() - 5);
}

void MainWindow::on_actionShowHideImpact_triggered(bool checked)
{
    TableView &vv = ui->drawWidget->getTableView();
    vv.setIsShowText(checked);
}

void MainWindow::on_actionStep_triggered()
{
    view.stepForward();
}

void MainWindow::on_actionToroidal_triggered(bool checked)
{
    view.setGameState(checked ? GameView::TOROIDAL : GameView::NORMAL);
}

void MainWindow::on_actionRun_triggered(bool checked)
{
    if(checked){
        timer.start();
    } else {
        timer.stop();
    }
}
