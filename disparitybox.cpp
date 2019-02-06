#include "disparitybox.h"
#include "mainwindow.h"

DisparityBox::DisparityBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new DisparityProcess((MainWindow *) parent);

    this->createSlider();

    this->_backToMain = new QPushButton("Retour au menu principal");

    this->_disparityGrid = new QGridLayout();

    this->_disparityGrid->addWidget(this->_mode, 0, 0);


    this->_disparityGrid->addWidget(this->_SBMnumDisparityLabel, 1, 0);
    this->_disparityGrid->addWidget(this->_SBMnumDisparitySlider, 1, 1);

    this->_disparityGrid->addWidget(this->_SBMblockSizeLabel, 2, 0);
    this->_disparityGrid->addWidget(this->_SBMblockSizeSlider, 2, 1);

    this->_disparityGrid->addWidget(this->_minDisparityLabel, 3, 0);
    this->_disparityGrid->addWidget(this->_minDisparitySlider, 3, 1);

    this->_disparityGrid->addWidget(this->_SGBMnumDisparityLabel, 4, 0);
    this->_disparityGrid->addWidget(this->_SGBMnumDisparitySlider, 4, 1);

    this->_disparityGrid->addWidget(this->_SGBMblockSizeLabel, 5, 0);
    this->_disparityGrid->addWidget(this->_SGBMblockSizeSlider, 5, 1);

    this->_disparityGrid->addWidget(this->_p1Label, 6, 0);
    this->_disparityGrid->addWidget(this->_p1Slider, 6, 1);

    this->_disparityGrid->addWidget(this->_p2Label, 7, 0);
    this->_disparityGrid->addWidget(this->_p2Slider, 7, 1);

    this->_disparityGrid->addWidget(this->_disp12MaxDiffLabel, 8, 0);
    this->_disparityGrid->addWidget(this->_disp12MaxDiffSlider, 8, 1);

    this->_disparityGrid->addWidget(this->_preFilterLabel, 9, 0);
    this->_disparityGrid->addWidget(this->_preFilterSlider, 9, 1);

    this->_disparityGrid->addWidget(this->_uniquenessRatioLabel, 10, 0);
    this->_disparityGrid->addWidget(this->_uniquenessRatioSlider, 10, 1);

    this->_disparityGrid->addWidget(this->_speckleWindowsSizeLabel, 11, 0);
    this->_disparityGrid->addWidget(this->_speckleWindowsSizeSlider, 11, 1);

    this->_disparityGrid->addWidget(this->_speckleRangeLabel, 12, 0);
    this->_disparityGrid->addWidget(this->_speckleRangeSlider, 12, 1);

    this->_disparityGrid->addWidget(this->_SGBMmodeLabel, 13, 0);
    this->_disparityGrid->addWidget(this->_SGBMmodeCombo, 13, 1);

    this->_disparityGrid->addWidget(this->_backToMain, 14, 0);

    setLayout(this->_disparityGrid);

}

DisparityBox::~DisparityBox() {

}

