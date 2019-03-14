#include "sobelprocess.h"
#include "mainwindow.h"

SobelProcess::SobelProcess(MainWindow* parent)
    : _activeBlur(1), _sizeH(3), _sizeL(3),
      _sigmaX(0), _sigmaY(0), _dx(1), _dy(1),
      _alpha(1), _beta(1), _gamma(0)
{
    this->_parent = parent;
}

void SobelProcess::process() {
    cv::Mat mat, sobel, grey;
    mat = Utils::Convert::qImage::toCvMat(this->_parent->getLeftPicture(), true);
    /// Generate grad_x and grad_y
    cv::Mat gradX, absX;
    cv::Mat gradY, absY;
    // reduce noise by blurring and convert in greyscale
    if (this->_activeBlur)
        cv::GaussianBlur(mat, mat, cv::Size(this->_sizeH, this->_sizeL), this->_sigmaX, this->_sigmaY);
    cv::cvtColor(mat, grey, cv::COLOR_BGR2GRAY);

    // Sobel gradient X
    cv::Sobel(grey, gradX, CV_16S, this->_dx, 0);
    cv::convertScaleAbs(gradX, absX);

    // Sobel gradient Y
    cv::Sobel(grey, gradY, CV_16S, 0, this->_dy);
    cv::convertScaleAbs(gradY, absY);

    // Total gradient
    cv::addWeighted(absX, this->_alpha, absY, this->_beta, this->_gamma, sobel);
    QImage pic = Utils::Convert::CvMat::toQImage(&sobel, true);
    this->_parent->setRightPicture(pic);
}

void SobelProcess::setImage(int value){
    switch (value){
        case 0:
            {
                std::cout << "Switching to left image" << std::endl;
                QImage left = *this->_parent->getOriginalLeftPicture();
                this->_parent->setLeftPicture(left);
                break;
            }
        case 1:
            {
                std::cout << "Switching to right image" << std::endl;
                QImage right = *this->_parent->getOriginalRightPicture();
                this->_parent->setLeftPicture(right);
                break;
            }
    }
    this->process();
    this->_parent->updateImage();
}

void SobelProcess::updatePicture() {
    std::cout << "Update picture" << std::endl;
    this->process();
    this->_parent->updateImage();
}

void SobelProcess::setActiveBlur(bool state) {
    this->_activeBlur = state;
    this->updatePicture();
}

// value must be odd
void SobelProcess::setSizeH(int value) {
    if (value & 1) {
        this->_sizeH = value;
        this->updatePicture();
    }
}

void SobelProcess::setSizeL(int value) {
    if (value & 1) {
        this->_sizeL = value;
        this->updatePicture();
    }
}

void SobelProcess::setSigmaX(int value) {
    this->_sigmaX = value;
    this->updatePicture();
}

void SobelProcess::setSigmaY(int value) {
    this->_sigmaY = value;
    this->updatePicture();
}

void SobelProcess::setDx(int value) {
    this->_dx = value;
    this->updatePicture();
}

void SobelProcess::setDy(int value) {
    this->_dy = value;
    this->updatePicture();
}

void SobelProcess::setAlpha(int value) {
    this->_alpha = value;
    this->updatePicture();
}

void SobelProcess::setBeta(int value) {
    this->_beta = value;
    this->updatePicture();
}
