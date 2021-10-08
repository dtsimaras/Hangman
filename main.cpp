#include "mainwindow.h"
#include "dialog.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(w.startApp())
        return a.exec();
    else
    {
        //a.quit();
        return -1;
    }
}
