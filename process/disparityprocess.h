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
    /**
     * @brief getInstance
     * @return a instance of DisparityProcess
     */
    DisparityProcess* getInstance(void) { return this; }

    /**
     * @brief getSBMProcess
     * @return the current SBMProcess
     */
    SBMProcess *getSBMProcess() const;
    /**
     * @brief getSGBMProcess
     * @return the current SGBMProcess
     */
    SGBMProcess *getSGBMProcess() const;

    /**
     * @brief process
     * @param left
     * @param right
     * @return a disparity map computed by left and right cv::mat
     */
    cv::Mat process(cv::Mat left, cv::Mat right);
    /**
     * @brief process display a disparity matrice in the main windows
     */
    void process(void);
    /**
     * @brief setMode permite to switch between the SBM mode and SGBM mode
     * @param value
     */
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
