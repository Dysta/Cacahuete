#ifndef TRACKER_H
#define TRACKER_H

#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>

class tracker
{


public:
    tracker();

private:
    void tracking(cv::Mat img);

    int _vmin = 10;
    int _vmax = 256;
    int _smin = 30;
};

#endif // TRACKER_H
