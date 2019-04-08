#include "trackerbox.h"
#include "mainwindow.h"

TrackerBox::TrackerBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new TrackerProcess((MainWindow*)parent);

    this->createSlider();

    this->_trackGrid = new QGridLayout();

    this->_trackGrid->addWidget(this->_useTracking, 0, 0);

    this->_trackGrid->addWidget(this->_switchHsizeLabel, 1, 0);
    this->_trackGrid->addWidget(this->_switchHsizeSlider, 1, 1);

    this->_trackGrid->addWidget(this->_switchHranges1Label, 2, 0);
    this->_trackGrid->addWidget(this->_switchHranges1Slider, 2, 1);

    this->_trackGrid->addWidget(this->_switchHranges2Label, 3, 0);
    this->_trackGrid->addWidget(this->_switchHranges2Slider, 3, 1);

    this->_trackGrid->addWidget(this->_switchVminLabel, 4, 0);
    this->_trackGrid->addWidget(this->_switchVminSlider, 4, 1);

    this->_trackGrid->addWidget(this->_switchVmaxLabel, 5, 0);
    this->_trackGrid->addWidget(this->_switchVmaxSlider, 5, 1);

    this->_trackGrid->addWidget(this->_switchSminLabel, 6, 0);
    this->_trackGrid->addWidget(this->_switchSminSlider, 6, 1);

    setLayout(this->_trackGrid);

}

TrackerBox::~TrackerBox(){

}

void TrackerBox::createSlider(){
    this->_useTracking = new QCheckBox("Utiliser le tracking");

    this->_switchHsizeLabel = new QLabel("Hsize");
    this->_switchHsizeSlider = new QSlider(Qt::Horizontal);
    this->_switchHsizeSlider->setRange(2,360);
    this->_switchHsizeSlider->setValue(16);

    this->_switchHranges1Label = new QLabel("Hranges1");
    this->_switchHranges1Slider = new QSlider(Qt::Horizontal);
    this->_switchHranges1Slider->setRange(0,360);
    this->_switchHranges1Slider->setValue(0);

    this->_switchHranges2Label = new QLabel("Hranges2");
    this->_switchHranges2Slider = new QSlider(Qt::Horizontal);
    this->_switchHranges2Slider->setRange(0,360);
    this->_switchHranges2Slider->setValue(180);

    this->_switchVminLabel = new QLabel("Vmin");
    this->_switchVminSlider = new QSlider(Qt::Horizontal);
    this->_switchVminSlider->setRange(0,100);
    this->_switchVminSlider->setValue(10);

    this->_switchVmaxLabel = new QLabel("Vmax");
    this->_switchVmaxSlider = new QSlider(Qt::Horizontal);
    this->_switchVmaxSlider->setRange(0,100);
    this->_switchVmaxSlider->setValue(100);

    this->_switchSminLabel = new QLabel("Smin");
    this->_switchSminSlider = new QSlider(Qt::Horizontal);
    this->_switchSminSlider->setRange(0,255);
    this->_switchSminSlider->setValue(100);

    connect(this->_useTracking,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(onTrackChange()));
    connect(this->_switchHsizeSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHsizeChange(int)));
    connect(this->_switchHranges1Slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHranges1Change(int)));
    connect(this->_switchHranges2Slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHranges2Change(int)));
    connect(this->_switchVminSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onVminChange(int)));
    connect(this->_switchVmaxSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onVmaxChange(int)));
    connect(this->_switchSminSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onSminChange(int)));
}

void TrackerBox::onTrackChange(){
    std::cout << "Tracking set to : " << this->_useTracking->isChecked() << std::endl;
    this->_process->setUseTracking(this->_useTracking->isChecked());
}

void TrackerBox::onHsizeChange(int hsize){
    std::cout << "hsize set to : " << hsize << std::endl;
    this->_process->setHsize(hsize);
}

void TrackerBox::onHranges1Change(int hranges1){
    if(hranges1 < this->_process->getHranges2()){
        std::cout << "hranges1 set to : " << hranges1 << std::endl;
        this->_process->setHranges1(hranges1);
    } else {
        this->_switchHranges1Slider->setValue(hranges1);
    }
}

void TrackerBox::onHranges2Change(int hranges2){
    if(hranges2 > this->_process->getHranges1()){
        std::cout << "hranges2 set to : " << hranges2 << std::endl;
        this->_process->setHranges2(hranges2);
    } else {
        this->_switchHranges2Slider->setValue(hranges2);
    }
}

void TrackerBox::onVminChange(int vmin){
    std::cout << "vmin set to : " << vmin << std::endl;
    this->_process->setVmin(vmin);
}

void TrackerBox::onVmaxChange(int vmax){
    std::cout << "vmax set to : " << vmax << std::endl;
    this->_process->setVmax(vmax);
}

void TrackerBox::onSminChange(int smin){
    std::cout << "smin set to : " << smin << std::endl;
    this->_process->setSmin(smin);
}