void DisparityBox::createSlider() {
    this->_mode = new QComboBox();
    this->_mode->addItem("Mode SBM");
    this->_mode->addItem("Mode SGBM");

    this->_SBMblockSizeLabel = new QLabel("Block size");    this->_SBMblockSizeSlider = new QSlider(Qt::Horizontal);
    this->_SBMblockSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_SBMblockSizeSlider->setTickInterval(5);
    this->_SBMblockSizeSlider->setSingleStep(1);
    this->_SBMblockSizeSlider->setRange(0, 10);
    this->_SBMblockSizeSlider->setValue(0);

    this->_SBMnumDisparityLabel = new QLabel("Disparity Number");
    this->_SBMnumDisparitySlider = new QSlider(Qt::Horizontal);
    this->_SBMnumDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_SBMnumDisparitySlider->setTickInterval(5);
    this->_SBMnumDisparitySlider->setSingleStep(1);
    this->_SBMnumDisparitySlider->setRange(0, 10);
    this->_SBMnumDisparitySlider->setValue(0);

    this->_minDisparityLabel = new QLabel("Minimum disparity Number");
    this->_minDisparitySlider = new QSlider(Qt::Horizontal);
    this->_minDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_minDisparitySlider->setTickInterval(5);
    this->_minDisparitySlider->setSingleStep(1);
    this->_minDisparitySlider->setRange(0, 10);
    this->_minDisparitySlider->setValue(0);

    this->_SGBMnumDisparityLabel = new QLabel("Disparity Number");
    this->_SGBMnumDisparitySlider = new QSlider(Qt::Horizontal);
    this->_SGBMnumDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_SGBMnumDisparitySlider->setTickInterval(5);
    this->_SGBMnumDisparitySlider->setSingleStep(1);
    this->_SGBMnumDisparitySlider->setRange(0, 10);
    this->_SGBMnumDisparitySlider->setValue(0);

    this->_SGBMblockSizeLabel = new QLabel("Block size");
    this->_SGBMblockSizeSlider = new QSlider(Qt::Horizontal);
    this->_SGBMblockSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_SGBMblockSizeSlider->setTickInterval(5);
    this->_SGBMblockSizeSlider->setSingleStep(1);
    this->_SGBMblockSizeSlider->setRange(0, 10);
    this->_SGBMblockSizeSlider->setValue(0);

    this->_p1Label = new QLabel("P1");
    this->_p1Slider = new QSlider(Qt::Horizontal);
    this->_p1Slider->setTickPosition(QSlider::TicksAbove);
    this->_p1Slider->setTickInterval(5);
    this->_p1Slider->setSingleStep(1);
    this->_p1Slider->setRange(0, 10);
    this->_p1Slider->setValue(0);

    this->_p2Label = new QLabel("P2");
    this->_p2Slider = new QSlider(Qt::Horizontal);
    this->_p2Slider->setTickPosition(QSlider::TicksAbove);
    this->_p2Slider->setTickInterval(5);
    this->_p2Slider->setSingleStep(1);
    this->_p2Slider->setRange(0, 10);
    this->_p2Slider->setValue(0);

    this->_disp12MaxDiffLabel = new QLabel("Disparity 12 max Diff");
    this->_disp12MaxDiffSlider = new QSlider(Qt::Horizontal);
    this->_disp12MaxDiffSlider->setTickPosition(QSlider::TicksAbove);
    this->_disp12MaxDiffSlider->setTickInterval(5);
    this->_disp12MaxDiffSlider->setSingleStep(1);
    this->_disp12MaxDiffSlider->setRange(0, 10);
    this->_disp12MaxDiffSlider->setValue(0);

    this->_preFilterLabel = new QLabel("Pre Filter");
    this->_preFilterSlider = new QSlider(Qt::Horizontal);
    this->_preFilterSlider->setTickPosition(QSlider::TicksAbove);
    this->_preFilterSlider->setTickInterval(5);
    this->_preFilterSlider->setSingleStep(1);
    this->_preFilterSlider->setRange(0, 10);
    this->_preFilterSlider->setValue(0);

    this->_uniquenessRatioLabel = new QLabel("Uniqueness Ration");
    this->_uniquenessRatioSlider = new QSlider(Qt::Horizontal);
    this->_uniquenessRatioSlider->setTickPosition(QSlider::TicksAbove);
    this->_uniquenessRatioSlider->setTickInterval(5);
    this->_uniquenessRatioSlider->setSingleStep(1);
    this->_uniquenessRatioSlider->setRange(0, 10);
    this->_uniquenessRatioSlider->setValue(0);

    this->_speckleWindowsSizeLabel = new QLabel("Speckle Window Size");
    this->_speckleWindowsSizeSlider = new QSlider(Qt::Horizontal);
    this->_speckleWindowsSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_speckleWindowsSizeSlider->setTickInterval(5);
    this->_speckleWindowsSizeSlider->setSingleStep(1);
    this->_speckleWindowsSizeSlider->setRange(0, 10);
    this->_speckleWindowsSizeSlider->setValue(0);

    this->_speckleRangeLabel = new QLabel("Speckle Range");
    this->_speckleRangeSlider = new QSlider(Qt::Horizontal);
    this->_speckleRangeSlider->setTickPosition(QSlider::TicksAbove);
    this->_speckleRangeSlider->setTickInterval(5);
    this->_speckleRangeSlider->setSingleStep(1);
    this->_speckleRangeSlider->setRange(0, 10);
    this->_speckleRangeSlider->setValue(0);

    this->_SGBMmodeLabel = new QLabel("SGBM Mode");
    this->_SGBMmodeCombo = new QComboBox();
    this->_SGBMmodeCombo->addItem("MODE_SGBM");
    this->_SGBMmodeCombo->addItem("MODE_SGBM_3WAY");
    this->_SGBMmodeCombo->addItem("MODE_HH");
    this->_SGBMmodeCombo->addItem("MODE_HH4");

    connect(this->_mode, SIGNAL(activated(int)),
            this, SLOT(onModeChange(int)));
    connect(this->_SBMnumDisparitySlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSBMnumDisparityChange(int)));
    connect(this->_SBMblockSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSBMblockSizeChange(int)));
    connect(this->_minDisparitySlider, SIGNAL(valueChanged(int)),
            this, SLOT(onMinDisparityChange(int)));
    connect(this->_SGBMnumDisparitySlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSGBMnumDisparityChange(int)));
    connect(this->_SGBMblockSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSGBMblockSizeChange(int)));
    connect(this->_p1Slider, SIGNAL(valueChanged(int)),
            this, SLOT(onP1Change(int)));
    connect(this->_p2Slider, SIGNAL(valueChanged(int)),
            this, SLOT(onP2Change(int)));
    connect(this->_disp12MaxDiffSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onDisp12MaxDiffChange(int)));
    connect(this->_preFilterSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onPreFilterChange(int)));
    connect(this->_uniquenessRatioSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onUniquenessRationChange(int)));
    connect(this->_speckleWindowsSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSpeckleWindowsSizeChange(int)));
    connect(this->_speckleRangeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSpeckleRangeChange(int)));
    connect(this->_SGBMmodeCombo, SIGNAL(activated(int)),
            this, SLOT(onSGBMmodeChange(int)));
}

