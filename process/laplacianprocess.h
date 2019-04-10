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
    /**
     * @brief setImage choose between left and right picture
     * @param value 1 for right picture, 0 for left picture
     */
    void setImage(int value);
    /**
     * @brief setActiveBlur
     * @param state
     */
    void setActiveBlur(bool state);
    /**
     * @brief setSizeH
     * @param value
     */
    void setSizeH(int value);
    /**
     * @brief setSizeL
     * @param value
     */
    void setSizeL(int value);
    /**
     * @brief setSigmaX
     * @param value
     */
    void setSigmaX(int value);
    /**
     * @brief setSigmaY
     * @param value
     */
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
