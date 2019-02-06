#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainbox.h"
#include "laplacianbox.h"
#include "sobelbox.h"
#include "utils.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QImageReader>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QStackedWidget>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum INDEX {
        MAINBOX,
        LAPLACIANBOX,
        SOBELBOX,
        DISPARITYBOX
    };

public:
    MainWindow(QWidget *parent, const QString title);
    ~MainWindow();
    void updateImage(void);
    QWidget* getMainWidget() { return _mainWidget; }
    QGridLayout* getMainLayout() { return _mainLayout; }
    QImage* getPicture() { return &_picture; }
    QImage* getOriginalPicture() { return &_originalPicture; }
    void setPicture(QImage pic) { _picture = pic; }


private slots:
    void open(void);
    void about(void);
    void close(void);
    void onLaplacianClick(void);
    void onSobelClick(void);
    void onMenuClick(void);

private:
    void createMenu(void);
    void createAction(void);
    void createImageGroup(const QString &title);
    void createSliderGroup(void);
    void copyImage(void);

    QWidget* _mainWidget;
    QGridLayout* _mainLayout;
    QStackedWidget* _menuStack;

    QGroupBox* _imageGroup;
    MainBox* _mainBox;
    LaplacianBox* _laplacianBox;
    SobelBox* _sobelBox;

    QMenu* _fileMenu;
    QMenu* _aboutMenu;

    QAction* _openFileAct;
    QAction* _exitAppAct;
    QAction* _aboutAct;

    QLabel* _imageLabel;

    QImage _picture;
    QImage _originalPicture;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
