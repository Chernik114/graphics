#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileDialog>
#include <QMessageBox>

class FileWatcher
{
public:
    FileWatcher();

    void newFile();
    void openFile();
    void saveFile();
    void saveNewFile();
    void closeFile();
    void changeFile();

    virtual bool save(QDataStream& f) = 0;
    virtual bool load(QDataStream& f) = 0;
    virtual bool create() = 0;

    QString getFileName();
    bool isSaved();
    void setWidget(QWidget& w);

    virtual ~FileWatcher(){}

private:
    class Error {};

    void isSaveFile();
    void goSave();
    void goLoad();
    void goCreate();

    void diaSave();
    void diaOpen();

    QString fileName;
    QWidget* w;
    bool saved;
};

#endif // FILEWATCHER_H
