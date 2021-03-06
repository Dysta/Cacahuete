#include "calibdepthbox.h"
#include "mainwindow.h"

using namespace std;

CalibDepthBox::CalibDepthBox(const QString &title, DisparityProcess* dispProcess, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->_process = new CalibDepthProcess((MainWindow *) parent, dispProcess);

    this->createSlider();

    this->_calibrationButton = new QPushButton("Faire une calibration");
    this->_undistortButton = new QPushButton("Retordre l'image");
    this->_stereoCalibButton = new QPushButton("Calibration camera stereo");
    this->_depthMapButton = new QPushButton("Obtenir carte de profondeur");
    this->_loadParamButton = new QPushButton("Charger les parametres");

    this->_calibGrid = new QGridLayout();

    this->_calibGrid->addWidget(this->_picture, 0, 0);
    this->_calibGrid->addWidget(this->_useRemap, 0, 1);

    this->_calibGrid->addWidget(this->_numCornersHLabel, 1, 0);
    this->_calibGrid->addWidget(this->_numCornersHBox, 1, 1);

    this->_calibGrid->addWidget(this->_numCornersVLabel, 2, 0);
    this->_calibGrid->addWidget(this->_numCornersVBox, 2, 1);

    this->_calibGrid->addWidget(this->_calibrationButton, 3, 0);
    this->_calibGrid->addWidget(this->_undistortButton, 3, 1);

    this->_calibGrid->addWidget(this->_stereoCalibButton, 4, 0);
    this->_calibGrid->addWidget(this->_depthMapButton, 4, 1);

    this->_calibGrid->addWidget(this->_loadParamButton, 5, 0, 1, 2);

    setLayout(this->_calibGrid);

    connect(this->_picture, SIGNAL(activated(int)), this, SLOT(onImageChange(int)));
    connect(this->_useRemap, SIGNAL(stateChanged(int)), this, SLOT(onRemapChange()));
    connect(this->_calibrationButton, SIGNAL(clicked(bool)), this, SLOT(onCalibrationDo()));
    connect(this->_undistortButton, SIGNAL(clicked(bool)), this, SLOT(onUndistortDo()));
    connect(this->_stereoCalibButton, SIGNAL(clicked(bool)), this, SLOT(onStereoCalibDo()));
    connect(this->_depthMapButton, SIGNAL(clicked(bool)), this, SLOT(onDepthMapDo()));
    connect(this->_loadParamButton, SIGNAL(clicked(bool)), this, SLOT(onLoadParamDo()));
}

CalibDepthBox::~CalibDepthBox() {

}

void CalibDepthBox::createSlider() {
    this->_picture = new QComboBox();
    this->_picture->addItem("Détordre l'image de gauche");
    this->_picture->addItem("Détordre l'image de droite");

    this->_useRemap = new QCheckBox("Utiliser le remapping");

    this->_numCornersHLabel = new QLabel("Number of corners horizontally");
    this->_numCornersHBox = new QSpinBox();
    this->_numCornersHBox->setValue(9);
    this->_numCornersHBox->setMinimum(0);

    this->_numCornersVLabel = new QLabel("Number of corners vertically");
    this->_numCornersVBox = new QSpinBox();
    this->_numCornersVBox->setValue(6);
    this->_numCornersVBox->setMinimum(0);

    connect(this->_numCornersHBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersHChange(int)));
    connect(this->_numCornersVBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersVChange(int)));
}

CalibDepthProcess *CalibDepthBox::getProcess() const
{
    return _process;
}

void CalibDepthBox::onCalibrationDo(){

    QMessageBox::warning(this, "Attention", "Veillez a bien charger plusieurs images avec un echiquer correspondant aux valeurs donnees.");

    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                "Sélectionnez des images",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::ReadOnly
                                                );

    if ( fileList.isEmpty() ) return;

    this->_process->calibration(fileList, fileList.length(), false);

}

void CalibDepthBox::onUndistortDo(){
    this->_process->undistort();
}

void CalibDepthBox::onStereoCalibDo(){

    QMessageBox::warning(this, "Attention", "Veillez a bien charger plusieurs images avec un echiquer correspondant aux valeurs donnees.\nVeillez aussi a avoir mis dans l'ordre d'abord les images de gauche, puis ceux de droite.");

    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                "Sélectionnez des images",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::ReadOnly
                                                );

    if ( fileList.isEmpty() ) return;

    if ( fileList.size() % 2 == 1) {
        QMessageBox::warning(this, "Erreur", "Vous devez charger un nombre paire d'images.");
        return;
    }

    this->_process->stereoCalib(fileList, fileList.length(), false);
}

void CalibDepthBox::onRemapChange(){
    this->_process->setUseRemap(this->_useRemap->isChecked());
}

void CalibDepthBox::onDepthMapDo(){
    QMessageBox::information(this, "Information", "N'oubliez pas de configurer la carte de disparite avant !");
    this->_process->depthMap();
}

void CalibDepthBox::onLoadParamDo(){
    this->_process->loadParam();
}

void CalibDepthBox::onImageChange(int index) {
    this->_process->setImage(index);
}

void CalibDepthBox::onNumCornersHChange(int value){
    this->_process->setNumCornersH(value);
}

void CalibDepthBox::onNumCornersVChange(int value){
    this->_process->setNumCornersV(value);
}
