#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

#include "qgameview.h"
#include "filewatcher.h"
#include "settingsdialog.h"
#include "filedriver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionColorBorder_triggered();

    void on_actionColorText_triggered();

    void on_actionColorCellAlive_triggered();

    void on_actionColorCellNAlive_triggered();

    void on_actionColorCellDead_triggered();

    void on_actionColorCellNDead_triggered();

    void on_actionCellSizeUp_triggered();

    void on_actionCellSizeDown_triggered();

    void on_actionShowHideImpact_triggered(bool checked);

    void on_actionStep_triggered();

    void on_actionToroidal_triggered(bool checked);

    void on_actionRun_triggered(bool checked);

    void on_actionSettings_triggered();

    void on_actionFillState_triggered(bool checked);

    void on_actionClear_triggered();

    void on_actionClose_triggered();

    bool on_fileSave(QFile& f);
    bool on_fileOpen(QFile& f);
    bool on_fileNew();

    void on_Change();
private:
    Ui::MainWindow *ui;
    QTimer timer;
    QString fileName;
    bool isSaved;

    QGameView view;
    SettingsDialog settingsDialog;
    FileWatcher fileWatcher;

    void setTitle(QString fileName);

protected:
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);
    void closeEvent(QCloseEvent* e);

};

#endif // MAINWINDOW_H
