#ifndef DISPARITYPROCESS_H
#define DISPARITYPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

class MainWindow;

class DisparityProcess
{
public:
    DisparityProcess(MainWindow* parent);
    void setMode(int value) { _mode = value; }
    void setSBMnumDisp(int value) { _SBMnumDisparity = value; }
    void setSBMblockSize(int value) { _SBMblockSize = value; }
    void setMinDisp(int value) { _minDisparity = value; }
    void setSGBMnumDisp(int value) { _SGBMnumDisparity = value; }
    void setSGBMblockSize(int value) { _SGBMblockSize = value; }
    void setP1(int value) { _p1 = value; }
    void setP2(int value) { _p2 = value; }
    void setPrefilter(int value) { _preFilter = value; }
    void setUniquenessRatio(int value) { _UniquenessRatio = value; }
    void setSpeckleWindowsSize(int value) { _speckleWindowsSize = value; }
    void setSpeckleRange(int value) { _speckleRange = value; }
    void setSGBMmode(int value) { _SGBMmode = value; }

private:
    void updatePicture(void);
    void process(void);

    MainWindow* _parent;

    int _mode;

    int _SBMnumDisparity;
    int _SBMblockSize;

    int _minDisparity;
    int _SGBMnumDisparity;
    int _SGBMblockSize;
    int _p1;
    int _p2;
    int _preFilter;
    int _UniquenessRatio;
    int _speckleWindowsSize;
    int _speckleRange;
    int _SGBMmode;


};

#endif // DISPARITYPROCESS_H
