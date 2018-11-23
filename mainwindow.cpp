#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"

// Penser à utiliser cv::calibrateCamera pour la calibration

MainWindow::MainWindow(QWidget *parent, const QString title) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    this->setMinimumSize(1200, 600);

    this->createAction();
    this->createMenu();
    this->createTab();
    this->createSliders();
    int winWidth = tabWidget->width();
    this->tabWidget->setMinimumWidth(winWidth/2);
    this->setCentralWidget(this->tabWidget);
    this->picture = new QImage();
}

MainWindow::~MainWindow() {
    delete label;
    delete picture;
    delete originalPic;
    delete QImageLabel;
    delete CVMatriceLabel;
    delete reconstructedChess;
    delete tabWidget;
    delete sliderWidget;
    delete ui;
}

void MainWindow::createAction() {
    this->openFileAct = new QAction("Ouvrir", this);
    this->openFileAct->setShortcut(QKeySequence::Open);
    connect(this->openFileAct, SIGNAL(triggered()), this, SLOT(open()));

    this->exitAppAct = new QAction("Fermer", this);
    this->exitAppAct->setShortcut(QKeySequence::Close);
    connect(this->exitAppAct, SIGNAL(triggered()), this, SLOT(close()));

    this->aboutAct = new QAction("Infos", this);
    connect(this->aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenu() {
    // Creating file menu
    this->fileMenu = menuBar()->addMenu("Fichier");
    this->fileMenu->addAction(openFileAct);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(exitAppAct);

    // Creating about menu
    this->aboutMenu = menuBar()->addMenu("A propos");
    this->aboutMenu->addAction(aboutAct);
}

void MainWindow::createTab() {
    this->tabWidget = new QTabWidget(this);

    this->originalPic = new QLabel(this->tabWidget);
    this->QImageLabel = new QLabel(this->tabWidget);
    this->CVMatriceLabel = new QLabel(this->tabWidget);
    this->reconstructedChess = new QLabel(this->tabWidget);

    this->tabWidget->addTab(this->originalPic, "Image original");
    this->tabWidget->addTab(this->QImageLabel, "SBM");
    this->tabWidget->addTab(this->CVMatriceLabel, "Carte de disparité");
    this->tabWidget->addTab(this->reconstructedChess, "Echiquier");
}

void MainWindow::createSliders(){
    this->sliderWidget = new QWidget(this);
    this->sliderWidget->setGeometry(400, 30, 300, 300);
    //this->sliderWidget->setFixedSize(300,300);

    this->sliders = new QLabel(this->sliderWidget);

    this->sliders0 = new QSlider(Qt::Horizontal, this->sliderWidget);
    this->sliders0->setMinimumWidth(100);
    this->sliders0->setValue(50);
}

void MainWindow::open() {
    QString file = QFileDialog::getOpenFileName(this,
                                                "Sélectionnez une image",
                                                "Images/",
                                                "Image (*.png *.jpg)",
                                                NULL,
                                                QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly
                                                );

    if ( file.isEmpty() ) return;

    if ( !this->picture->load(file) ) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir cette image");
        return;
    }
    if ( this->picture->isNull() ) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir une image vide");
        return;
    }
    // On affiche l'image original sans aucune convertion
    this->originalPic->setPixmap(QPixmap::fromImage(*picture));

    /*
     * On convertit les images à la suite pour continuer de les affichers
     * dans notre QApplication
    */
    cv::Mat mat = Utils::Convert::qImage::toCvMat(picture, true);
    //cv::imshow("Matrice", mat);
    cv::Mat sbm = Utils::Convert::CvMat::toDisparity(mat, Utils::Convert::Mode::SBM);
    //cv::imshow("SBM", sbm);
    cv::Mat sgbm = Utils::Convert::CvMat::toDisparity(mat, Utils::Convert::Mode::SGBM);
    //cv::imshow("SGBM", sgbm);
    Utils::Convert::CvMat::reconstructChess(mat, 11, 8); // Penser à créer des Sliders pour modifier les parametres Lines et Columns

    QImage qsbm = Utils::Convert::CvMat::toQImage(&sbm, false);
    QImage qsgbm = Utils::Convert::CvMat::toQImage(&sgbm, false);
    QImage qmat = Utils::Convert::CvMat::toQImage(&mat, false);

    this->QImageLabel->setPixmap(QPixmap::fromImage(qsbm));
    this->CVMatriceLabel->setPixmap(QPixmap::fromImage(qsgbm));
    this->reconstructedChess->setPixmap(QPixmap::fromImage(qmat));
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

