#include "laplacianbox.h"

LaplacianBox::LaplacianBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new LaplacianProcess();

    this->createSlider();

    this->backToMain = new QPushButton("Retour au menu principal");

    this->laplacianGrid = new QGridLayout();

    this->laplacianGrid->addWidget(this->_switchBlurLabel, 0, 0);
    this->laplacianGrid->addWidget(this->_switchBlurSlider, 0, 1);

    this->laplacianGrid->addWidget(this->_sizeHLabel, 1, 0);
    this->laplacianGrid->addWidget(this->_sizeHSlider, 1, 1);

    this->laplacianGrid->addWidget(this->_sizeLLabel, 2, 0);
    this->laplacianGrid->addWidget(this->_sizeLSlider, 2, 1);

    this->laplacianGrid->addWidget(this->_sigmaXLabel, 3, 0);
    this->laplacianGrid->addWidget(this->_sigmaXSlider, 3, 1);

    this->laplacianGrid->addWidget(this->_sigmaYLabel, 4, 0);
    this->laplacianGrid->addWidget(this->_sigmaYSlider, 4, 1);

    this->laplacianGrid->addWidget(this->backToMain, 5, 0);

    setLayout(this->laplacianGrid);
}

LaplacianBox::~LaplacianBox() {

}


void LaplacianBox::createSlider() {
    this->_switchBlurLabel = new QLabel("Enable/Disable Blur");
    this->_switchBlurSlider = new QSlider(Qt::Horizontal);
    this->_switchBlurSlider->setRange(0,1);
    this->_switchBlurSlider->setValue(1);

    this->_sizeHLabel = new QLabel("Horizontal blur :");
    this->_sizeHSlider = new QSlider(Qt::Horizontal);
    this->_sizeHSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeHSlider->setTickInterval(5);
    this->_sizeHSlider->setSingleStep(2);

    this->_sizeLLabel = new QLabel("Vertical blur :");
    this->_sizeLSlider = new QSlider(Qt::Horizontal);
    this->_sizeLSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeLSlider->setTickInterval(5);
    this->_sizeLSlider->setSingleStep(2);
    this->_sizeLSlider->setRange(0, 10);

    this->_sigmaXLabel = new QLabel("Sigma X");
    this->_sigmaXSlider = new QSlider(Qt::Horizontal);
    this->_sigmaXSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaXSlider->setTickInterval(5);
    this->_sigmaXSlider->setSingleStep(1);

    this->_sigmaYLabel = new QLabel("Sigma X");
    this->_sigmaYSlider = new QSlider(Qt::Horizontal);
    this->_sigmaYSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaYSlider->setTickInterval(5);
    this->_sigmaYSlider->setSingleStep(1);

    connect(this->_sizeHSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeHChange(int)));
    connect(this->_sizeLSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeLChange(int)));
    connect(this->_sigmaXSlider, SIGNAL(valueChanged(int)), this, SLOT(onSigmaXChange(int)));
    connect(this->_sigmaYSlider, SIGNAL(valueChanged(int)), this, SLOT(onSigmaYChange(int)));
    connect(this->_switchBlurSlider, SIGNAL(valueChanged(int)), this, SLOT(onBlurSwitch(int)));
}

void LaplacianBox::onSizeHChange(int value) {
    if (value & 1) {
        std::cout << "Size h value : " << value << std::endl;
        this->_process->setSizeH(value);
    }
}

void LaplacianBox::onSizeLChange(int value) {
    if (value & 1) {
        std::cout << "Size l value : " << value << std::endl;
        this->_process->setSizeL(value);
    }
}

void LaplacianBox::onSigmaXChange(int value) {
    std::cout << "Sigma X value : " << value << std::endl;
    this->_process->setSigmaX(value);
}

void LaplacianBox::onSigmaYChange(int value) {
    std::cout << "Sigma Y value : " << value << std::endl;
    this->_process->setSigmaY(value);
}

void LaplacianBox::onBlurSwitch(int value) {
    std::cout << "Blur value : " << value << std::endl;
    this->_process->setActiveBlur((bool) value);

    this->_sizeHLabel->setVisible((bool) value);
    this->_sizeHSlider->setVisible((bool) value);
    this->_sizeLLabel->setVisible((bool) value);
    this->_sizeLSlider->setVisible((bool) value);
    this->_sigmaXLabel->setVisible((bool) value);
    this->_sigmaXSlider->setVisible((bool) value);
    this->_sigmaYLabel->setVisible((bool) value);
    this->_sigmaYSlider->setVisible((bool) value);
}
