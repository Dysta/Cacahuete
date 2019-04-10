#ifndef CALIBDEPTHPROCESS_H
#define CALIBDEPTHPROCESS_H

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <vector>

#include <QImage>

#include "process/disparityprocess.h"

class MainWindow;

class CalibDepthProcess
{
public:
    CalibDepthProcess(MainWindow* parent, DisparityProcess* dispProcess);
    /**
     * @brief setImage value = 0 if we choose left picture; value = 1 if we choose right picture
     * @param value
     */
    void setImage(int value);
    /**
     * @brief setNumCornersH
     */
    void setNumCornersH(int);
    /**
     * @brief setNumCornersV
     */
    void setNumCornersV(int);
    /**
     * @brief setIntrisic
     */
    void setIntrisic(cv::Mat);
    /**
     * @brief setDistCoeffs
     */
    void setDistCoeffs(cv::Mat);
    /**
     * @brief setQ
     */
    void setQ(cv::Mat);
    /**
     * @brief setMaps
     */
    void setMaps(cv::Mat, cv::Mat);
    /**
     * @brief calibration
     * @param sList
     * @param numBoards
     * @param isVideo
     */
    void calibration(QStringList sList, int numBoards, bool isVideo);
    /**
     * @brief undistort
     */
    void undistort(void);
    /**
     * @brief stereoCalib
     * @param sList
     * @param numBoards
     * @param isVideo
     */
    void stereoCalib(QStringList sList, int numBoards, bool isVideo);
    /**
     * @brief depthMap create a depth Map and display it in the mainwindows
     */
    void depthMap(void);
    /**
     * @brief depthMap
     * @param left
     * @param right
     * @return a depth map compute by left and right cv::Mat
     */
    cv::Mat depthMap(cv::Mat left, cv::Mat right);
    /**
     * @brief loadParam load parameters to compute a depth map
     */
    void loadParam(void);
    /**
     * @brief setUseRemap true if we use remap, false otherwise
     * @param useRemap
     */
    void setUseRemap(bool useRemap);

private:
    MainWindow* _parent;
    DisparityProcess* _dispProcess;

    int _numCornersH;
    int _numCornersV;
    bool _useRemap;

    cv::Mat _intrinsic;
    cv::Mat _distcoeffs;
    cv::Mat _map1, _map2;
    cv::Mat _Q;

};

#endif // CALIBDEPTHPROCESS_H
