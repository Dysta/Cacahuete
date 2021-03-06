#include "sobelbox.h"

SobelBox::SobelBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new SobelProcess((MainWindow *) parent);

    this->createSlider();

    this->_sobelGrid = new QGridLayout();

    this->_sobelGrid->addWidget(this->_picture, 0, 0);

    this->_sobelGrid->addWidget(this->_enableBlurLabel, 1, 0);
    this->_sobelGrid->addWidget(this->_enableBlurSlider, 1, 1);

    this->_sobelGrid->addWidget(this->_sizeHLabel, 2, 0);
    this->_sobelGrid->addWidget(this->_sizeHSlider, 2, 1);

    this->_sobelGrid->addWidget(this->_sizeLLabel, 3, 0);
    this->_sobelGrid->addWidget(this->_sizeLSlider, 3, 1);

    this->_sobelGrid->addWidget(this->_sigmaXLabel, 4, 0);
    this->_sobelGrid->addWidget(this->_sigmaXSlider, 4, 1);

    this->_sobelGrid->addWidget(this->_sigmaYLabel, 5, 0);
    this->_sobelGrid->addWidget(this->_sigmaYSlider, 5, 1);

    this->_sobelGrid->addWidget(this->_dxLabel, 6, 0);
    this->_sobelGrid->addWidget(this->_dxSlider, 6, 1);

    this->_sobelGrid->addWidget(this->_dyLabel, 7, 0);
    this->_sobelGrid->addWidget(this->_dySlider, 7, 1);

    this->_sobelGrid->addWidget(this->_alphaLabel, 8, 0);
    this->_sobelGrid->addWidget(this->_alphaSlider, 8, 1);

    this->_sobelGrid->addWidget(this->_betaLabel, 9, 0);
    this->_sobelGrid->addWidget(this->_betaSlider, 9, 1);

    this->_sobelGrid->addWidget(this->_gammaLabel, 10, 0);
    this->_sobelGrid->addWidget(this->_gammaSlider, 10, 1);

    setLayout(this->_sobelGrid);
}

SobelBox::~SobelBox() {

}

void SobelBox::createSlider() {
    this->_picture = new QComboBox();
    this->_picture->addItem("Image de Gauche");
    this->_picture->addItem("Image de Droite");

    this->_enableBlurLabel = new QLabel("Enable/Disable Blur");
    this->_enableBlurSlider = new QSlider(Qt::Horizontal);
    this->_enableBlurSlider->setRange(0,1);
    this->_enableBlurSlider->setValue(1);

    this->_sizeHLabel = new QLabel("Horizontal blur :");
    this->_sizeHSlider = new QSlider(Qt::Horizontal);
    this->_sizeHSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeHSlider->setTickInterval(10);
    this->_sizeHSlider->setSingleStep(2);
    this->_sizeHSlider->setRange(1, 20);
    this->_sizeHSlider->setValue(3);

    this->_sizeLLabel = new QLabel("Vertical blur :");
    this->_sizeLSlider = new QSlider(Qt::Horizontal);
    this->_sizeLSlider->setTickPosition(QSlider::TicksAbove);
    this->_sizeLSlider->setTickInterval(10);
    this->_sizeLSlider->setSingleStep(2);
    this->_sizeLSlider->setRange(1, 20);
    this->_sizeLSlider->setValue(3);

    this->_sigmaXLabel = new QLabel("Sigma X");
    this->_sigmaXSlider = new QSlider(Qt::Horizontal);
    this->_sigmaXSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaXSlider->setTickInterval(5);
    this->_sigmaXSlider->setSingleStep(1);
    this->_sigmaXSlider->setRange(0, 100);
    this->_sigmaXSlider->setValue(0);

    this->_sigmaYLabel = new QLabel("Sigma Y");
    this->_sigmaYSlider = new QSlider(Qt::Horizontal);
    this->_sigmaYSlider->setTickPosition(QSlider::TicksAbove);
    this->_sigmaYSlider->setTickInterval(5);
    this->_sigmaYSlider->setSingleStep(1);
    this->_sigmaYSlider->setRange(0, 100);
    this->_sigmaYSlider->setValue(0);

    this->_dxLabel = new QLabel("dx");
    this->_dxSlider = new QSlider(Qt::Horizontal);
    this->_dxSlider->setTickPosition(QSlider::TicksAbove);
    this->_dxSlider->setTickInterval(5);
    this->_dxSlider->setSingleStep(1);
    this->_dxSlider->setRange(0, 30);
    this->_dxSlider->setValue(1);

    this->_dyLabel = new QLabel("dy");
    this->_dySlider = new QSlider(Qt::Horizontal);
    this->_dySlider->setTickPosition(QSlider::TicksAbove);
    this->_dySlider->setTickInterval(5);
    this->_dySlider->setSingleStep(1);
    this->_dySlider->setRange(0, 30);
    this->_dySlider->setValue(1);

    this->_alphaLabel = new QLabel("Alpha");
    this->_alphaSlider = new QSlider(Qt::Horizontal);
    this->_alphaSlider->setTickPosition(QSlider::TicksAbove);
    this->_alphaSlider->setTickInterval(5);
    this->_alphaSlider->setSingleStep(1);
    this->_alphaSlider->setRange(0, 30);
    this->_alphaSlider->setValue(1);

    this->_betaLabel = new QLabel("Beta");
    this->_betaSlider = new QSlider(Qt::Horizontal);
    this->_betaSlider->setTickPosition(QSlider::TicksAbove);
    this->_betaSlider->setTickInterval(5);
    this->_betaSlider->setSingleStep(1);
    this->_betaSlider->setRange(0, 30);
    this->_betaSlider->setValue(1);

    this->_gammaLabel = new QLabel("Gamma");
    this->_gammaSlider = new QSlider(Qt::Horizontal);
    this->_gammaSlider->setTickPosition(QSlider::TicksAbove);
    this->_gammaSlider->setTickInterval(5);
    this->_gammaSlider->setSingleStep(1);
    this->_gammaSlider->setRange(0, 30);
    this->_gammaSlider->setValue(0);

    connect(this->_picture, SIGNAL(activated(int)),
            this, SLOT(onImageChange(int)));
    connect(this->_enableBlurSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onBlurSwitch(int)));
    connect(this->_sizeHSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSizeHChange(int)));
    connect(this->_sizeLSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSizeLChange(int)));
    connect(this->_sigmaXSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSigmaXChange(int)));
    connect(this->_sigmaYSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSigmaYChange(int)));
    connect(this->_dxSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onDxChange(int)));
    connect(this->_dySlider, SIGNAL(valueChanged(int)),
            this, SLOT(onDyChange(int)));
    connect(this->_alphaSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onAlphaChange(int)));
    connect(this->_betaSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onBetaChange(int)));
    connect(this->_gammaSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onGammaChange(int)));
}

void SobelBox::onImageChange(int index) {
    this->_process->setImage(index);
}

void SobelBox::onSizeHChange(int value) {
    this->_process->setSizeH(value);
}

void SobelBox::onSizeLChange(int value) {
    this->_process->setSizeL(value);
}

void SobelBox::onSigmaXChange(int value) {
    this->_process->setSigmaX(value);
}

void SobelBox::onSigmaYChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onDxChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onDyChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onAlphaChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onBetaChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onGammaChange(int value) {
    this->_process->setSigmaY(value);
}

void SobelBox::onBlurSwitch(int value) {
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
