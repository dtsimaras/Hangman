#include "dialog.h"

Dialog::Dialog(Database *database)
{
    setModal(true);

    // Set Database
    db = database;

    setFixedSize(200,120);
    setWindowTitle("Log In");

    // Creating Layout
    layout = new QVBoxLayout;
    setLayout(layout);

    // Creating Widgets ( Components )
    label = new QLabel;
    label->setText("Enter your name: ");
    label->setAlignment(Qt::AlignVCenter);

    name = new QLineEdit;
    name->setPlaceholderText("Player");

    button = new QPushButton;
    button->setText("OK");

    // Add Widgets into layout
    layout->addWidget(label);
    layout->addWidget(name);
    layout->addWidget(button);

    connect(button, SIGNAL(released()), this, SLOT(confirm()));
    //connect(button, SIGNAL(clicked()), this, SLOT(accept()));

}

void Dialog::confirm()
{
    QString pName = name->text().trimmed();
    if(pName=="" || pName==NULL) {
        QMessageBox::critical(this,"Invalid Name","Please enter players name");
        return;
    }
    if(db->getPlayer(pName).getName()!=pName)
    {
        if(!db->insertPlayer(pName)) { //Tha eprepe na ginei me try catch kalutera
            QMessageBox::critical(this,"Database Error", "Something Went Wrong, Try Again");
            return;
        }
    }
    p = new Player(db->getPlayer(pName).getName(),db->getPlayer(pName).getScore());
    accept();
}

Player Dialog::getCurrentPlayer() {
    return *p;
}

Dialog::~Dialog() //Delete this probably and from constructor
{
   // db->~Database();
}
