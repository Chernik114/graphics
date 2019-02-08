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
    IGameView* v = new SimpleGameView();
    ui->drawWidget->setIView(v);
    ui->scrollArea->setMinimumSize(ui->centralWidget->size());
    ui->scrollArea->setMaximumSize(ui->centralWidget->size());
    ui->drawWidget->setSize(QSize(500, 500));
}


