#include "tracker.h"

tracker::tracker()
{

}

void tracker::tracking(cv::Mat img){
    cv::Rect trackWindow;
    int hsize = 16;
    float hranges[] = {0, 180};
    const float* phranges = hranges;

    cv::Mat hsv, hue, mask, hist, histimg = cv::Mat::zeros(200 ,320, CV_8UC3), backproj;

    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    int vmin = this->_vmin;
    int vmax = this->_vmax;

    cv::inRange(hsv,
                cv::Scalar(0, this->_smin, MIN(vmin, vmax)),
                cv::Scalar(180, 256, MAX(vmin, vmax)),
                mask);

    int ch[] = {0, 0};
    hue.create(hsv.size(), hsv.depth());
    cv::mixChannels(&hsv, 1, &hue, 1, ch, 1);

    cv::Rect selection(hue.cols/2, hue.rows/2, 0, 0);
    cv::Mat roi(hue, selection), maskroi(mask, selection);

    cv::calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

    trackWindow = selection;

    histimg = cv::Scalar::all(0);
    int binW = histimg.cols/hsize;

    cv::Mat buf(1, hsize, CV_8UC3);
    for(int i = 0; i < hsize; i++)
        buf.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i*180./hsize), 255, 255);
    cv::cvtColor(buf, buf, cv::COLOR_HSV2BGR);

    for(int i = 0; i < hsize; i++){
        int val = cv::saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
        cv::rectangle(histimg,
                      cv::Point(i*binW, histimg.rows),
                      cv::Point((i+1)*binW, histimg.rows - val),
                      cv::Scalar(buf.at<cv::Vec3b>(i)),
                      -1,
                      8);
    }

    cv::calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
    backproj &= mask;
    cv::RotatedRect trackBox = cv::CamShift(backproj,
                                            trackWindow,
                                            cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));

    if(trackWindow.area() <= 1){
        int cols = backproj.cols;
        int rows = backproj.rows;
        int r = (MIN(cols, rows) + 5)/6;
        trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
                               trackWindow.x + r, trackWindow.y + r)
                      & cv::Rect (0, 0, cols, rows);
    }
    cv::ellipse(img, trackBox, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);

    cv::imshow("CamShift", img);
    cv::imshow("Histogram", histimg);
}
