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
    /**
     * @brief getMainWidget
     * @return main Widget
     */
    QWidget* getMainWidget() { return _mainWidget; }
    /**
     * @brief getMainLayout
     * @return main Layou
     */
    QGridLayout* getMainLayout() { return _mainLayout; }
    /**
     * @brief getLeftPicture
     * @return the current left picture
     */
    QImage* getLeftPicture() { return &_pictureLeft; }
    /**
     * @brief getRightPicture
     * @return the current right picture
     */
    QImage* getRightPicture() { return &_pictureRight; }
    /**
     * @brief getOriginalLeftPicture
     * @return the original left picture
     */
    QImage* getOriginalLeftPicture() { return &_originalLeftPicture; }
    /**
     * @brief getOriginalRightPicture
     * @return the original right picture
     */
    QImage* getOriginalRightPicture() { return &_originalRightPicture; }
    /**
     * @brief getMatDisp
     * @return the disparity cv::Mat
     */
    cv::Mat getMatDisp() const;
    /**
     * @brief getMatDepth
     * @return the depth cv::Mat
     */
    cv::Mat getMatDepth() const;
    /**
     * @brief getMatTrack
     * @return the tracking cv::Mat
     */
    cv::Mat getMatTrack() const;
    /**
     * @brief getNetwork
     * @return the current network (nullptr if it doesn't exist)
     */
    Network* getNetwork(void) { return _network; }

    /**
     * @brief setLeftPicture
     * @param pic
     */
    void setLeftPicture(QImage pic) { _pictureLeft = pic; }
    /**
     * @brief setRightPicture
     * @param pic
     */
    void setRightPicture(QImage pic) { _pictureRight = pic; }
    /**
     * @brief setOriLeftPucture
     * @param pic
     */
    void setOriLeftPucture(QImage pic) { _originalLeftPicture = pic; }
    /**
     * @brief setOriRightPucture
     * @param pic
     */
    void setOriRightPucture(QImage pic) { _originalRightPicture = pic; }
    /**
     * @brief setPictureTrack
     * @param pic
     */
    void setPictureTrack(QImage pic) { _pictureTrack = pic; }
    /**
     * @brief setPictureDepth
     * @param pic
     */
    void setPictureDepth(QImage pic) { _pictureDepth = pic; }
    /**
     * @brief setPictureDisp
     * @param pic
     */
    void setPictureDisp(QImage pic) { _pictureDisp = pic; }
    /**
     * @brief setIntrinsic
     * @param Intrinsic
     */
    void setIntrinsic(cv::Mat Intrinsic) { _intrinsic = Intrinsic; }
    /**
     * @brief setDistcoeffs
     * @param Distcoeff
     */
    void setDistcoeffs(cv::Mat Distcoeff) { _distcoeffs = Distcoeff; }
    /**
     * @brief setNetworkSuccess
     * @param val
     */
    void setNetworkSuccess(bool val) { _networkSuccess = val; }
    /**
     * @brief setMatDisp
     * @param matDisp
     */
    void setMatDisp(const cv::Mat &matDisp);
    /**
     * @brief setMatDepth
     * @param matDepth
     */
    void setMatDepth(const cv::Mat &matDepth);
    /**
     * @brief setMatTrack
     * @param matTrack
     */
    void setMatTrack(const cv::Mat &matTrack);
    /**
     * @brief copyImage
     */
    void copyImage(void);
    /**
     * @brief networkExist
     * @return true if network exist, false otherwise
     */
    bool networkExist(void) { return _networkExist; }

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
