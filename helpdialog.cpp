#include "dialog.h"

Dialog::Dialog()
{
    setModal(true);

    //setFixedSize(300,400);
    setWindowTitle("Help!");

    // Creating Layout
    layout = new QVBoxLayout;
    setLayout(layout);

    // Creating Widgets ( Components )
    label = new QLabel;
    label->setText(" ");
    label->setAlignment(Qt::AlignCenter);

    button = new QPushButton;
    button->setText("Back");
    connect(button,SIGNAL(clicked()),this,SLOT(reject())); //accept() ?

    layout->addWidget(label);
    layout->addWidget(button);
}

void Dialog::CSVInfo()
{
    label->setText("<br/><br/><h3> In order to insert new words you need the words in a .txt file <br/>"
                                  "with the format 'word, category'. If you want to insert more   <br/>"
                                  "than one words, type one word per line in the above format. In <br/>"
                                  "case something goes wrong, you can reset the Words to the      <br/>"
                                  "default ones through the edit menu. The word 'Hangman' can't be<br/>"
                                  " used. Enjoy!!</h3><br/>");
}

void Dialog::About()
{
    label->setText("<br/><h3>This game was created by Tsimo, an aspiring programmer and nature<br/>"
                            "lover. It was created with Qt Creator in C++ for a univeristy    <br/>"
                            " assignment with scalability in mind.                            <br/></h3><br/>");
}
