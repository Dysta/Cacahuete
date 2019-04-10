#include "sbmprocess.h"
#include "mainwindow.h"

SBMProcess::SBMProcess(MainWindow* parent)
    : _parent(parent), _numDisparity(64), _blockSize(29), _preFilterCap(39), _preFilterSize(31), _preFilterType(0),
      _roi1(0), _roi2(0), _textureThreshold(219), _uniquenessRatio(3)
{

}

void SBMProcess::process() {
    cv::Mat left = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalLeftPicture(), true); //Création de l'image gauche
    //Si la largeur de l'image (en pixels) est impaire on retire un pixel de largeur sur l'image droite
    cv::Mat right = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalRightPicture(), true); //Création de l'image droite

    if (left.empty() || right.empty()) return; // évite les crashs

    cv::Mat disp = this->process(left, right);

    QImage pic = Utils::Convert::CvMat::toQImage(&disp, true);
    this->_parent->setMatDisp(disp);
    this->_parent->setPictureDisp(pic);
}

cv::Mat SBMProcess::process(cv::Mat left, cv::Mat right) {
    Q_ASSERT(!left.empty());
    Q_ASSERT(!right.empty());

    cv::Mat gLeft, gRight, disp, disp8;

    cv::cvtColor(left, gLeft, CV_BGR2GRAY);
    cv::cvtColor(right, gRight, CV_BGR2GRAY);

    cv::Ptr<cv::StereoBM> sbm = cv::StereoBM::create(this->_numDisparity, this->_blockSize);
    sbm->setPreFilterCap(this->_preFilterCap);
    sbm->setPreFilterSize(this->_preFilterSize);
    sbm->setPreFilterType(this->_preFilterType);
    sbm->setROI1(cv::Rect(this->_roi1, this->_roi1, this->_roi1, this->_roi1));
    sbm->setROI2(cv::Rect(this->_roi2, this->_roi2, this->_roi2, this->_roi2));
    sbm->setTextureThreshold(this->_textureThreshold);
    sbm->setUniquenessRatio(this->_uniquenessRatio);

    sbm->compute(gLeft, gRight, disp);

    cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    return disp8;
}

void SBMProcess::updatePicture() {
    std::cout << "Update de l'image" << std::endl;
    this->process();
    this->_parent->updateImage();
}

// value must be positive and divisible by 16
void SBMProcess::setNumDisp(int value) {
    if (value > 0 && value % 16 == 0) {
        this->_numDisparity = value;
        this->updatePicture();
    }
}

// value must be odd
void SBMProcess::setBlockSize(int value) {
    if (value & 1) {
        this->_blockSize = value;
        this->updatePicture();
    }
}

void SBMProcess::setPrefilterCap(int value) {
    this->_preFilterCap = value;
    this->updatePicture();
}

// odd
void SBMProcess::setPrefilterSize(int value) {
    if (value & 1) {
        this->_preFilterSize = value;
        this->updatePicture();
    }
}

void SBMProcess::setPrefilterType(int value) {
    this->_preFilterType = value;
    this->updatePicture();
}

void SBMProcess::setRoi1(int value) {
    this->_roi1 = value;
    this->updatePicture();
}

void SBMProcess::setRoi2(int value) {
    this->_roi2 = value;
    this->updatePicture();
}

void SBMProcess::setTextureThreshold(int value) {
    this->_textureThreshold = value;
    this->updatePicture();
}

void SBMProcess::setUniquenessRatio(int value) {
    this->_uniquenessRatio = value;
    this->updatePicture();
}

