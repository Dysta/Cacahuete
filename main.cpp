#include "mainwindow.h"
#include <QApplication>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(NULL, "Projet Tech");
    w.show();

    cout << "OpenCV version : " << CV_VERSION << endl;
      cout << "Major version : " << CV_MAJOR_VERSION << endl;
      cout << "Minor version : " << CV_MINOR_VERSION << endl;
      cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;
    return a.exec();
}
