#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_actionSize_up_triggered()
{
    size += 5;
    ui->drawWidget->getTableView().setSizeCell(size);
}

void MainWindow::on_actionSize_down_triggered()
{
    size -= 5;
    ui->drawWidget->getTableView().setSizeCell(size);
}
