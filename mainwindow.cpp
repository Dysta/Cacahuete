#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"

MainWindow::MainWindow(QWidget *parent, const QString title) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    this->setMinimumSize(300, 300);

    this->createAction();
    this->createMenu();
    this->createTab();
    /*
    this->label = new QLabel(this);
    this->setCentralWidget(this->label);
    */
    this->setCentralWidget(this->tabWidget);

    this->picture = new QImage();
}

MainWindow::~MainWindow() {
    delete label;
    delete picture;
    delete originalPic;
    delete QImageLabel;
    delete CVMatriceLabel;
    delete tabWidget;
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

    this->tabWidget->addTab(this->originalPic, "Image original");
    this->tabWidget->addTab(this->QImageLabel, "QImage");
    this->tabWidget->addTab(this->CVMatriceLabel, "Matrice OpenCV");
}

void MainWindow::open() {
    QString file = QFileDialog::getOpenFileName(this,
                                                "Sélectionnez une image",
                                                "",
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
    cv::Mat mat = Convert::qImage::toCvMat(picture, true);
    QImage pic = Convert::CvMat::toQImage(&mat, true);

    cv::imshow("Matrice", mat);
    this->QImageLabel->setPixmap(QPixmap::fromImage(pic));
    this->CVMatriceLabel->setPixmap(QPixmap::fromImage(pic));
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

