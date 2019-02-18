#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDebug>
#include <QDesktopServices>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private slots:
    void on_textBrowser_anchorClicked(const QUrl &arg1);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
