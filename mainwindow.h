#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QImageReader>
#include <QSlider>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, const QString title);
    ~MainWindow();

private slots:
    void open(void);
    void about(void);
    void close(void);

private:
    void createMenu(void);
    void createAction(void);
    void createTab(void);
    void createSliders(void);

    QMenu* fileMenu;
    QMenu* aboutMenu;

    QAction* openFileAct;
    QAction* exitAppAct;
    QAction* aboutAct;

    QTabWidget* tabWidget;

    QLabel* label;
    QImage* picture;

    QWidget* sliderWidget;
    QLabel* sliders;

    QSlider* sliders0;

    QLabel* originalPic;
    QLabel* QImageLabel;
    QLabel* CVMatriceLabel;
    QLabel* reconstructedChess;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
