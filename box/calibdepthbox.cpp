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
    this->_undistortButton = new QPushButton("Retordre l'image");
    this->_depthMapButton = new QPushButton("Creer une carte de profondeur");

    this->_calibGrid = new QGridLayout();

    this->_calibGrid->addWidget(this->_picture, 0, 0);

    this->_calibGrid->addWidget(this->_numCornersHLabel, 1, 0);
    this->_calibGrid->addWidget(this->_numCornersHBox, 1, 1);

    this->_calibGrid->addWidget(this->_numCornersVLabel, 2, 0);
    this->_calibGrid->addWidget(this->_numCornersVBox, 2, 1);

    this->_calibGrid->addWidget(this->_calibrationButton, 3, 0);
    this->_calibGrid->addWidget(this->_undistortButton, 3, 1);

    this->_calibGrid->addWidget(this->_depthMapButton, 4, 0);

    this->_calibGrid->addWidget(this->_backToMain, 5, 0);

    setLayout(this->_calibGrid);

    connect(this->_picture, SIGNAL(activated(int)), this, SLOT(onImageChange(int)));
    connect(this->_calibrationButton, SIGNAL(clicked(bool)), this, SLOT(onCalibrationDo()));
    connect(this->_undistortButton, SIGNAL(clicked(bool)), this, SLOT(onUndistortDo()));
    connect(this->_depthMapButton, SIGNAL(clicked(bool)), this, SLOT(onDepthMapDo()));
}

CalibDepthBox::~CalibDepthBox() {

}

void CalibDepthBox::createSlider() {
    this->_picture = new QComboBox();
    this->_picture->addItem("Image de Gauche");
    this->_picture->addItem("Image de Droite");

    this->_numCornersHLabel = new QLabel("Number of corners horizontally");
    this->_numCornersHBox = new QSpinBox();
    this->_numCornersHBox->setMinimum(0);

    this->_numCornersVLabel = new QLabel("Number of corners vertically");
    this->_numCornersVBox = new QSpinBox();
    this->_numCornersVBox->setMinimum(0);

    connect(this->_numCornersHBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersHChange(int)));
    connect(this->_numCornersVBox, SIGNAL(valueChanged(int)), this, SLOT(onNumCornersVChange(int)));
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

    //
    //  L'ECHIQUIER DU PROJET TECH EST DE 9 PAR 6
    //
    this->_process->calibration(fileList, fileList.length(), false);

}

void CalibDepthBox::onUndistortDo(){
    cout << "Undistorting image..." << endl;
    this->_process->undistort();
}

void CalibDepthBox::onDepthMapDo(){
    cout << "Creating depth map..." << endl;

    QMessageBox::warning(this, "Attention", "Veillez a bien charger plusieurs images avec un echiquer correspondant aux valeurs donnees.\nVeillez aussi a avoir mis dans l'ordre d'abord les images de gauche, puis ceux de droite.");

    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                "Sélectionnez des images",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::ReadOnly
                                                );

    if ( fileList.isEmpty() ) return;

    this->_process->depthMap(fileList, fileList.length(), false);
}

void CalibDepthBox::onImageChange(int index) {
    std::cout << "Index : " << std::endl;
    this->_process->setImage(index);
}

void CalibDepthBox::onNumCornersHChange(int value){
    cout << "Number of corners hotizontally : " << value << endl;
    this->_process->setNumCornersH(value);
}

void CalibDepthBox::onNumCornersVChange(int value){
    cout << "Number of corners vertically : " << value << endl;
    this->_process->setNumCornersV(value);
}
