#include "laplacianbox.h"
#include "mainwindow.h"

LaplacianBox::LaplacianBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new LaplacianProcess((MainWindow *) parent);

    this->createSlider();

    this->_laplacianGrid = new QGridLayout();

    this->_laplacianGrid->addWidget(this->_picture, 0, 0);

    this->_laplacianGrid->addWidget(this->_switchBlurLabel, 1, 0);
    this->_laplacianGrid->addWidget(this->_switchBlurSlider, 1, 1);

    this->_laplacianGrid->addWidget(this->_sizeHLabel, 2, 0);
    this->_laplacianGrid->addWidget(this->_sizeHSlider, 2, 1);

    this->_laplacianGrid->addWidget(this->_sizeLLabel, 3, 0);
    this->_laplacianGrid->addWidget(this->_sizeLSlider, 3, 1);

    this->_laplacianGrid->addWidget(this->_sigmaXLabel, 4, 0);
    this->_laplacianGrid->addWidget(this->_sigmaXSlider, 4, 1);

    this->_laplacianGrid->addWidget(this->_sigmaYLabel, 5, 0);
    this->_laplacianGrid->addWidget(this->_sigmaYSlider, 5, 1);

    setLayout(this->_laplacianGrid);
}

LaplacianBox::~LaplacianBox() {

}


void LaplacianBox::createSlider() {
    this->_picture = new QComboBox();
    this->_picture->addItem("Image de Gauche");
    this->_picture->addItem("Image de Droite");

    this->_switchBlurLabel = new QLabel("Enable/Disable Blur");
    this->_switchBlurSlider = new QSlider(Qt::Horizontal);
    this->_switchBlurSlider->setRange(0,1);
    this->_switchBlurSlider->setValue(1);

    this->_sizeHLabel = new QLabel("Horizontal blur :");
    this->_sizeHSlider = new QSlider(Qt::Horizontal);
    this->_sizeHSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeHSlider->setTickInterval(5);
    this->_sizeHSlider->setSingleStep(2);
    this->_sizeHSlider->setRange(1, 20);
    this->_sizeHSlider->setValue(3);

    this->_sizeLLabel = new QLabel("Vertical blur :");
    this->_sizeLSlider = new QSlider(Qt::Horizontal);
    this->_sizeLSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeLSlider->setTickInterval(5);
    this->_sizeLSlider->setSingleStep(2);
    this->_sizeLSlider->setRange(1, 20);
    this->_sizeLSlider->setValue(3);

    this->_sigmaXLabel = new QLabel("Sigma X");
    this->_sigmaXSlider = new QSlider(Qt::Horizontal);
    this->_sigmaXSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaXSlider->setTickInterval(10);
    this->_sigmaXSlider->setSingleStep(1);
    this->_sigmaXSlider->setRange(0, 100);
    this->_sigmaXSlider->setValue(0);


    this->_sigmaYLabel = new QLabel("Sigma Y");
    this->_sigmaYSlider = new QSlider(Qt::Horizontal);
    this->_sigmaYSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaYSlider->setTickInterval(10);
    this->_sigmaYSlider->setSingleStep(1);
    this->_sigmaYSlider->setRange(0, 100);
    this->_sigmaXSlider->setValue(0);

    connect(this->_picture, SIGNAL(activated(int)), this, SLOT(onImageChange(int)));
    connect(this->_sizeHSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeHChange(int)));
    connect(this->_sizeLSlider, SIGNAL(valueChanged(int)), this, SLOT(onSizeLChange(int)));
    connect(this->_sigmaXSlider, SIGNAL(valueChanged(int)), this, SLOT(onSigmaXChange(int)));
    connect(this->_sigmaYSlider, SIGNAL(valueChanged(int)), this, SLOT(onSigmaYChange(int)));
    connect(this->_switchBlurSlider, SIGNAL(valueChanged(int)), this, SLOT(onBlurSwitch(int)));
}

void LaplacianBox::onImageChange(int index) {
    std::cout << "Index : " << std::endl;
    this->_process->setImage(index);
}

void LaplacianBox::onSizeHChange(int value) {
    std::cout << "Size h value : " << value << std::endl;
    this->_process->setSizeH(value);
}

void LaplacianBox::onSizeLChange(int value) {
    std::cout << "Size l value : " << value << std::endl;
    this->_process->setSizeL(value);
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

