#ifndef WORD_H
#define WORD_H

#include <QString>



class Word
{
private:
    QString name;
    QString category;
public:
    Word(QString n, QString c);
    QString getName();
    QString getCategory();
};

#endif // WORD_H
