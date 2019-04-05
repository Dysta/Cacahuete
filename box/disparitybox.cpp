#include "disparitybox.h"
#include "mainwindow.h"

DisparityBox::DisparityBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new DisparityProcess((MainWindow *) parent);

    this->createSlider();


    this->_disparityGrid = new QGridLayout();

    this->_disparityGrid->addWidget(this->_mode, 0, 0);


    this->_disparityGrid->addWidget(this->_SBMnumDisparityLabel, 1, 0);
    this->_disparityGrid->addWidget(this->_SBMnumDisparitySlider, 1, 1);

    this->_disparityGrid->addWidget(this->_SBMblockSizeLabel, 2, 0);
    this->_disparityGrid->addWidget(this->_SBMblockSizeSlider, 2, 1);

    this->_disparityGrid->addWidget(this->_preFilterCapLabel, 3, 0);
    this->_disparityGrid->addWidget(this->_preFilterCapSlider, 3, 1);

    this->_disparityGrid->addWidget(this->_preFilterSizeLabel, 4, 0);
    this->_disparityGrid->addWidget(this->_preFilterSizeSlider, 4, 1);

    this->_disparityGrid->addWidget(this->_preFilterTypeLabel, 5, 0);
    this->_disparityGrid->addWidget(this->_preFilterTypeCombo, 5, 1);

    this->_disparityGrid->addWidget(this->_roi1Label, 6, 0);
    this->_disparityGrid->addWidget(this->_roi1Slider, 6, 1);

    this->_disparityGrid->addWidget(this->_roi2Label, 7, 0);
    this->_disparityGrid->addWidget(this->_roi2Slider, 7, 1);

    this->_disparityGrid->addWidget(this->_textureThresholdLabel, 8, 0);
    this->_disparityGrid->addWidget(this->_textureThresholdSlider, 8, 1);

    this->_disparityGrid->addWidget(this->_SBMuniquenessRationLabel, 9, 0);
    this->_disparityGrid->addWidget(this->_SBMuniquenessRationSlider, 9, 1);


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


    setLayout(this->_disparityGrid);

}

DisparityBox::~DisparityBox() {

}

