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

    this->_networkAct = new QAction("Recevoir un fichier depuis le reseau", this);
    this->_networkAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
    connect(this->_networkAct, SIGNAL(triggered()), this, SLOT(network()));
}

void MainWindow::createMenu() {
    // Creating file menu
    this->_fileMenu = menuBar()->addMenu("Fichier");
    this->_fileMenu->addAction(_openFileAct);
    this->_fileMenu->addSeparator();
    this->_fileMenu->addAction(_networkAct);

    // Creating about menu
    this->_aboutMenu = menuBar()->addMenu("A propos");
    this->_aboutMenu->addAction(_aboutAct);
    this->_aboutMenu->addSeparator();
    this->_aboutMenu->addAction(_exitAppAct);
}

void MainWindow::createImageGroup(const QString &title) {
    this->_imageGroup = new QGroupBox(title);
    this->_imageLeftLabel = new QLabel();
    this->_imageRightLabel = new QLabel();

    QBoxLayout* box = new QBoxLayout(QBoxLayout::TopToBottom);
    box->addWidget(this->_imageLeftLabel);
    box->addWidget(this->_imageRightLabel);
    this->_imageGroup->setLayout(box);
    this->_mainLayout->addWidget(this->_imageGroup, 0, 0);

    //this->imageGroup->setVisible(false);
}

void MainWindow::createSliderGroup() {
    this->_tabWidget = new QTabWidget(this);

    this->_laplacianBox = new LaplacianBox("Laplacian effect", this);
    this->_sobelBox = new SobelBox("Sobel effect", this);
    this->_disparityBox = new DisparityBox("Disparity effect", this);
    this->_calibBox = new CalibDepthBox("Calibration and depth map", this->_disparityBox->getProcess(), this);

    this->_tabWidget->addTab(this->_laplacianBox, "Laplacian");
    this->_tabWidget->addTab(this->_sobelBox, "Sobel");
    this->_tabWidget->addTab(this->_disparityBox, "Disparity");
    this->_tabWidget->addTab(this->_calibBox, "Calibrate");

    this->_mainLayout->addWidget(this->_tabWidget, 0, 1);

}


void MainWindow::open() {
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                "Sélectionnez les images gauche et droite",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly
                                                );

    if (files.isEmpty()) return;

    if (files.length() != 2) {
        QMessageBox::critical(this, "Erreur", "Vous devez choisir 2 images (camera gauche et droite)");
        return;
    }

    if (!this->_originalLeftPicture.load(files.at(0))) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir l'image gauche");
        return;
    }
    if (!this->_originalRightPicture.load(files.at(1))) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir l'image droite");
        return;
    }

    if (this->_originalLeftPicture.isNull() || this->_originalRightPicture.isNull()) {
        QMessageBox::critical(this, "Erreur", "Image gauche ou droite vide");
        return;
    }

    this->copyImage();

    // On affiche l'image original sans aucune convertion
    this->updateImage();

}

void MainWindow::about() {
    QMessageBox::information(this, "A propos", "Application realise dans le cadre du projet tech de l'universite de Bordeaux.");
}

void MainWindow::close() {
    QMessageBox::StandardButton answer = QMessageBox::question(this, "Quitter", "Quitter l'application ?", QMessageBox::Yes | QMessageBox::No);
    if ( answer == QMessageBox::Yes ) {
       QApplication::quit();
    }
}

void MainWindow::network() {
    if (this->_networkExist) {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Supprimer", "Confirmer la suppression de l'ancien réseau ?", QMessageBox::Yes | QMessageBox::No);
        if ( answer == QMessageBox::Yes ) {
            if (this->_networkSuccess)
                delete this->_network;
        }
        else
            return;
    }

    this->_networkWidget = new QWidget();
    this->_networkBox = new QHBoxLayout(this->_networkWidget);
    this->_hostLine = new QLineEdit(this->_networkWidget);
    this->_hostLine->setText("10.0.208.11");
    this->_portLine = new QSpinBox(this->_networkWidget);
    this->_portLine->setRange(1024, 10000);
    this->_portLine->setValue(7777);
    this->_networkBtn = new QPushButton("Connexion", this->_networkWidget);

    this->_networkBox->addWidget(this->_hostLine);
    this->_networkBox->addWidget(this->_portLine);
    this->_networkBox->addWidget(this->_networkBtn);

    this->_networkWidget->setWindowTitle("Connexion à un serveur");
    this->_networkWidget->show();

    connect(this->_networkBtn, SIGNAL(clicked(bool)),
            this, SLOT(onNetworkBtnClick()));
}

void MainWindow::onNetworkBtnClick() {
    this->_host = this->_hostLine->text();
    this->_port = this->_portLine->text().toInt();
    if (!this->_host.isEmpty()) {
        this->_network = new Network(this, this->_host, this->_port, this->_disparityBox->getProcess(), this->_calibBox->getProcess());
        this->_networkWidget->hide();
        delete this->_networkWidget;
        this->_networkExist = true;
    }
}

void MainWindow::copyImage() {
    this->_pictureLeft = this->_originalLeftPicture.copy(this->_originalLeftPicture.rect());
    this->_pictureRight = this->_originalRightPicture.copy(this->_originalRightPicture.rect());
}

void MainWindow::updateImage() {
    this->_imageLeftLabel->setPixmap(QPixmap::fromImage(this->_pictureLeft));
    this->_imageRightLabel->setPixmap(QPixmap::fromImage(this->_pictureRight));
}

