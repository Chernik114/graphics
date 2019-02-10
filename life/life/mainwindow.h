#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_actionSize_up_triggered();

    void on_actionSize_down_triggered();

    void on_actionNext_triggered();

    void on_actionShow_triggered();

    void on_actionHide_triggered();

    void on_action_triggered();

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
