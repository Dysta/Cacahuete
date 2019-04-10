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
    /**
     * @brief setMode
     * @param value
     */
    void setMode(int value);
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
     * @brief setPrefilterCap
     * @param value
     */
    void setPrefilterCap(int value);
    /**
     * @brief setPrefilterSize
     * @param Value
     */
    void setPrefilterSize(int Value);
    /**
     * @brief setPrefilterType
     * @param value
     */
    void setPrefilterType(int value);
    /**
     * @brief setRoi1
     * @param value
     */
    void setRoi1(int value);
    /**
     * @brief setRoi2
     * @param value
     */
    void setRoi2(int value);
    /**
     * @brief setTextureThreshold
     * @param value
     */
    void setTextureThreshold(int value);
    /**
     * @brief setUniquenessRatio
     * @param value
     */
    void setUniquenessRatio(int value);

    /**
     * @brief process
     * @param left
     * @param right
     * @return a SBM matrice compute by left and right picture
     */
    cv::Mat process(cv::Mat left, cv::Mat right);
    /**
     * @brief process display a SBM matrice in main window
     */
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
