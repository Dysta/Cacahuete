#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "utils.h"
#include "box/laplacianbox.h"
#include "box/sobelbox.h"
#include "box/disparitybox.h"
#include "box/calibdepthbox.h"
#include "box/trackerbox.h"
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
#include <QTabWidget>

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
        CALIBDEPTHBOX,
        TRACKERBOX
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
    void setOriLeftPucture(QImage pic) { _originalLeftPicture = pic; }
    void setOriRightPucture(QImage pic) { _originalRightPicture = pic; }
    void setPictureTrack(QImage pic) { _pictureTrack = pic; }
    void setPictureDepth(QImage pic) { _pictureDepth = pic; }
    void setPictureDisp(QImage pic) { _pictureDisp = pic; }
    void setIntrinsic(cv::Mat Intrinsic) { _intrinsic = Intrinsic; }
    void setDistcoeffs(cv::Mat Distcoeff) { _distcoeffs = Distcoeff; }
    void setNetworkSuccess(bool val) { _networkSuccess = val; }
    void copyImage(void);
    bool networkExist(void) { return _networkExist; }
    Network* getNetwork(void) { return _network; }



    void setMatDisp(const cv::Mat &matDisp);

    void setMatDepth(const cv::Mat &matDepth);

    void setMatTrack(const cv::Mat &matTrack);

    cv::Mat getMatDisp() const;

    cv::Mat getMatDepth() const;

    cv::Mat getMatTrack() const;

private slots:
    void open(void);
    void about(void);
    void close(void);
    void network(void);

    void onNetworkBtnClick(void);
    
private:
    void createMenu(void);
    void createAction(void);
    void createImageGroup(const QString &title);
    void createSliderGroup(void);
    void createDispGroup(const QString &title);
    void createDepthGroup(const QString &title);
    void createTrackGroup(const QString &title);

    QWidget* _mainWidget;
    QGridLayout* _mainLayout;
    QStackedWidget* _menuStack;
    QTabWidget* _tabWidget;


    QGroupBox* _imageGroup;
    QGroupBox* _disparityGroup;
    QGroupBox* _depthGroup;
    QGroupBox* _trackGroup;

    LaplacianBox* _laplacianBox;
    SobelBox* _sobelBox;
    DisparityBox* _disparityBox;
    CalibDepthBox* _calibBox;
    TrackerBox* _trackBox;

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
    QLabel* _dispartyLabel;
    QLabel* _depthLabel;
    QLabel* _trackLabel;

    QImage _pictureLeft;
    QImage _pictureRight;
    QImage _pictureDisp;
    QImage _pictureDepth;
    QImage _pictureTrack;

    QImage _originalLeftPicture;
    QImage _originalRightPicture;
    
    cv::Mat _matDisp;
    cv::Mat _matDepth;
    cv::Mat _matTrack;
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
