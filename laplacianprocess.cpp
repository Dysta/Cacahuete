#include "laplacianprocess.h"

LaplacianProcess::LaplacianProcess()
    : _activeBlur(0), _sizeH(0), _sizeL(0), _sigmaX(0), _sigmaY(0)
{

}

void LaplacianProcess::updatePicture() {
    std::cout << "Update de l'image" << std::endl;
}

void LaplacianProcess::setActiveBlur(bool state) {
    this->_activeBlur = state;
    this->updatePicture();
}

void LaplacianProcess::setSizeH(int value) {
    this->_sizeH = value;
    this->updatePicture();
}

void LaplacianProcess::setSizeL(int value) {
    this->_sizeL = value;
    this->updatePicture();
}

void LaplacianProcess::setSigmaX(int value) {
    this->_sigmaX = value;
    this->updatePicture();
}

void LaplacianProcess::setSigmaY(int value) {
    this->_sigmaY = value;
    this->updatePicture();
}