void DisparityBox::createSlider() {
    this->_mode = new QComboBox();
    this->_mode->addItem("Mode SBM");
    this->_mode->addItem("Mode SGBM");

    this->_SBMnumDisparityLabel = new QLabel("Disparity Number");
    this->_SBMnumDisparitySlider = new QSlider(Qt::Horizontal);
    this->_SBMnumDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_SBMnumDisparitySlider->setTickInterval(10);
    this->_SBMnumDisparitySlider->setSingleStep(16);
    this->_SBMnumDisparitySlider->setRange(0, 250);
    this->_SBMnumDisparitySlider->setValue(64);

    this->_SBMblockSizeLabel = new QLabel("Block size");
    this->_SBMblockSizeSlider = new QSlider(Qt::Horizontal);
    this->_SBMblockSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_SBMblockSizeSlider->setTickInterval(10);
    this->_SBMblockSizeSlider->setSingleStep(2);
    this->_SBMblockSizeSlider->setRange(5, 255);
    this->_SBMblockSizeSlider->setValue(27);

    this->_preFilterCapLabel = new QLabel("Prefilter Cap");
    this->_preFilterCapSlider = new QSlider(Qt::Horizontal);
    this->_preFilterCapSlider->setTickPosition(QSlider::TicksAbove);
    this->_preFilterCapSlider->setTickInterval(10);
    this->_preFilterCapSlider->setSingleStep(2);
    this->_preFilterCapSlider->setRange(1, 63);
    this->_preFilterCapSlider->setValue(39);

    this->_preFilterSizeLabel = new QLabel("Prefilter Size");
    this->_preFilterSizeSlider = new QSlider(Qt::Horizontal);
    this->_preFilterSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_preFilterSizeSlider->setTickInterval(10);
    this->_preFilterSizeSlider->setSingleStep(2);
    this->_preFilterSizeSlider->setRange(5, 255);
    this->_preFilterSizeSlider->setValue(31);

    this->_preFilterTypeLabel = new QLabel("Prefilter Type");
    this->_preFilterTypeCombo = new QComboBox();
    this->_preFilterTypeCombo->addItem("PREFILTER_NORMALIZED_RESPONSE");
    this->_preFilterTypeCombo->addItem("PREFILTER_XSOBEL");

    this->_roi1Label = new QLabel("ROI 1");
    this->_roi1Slider = new QSlider(Qt::Horizontal);
    this->_roi1Slider->setTickPosition(QSlider::TicksAbove);
    this->_roi1Slider->setTickInterval(10);
    this->_roi1Slider->setSingleStep(2);
    this->_roi1Slider->setRange(0, 255);
    this->_roi1Slider->setValue(1);

    this->_roi2Label = new QLabel("ROI 2");
    this->_roi2Slider = new QSlider(Qt::Horizontal);
    this->_roi2Slider->setTickPosition(QSlider::TicksAbove);
    this->_roi2Slider->setTickInterval(10);
    this->_roi2Slider->setSingleStep(2);
    this->_roi2Slider->setRange(0, 255);
    this->_roi2Slider->setValue(1);

    this->_textureThresholdLabel = new QLabel("Texture Threshold");
    this->_textureThresholdSlider = new QSlider(Qt::Horizontal);
    this->_textureThresholdSlider->setTickPosition(QSlider::TicksAbove);
    this->_textureThresholdSlider->setTickInterval(10);
    this->_textureThresholdSlider->setSingleStep(2);
    this->_textureThresholdSlider->setRange(0, 255);
    this->_textureThresholdSlider->setValue(219);

    this->_SBMuniquenessRationLabel = new QLabel("Uniqueness Ration");
    this->_SBMuniquenessRationSlider = new QSlider(Qt::Horizontal);
    this->_SBMuniquenessRationSlider->setTickPosition(QSlider::TicksAbove);
    this->_SBMuniquenessRationSlider->setTickInterval(10);
    this->_SBMuniquenessRationSlider->setSingleStep(2);
    this->_SBMuniquenessRationSlider->setRange(0, 255);
    this->_SBMuniquenessRationSlider->setValue(3);




    this->_minDisparityLabel = new QLabel("Minimum disparity Number");
    this->_minDisparityLabel->setVisible(false);
    this->_minDisparitySlider = new QSlider(Qt::Horizontal);
    this->_minDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_minDisparitySlider->setTickInterval(50);
    this->_minDisparitySlider->setSingleStep(1);
    this->_minDisparitySlider->setRange(-1000, 1000);
    this->_minDisparitySlider->setValue(-64);
    this->_minDisparitySlider->setVisible(false);

    this->_SGBMnumDisparityLabel = new QLabel("Disparity Number");
    this->_SGBMnumDisparityLabel->setVisible(false);
    this->_SGBMnumDisparitySlider = new QSlider(Qt::Horizontal);
    this->_SGBMnumDisparitySlider->setTickPosition(QSlider::TicksAbove);
    this->_SGBMnumDisparitySlider->setTickInterval(50);
    this->_SGBMnumDisparitySlider->setSingleStep(16);
    this->_SGBMnumDisparitySlider->setRange(1, 1000);
    this->_SGBMnumDisparitySlider->setValue(192);
    this->_SGBMnumDisparitySlider->setVisible(false);

    this->_SGBMblockSizeLabel = new QLabel("Block size");
    this->_SGBMblockSizeLabel->setVisible(false);
    this->_SGBMblockSizeSlider = new QSlider(Qt::Horizontal);
    this->_SGBMblockSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_SGBMblockSizeSlider->setTickInterval(2);
    this->_SGBMblockSizeSlider->setSingleStep(2);
    this->_SGBMblockSizeSlider->setRange(3, 11);
    this->_SGBMblockSizeSlider->setValue(5);
    this->_SGBMblockSizeSlider->setVisible(false);

    this->_p1Label = new QLabel("P1");
    this->_p1Label->setVisible(false);
    this->_p1Slider = new QSlider(Qt::Horizontal);
    this->_p1Slider->setTickPosition(QSlider::TicksAbove);
    this->_p1Slider->setTickInterval(100);
    this->_p1Slider->setSingleStep(1);
    this->_p1Slider->setRange(0, 5000);
    this->_p1Slider->setValue(600);
    this->_p1Slider->setVisible(false);

    this->_p2Label = new QLabel("P2");
    this->_p2Label->setVisible(false);
    this->_p2Slider = new QSlider(Qt::Horizontal);
    this->_p2Slider->setTickPosition(QSlider::TicksAbove);
    this->_p2Slider->setTickInterval(100);
    this->_p2Slider->setSingleStep(1);
    this->_p2Slider->setRange(0, 5000);
    this->_p2Slider->setValue(2400);
    this->_p2Slider->setVisible(false);

    this->_disp12MaxDiffLabel = new QLabel("Disparity 12 max Diff");
    this->_disp12MaxDiffLabel->setVisible(false);
    this->_disp12MaxDiffSlider = new QSlider(Qt::Horizontal);
    this->_disp12MaxDiffSlider->setTickPosition(QSlider::TicksAbove);
    this->_disp12MaxDiffSlider->setTickInterval(50);
    this->_disp12MaxDiffSlider->setSingleStep(1);
    this->_disp12MaxDiffSlider->setRange(-1, 1000);
    this->_disp12MaxDiffSlider->setValue(10);
    this->_disp12MaxDiffSlider->setVisible(false);

    this->_preFilterLabel = new QLabel("Pre Filter");
    this->_preFilterLabel->setVisible(false);
    this->_preFilterSlider = new QSlider(Qt::Horizontal);
    this->_preFilterSlider->setTickPosition(QSlider::TicksAbove);
    this->_preFilterSlider->setTickInterval(5);
    this->_preFilterSlider->setSingleStep(1);
    this->_preFilterSlider->setRange(-50, 50);
    this->_preFilterSlider->setValue(4);
    this->_preFilterSlider->setVisible(false);

    this->_uniquenessRatioLabel = new QLabel("Uniqueness Ration");
    this->_uniquenessRatioLabel->setVisible(false);
    this->_uniquenessRatioSlider = new QSlider(Qt::Horizontal);
    this->_uniquenessRatioSlider->setTickPosition(QSlider::TicksAbove);
    this->_uniquenessRatioSlider->setTickInterval(5);
    this->_uniquenessRatioSlider->setSingleStep(1);
    this->_uniquenessRatioSlider->setRange(0, 20);
    this->_uniquenessRatioSlider->setValue(1);
    this->_uniquenessRatioSlider->setVisible(false);

    this->_speckleWindowsSizeLabel = new QLabel("Speckle Window Size");
    this->_speckleWindowsSizeLabel->setVisible(false);
    this->_speckleWindowsSizeSlider = new QSlider(Qt::Horizontal);
    this->_speckleWindowsSizeSlider->setTickPosition(QSlider::TicksAbove);
    this->_speckleWindowsSizeSlider->setTickInterval(10);
    this->_speckleWindowsSizeSlider->setSingleStep(1);
    this->_speckleWindowsSizeSlider->setRange(0, 200);
    this->_speckleWindowsSizeSlider->setValue(150);
    this->_speckleWindowsSizeSlider->setVisible(false);

    this->_speckleRangeLabel = new QLabel("Speckle Range");
    this->_speckleRangeLabel->setVisible(false);
    this->_speckleRangeSlider = new QSlider(Qt::Horizontal);
    this->_speckleRangeSlider->setTickPosition(QSlider::TicksAbove);
    this->_speckleRangeSlider->setTickInterval(1);
    this->_speckleRangeSlider->setSingleStep(1);
    this->_speckleRangeSlider->setRange(1, 2);
    this->_speckleRangeSlider->setValue(2);
    this->_speckleRangeSlider->setVisible(false);

    this->_SGBMmodeLabel = new QLabel("SGBM Mode");
    this->_SGBMmodeLabel->setVisible(false);
    this->_SGBMmodeCombo = new QComboBox();
    this->_SGBMmodeCombo->addItem("MODE_SGBM");
    this->_SGBMmodeCombo->addItem("MODE_HH");
    this->_SGBMmodeCombo->addItem("MODE_SGBM_3WAY");
    this->_SGBMmodeCombo->setVisible(false);

    connect(this->_mode, SIGNAL(activated(int)),
            this, SLOT(onModeChange(int)));

    connect(this->_SBMnumDisparitySlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSBMnumDisparityChange(int)));
    connect(this->_SBMblockSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSBMblockSizeChange(int)));
    connect(this->_preFilterCapSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onPrefilterCapChange(int)));
    connect(this->_preFilterSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onPrefilterSizeChange(int)));
    connect(this->_preFilterTypeCombo, SIGNAL(activated(int)),
            this, SLOT(onPrefilterTypeChange(int)));
    connect(this->_roi1Slider, SIGNAL(valueChanged(int)),
            this, SLOT(onRoi1Change(int)));
    connect(this->_roi2Slider, SIGNAL(valueChanged(int)),
            this, SLOT(onRoi2Change(int)));
    connect(this->_textureThresholdSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onTextureThresholdChange(int)));
    connect(this->_SBMuniquenessRationSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSBMuniquenessRationChange(int)));


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
            this, SLOT(onUniquenessRatioChange(int)));
    connect(this->_speckleWindowsSizeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSpeckleWindowsSizeChange(int)));
    connect(this->_speckleRangeSlider, SIGNAL(valueChanged(int)),
            this, SLOT(onSpeckleRangeChange(int)));
    connect(this->_SGBMmodeCombo, SIGNAL(activated(int)),
            this, SLOT(onSGBMmodeChange(int)));
}

