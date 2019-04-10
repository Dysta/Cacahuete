#ifndef SOBELPROCESS_H
#define SOBELPROCESS_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <QImage>

#include "utils.h"

class MainWindow;

class SobelProcess
{
public:
    SobelProcess(MainWindow* parent);
    /**
     * @brief setImage
     * @param value
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
    /**
     * @brief setDx
     * @param value
     */
    void setDx(int value);
    /**
     * @brief setDy
     * @param value
     */
    void setDy(int value);
    /**
     * @brief setAlpha
     * @param value
     */
    void setAlpha(int value);
    /**
     * @brief setBeta
     * @param value
     */
    void setBeta(int value);
    /**
     * @brief setGamma
     * @param value
     */
    void setGamma(int value);

private:
    void updatePicture(void);
    void process(void);

    MainWindow* _parent;

    bool _activeBlur;
    int _sizeH;
    int _sizeL;
    int _sigmaX;
    int _sigmaY;

    int _dx;
    int _dy;

    double _alpha;
    double _beta;
    double _gamma;
};

#endif // SOBELPROCESS_H
