#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(NULL, "Tittte");
    w.show();

    return a.exec();
}
