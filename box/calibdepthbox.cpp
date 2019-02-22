#include "calibdepthbox.h"
#include "mainwindow.h"

using namespace std;

CalibDepthBox::CalibDepthBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new CalibDepthProcess((MainWindow *) parent);

    this->createSlider();

    this->_backToMain = new QPushButton("Retour au menu principal");
    this->_calibrationButton = new QPushButton("Faire une calibration");
    this->_undistortButton = new QPushButton("Corriger une image");

    this->_calibGrid = new QGridLayout();

    this->_calibGrid->addWidget(this->_numCornersHLabel, 0, 0);
    this->_calibGrid->addWidget(this->_numCornersHBox, 0, 1);

    this->_calibGrid->addWidget(this->_numCornersVLabel, 1, 0);
    this->_calibGrid->addWidget(this->_numCornersVBox, 1, 1);

    this->_calibGrid->addWidget(this->_calibrationButton, 2, 0);

    this->_calibGrid->addWidget(this->_undistortButton, 3, 0);
    this->_calibGrid->addWidget(this->_depthMapButton, 3, 1);

    this->_calibGrid->addWidget(this->_backToMain, 4, 0);
}

CalibDepthBox::~CalibDepthBox() {

}

void CalibDepthBox::createSlider() {
    this->_numCornersHLabel = new QLabel("Number of corners horizontally");
    this->_numCornersHBox = new QSpinBox();
    this->_numCornersHBox->setMinimum(0);

    this->_numCornersVLabel = new QLabel("Number of corners vertically");
    this->_numCornersVBox = new QSpinBox();
    this->_numCornersVBox->setMinimum(0);

    connect(this->_numCornersHBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersHChange(int)));
    connect(this->_numCornersVBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersVChange(int)));
}

void CalibDepthBox::onNumCornersHChange(int value){
    cout << "Number of corners hotizontally : " << value << endl;
    this->_process->setNumCornersH(value);
}

void CalibDepthBox::onNumCornersVChange(int value){
    cout << "Number of corners vertically : " << value << endl;
    this->_process->setNumCornersV(value);
}
