#ifndef DISPARITYPROCESS_H
#define DISPARITYPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

#include "sbmprocess.h"
#include "sgbmprocess.h"

class MainWindow;

class DisparityProcess
{
public:
    DisparityProcess(MainWindow* parent);
    DisparityProcess* getInstance(void) { return this; }

    SBMProcess *getSBMProcess() const;
    SGBMProcess *getSGBMProcess() const;

    cv::Mat process(cv::Mat left, cv::Mat right);
    void process(void);

    void setMode(int value);

private:
    enum {
        SBM,
        SGBM
    };

    void updatePicture(void);
    MainWindow* _parent;

    SBMProcess* _SBMProcess;
    SGBMProcess* _SGBMProcess;

    int _mode;
};

#endif // DISPARITYPROCESS_H
