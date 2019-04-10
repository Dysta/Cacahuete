#ifndef TRACKERPROCESS_H
#define TRACKERPROCESS_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>

class MainWindow;

class TrackerProcess
{
public:
    TrackerProcess(MainWindow* parent);
    void setUseTracking(bool useTracking);
    void process();
    cv::Mat process(cv::Mat img);
    int checkMovement(cv::RotatedRect trackBox);
    int checkMovementDepth(cv::RotatedRect trackBox, cv::Mat depthMap);

    void updatePicture();
    void setHsize(int hsize);
    void setHranges(float hranges);
    float getHranges();
    void setVmin(int vmin);
    void setVmax(int vmax);
    void setSmin(int smin);
    void setX(int x);
    int getX();
    void setY(int y);
    int getY();
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();
    void setTrackBox(cv::RotatedRect trackBox);
    cv::RotatedRect getTrackBox();
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
