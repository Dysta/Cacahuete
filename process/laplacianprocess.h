#ifndef LAPLACIANPROCESS_H
#define LAPLACIANPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

#include "utils.h"

class MainWindow;

class LaplacianProcess
{
public:
    LaplacianProcess(MainWindow* parent);
    void setImage(int value);
    void setActiveBlur(bool state);
    void setSizeH(int value);
    void setSizeL(int value);
    void setSigmaX(int value);
    void setSigmaY(int value);

private:
    void updatePicture(void);
    void process(void);

    MainWindow* _parent;

    bool _activeBlur;
    int _sizeH;
    int _sizeL;
    int _sigmaX;
    int _sigmaY;
};

#endif // LAPLACIANPROCESS_H
