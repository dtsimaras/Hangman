#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <player.h>
#include <word.h>

class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    bool insertPlayer(QString p);
    Player getPlayer(QString n);
    bool insertWords(QString);
    QVector<Player> getPlayers();
    QVector<Word> getWords();
    QVector<QString> getCategories();
    bool updateScore(Player);
    void deletePlayers();
    void resetWords();
    ~Database();
};

#endif // DATABASE_H
