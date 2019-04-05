#include "trackerbox.h"
#include "mainwindow.h"

TrackerBox::TrackerBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new TrackerProcess((MainWindow*)parent);

    this->createSlider();

    this->_trackGrid = new QGridLayout();

    this->_trackGrid->addWidget(this->_useTracking, 0, 0);

    setLayout(this->_trackGrid);

}

TrackerBox::~TrackerBox(){

}

void TrackerBox::createSlider(){
    this->_useTracking = new QCheckBox("Utiliser le tracking");

    connect(this->_useTracking,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(onTrackChange(int)));
}

void TrackerBox::onTrackChange(int useTracking){
    std::cout << "Tracking set to : " << this->_useTracking->isChecked() << std::endl;
    this->_process->setUseTracking(this->_useTracking->isChecked());
}
