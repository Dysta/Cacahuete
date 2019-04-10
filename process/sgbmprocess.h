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

    /**
     * @brief setMinDisp
     * @param value
     */
    void setMinDisp(int value);
    /**
     * @brief setNumDisp
     * @param value
     */
    void setNumDisp(int value);
    /**
     * @brief setBlockSize
     * @param value
     */
    void setBlockSize(int value);
    /**
     * @brief setP1
     * @param value
     */
    void setP1(int value);
    /**
     * @brief setP2
     * @param value
     */
    void setP2(int value);
    /**
     * @brief setDisp12MaxDiffChange
     * @param value
     */
    void setDisp12MaxDiffChange(int value);
    /**
     * @brief setPrefilter
     * @param value
     */
    void setPrefilter(int value);
    /**
     * @brief setUniquenessRatio
     * @param value
     */
    void setUniquenessRatio(int value);
    /**
     * @brief setSpeckleWindowsSize
     * @param value
     */
    void setSpeckleWindowsSize(int value);
    /**
     * @brief setSpeckleRange
     * @param value
     */
    void setSpeckleRange(int value);
    /**
     * @brief setMode
     * @param value
     */
    void setMode(int value);

    /**
     * @brief process
     * @param left
     * @param right
     * @return a SGBM matrice compute by left and right picture
     */
    cv::Mat process(cv::Mat left, cv::Mat right);
    /**
     * @brief process display a SGBM matrice in mainwindow
     */
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
