#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "gameview.h"

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

private:
    Ui::MainWindow *ui;
    int size = 20;

    class MyView : public GameView {
    private:
        QWidget *w = nullptr;

    public:
        void setWidget(QWidget &w){
            this->w = &w;
        }
        void mouseClick(int x, int y, Mouse state){
            if(getCellState(x, y) == ALIVE || getCellState(x, y) == NEW_ALIVE){
                setCellState(x, y, DEAD);
            } else {
                setCellState(x, y, ALIVE);
            }
            repaint();
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
