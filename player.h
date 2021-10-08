#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString name;
    int score;
public:
    Player(QString n);
    Player(QString n, int s);
    QString getName();
    int getScore();
};

#endif // PLAYER_H
