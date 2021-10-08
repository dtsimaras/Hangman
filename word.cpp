#include "word.h"

Word::Word(QString n, QString c)
{
    name = n;
    category = c;
}

QString Word::getName()
{
    return name;
}

QString Word::getCategory()
{
    return category;
}