void DisparityBox::onModeChange(int index) {
    std::cout << "Mode : " << index << std::endl;

    this->_SBMnumDisparityLabel->setVisible((bool) !index);
    this->_SBMnumDisparitySlider->setVisible((bool) !index);
    this->_SBMblockSizeLabel->setVisible((bool) !index);
    this->_SBMblockSizeSlider->setVisible((bool) !index);

    this->_minDisparityLabel->setVisible((bool) index);
    this->_minDisparitySlider->setVisible((bool) index);
    this->_SGBMnumDisparityLabel->setVisible((bool) index);
    this->_SGBMnumDisparitySlider->setVisible((bool) index);
    this->_SGBMblockSizeLabel->setVisible((bool) index);
    this->_SGBMblockSizeSlider->setVisible((bool) index);
    this->_p1Label->setVisible((bool) index);
    this->_p1Slider->setVisible((bool) index);
    this->_p2Label->setVisible((bool) index);
    this->_p2Slider->setVisible((bool) index);
    this->_disp12MaxDiffLabel->setVisible((bool) index);
    this->_disp12MaxDiffSlider->setVisible((bool) index);
    this->_preFilterLabel->setVisible((bool) index);
    this->_preFilterSlider->setVisible((bool) index);
    this->_uniquenessRatioLabel->setVisible((bool) index);
    this->_uniquenessRatioSlider->setVisible((bool) index);
    this->_speckleWindowsSizeLabel->setVisible((bool) index);
    this->_speckleWindowsSizeSlider->setVisible((bool) index);
    this->_speckleRangeLabel->setVisible((bool) index);
    this->_speckleRangeSlider->setVisible((bool) index);
    this->_SGBMmodeLabel->setVisible((bool) index);
    this->_SGBMmodeCombo->setVisible((bool) index);
}

void DisparityBox::onSBMnumDisparityChange(int value) {
    std::cout << "SBM Num Disp : " << value << std::endl;
}

void DisparityBox::onSBMblockSizeChange(int value) {
    std::cout << "SBM Block Size : " << value << std::endl;
}

void DisparityBox::onMinDisparityChange(int value) {
    std::cout << "Min Disp : " << value << std::endl;
}

void DisparityBox::onSGBMnumDisparityChange(int value) {
    std::cout << "SGBM Num Disp : " << value << std::endl;
}

void DisparityBox::onSGBMblockSizeChange(int value) {
    std::cout << "SGBM Block Size : " << value << std::endl;
}

void DisparityBox::onP1Change(int value) {
    std::cout << "P1 : " << value << std::endl;
}

void DisparityBox::onP2Change(int value) {
    std::cout << "P2 : " << value << std::endl;
}

void DisparityBox::onDisp12MaxDiffChange(int value) {
    std::cout << "Disp12 Max Diff : " << value << std::endl;
}

void DisparityBox::onPreFilterChange(int value) {
    std::cout << "Prefilter : " << value << std::endl;
}

void DisparityBox::onUniquenessRatioChange(int value) {
    std::cout << "Uniqueness Ration : " << value << std::endl;
}

void DisparityBox::onSpeckleWindowsSizeChange(int value) {
    std::cout << "Speckle Window Size : " << value << std::endl;
}

void DisparityBox::onSpeckleRangeChange(int value) {
    std::cout << "Speckle Range : " << value << std::endl;
}

void DisparityBox::onSGBMmodeChange(int value) {
    std::cout << "SGBM Mode : " << value << std::endl;
}
