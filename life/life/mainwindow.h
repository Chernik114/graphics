#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QTime>
#include <QTimer>

#include "mousegameview.h"

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

private:
    Ui::MainWindow *ui;
    QTimer timer;

    class MyView : public MouseGameView {
    private:
        QWidget *w = nullptr;

    public:
        void setWidget(QWidget &w){
            this->w = &w;
        }
        void repaint(){
            if(w == nullptr){
                qDebug() << "NULL VIEW";
                return;
            }
            w->repaint();
        }
    };

    MyView view;

protected:
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);

};

#endif // MAINWINDOW_H
