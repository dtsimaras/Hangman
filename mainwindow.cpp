#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Create-Open Database
    db = new Database();
    //words = db->getWords();
    //players = db->getPlayers();

    // Set Main Window // TODO change the icons too and create a logo for .exe
    //setFixedSize(300,300);
    resize(dw.width()*0.7,dw.height()*0.7);
    setWindowTitle("Hangman");
    // Set Background Image - Set Style Sheet - Soundrack
    setStyleSheet("QMainWindow {border-image:url(:/img/images/background.png) 0 0 0 0 stretch stretch}");
    music = new QSound(":/aud/audio/soundtrack.wav");
    music->setLoops(QSound::Infinite);

    // Set Main Widget
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->resize(this->width(),this->height());

    // Set Layouts
    mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    row0 = new QHBoxLayout;
    mainLayout->addLayout(row0);
    row1 = new QHBoxLayout;
    mainLayout->addLayout(row1);
    row2 = new QHBoxLayout;
    mainLayout->addLayout(row2);
    row3 = new QHBoxLayout;
    mainLayout->addLayout(row3);
    row4 = new QHBoxLayout;
    mainLayout->addLayout(row4);
    //mainLayout->setContentsMargins(0,0,0,0); // Don't need it anymore. Keep it just in case

    // Set Labels
    QFont f1("Comic Sans MS", this->width()/60, QFont::Thin);
    label1 = new QLabel;
    label1->setText("Welcome");
    label1->setAlignment(Qt::AlignTop);
    label1->setFont(f1);

    QPixmap pix(":/img/images/hang.png");
    QFont f0("Comic Sans MS", this->width()/60, QFont::Thin);
    label20 = new QLabel;
    label20->setPixmap(pix);
    label20->setScaledContents(true);

    QFont f2("Comic Sans MS", this->width()/30, QFont::Thin);
    f2.setLetterSpacing(QFont::PercentageSpacing, 150);
    //f2.setUnderline(true);
    label2 = new QLabel;
    label2->setAlignment(Qt::AlignVCenter);
    label2->setFont(f2);

    // Create Help Menu
    helpMenu = new QMenu("Help");
    helpMenu->addAction("CSV Info");
    helpMenu->addAction("About");

    // Create Edit Menu
    editMenu = new QMenu("Edit");
    //editMenu->addAction("Clear Scores"); //Not really needed.
    editMenu->addAction("Clear Players");
    editMenu->addSeparator();
    editMenu->addAction("Insert Words from CSV");
    editMenu->addAction("Reset Words");
    editMenu->addSeparator();
    musicMenu = new QAction("Music On/Off");
    editMenu->addAction(musicMenu); //TODO CheckBoxMenu or Dialog with music & sound?
    musicMenu->setCheckable(true);
    musicMenu->setChecked(true);

    // Create Main Menu
    mainMenu = new QMenu("Menu");
    mainMenu->addAction("New Game")->setShortcut(QKeySequence(tr("Ctrl+N")));
    //mainMenu->addAction("Custom Game");
    mainMenu->addSeparator();
    mainMenu->addAction("Change Player")->setShortcut(QKeySequence(tr("Ctrl+C")));;
    mainMenu->addAction("View Scoreboard")->setShortcut(QKeySequence(tr("Ctrl+S")));;
    mainMenu->addSeparator();
    mainMenu->addAction("Exit")->setShortcut(QKeySequence(tr("Ctrl+X")));;

    connect(mainMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuSlot(QAction*)));
    connect(editMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuSlot(QAction*)));
    connect(helpMenu, SIGNAL(triggered(QAction*)), this, SLOT(menuSlot(QAction*)));

    // Create Menu Bar
    menuBar = new QMenuBar;
    menuBar->addMenu(mainMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(helpMenu);

    //Create Play Button
    playButton = new QPushButton;
    playButton->setText("Play");
    playButton->setFont(f1);
    playButton->setFixedSize(dw.width()*0.2,60);
    playButton->setStyleSheet("background-color:rgba(255,255,0,60%);"
                              "color:rgba(0,0,0,100%);"
                              "border-style: solid;"
                              "border-color: black;"
                              "border-width: 4px;"
                              "border-radius: 15px;");
    connect(playButton, SIGNAL(clicked()), this, SLOT(wordSlot()));

    // Add Widgets to Layouts
    mainLayout->setMenuBar(menuBar);
    row0->addWidget(label1);
    row0->addSpacing(dw.width()*0.15);
    row0->addWidget(playButton);
    row0->addSpacing(dw.width()*0.05);
    row1->addWidget(label20);
    row1->addWidget(label2);

    createButtons();
}

