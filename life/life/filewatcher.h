#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileDialog>
#include <QMessageBox>

class FileWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileWatcher(QObject* parent = nullptr);

    QString getFileName();
    bool isSaved();
    void setWidget(QWidget& w);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveNewFile();
    bool closeFile();
    void changeFile();

signals:
    bool save(QFile&);
    bool load(QFile&);
    bool create();
    void change();

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
