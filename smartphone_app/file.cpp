/*

  Clase para escrita e leitura de arquivos

*/

#include "file.h"


File::File()
{

}

File::~File()
{

}

QString File::Read(QString Filename,QString text)
{
    QFile mFile(Filename);

    if (mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&mFile);
        text = in.readAll();
        mFile.close();
        return text;
    }
}

void File::Write(QString Filename,QString text)
{
    QFile mFile(Filename);
    if (mFile.open(QFile::WriteOnly | QFile::Text))
    {
    QTextStream out(&mFile);
    out << text;
    mFile.flush();
    mFile.close();
    }
}