void MainWindow::createButtons()
{
    QString a;
    QFont f3( "Comic Sans MS", this->width()/70, QFont::Bold);
    int i = 0;
    for(char letter = 'A';letter<='Z';letter++)
    {
        //qDebug()<<letter;
        buttons[i] = new QPushButton;
        a = letter;
        buttons[i]->setText(a);
        if(letter<'J')
            row2->addWidget(buttons[i]);
        else if(letter<'S')
            row3->addWidget(buttons[i]);
        else
            row4->addWidget(buttons[i]);

        connect(buttons[i],SIGNAL(clicked()), this, SLOT(letterSlot()));
        //buttons[i]->setFlat(true);
        buttons[i]->setFont(f3);
        buttons[i]->setFixedSize(60,60);
        buttons[i]->setStyleSheet("background-color:rgba(255,255,255,60%);"
                             "color:rgba(0,0,0,100%);"
                             "border-style: solid;"
                             "border-color: blue;"
                             "border-width: 2px;"
                             "border-radius: 27px;");
        i++;
    }
    row2->setAlignment(Qt::AlignRight);
    row3->setAlignment(Qt::AlignRight);
    row4->setAlignment(Qt::AlignRight);
}

void  MainWindow::menuSlot(QAction *action)
{
    QMessageBox::StandardButton reply;
    if(action->text()=="New Game")
        wordSlot();
    if(action->text()=="Change Player")
        startApp();
    if(action->text()=="View Scoreboard")
        scoreSlot();
    if(action->text()=="Exit")
    {
        reply = QMessageBox::question(this, windowTitle(), "Are you sure?", QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
              close();
    }
    if(action->text()=="Clear Players")
    {
        reply = QMessageBox::question(this, windowTitle(), "This will delete all Players, are you sure?", QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
          {
              db->deletePlayers();
              startApp();
          }
    }
    if(action->text()=="Reset Words")
    {
        reply = QMessageBox::question(this, windowTitle(), "Are you sure?", QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
              db->resetWords();
    }
    if(action->text()=="Insert Words from CSV")
        insertWordsFromCSV();
    if(action->text()=="Music On/Off")
    {
        if(musicMenu->isChecked())
            music->play();
        else
            music->stop();
    }
    if(action->text()=="CSV Info")
    {
         d = new Dialog();
         d->show();
         d->CSVInfo();
    }
    if(action->text()=="About")
    {
         d = new Dialog();
         d->show();
         d->About();
    }
}

bool MainWindow::startApp()
{
    d = new Dialog(db);
    //Qt::WindowFlags flags(Qt::WindowTitleHint); // TODO removes ? but deactivates X button too
    //d->setWindowFlags(flags);
    if(d->exec()) {
        show();
        music->play();
        currentPlayer = new Player(d->getCurrentPlayer().getName(), d->getCurrentPlayer().getScore());
        //currentPlayer = new Player("Jack",1);
        label1->setText("Welcome "+currentPlayer->getName()+", Score: "+QString::number(currentPlayer->getScore()));
        label2->setText("Hangman");
        resetWidgets();
        return true;
    }
    return false;
}

void MainWindow::wordSlot() {
    words = db->getWords();
    categories = db->getCategories();
    if(words.size()>0) {
        d = new Dialog(categories);
        //Qt::WindowFlags flags(Qt::WindowTitleHint); //TODO
        //d->setWindowFlags(flags);
        d->show();
    }
    else
        QMessageBox::critical(this,"No Words","No Words were found, please check your installation");
    if(d->exec()) {
        currentCategory = d->getCategory();
        QVector<QString> catWords;
        labelText = "";
        for(int i=0;i<words.size();i++)
        {
            if(words[i].getCategory()==currentCategory)
            {
                catWords.append(words[i].getName());
            }
        }
        srand(time(NULL)); // Randomize rand() Results
        int randIndex = rand() % catWords.size();
        currentWord = catWords[randIndex];
        for(int i=0;i<currentWord.size();i++){
            labelText+="_";
        }
        label1->setText("Welcome "+currentPlayer->getName()+", Score: "+QString::number(currentPlayer->getScore()));
        label2->setText(labelText);
        resetWidgets();
    }
}

void MainWindow::scoreSlot() { //TODO Add a Delete Button, to delete selected Player
    players = db->getPlayers();
    if(players.size()>0) {
        d = new Dialog(players);
        //Qt::WindowFlags flags(Qt::WindowTitleHint); //TODO
        //d->setWindowFlags(flags);
        d->show();
    }
    else
        QMessageBox::critical(this,"Database Error","Please check with the developer");
}

void MainWindow::letterSlot() {
    QSound::play(":/aud/audio/click.wav");
    QPushButton *button = (QPushButton *)sender();
    QString a = button->text();
    bool contains = false;
    if(mistake==6)
    {
        QSound::play(":/aud/audio/lose.wav");
        label1->setText("You lost "+currentPlayer->getName()+"!! Score: "+QString::number(currentPlayer->getScore()));
        return;
    }

    if(label2->text()=="Hangman" || label2->text()==currentWord)
        return;
    //QString letter = QInputDialog::getText(this,windowTitle(),"Enter Letter",QLineEdit::Normal).toLower();
    if(a >= "A" && a <= "Z")// || (letter >= "A" && letter <= "Z"))
    {
        for(int i=0;i<currentWord.size();i++)
        {
            if(a[0]==currentWord[i].toUpper())
            {
                contains = true;
                if(i==0)
                    labelText[i] = a[0].toUpper();
                else
                    labelText[i] = a[0].toLower();

                button->setStyleSheet("background-color:rgba(0,255,0,60%);"
                                     "color:rgba(0,0,0,100%);"
                                     "border-style: solid;"
                                     "border-color: blue;"
                                     "border-width: 2px;"
                                     "border-radius: 27px;");
            }
            else
            {

            }
        }
    }
    if(!contains) {
        mistake++;
        QPixmap pix(QString(":/img/images/miss"+QString::number(mistake)+".png"));
        label20->setPixmap(pix);
        button->setStyleSheet("background-color:rgba(255,0,0,60%);"
                             "color:rgba(0,0,0,100%);"
                             "border-style: solid;"
                             "border-color: blue;"
                             "border-width: 2px;"
                             "border-radius: 27px;");
        if(mistake==6)
        {
             label1->setText("You lost "+currentPlayer->getName()+"!! Score: "+QString::number(currentPlayer->getScore()));
             QSound::play(":/aud/audio/lose.wav");
        }
    }

    label2->setText(labelText);
    if(labelText.toLower()==currentWord.toLower())
    {
        QSound::play(":/aud/audio/win.wav");
        db->updateScore(*currentPlayer);
        *currentPlayer = db->getPlayer(currentPlayer->getName());
        label1->setText("Congratulations "+currentPlayer->getName()+"!! Score: "+QString::number(currentPlayer->getScore()));
    }
}

void MainWindow::insertWordsFromCSV()
{
    QString path = QInputDialog::getText(this,windowTitle(),"Enter Path:",QLineEdit::Normal).toLower();
    if(!db->insertWords(path))
        QMessageBox::critical(this,"Error","Something Went Wrong, Check Help from correct file format");
}

void MainWindow::resetWidgets()
{
    mistake = 0;
    QPixmap pix(QString(":/img/images/hang.png"));
    label20->setPixmap(pix);
    for(int i=0;i<26;i++)
    {
        buttons[i]->setStyleSheet("background-color:rgba(255,255,255,60%);"
                             "color:rgba(0,0,0,100%);"
                             "border-style: solid;"
                             "border-color: blue;"
                             "border-width: 2px;"
                             "border-radius: 27px;");
    }
}

MainWindow::~MainWindow()
{
    db->~Database();
}
