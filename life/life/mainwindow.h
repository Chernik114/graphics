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

private:
    Ui::MainWindow *ui;
    SimpleGameView view;

    class View : public SimpleGameView {

    };

protected:
    void resizeEvent(QResizeEvent*);
    void showEvent(QShowEvent*);
};

#endif // MAINWINDOW_H
