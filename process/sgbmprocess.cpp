#include "sgbmprocess.h"
#include "mainwindow.h"

SGBMProcess::SGBMProcess(MainWindow* parent)
    : _parent(parent), _minDisparity(-64), _numDisparity(192),
      _blockSize(5), _p1(600), _p2(2400), _disp12MaxDiff(10), _preFilter(4), _uniquenessRatio(1),
      _speckleWindowsSize(150), _speckleRange(2), _mode(cv::StereoSGBM::MODE_SGBM)
{

}

void SGBMProcess::process() {
    cv::Mat left = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalLeftPicture(), true); //Création de l'image gauche
    //Si la largeur de l'image (en pixels) est impaire on retire un pixel de largeur sur l'image droite
    cv::Mat right = Utils::Convert::qImage::toCvMat(this->_parent->getOriginalRightPicture(), true); //Création de l'image droite

    if (left.empty() || right.empty()) return; // évite les crashs

    cv::Mat disp = this->process(left, right);

    QImage pic = Utils::Convert::CvMat::toQImage(&disp, true);
    this->_parent->setMatDisp(disp);
    this->_parent->setPictureDisp(pic);
}

cv::Mat SGBMProcess::process(cv::Mat left, cv::Mat right) {
    Q_ASSERT(!left.empty());
    Q_ASSERT(!right.empty());

    cv::Mat gLeft, gRight, disp, disp8;

    cv::cvtColor(left, gLeft, CV_BGR2GRAY);
    cv::cvtColor(right, gRight, CV_BGR2GRAY);

    // default param : -64,192,5,600,2400,10,4,1,150,2,cv::StereoSGBM::MODE_SGBM
    cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(
                this->_minDisparity ,
                this->_numDisparity,
                this->_blockSize,
                this->_p1,
                this->_p2,
                this->_disp12MaxDiff,
                this->_preFilter,
                this->_uniquenessRatio,
                this->_speckleWindowsSize,
                this->_speckleRange,
                this->_mode
                );
    sgbm->compute(gLeft, gRight, disp);


    cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
    return disp8;
}

void SGBMProcess::updatePicture() {
    std::cout << "Update de l'image" << std::endl;
    this->process();
    this->_parent->updateImage();
}

void SGBMProcess::setMinDisp(int value) {
    this->_minDisparity = value;
    this->updatePicture();
}

// value need to be greater than 0 and divisible by 16
void SGBMProcess::setNumDisp(int value) {
    if (value > 0 && value % 16 == 0) {
        this->_numDisparity = value;
        this->updatePicture();
    }
}

// value must be odd and in the range 3-11
void SGBMProcess::setBlockSize(int value) {
    if (value & 1 && value >= 3 && value <= 11) {
        this->_blockSize = value;
        this->updatePicture();
    }
}

void SGBMProcess::setP1(int value) {
    this->_p1 = value;
    this->updatePicture();
}

// value must be > to _p1
void SGBMProcess::setP2(int value) {
    if (value > this->_p1) {
        this->_p2 = value;
        this->updatePicture();
    }
}

void SGBMProcess::setDisp12MaxDiffChange(int value) {
    this->_disp12MaxDiff = value;
    this->updatePicture();
}

void SGBMProcess::setPrefilter(int value) {
    this->_preFilter = value;
    this->updatePicture();
}

// value betwen 5-15 is good
void SGBMProcess::setUniquenessRatio(int value) {
    this->_uniquenessRatio = value;
    this->updatePicture();
}

// 0 disable this feature otherwise 50-200
void SGBMProcess::setSpeckleWindowsSize(int value) {
    if (value < 50 || value > 200){
        this->_speckleWindowsSize = 0;
    } else {
        this->_speckleWindowsSize = value;
    }
    this->updatePicture();
}

// value must be divisible by 16 or be 1 or 2
void SGBMProcess::setSpeckleRange(int value) {
    this->_speckleRange = value;
    this->updatePicture();
}

// 0 or 1 or 2
void SGBMProcess::setMode(int value) {
    this->_mode = value;
    this->updatePicture();
}
