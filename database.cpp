#include "database.h"
#include <QDebug>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    if(db.isOpen()) db.close();
    db.setDatabaseName("Hangman.db");
    db.open();
    QSqlQuery q(db),q1(db);

    q.prepare(QString("create table if not exists Player(")+
              QString("name varchar(1024) primary key, score integer)"));

    q1.prepare(QString("create table if not exists Word(")+
               QString("name varchar(1024) primary key, category varchar(1024))"));
    if(q.exec() && q1.exec())
    {
        qDebug()<<"Database Created (or Exists)";
        insertWords(":/txt/csv/words.txt");
    }
    else
        qDebug()<<"Database Not Created: "<<q.lastError();
}

bool Database::insertPlayer(QString pName)
{
    QSqlQuery query1(db);
    query1.prepare(QString("INSERT INTO Player (name,score) VALUES (:name,:score)"));
    query1.bindValue(":name", pName);
    query1.bindValue(":score", 0);
    if (query1.exec()){
        qDebug()<<"Player Created";
        return true;
    }
    else
        qDebug()<<"Database error:  "<<query1.lastError();
    return false;
}

Player Database::getPlayer(QString n)
{
    QSqlQuery query(db);
    query.exec(QString("SELECT name, score FROM Player WHERE name='"+n+"'"));
    if(query.next()==true)
    {
        Player p(query.value(0).toString(), query.value(1).toInt());
        return p;
    }
    Player p("ptoihbjhuveisrisodprlfjerndiykghfjwepsaodfkln",1);
    return p;
}

QVector<Player> Database::getPlayers()
{
    QVector<Player> players;
    QSqlQuery query(db);
    query.exec("SELECT name, score FROM Player");
    if(query.next())
        do
        {
            Player p(query.value(0).toString(), query.value(1).toInt());
            players.append(p);
        } while (query.next());
    else
        qDebug()<<"Empty table Player";
    return players;
}

bool Database::insertWords(QString dir) //Input CSV file
{
    QFile file(dir);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream stream(&file);
    QVector<QString> lines;
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        lines.append(line);
    }

    QSqlQuery query(db);

    for(int i=0;i<lines.size();i++)
    {
        QStringList items = lines[i].split(",");
        query.prepare(QString("INSERT OR REPLACE INTO Word (name,category) VALUES (:name,:category)"));
        query.bindValue(":name", items[0].trimmed());
        query.bindValue(":category", items[1].trimmed());
        if(!query.exec())
        {
            qDebug()<<"Words not inserted. Error in line ["+QString::number(i)+"]";
            return false;
        }
    }
    return true;
}

QVector<Word> Database::getWords()
{
    QVector<Word> words;
    QSqlQuery query(db);
    query.exec("SELECT name, category FROM Word");
    if(query.next())
        do
        {
            Word p(query.value(0).toString(), query.value(1).toString());
            words.append(p);
        } while (query.next());
    else
        qDebug()<<"Empty table word";
    return words;
}

bool Database::updateScore(Player p)
{
    QSqlQuery query(db);
    query.prepare(QString("UPDATE Player SET score="+QString::number(p.getScore()+1)+" WHERE name='"+p.getName()+"'"));
    if (query.exec())
        return true;
    qDebug()<<"Score didn't Update";
    return false;
}

QVector<QString> Database::getCategories()
{
    QVector<QString> categories;
    QSqlQuery query(db);
    query.exec("SELECT DISTINCT category FROM Word");
    if(query.next())
        do
        {
            QString p(query.value(0).toString());
            categories.append(p);
        } while (query.next());
    else
        qDebug()<<"Empty table word";
    return categories;
}

void Database::deletePlayers()
{
    QSqlQuery query(db);
    query.exec("DELETE FROM Player");
}

void Database::resetWords()
{
    QSqlQuery query(db);
    query.exec("DELETE FROM Word");
    insertWords(":/txt/csv/words.txt");
}

Database::~Database()
{
    if(db.isOpen()) db.close();
}
