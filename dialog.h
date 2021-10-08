#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <database.h>
#include <player.h>


class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();
    Dialog(Database *db);
    Dialog(QVector<QString>);
    Dialog(QVector<Player>);
    ~Dialog();
    Player getCurrentPlayer();
    QString getCategory();
    void CSVInfo();
    void About();
private:
    QVBoxLayout *layout;
    QLabel *label;
    QLineEdit *name;
    QPushButton *button;
    QListWidget *list;
    QComboBox *combo;
    Database *db;
    Player *p;
public slots:
    void confirm();
};

#endif // LOGINDIALOG_H
