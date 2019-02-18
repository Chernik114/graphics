#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileName(""),
    isSaved(true),
    settingsDialog(this)
{
    ui->setupUi(this);
    timer.setInterval(500);
    fileWatcher.setWidget(*this);

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(on_actionStep_triggered()));
    QObject::connect(&view, SIGNAL(repaint()), ui->drawWidget, SLOT(repaint()));

    QObject::connect(ui->actionFileNew, SIGNAL(triggered()), &fileWatcher, SLOT(newFile()));
    QObject::connect(ui->actionFileOpen, SIGNAL(triggered()), &fileWatcher, SLOT(openFile()));
    QObject::connect(ui->actionFileSave, SIGNAL(triggered()), &fileWatcher, SLOT(saveFile()));
    QObject::connect(ui->actionFileSaveAs, SIGNAL(triggered()), &fileWatcher, SLOT(saveNewFile()));
    QObject::connect(ui->drawWidget, SIGNAL(click()), &fileWatcher, SLOT(changeFile()));

    QObject::connect(&fileWatcher, SIGNAL(save(QFile&)), this, SLOT(on_fileSave(QFile&)));
    QObject::connect(&fileWatcher, SIGNAL(load(QFile&)), this, SLOT(on_fileOpen(QFile&)));
    QObject::connect(&fileWatcher, SIGNAL(create()), this, SLOT(on_fileNew()));
    QObject::connect(&fileWatcher, SIGNAL(change()), this, SLOT(on_Change()));
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
    ui->drawWidget->setIView(view.v());
    setTitle("<unknown>");
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->setAccepted(fileWatcher.closeFile());
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
    vv.setSizeCell(vv.getSizeCell() <= 95 ? vv.getSizeCell() + 5 : 100);
    fileWatcher.changeFile();
}

void MainWindow::on_actionCellSizeDown_triggered()
{
    TableView &vv = ui->drawWidget->getTableView();
    vv.setSizeCell(vv.getSizeCell() >= 11 ? vv.getSizeCell() - 5 : 6);
    fileWatcher.changeFile();
}

void MainWindow::on_actionShowHideImpact_triggered(bool checked)
{
    TableView &vv = ui->drawWidget->getTableView();
    vv.setIsShowText(checked);
}

void MainWindow::on_actionStep_triggered()
{
    view.v().stepForward();
    fileWatcher.changeFile();
}

void MainWindow::on_actionToroidal_triggered(bool checked)
{
    view.v().setGameState(checked ? GameView::TOROIDAL : GameView::NORMAL);
}

void MainWindow::on_actionRun_triggered(bool checked)
{
    ui->actionClear->setEnabled(!checked);
    ui->actionFillState->setEnabled(!checked);
    ui->actionStep->setEnabled(!checked);
    if(checked){
        timer.start();
        view.v().setFillState(MouseGameView::NONE);
    } else {
        timer.stop();
        on_actionFillState_triggered(ui->actionFillState->isChecked());
    }
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDriver drv(view.v(), ui->drawWidget->getTableView(), timer);
    settingsDialog.setDrv(drv);
    settingsDialog.exec();
    fileWatcher.changeFile();
}

void MainWindow::on_actionFillState_triggered(bool checked)
{
    view.v().setFillState(checked ? MouseGameView::XOR : MouseGameView::REPLACE);
}

void MainWindow::on_actionClear_triggered()
{
    view.v().clear();
    fileWatcher.changeFile();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

bool MainWindow::on_fileSave(QFile &f)
{
    QTextStream s(&f);
    FileDriver fd(ui->drawWidget->getTableView(), view.v());
    s << fd;
    setTitle(f.fileName());
    return true;
}

bool MainWindow::on_fileOpen(QFile &f)
{
    QTextStream s(&f);
    FileDriver fd(ui->drawWidget->getTableView(), view.v());
    s >> fd;
    setTitle(f.fileName());
    return true;
}

bool MainWindow::on_fileNew()
{
    view.v().clear();
    setTitle("<unknown>");
    SettingsDriver drv(view.v(), ui->drawWidget->getTableView(), timer);
    settingsDialog.setDrv(drv);
    settingsDialog.exec();
    return true;
}

void MainWindow::on_Change()
{
    if(*(windowTitle().end()-1) != '*'){
        setWindowTitle(windowTitle() + " *");
    }
}

void MainWindow::setTitle(QString fileName)
{
    setWindowTitle("Game Life > " + fileName);
}

