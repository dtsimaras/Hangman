#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <dialog.h>
#include <database.h>
#include <player.h>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QSound>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool startApp();
    void scoreSlot();
    void createButtons();
    void insertWordsFromCSV();
    void resetWidgets();
    ~MainWindow();
private:
    void createActions();
    Dialog *d;
    QDesktopWidget dw;
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *row0, *row1, *row2, *row3, *row4;
    QLabel *label20, *label1, *label2;
    QPushButton *buttons[26], *playButton;
    Database *db;
    QVector<Word> words;
    QVector<Player> players;
    QVector<QString> categories;
    Player *currentPlayer;
    QString currentCategory, currentWord;
    QString labelText;
    QMenuBar *menuBar;
    QMenu *mainMenu, *editMenu, *helpMenu;
    QAction *musicMenu;
    QSound *music;
    int mistake = 0;
public slots:
    void letterSlot();
    void wordSlot();
    void menuSlot(QAction *action);
};
#endif // MAINWINDOW_H
