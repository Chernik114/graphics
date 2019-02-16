#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileDialog>
#include <QMessageBox>

class FileWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileWatcher(QObject* parent = nullptr);

    void newFile();
    void openFile();
    void saveFile();
    void saveNewFile();
    void closeFile();
    void changeFile();

    QString getFileName();
    bool isSaved();
    void setWidget(QWidget& w);

signals:
    bool save(QFile&);
    bool load(QFile&);
    bool create();

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
