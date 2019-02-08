#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "igameview.h"

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

private:
    Ui::MainWindow *ui;
    SimpleGameView view;
    int size = 20;

    class View : public SimpleGameView {

    };

protected:
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);
};

#endif // MAINWINDOW_H
