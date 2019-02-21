#include "filewatcher.h"

FileWatcher::FileWatcher(QObject *parent):
    QObject (parent),
    fileName(""),
    w(nullptr),
    saved(true)
{}

void FileWatcher::newFile()
{
    try {
        isSaveFile();
        goCreate();
    } catch(Error&){

    }
}

void FileWatcher::openFile()
{
    try {
        isSaveFile();
        diaOpen();
        goLoad();
    } catch (Error&) {

    }
}

void FileWatcher::saveFile()
{
    try {
        goSave();
    } catch(Error&){

    }
}

void FileWatcher::saveNewFile()
{
    try {
        diaSave();
        goSave();
    } catch (Error&){

    }
}

bool FileWatcher::closeFile()
{
    try {
        isSaveFile();
        return true;
    } catch(Error&){
        return false;
    }
}

void FileWatcher::changeFile()
{
    saved = false;
    change();
}

QString FileWatcher::getFileName()
{
    return fileName;
}

bool FileWatcher::isSaved()
{
    return saved;
}

void FileWatcher::setWidget(QWidget &w)
{
    this->w = &w;
}

void FileWatcher::isSaveFile()
{
    if(saved){
        return;
    }
    auto but = QMessageBox::warning(w, "Save file?", fileName == "" ? "<unknown>" : fileName, QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::No);
    if(but == QMessageBox::Cancel){
        throw Error();
    }
    if(but == QMessageBox::Yes){
        goSave();
    }
}

void FileWatcher::goSave()
{
    if(fileName == ""){
        diaSave();
    }
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly)){
        QMessageBox::warning(w, "Cannot save file", f.errorString());
        throw Error();
    }
    if(!save(f)){
        QMessageBox::warning(w, "Cannot save file", "<internal>");
        throw Error();
    }
    saved = true;
}

void FileWatcher::goLoad()
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly)){
        QMessageBox::warning(w, "Cannot load file", f.errorString());
        throw Error();
    }
    if(!load(f)){
        QMessageBox::warning(w, "Cannot load file", "<internal>");
        throw Error();
    }
    saved = true;
}

void FileWatcher::goCreate()
{
    if(!create()){
        QMessageBox::warning(w, "Cannot create file", "<internal>");
        throw Error();
    }
    saved = true;
    fileName = "";
}

void FileWatcher::diaSave()
{
    QString name = QFileDialog::getSaveFileName(w, "Save file", fileName, "TXT (*.txt)");
    if(name == ""){
        throw Error();
    }
    fileName = name;
}

void FileWatcher::diaOpen()
{
    QString name = QFileDialog::getOpenFileName(w, "Load file", fileName, "TXT (*.txt)");
    if(name == ""){
        throw Error();
    }
    fileName = name;
}
