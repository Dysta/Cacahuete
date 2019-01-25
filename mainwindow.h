#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainbox.h"
#include "laplacianbox.h"
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
    QWidget* getMainWidget() { return mainWidget; }
    QGridLayout* getMainLayout() { return mainLayout; }
    QImage* getPicture() { return &picture; }
    void setPicture(QImage pic) { picture = pic; }


private slots:
    void open(void);
    void about(void);
    void close(void);
    void onLaplacianClick(void);
    void onMenuClick(void);

private:
    void createMenu(void);
    void createAction(void);
    void createImageGroup(const QString &title);
    void createSliderGroup(void);
    void copyImage(void);

    QWidget* mainWidget;
    QGridLayout* mainLayout;
    QStackedWidget* menuStack;

    QGroupBox* imageGroup;
    MainBox* mainBox;
    LaplacianBox* laplacianBox;

    QMenu* fileMenu;
    QMenu* aboutMenu;

    QAction* openFileAct;
    QAction* exitAppAct;
    QAction* aboutAct;

    QLabel* imageLabel;

    QImage picture;
    QImage originalPicture;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
