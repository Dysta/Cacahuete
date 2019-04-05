#include "disparityprocess.h"
#include "mainwindow.h"

DisparityProcess::DisparityProcess(MainWindow* parent)
    : _parent(parent), _mode(0)
{
    this->_SBMProcess = new SBMProcess(parent);
    this->_SGBMProcess = new SGBMProcess(parent);
}

void DisparityProcess::updatePicture() {
    std::cout << "Update de l'image" << std::endl;
    if (this->_mode == DisparityProcess::SBM)
        this->_SBMProcess->process();
    else if (this->_mode == DisparityProcess::SGBM)
        this->_SGBMProcess->process();

    this->_parent->updateImage();
}

void DisparityProcess::process() {
    if (this->_mode == DisparityProcess::SBM)
        this->_SBMProcess->process();
    else if (this->_mode == DisparityProcess::SGBM)
        this->_SGBMProcess->process();
}

cv::Mat DisparityProcess::process(cv::Mat left, cv::Mat right) {
    if (this->_mode == DisparityProcess::SBM)
        return this->_SBMProcess->process(left, right);
    else if (this->_mode == DisparityProcess::SGBM)
        return this->_SGBMProcess->process(left, right);
}

SGBMProcess *DisparityProcess::getSGBMProcess() const
{
    return _SGBMProcess;
}

SBMProcess *DisparityProcess::getSBMProcess() const
{
    return _SBMProcess;
}

void DisparityProcess::setMode(int value) {
    _mode = value;
    this->updatePicture();
}
