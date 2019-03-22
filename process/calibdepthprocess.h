#ifndef CALIBDEPTHPROCESS_H
#define CALIBDEPTHPROCESS_H

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <vector>

#include <QImage>

#include "utils.h"

class MainWindow;

class CalibDepthProcess
{
public:
    CalibDepthProcess(MainWindow* parent);
    void setImage(int value);
    void setNumCornersH(int);
    void setNumCornersV(int);
    void setIntrisic(cv::Mat);
    void setDistCoeffs(cv::Mat);
    void setQ(cv::Mat);
    void setMaps(cv::Mat, cv::Mat);
    void calibration(QStringList sList, int numBoards, bool isVideo);
    void undistort(void);
    void stereoCalib(QStringList sList, int numBoards, bool isVideo);
    void depthMap(void);

private:
    //void updatePicture(void);

    MainWindow* _parent;

    int _numCornersH;
    int _numCornersV;

    cv::Mat _intrinsic;
    cv::Mat _distcoeffs;
    cv::Mat _map1, _map2;
    cv::Mat _Q;

};

#endif // CALIBDEPTHPROCESS_H
