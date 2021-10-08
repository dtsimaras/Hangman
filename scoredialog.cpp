#include "dialog.h"

Dialog::Dialog(QVector<Player> players)
{
    setModal(true);

    setFixedSize(300,400);
    setWindowTitle("Scoreboard");

    // Creating Layout
    layout = new QVBoxLayout;
    setLayout(layout);

    // Creating Widgets ( Components )
    list = new QListWidget;
    for(int i=0;i<players.size();i++) {
        list->addItem(players[i].getName()+" - Score: "+QString::number(players[i].getScore()));
    }

    button = new QPushButton;
    button->setText("Back");
    connect(button,SIGNAL(clicked()),this,SLOT(reject())); //accept() ?

    layout->addWidget(list);
    layout->addWidget(button);
}
