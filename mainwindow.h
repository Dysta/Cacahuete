#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "box/mainbox.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "box/laplacianbox.h"
#include "box/sobelbox.h"
#include "box/disparitybox.h"
#include "box/calibdepthbox.h"
#include "network.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>

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

    enum INDEX {
        MAINBOX,
        LAPLACIANBOX,
        SOBELBOX,
        DISPARITYBOX,
        CALIBDEPTHBOX
    };

public:
    MainWindow(QWidget *parent, const QString title);
    ~MainWindow();
    void updateImage(void);
    QWidget* getMainWidget() { return _mainWidget; }
    QGridLayout* getMainLayout() { return _mainLayout; }
    QImage* getLeftPicture() { return &_pictureLeft; }
    QImage* getRightPicture() { return &_pictureRight; }
    QImage* getOriginalLeftPicture() { return &_originalLeftPicture; }
    QImage* getOriginalRightPicture() { return &_originalRightPicture; }
    void setLeftPicture(QImage pic) { _pictureLeft = pic; }
    void setRightPicture(QImage pic) { _pictureRight = pic; }
    void setOrileftPucture(QImage pic) { _originalLeftPicture = pic; }
    void setOriRightPucture(QImage pic) { _originalRightPicture = pic; }
    void setIntrinsic(cv::Mat Intrinsic) { _intrinsic = Intrinsic; }
    void setDistcoeffs(cv::Mat Distcoeff) { _distcoeffs = Distcoeff; }
    void setNetworkSuccess(bool val) { _networkSuccess = val; }
    void copyImage(void);
    Network* getNetwork(void) { return _network; }


private slots:
    void open(void);
    void about(void);
    void close(void);
    void network(void);

    void onLaplacianClick(void);
    void onSobelClick(void);
    void onDisparityClick(void);
    void onCalibClick(void);
    void onMenuClick(void);

    void onNetworkBtnClick(void);
    
private:
    void createMenu(void);
    void createAction(void);
    void createImageGroup(const QString &title);
    void createSliderGroup(void);

    QWidget* _mainWidget;
    QGridLayout* _mainLayout;
    QStackedWidget* _menuStack;


    QGroupBox* _imageGroup;
    MainBox* _mainBox;
    LaplacianBox* _laplacianBox;
    SobelBox* _sobelBox;
    DisparityBox* _disparityBox;
    CalibDepthBox* _calibBox;

    QMenu* _fileMenu;
    QMenu* _aboutMenu;

    QAction* _openFileAct;
    QAction* _exitAppAct;
    QAction* _aboutAct;
    QAction* _calibPicAct;
    QAction* _calibVidAct;
    QAction* _undistordAct;
    QAction* _depthAct;
    QAction* _networkAct;

    QLabel* _imageLeftLabel;
    QLabel* _imageRightLabel;

    QImage _pictureLeft;
    QImage _pictureRight;

    QImage _originalLeftPicture;
    QImage _originalRightPicture;
    
    cv::Mat _intrinsic;
    cv::Mat _distcoeffs;

    Network* _network;
    bool _networkExist = false;
    bool _networkSuccess = false;
    QWidget* _networkWidget;
    QHBoxLayout* _networkBox;
    QLineEdit* _hostLine;
    QSpinBox* _portLine;
    QPushButton* _networkBtn;
    QString _host;
    quint16 _port;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
