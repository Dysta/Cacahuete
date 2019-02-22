#ifndef CALIBDEPTHPROCESS_H
#define CALIBDEPTHPROCESS_H

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <vector>

#include <QImage>

#include "utils.h"

class MainWindow;

class CalibDepthProcess
{
public:
    CalibDepthProcess(MainWindow* parent);
    void setNumCornersH(int);
    void setNumCornersV(int);
    void setIntrisic(cv::Mat);
    void setDistCoeffs(cv::Mat);

private:
    //void updatePicture(void);
    void calibration(QStringList sList, int numBoards, bool isVideo);
    void undistort(void);
    void depthMap(QStringList sList, int numBoards, bool isVideo);

    MainWindow* _parent;

    int _numCornersH;
    int _numCornersV;

    cv::Mat _intrinsic;
    cv::Mat _distcoeffs;

};

#endif // CALIBDEPTHPROCESS_H
