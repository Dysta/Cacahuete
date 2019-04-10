#ifndef TRACKERPROCESS_H
#define TRACKERPROCESS_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>

class MainWindow;

class TrackerProcess
{
public:
    TrackerProcess(MainWindow* parent);
    /**
     * @brief setUseTracking
     * @param useTracking
     */
    void setUseTracking(bool useTracking);
    /**
     * @brief process
     */
    void process();
    /**
     * @brief process
     * @param img
     * @return
     */
    cv::Mat process(cv::Mat img);
    /**
     * @brief checkMovement
     * @param trackBox
     * @return
     */
    int checkMovement(cv::RotatedRect trackBox);
    int checkMovementDepth(cv::RotatedRect trackBox, cv::Mat depthMap);

    /**
     * @brief updatePicture
     */
    void updatePicture();
    /**
     * @brief setHsize
     * @param hsize
     */
    void setHsize(int hsize);
    /**
     * @brief setHranges
     * @param hranges
     */
    void setHranges(float hranges);
    /**
     * @brief getHranges
     * @return
     */
    float getHranges();
    /**
     * @brief setVmin
     * @param vmin
     */
    void setVmin(int vmin);
    /**
     * @brief setVmax
     * @param vmax
     */
    void setVmax(int vmax);
    /**
     * @brief setSmin
     * @param smin
     */
    void setSmin(int smin);
    /**
     * @brief setX
     * @param x
     */
    void setX(int x);
    /**
     * @brief getX
     * @return
     */
    int getX();
    /**
     * @brief setY
     * @param y
     */
    void setY(int y);
    /**
     * @brief getY
     * @return
     */
    int getY();
    /**
     * @brief setWidth
     * @param width
     */
    void setWidth(int width);
    /**
     * @brief getWidth
     * @return the width
     */
    int getWidth();
    /**
     * @brief setHeight
     * @param height
     */
    void setHeight(int height);
    /**
     * @brief getHeight
     * @return the height
     */
    int getHeight();
    /**
     * @brief setTrackBox
     * @param trackBox
     */
    void setTrackBox(cv::RotatedRect trackBox);
    /**
     * @brief getTrackBox
     * @return the current rectangle of  the tracked object
     */
    cv::RotatedRect getTrackBox();
    /**
     * @brief getParent
     * @return the parent
     */
    MainWindow *getParent() const;

private:
    MainWindow* _parent;

    bool _useTracking;

    cv::RotatedRect _trackBox;
    int _hsize;
    float _hranges;
    int _vmin;
    int _vmax;
    int _smin;
    int _width;
    int _height;
    int _x;
    int _y;
};

#endif // TRACKERPROCESS_H
