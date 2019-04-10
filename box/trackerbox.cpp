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

    this->_trackGrid->addWidget(this->_switchHrangesLabel, 2, 0);
    this->_trackGrid->addWidget(this->_switchHrangesSlider, 2, 1);

    this->_trackGrid->addWidget(this->_switchVminLabel, 3, 0);
    this->_trackGrid->addWidget(this->_switchVminSlider, 3, 1);

    this->_trackGrid->addWidget(this->_switchVmaxLabel, 4, 0);
    this->_trackGrid->addWidget(this->_switchVmaxSlider, 4, 1);

    this->_trackGrid->addWidget(this->_switchSminLabel, 5, 0);
    this->_trackGrid->addWidget(this->_switchSminSlider, 5, 1);

    this->_trackGrid->addWidget(this->_switchXLabel, 6, 0);
    this->_trackGrid->addWidget(this->_switchXSlider, 6, 1);

    this->_trackGrid->addWidget(this->_switchYLabel, 7, 0);
    this->_trackGrid->addWidget(this->_switchYSlider, 7, 1);

    this->_trackGrid->addWidget(this->_switchWidthLabel, 8, 0);
    this->_trackGrid->addWidget(this->_switchWidthSlider, 8, 1);

    this->_trackGrid->addWidget(this->_switchHeightLabel, 9, 0);
    this->_trackGrid->addWidget(this->_switchHeightSlider, 9, 1);

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

    this->_switchHrangesLabel = new QLabel("Tolerance intensite lumineuse");
    this->_switchHrangesSlider = new QSlider(Qt::Horizontal);
    this->_switchHrangesSlider->setRange(1,360);
    this->_switchHrangesSlider->setValue(180);

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

    this->_switchXLabel = new QLabel("Position en X :");
    this->_switchXSlider = new QSlider(Qt::Horizontal);
    this->_switchXSlider->setRange(0,0);
    this->_switchXSlider->setValue(0);

    this->_switchYLabel = new QLabel("Position en Y :");
    this->_switchYSlider = new QSlider(Qt::Horizontal);
    this->_switchYSlider->setRange(0,0);
    this->_switchYSlider->setValue(0);

    this->_switchWidthLabel = new QLabel("Largeur de la portion :");
    this->_switchWidthSlider = new QSlider(Qt::Horizontal);
    this->_switchWidthSlider->setRange(1,255);
    this->_switchWidthSlider->setValue(50);

    this->_switchHeightLabel = new QLabel("Hauteur de la portion :");
    this->_switchHeightSlider = new QSlider(Qt::Horizontal);
    this->_switchHeightSlider->setRange(1,255);
    this->_switchHeightSlider->setValue(50);

    connect(this->_useTracking,
            SIGNAL(stateChanged(int)),
            this,
            SLOT(onTrackChange()));
    connect(this->_switchHsizeSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHsizeChange(int)));
    connect(this->_switchHrangesSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHrangesChange(int)));
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
    connect(this->_switchXSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onXChange(int)));
    connect(this->_switchYSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onYChange(int)));
    connect(this->_switchWidthSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onWidthChange(int)));
    connect(this->_switchHeightSlider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onHeightChange(int)));
}

QSlider *TrackerBox::getSwitchYSlider() const
{
    return _switchYSlider;
}

QSlider *TrackerBox::getSwitchXSlider() const
{
    return _switchXSlider;
}

TrackerProcess *TrackerBox::getProcess() const
{
    return _process;
}

void TrackerBox::onTrackChange(){
    std::cout << "Tracking set to : " << this->_useTracking->isChecked() << std::endl;
    this->_process->setUseTracking(this->_useTracking->isChecked());
}

void TrackerBox::onHsizeChange(int hsize){
    std::cout << "hsize set to : " << hsize << std::endl;
    this->_process->setHsize(hsize);
}

void TrackerBox::onHrangesChange(int hranges){
    std::cout << "hranges2 set to : " << hranges << std::endl;
    this->_process->setHranges(hranges);
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

void TrackerBox::onXChange(int x){
    if(x + this->_process->getWidth() >= this->_process->getParent()->getOriginalLeftPicture()->width()){
        this->_process->setWidth((x + this->_process->getWidth()) - this->_process->getParent()->getOriginalLeftPicture()->width());
        this->_switchWidthSlider->setValue((x + this->_process->getWidth()) - this->_process->getParent()->getOriginalLeftPicture()->width());
    }
    std::cout << "x position set to : " << x << std::endl;
    this->_process->setX(x);
}

void TrackerBox::onYChange(int y){
    if(y + this->_process->getHeight() >= this->_process->getParent()->getOriginalLeftPicture()->height()){
        this->_process->setHeight((y + this->_process->getHeight()) - this->_process->getParent()->getOriginalLeftPicture()->height());
        this->_switchHeightSlider->setValue((y + this->_process->getHeight()) - this->_process->getParent()->getOriginalLeftPicture()->height());
    }
    std::cout << "y position set to : " << y << std::endl;
    this->_process->setY(y);
}

void TrackerBox::onWidthChange(int width){
    if(this->_process->getX() + width < this->_process->getParent()->getOriginalLeftPicture()->width()){
        std::cout << "smin set to : " << width << std::endl;
        this->_process->setWidth(width);
    }
}

void TrackerBox::onHeightChange(int height){
    if(this->_process->getY() + height < this->_process->getParent()->getOriginalLeftPicture()->height()){
        std::cout << "smin set to : " << height << std::endl;
        this->_process->setHeight(height);
    }
}
