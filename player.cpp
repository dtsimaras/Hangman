#include "player.h"

Player::Player(QString n)
{
    name = n;
    score = 0;
}

Player::Player(QString n, int s)
{
    name = n;
    score = s;
}

QString Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}
