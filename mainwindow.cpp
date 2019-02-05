#include "mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent, const QString title)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    this->setMinimumSize(1200, 600);

    this->mainWidget = new QWidget(this);
    this->mainLayout = new QGridLayout(this->mainWidget);

    this->menuStack = new QStackedWidget();

    this->createAction();
    this->createMenu();
    this->createImageGroup("Image");
    this->createSliderGroup();

    this->mainWidget->setLayout(this->mainLayout);
    this->setCentralWidget(this->mainWidget);
}

MainWindow::~MainWindow() {
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

void MainWindow::createImageGroup(const QString &title) {
    this->imageGroup = new QGroupBox(title);
    this->imageLabel = new QLabel();

    QBoxLayout* box = new QBoxLayout(QBoxLayout::TopToBottom);
    box->addWidget(this->imageLabel);
    this->imageGroup->setLayout(box);
    this->mainLayout->addWidget(this->imageGroup, 0, 0);

    //this->imageGroup->setVisible(false);
}

void MainWindow::createSliderGroup() {
    this->mainBox = new MainBox("Menu principal");
    this->laplacianBox = new LaplacianBox("Laplacian effect", this);

    this->menuStack->insertWidget(MAINBOX, this->mainBox);
    this->menuStack->insertWidget(LAPLACIANBOX, this->laplacianBox);

    this->mainLayout->addWidget(this->menuStack, 0, 1);

    connect(this->mainBox->getLaplacianButton(), SIGNAL(clicked()),
            this, SLOT(onLaplacianClick()));
    connect(this->laplacianBox->getBacktoMainButton(), SIGNAL(clicked()),
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

    if (!this->originalPicture.load(file)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir cette image");
        return;
    }
    if (this->originalPicture.isNull()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir une image vide");
        return;
    }

    this->copyImage();

    // On affiche l'image original sans aucune convertion
    this->imageLabel->setPixmap(QPixmap::fromImage(this->picture));

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
    if (!this->imageLabel->pixmap()) {
        QMessageBox::critical(this, "Erreur", "Vous devez d'abord charger une image");
        return;
    }
    this->menuStack->setCurrentIndex(LAPLACIANBOX);
}

void MainWindow::onMenuClick() {
    this->copyImage();
    this->updateImage();
    this->menuStack->setCurrentIndex(MAINBOX);
}

void MainWindow::copyImage() {
    this->picture = this->originalPicture.copy(this->originalPicture.rect());
}

void MainWindow::updateImage() {
    this->imageLabel->setPixmap(QPixmap::fromImage(this->picture));
}

