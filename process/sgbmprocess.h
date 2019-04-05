#ifndef SGBMPROCESS_H
#define SGBMPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

class MainWindow;

class SGBMProcess
{
public:
    SGBMProcess(MainWindow* parent);

    void setMinDisp(int value);
    void setNumDisp(int value);
    void setBlockSize(int value);
    void setP1(int value);
    void setP2(int value);
    void setDisp12MaxDiffChange(int value);
    void setPrefilter(int value);
    void setUniquenessRatio(int value);
    void setSpeckleWindowsSize(int value);
    void setSpeckleRange(int value);
    void setMode(int value);

    cv::Mat process(cv::Mat left, cv::Mat right);
    void process(void);

private:
    void updatePicture(void);
    MainWindow* _parent;

    int _minDisparity;
    int _numDisparity;
    int _blockSize;
    int _p1;
    int _p2;
    int _disp12MaxDiff;
    int _preFilter;
    int _uniquenessRatio;
    int _speckleWindowsSize;
    int _speckleRange;
    int _mode;
};

#endif // SGBMPROCESS_H
