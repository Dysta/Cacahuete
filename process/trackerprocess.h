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
    void process(cv::Mat img);

private:
    MainWindow* _parent;

    bool _useTracking;

    int _vmin = 10;
    int _vmax = 100;
    int _smin = 100;
};

#endif // TRACKERPROCESS_H
