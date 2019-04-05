#ifndef DISPARITYSBMPROCESS_H
#define DISPARITYSBMPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

class MainWindow;

class SBMProcess
{
public:
    SBMProcess(MainWindow* parent);
    void setMode(int value);
    void setNumDisp(int value);
    void setBlockSize(int value);
    void setPrefilterCap(int value);
    void setPrefilterSize(int Value);
    void setPrefilterType(int value);
    void setRoi1(int value);
    void setRoi2(int value);
    void setTextureThreshold(int value);
    void setUniquenessRatio(int value);

    cv::Mat process(cv::Mat left, cv::Mat right);
    void process(void);

private:
    void updatePicture(void);
    MainWindow* _parent;

    int _numDisparity;
    int _blockSize;
    int _preFilterCap;
    int _preFilterSize;
    int _preFilterType;
    int _roi1;
    int _roi2;
    int _textureThreshold;
    int _uniquenessRatio;

};

#endif // DISPARITYSBMPROCESS_H