DisparityProcess *DisparityBox::getProcess() const
{
    return _process;
}

void DisparityBox::onModeChange(int index) {
    std::cout << "Mode : " << index << std::endl;
    this->_process->setMode(index);

    this->_SBMnumDisparityLabel->setVisible((bool) !index);
    this->_SBMnumDisparitySlider->setVisible((bool) !index);
    this->_SBMblockSizeLabel->setVisible((bool) !index);
    this->_SBMblockSizeSlider->setVisible((bool) !index);
    this->_preFilterCapLabel->setVisible((bool) !index);
    this->_preFilterCapSlider->setVisible((bool) !index);
    this->_preFilterSizeLabel->setVisible((bool) !index);
    this->_preFilterSizeSlider->setVisible((bool) !index);
    this->_preFilterTypeLabel->setVisible((bool) !index);
    this->_preFilterTypeCombo->setVisible((bool) !index);
    this->_roi1Label->setVisible((bool) !index);
    this->_roi1Slider->setVisible((bool) !index);
    this->_roi2Label->setVisible((bool) !index);
    this->_roi2Slider->setVisible((bool) !index);
    this->_textureThresholdLabel->setVisible((bool) !index);
    this->_textureThresholdSlider->setVisible((bool) !index);
    this->_SBMuniquenessRationLabel->setVisible((bool) !index);
    this->_SBMuniquenessRationSlider->setVisible((bool) !index);


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
    this->_process->setSBMnumDisp(value);
}

