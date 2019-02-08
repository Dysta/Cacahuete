#include "disparityprocess.h"
#include "mainwindow.h"

DisparityProcess::DisparityProcess(MainWindow* parent)
    : _mode(0)
{
    this->_parent = parent;
}

void DisparityProcess::process() {
    cv::Mat mat, gLeft, gRight, disp, disp8;

    mat = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalPicture(), true);
    //Division de l'image source en deux images gauche et droite
    cv::Mat left = mat.colRange(0, mat.cols/2); //Création de l'image gauche
    int cropping = 0;
    //Si la largeur de l'image (en pixels) est impaire on retire un pixel de largeur sur l'image droite
    if(mat.cols%2 != 0) cropping = 1;
    cv::Mat right = mat.colRange(mat.cols/2+cropping, mat.cols); //Création de l'image droite

    cv::cvtColor(left, gLeft, CV_BGR2GRAY);
    cv::cvtColor(right, gRight, CV_BGR2GRAY);


    if(this->_mode == Utils::Convert::Mode::SBM ){
        cv::Ptr<cv::StereoBM> sbm = cv::StereoBM::create(this->_SBMnumDisparity, this->_SBMblockSize);
        sbm->compute(gLeft, gRight, disp);
    } else if(this->_mode == Utils::Convert::Mode::SGBM){
        // default param : -64,192,5,600,2400,10,4,1,150,2,cv::StereoSGBM::MODE_SGBM
        cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(
                    this->_minDisparity ,
                    this->_SBMnumDisparity,
                    this->_SBMblockSize,
                    this->_p1,
                    this->_p2,
                    this->_disp12MaxDiff,
                    this->_preFilter,
                    this->_UniquenessRatio,
                    this->_speckleWindowsSize,
                    this->_speckleRange,
                    cv::StereoSGBM::MODE_SGBM
                    );
        sgbm->compute(gLeft, gRight, disp);
    }


    cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    QImage pic = Utils::Convert::CvMat::toQImage(&disp8, false);
    this->_parent->setPicture(pic);
}

void DisparityProcess::updatePicture() {
    std::cout << "Update de l'umage" << std::endl;
    this->process();
    this->_parent->updateImage();
}

void DisparityProcess::setMode(int value) {
    _mode = value;
    this->updatePicture();
}
void DisparityProcess::setSBMnumDisp(int value) {
    _SBMnumDisparity = value;
    this->updatePicture();
}
void DisparityProcess::setSBMblockSize(int value) {
    _SBMblockSize = value;
    this->updatePicture();
}

void DisparityProcess::setMinDisp(int value) {
    _minDisparity = value;
    this->updatePicture();
}

void DisparityProcess::setSGBMnumDisp(int value) {
    _SGBMnumDisparity = value;
    this->updatePicture();
}

void DisparityProcess::setSGBMblockSize(int value) {
    _SGBMblockSize = value;
    this->updatePicture();
}

void DisparityProcess::setP1(int value) {
    _p1 = value;
    this->updatePicture();
}

void DisparityProcess::setP2(int value) {
    _p2 = value;
    this->updatePicture();
}

void DisparityProcess::setDisp12MaxDiffChange(int value) {
    _disp12MaxDiff = value;
    this->updatePicture();
}

void DisparityProcess::setPrefilter(int value) {
    _preFilter = value;
    this->updatePicture();
}

void DisparityProcess::setUniquenessRatio(int value) {
    _UniquenessRatio = value;
    this->updatePicture();
}

void DisparityProcess::setSpeckleWindowsSize(int value) {
    _speckleWindowsSize = value;
    this->updatePicture();
}

void DisparityProcess::setSpeckleRange(int value) {
    _speckleRange = value;
    this->updatePicture();
}

void DisparityProcess::setSGBMmode(int value) {
    _SGBMmode = value;
    this->updatePicture();
}
