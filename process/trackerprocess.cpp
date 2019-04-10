#include "trackerprocess.h"
#include "mainwindow.h"

TrackerProcess::TrackerProcess(MainWindow* parent)
    : _hsize(16), _hranges(180), _vmin(10), _vmax(100), _smin(100), _width(50), _height(50), _x(0), _y(0)
{
    this->_parent = parent;
}

void TrackerProcess::process(){
    cv::Mat img = Utils::Convert::qImage::toCvMat(this->_parent->getLeftPicture(), true), track;

    track = this->process(img);

    QImage pic = Utils::Convert::CvMat::toQImage(&track, true);
    this->_parent->setMatTrack(track);
    this->_parent->setPictureTrack(pic);
}

cv::Mat TrackerProcess::process(cv::Mat img){

    cv::Rect trackWindow;
    int hsize = _hsize;
    float hranges[] = {0, _hranges};
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

    cv::Rect selection(this->_x, this->_y, this->_width, this->_height);
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
    std::cout << "Getting CamShift" << std::endl;
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

    //cv::imshow("tracking", img);

    return img;
}

void TrackerProcess::updatePicture() {
    if(_useTracking && !(this->_parent->getOriginalLeftPicture()->isNull())){
        std::cout << "Update de l'image" << std::endl;
        this->process();
        this->_parent->updateImage();
    }
}

void TrackerProcess::setUseTracking(bool useTracking){
    this->_useTracking = useTracking;
    this->updatePicture();
}

void TrackerProcess::setHsize(int hsize){
    this->_hsize = hsize;
    this->updatePicture();
}

void TrackerProcess::setHranges(float hranges){
    this->_hranges = hranges;
    this->updatePicture();
}

float TrackerProcess::getHranges(){
    return this->_hranges;
}

void TrackerProcess::setVmin(int vmin){
    this->_vmin = vmin;
    this->updatePicture();
}

void TrackerProcess::setVmax(int vmax){
    this->_vmax = vmax;
    this->updatePicture();
}

void TrackerProcess::setSmin(int smin){
    this->_smin = smin;
    this->updatePicture();
}

void TrackerProcess::setX(int x){
    this->_x = x;
    this->updatePicture();
}

int TrackerProcess::getX(){
    return this->_x;
}

void TrackerProcess::setY(int y){
    this->_y = y;
    this->updatePicture();
}

int TrackerProcess::getY(){
    return this->_y;
}

void TrackerProcess::setWidth(int width){
    this->_width = width;
    this->updatePicture();
}

int TrackerProcess::getWidth(){
    return this->_width;
}

void TrackerProcess::setHeight(int height){
    this->_height = height;
    this->updatePicture();
}

int TrackerProcess::getHeight(){
    return this->_height;
}

MainWindow *TrackerProcess::getParent() const
{
    return _parent;
}
