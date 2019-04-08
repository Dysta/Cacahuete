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

    void updatePicture();
    void setHsize(int hsize);
    void setHranges1(float hranges1);
    void setHranges2(float hranges2);
    float getHranges1();
    float getHranges2();
    void setVmin(int vmin);
    void setVmax(int vmax);
    void setSmin(int smin);
private:
    MainWindow* _parent;

    bool _useTracking;

    int _vmin;
    int _vmax;
    int _smin;
    int _hsize;
    float _hranges1;
    float _hranges2;
};

#endif // TRACKERPROCESS_H
