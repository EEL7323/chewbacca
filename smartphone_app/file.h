#ifndef FILE_H
#define FILE_H

#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>


class File
{

public:
    File();
    ~File();

    QString Read(QString a,QString b);
    void Write(QString a,QString b);
private:
    //File *file;
};

#endif // FILE_H
