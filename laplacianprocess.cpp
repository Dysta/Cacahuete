#include "laplacianprocess.h"
#include "mainwindow.h"

LaplacianProcess::LaplacianProcess(MainWindow* parent)
    : _activeBlur(1), _sizeH(3), _sizeL(3), _sigmaX(0), _sigmaY(0)
{
    this->_parent = parent;
}

void LaplacianProcess::process() {
    cv::Mat mat, laplacian, grey, absLaplacian;
    mat = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalPicture(), true);
    // reduce noise by blurring and convert in greyscale
    if (this->_activeBlur)
        cv::GaussianBlur(mat, mat, cv::Size(this->_sizeH, this->_sizeL), this->_sigmaX, this->_sigmaY);
    cv::cvtColor(mat, grey, cv::COLOR_BGR2GRAY);
    cv::Laplacian(grey, laplacian, CV_16S);
    cv::convertScaleAbs(laplacian, absLaplacian);
    QImage pic = Utils::Convert::CvMat::toQImage(&absLaplacian, false);
    this->_parent->setPicture(pic);
}

void LaplacianProcess::updatePicture() {
    std::cout << "Update de l'image" << std::endl;
    this->process();
    this->_parent->updateImage();
}

void LaplacianProcess::setActiveBlur(bool state) {
    this->_activeBlur = state;
    this->updatePicture();
}

// value must be odd
void LaplacianProcess::setSizeH(int value) {
    if (value & 1) {
        this->_sizeH = value;
        this->updatePicture();
    }
}

// value must be odd
void LaplacianProcess::setSizeL(int value) {
    if (value & 1) {
        this->_sizeL = value;
        this->updatePicture();
    }
}

void LaplacianProcess::setSigmaX(int value) {
    this->_sigmaX = value;
    this->updatePicture();
}

void LaplacianProcess::setSigmaY(int value) {
    this->_sigmaY = value;
    this->updatePicture();
}
