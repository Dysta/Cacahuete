#include "mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent, const QString title)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    this->setMinimumSize(1200, 600);

    this->_mainWidget = new QWidget(this);
    this->_mainLayout = new QGridLayout(this->_mainWidget);

    this->_menuStack = new QStackedWidget();

    this->createAction();
    this->createMenu();
    this->createImageGroup("Image");
    this->createSliderGroup();

    this->_mainWidget->setLayout(this->_mainLayout);
    this->setCentralWidget(this->_mainWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createAction() {
    this->_openFileAct = new QAction("Ouvrir", this);
    this->_openFileAct->setShortcut(QKeySequence::Open);
    connect(this->_openFileAct, SIGNAL(triggered()), this, SLOT(open()));

    this->_exitAppAct = new QAction("Fermer", this);
    this->_exitAppAct->setShortcut(QKeySequence::Close);
    connect(this->_exitAppAct, SIGNAL(triggered()), this, SLOT(close()));

    this->_aboutAct = new QAction("Infos", this);
    connect(this->_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createMenu() {
    // Creating file menu
    this->_fileMenu = menuBar()->addMenu("Fichier");
    this->_fileMenu->addAction(_openFileAct);
    this->_fileMenu->addSeparator();
    this->_fileMenu->addAction(_exitAppAct);

    // Creating about menu
    this->_aboutMenu = menuBar()->addMenu("A propos");
    this->_aboutMenu->addAction(_aboutAct);
}

void MainWindow::createImageGroup(const QString &title) {
    this->_imageGroup = new QGroupBox(title);
    this->_imageLabel = new QLabel();
  
    QBoxLayout* box = new QBoxLayout(QBoxLayout::TopToBottom);
    box->addWidget(this->_imageLabel);
    this->_imageGroup->setLayout(box);
    this->_mainLayout->addWidget(this->_imageGroup, 0, 0);

    //this->imageGroup->setVisible(false);
}

void MainWindow::createSliderGroup() {
    this->_mainBox = new MainBox("Menu principal");
    this->_laplacianBox = new LaplacianBox("Laplacian effect", this);
    this->_sobelBox = new SobelBox("Sobel effect", this);
    this->_disparityBox = new DisparityBox("Disparity effect", this);
    this->_calibBox = new CalibDepthBox("Calibration and depth map", this);

    this->_menuStack->insertWidget(MAINBOX, this->_mainBox);
    this->_menuStack->insertWidget(LAPLACIANBOX, this->_laplacianBox);
    this->_menuStack->insertWidget(SOBELBOX, this->_sobelBox);
    this->_menuStack->insertWidget(DISPARITYBOX, this->_disparityBox);
    this->_menuStack->insertWidget(CALIBDEPTHBOX, this->_calibBox);

    this->_mainLayout->addWidget(this->_menuStack, 0, 1);

    connect(this->_mainBox->getLaplacianButton(), SIGNAL(clicked()),
            this, SLOT(onLaplacianClick()));
    connect(this->_mainBox->getSobelButton(), SIGNAL(clicked(bool)),
            this, SLOT(onSobelClick()));
    connect(this->_mainBox->getDisparityButton(), SIGNAL(clicked(bool)),
            this, SLOT(onDisparityClick()));
    connect(this->_mainBox->getCailbDepthButton(), SIGNAL(clicked(bool)), this, SLOT(onCalibClick()));

    connect(this->_laplacianBox->getBacktoMainButton(), SIGNAL(clicked()),
            this, SLOT(onMenuClick()));
    connect(this->_sobelBox->getBacktoMainButton(), SIGNAL(clicked()),
            this, SLOT(onMenuClick()));
    connect(this->_disparityBox->getBackToMainButton(), SIGNAL(clicked(bool)),
            this, SLOT(onMenuClick()));
    connect(this->_calibBox->getBackToMainButton(), SIGNAL(clicked(bool)),
            this, SLOT(onMenuClick()));
}


void MainWindow::open() {
    QString file = QFileDialog::getOpenFileName(this,
                                                "Sélectionnez une image",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                /* QFileDialog::DontUseNativeDialog |*/ QFileDialog::ReadOnly
                                                );

    if (file.isEmpty()) return;

    if (!this->_originalPicture.load(file)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir cette image");
        return;
    }
    if (this->_originalPicture.isNull()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir une image vide");
        return;
    }

    this->copyImage();

    // On affiche l'image original sans aucune convertion
    this->_imageLabel->setPixmap(QPixmap::fromImage(this->_picture));

}


void MainWindow::getDepthMap(){
    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                "Sélectionnez des images",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly
                                                );

    if ( fileList.isEmpty() ) return;

    for(int i = 0; i < fileList.size(); i++){

        if ( !this->_picture.load(fileList.at(i)) ) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir cette image");
            return;
        }
        if ( this->_picture.isNull() ) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir une image vide");
            return;
        }
    }
    depthmap::Depthmap(fileList, fileList.size(), 9, 6, false);
}

void MainWindow::about() {
    QMessageBox::information(this, "A propos", "Application realise dans le cadre du projet tech de l'universite de Bordeaux ! Permet d'ouvrir et afficher une image de type \" QImage\" et de la convertir en type \" CvMatrice\"");
}

void MainWindow::close() {
    QMessageBox::StandardButton answer = QMessageBox::question(this, "Quitter", "Quitter l'application ?", QMessageBox::Yes | QMessageBox::No);
    if ( answer == QMessageBox::Yes ) {
       QApplication::quit();
    }
}

void MainWindow::onLaplacianClick() {
    if (!this->_imageLabel->pixmap()) {
        QMessageBox::critical(this, "Erreur", "Vous devez d'abord charger une image");
        return;
    }
    this->_menuStack->setCurrentIndex(LAPLACIANBOX);
}

void MainWindow::onSobelClick() {
    if (!this->_imageLabel->pixmap()) {
        QMessageBox::critical(this, "Erreur", "Vous devez d'abord charger une image");
        return;
    }
    this->_menuStack->setCurrentIndex(SOBELBOX);
}

void MainWindow::onDisparityClick() {
    if (!this->_imageLabel->pixmap()) {
        QMessageBox::critical(this, "Erreur", "Vous devez d'abord charger une image");
        return;
    }
    QMessageBox::warning(this, "Attention", "Vous devez avoir chargé une image stereoscopique");
    this->_menuStack->setCurrentIndex(DISPARITYBOX);
}

void MainWindow::onCalibClick() {
    if (!this->_imageLabel->pixmap()) {
        QMessageBox::critical(this, "Erreur", "Vous devez d'abord charger une image");
        return;
    }
    QMessageBox::warning(this, "Attention", "Veillez à bien ouvrir une image pour la correction");
    this->_menuStack->setCurrentIndex(CALIBDEPTHBOX);
}

void MainWindow::onMenuClick() {
    this->copyImage();
    this->updateImage();
    this->_menuStack->setCurrentIndex(MAINBOX);
}

void MainWindow::copyImage() {
    this->_picture = this->_originalPicture.copy(this->_originalPicture.rect());
}

void MainWindow::updateImage() {
    this->_imageLabel->setPixmap(QPixmap::fromImage(this->_picture));
}

