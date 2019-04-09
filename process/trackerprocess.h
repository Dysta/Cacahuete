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
    void process(cv::Mat img);
    MainWindow* _parent;

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
private:

    bool _useTracking;

    int _vmin;
    int _vmax;
    int _smin;
    int _hsize;
    float _hranges;
    int _x;
    int _y;
    int _width;
    int _height;
};

#endif // TRACKERPROCESS_H
