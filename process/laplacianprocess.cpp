#include "laplacianprocess.h"
#include "mainwindow.h"

LaplacianProcess::LaplacianProcess(MainWindow* parent)
    : _activeBlur(1), _sizeH(3), _sizeL(3), _sigmaX(0), _sigmaY(0)
{
    this->_parent = parent;
}

void LaplacianProcess::process() {
    cv::Mat mat, laplacian, grey, absLaplacian;
    mat = Utils::Convert::qImage::toCvMat(this->_parent->getLeftPicture(), true);
    if (mat.empty()) return;
    // reduce noise by blurring and convert in greyscale
    if (this->_activeBlur)
        cv::GaussianBlur(mat, mat, cv::Size(this->_sizeH, this->_sizeL), this->_sigmaX, this->_sigmaY);
    cv::cvtColor(mat, grey, cv::COLOR_BGR2GRAY);
    cv::Laplacian(grey, laplacian, CV_16S);
    cv::convertScaleAbs(laplacian, absLaplacian);
    QImage pic = Utils::Convert::CvMat::toQImage(&absLaplacian, true);
    this->_parent->setRightPicture(pic);
}

void LaplacianProcess::setImage(int value){
    switch (value){
        case 0:
            {
                QImage left = *this->_parent->getOriginalLeftPicture();
                this->_parent->setLeftPicture(left);
                break;
            }
        case 1:
            {
                QImage right = *this->_parent->getOriginalRightPicture();
                this->_parent->setLeftPicture(right);
                break;
            }
    }
    this->process();
    this->_parent->updateImage();
}

void LaplacianProcess::updatePicture() {
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