void DisparityBox::onSBMblockSizeChange(int value) {
    std::cout << "SBM Block Size : " << value << std::endl;
    this->_process->setSBMblockSize(value);
}

void DisparityBox::onPrefilterCapChange(int value) {
    std::cout << "SBM Prefilter Cap : " << value << std::endl;
    this->_process->setPrefilterCap(value);
}

void DisparityBox::onPrefilterSizeChange(int value) {
    std::cout << "SBM Prefilter Size : " << value << std::endl;
    this->_process->setPrefilterSize(value);
}

void DisparityBox::onPrefilterTypeChange(int value) {
    std::cout << "SBM Prefilter Type : " << value << std::endl;
    this->_process->setPrefilterType(value);
}

void DisparityBox::onRoi1Change(int value) {
    std::cout << "SBM ROI1 : " << value << std::endl;
    this->_process->setRoi1(value);
}

void DisparityBox::onRoi2Change(int value) {
    std::cout << "SBM ROI2 : " << value << std::endl;
    this->_process->setRoi2(value);
}

void DisparityBox::onTextureThresholdChange(int value) {
    std::cout << "SBM Texture Threshold : " << value << std::endl;
    this->_process->setTextureThreshold(value);
}

void DisparityBox::onSBMuniquenessRationChange(int value) {
    std::cout << "SBM Uniqueness Ratio : " << value << std::endl;
    this->_process->setSBMuniquenessRatio(value);
}


void DisparityBox::onMinDisparityChange(int value) {
    std::cout << "Min Disp : " << value << std::endl;
    this->_process->setMinDisp(value);
}

void DisparityBox::onSGBMnumDisparityChange(int value) {
    std::cout << "SGBM Num Disp : " << value << std::endl;
    this->_process->setSGBMnumDisp(value);
}

void DisparityBox::onSGBMblockSizeChange(int value) {
    std::cout << "SGBM Block Size : " << value << std::endl;
    this->_process->setSGBMblockSize(value);
}

void DisparityBox::onP1Change(int value) {
    std::cout << "P1 : " << value << std::endl;
    this->_process->setP1(value);
}

void DisparityBox::onP2Change(int value) {
    std::cout << "P2 : " << value << std::endl;
    this->_process->setP2(value);
}

void DisparityBox::onDisp12MaxDiffChange(int value) {
    std::cout << "Disp12 Max Diff : " << value << std::endl;
    this->_process->setDisp12MaxDiffChange(value);
}

void DisparityBox::onPreFilterChange(int value) {
    std::cout << "Prefilter : " << value << std::endl;
    this->_process->setPrefilter(value);
}

void DisparityBox::onUniquenessRatioChange(int value) {
    std::cout << "Uniqueness Ration : " << value << std::endl;
    this->_process->setUniquenessRatio(value);
}

void DisparityBox::onSpeckleWindowsSizeChange(int value) {
    std::cout << "Speckle Window Size : " << value << std::endl;
    this->_process->setSpeckleWindowsSize(value);
}

void DisparityBox::onSpeckleRangeChange(int value) {
    std::cout << "Speckle Range : " << value << std::endl;
    this->_process->setSpeckleRange(value);
}

void DisparityBox::onSGBMmodeChange(int value) {
    std::cout << "SGBM Mode : " << value << std::endl;
    this->_process->setSGBMmode(value);
}
