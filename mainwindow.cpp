#include "mainwindow.h"

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

    this->picture = new QImage();
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
    this->laplacianBox = new LaplacianBox("Laplacian effect");

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

    if (!this->picture->load(file)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir cette image");
        return;
    }
    if (this->picture->isNull()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir une image vide");
        return;
    }

    // On affiche l'image original sans aucune convertion
    this->imageLabel->setPixmap(QPixmap::fromImage(*picture));

    /*
     * On convertit les images à la suite pour continuer de les affichers
     * dans notre QApplication

    cv::Mat mat = Utils::Convert::qImage::toCvMat(picture, true);
    //cv::imshow("Matrice", mat);
    cv::Mat sbm = Utils::Convert::CvMat::toDisparity(mat, Utils::Convert::Mode::SBM);
    //cv::imshow("SBM", sbm);
    cv::Mat sgbm = Utils::Convert::CvMat::toDisparity(mat, Utils::Convert::Mode::SGBM);
    //cv::imshow("SGBM", sgbm);

    QImage qsbm = Utils::Convert::CvMat::toQImage(&sbm, false);
    QImage qsgbm = Utils::Convert::CvMat::toQImage(&sgbm, false);

    this->QImageLabel->setPixmap(QPixmap::fromImage(qsbm));
    this->CVMatriceLabel->setPixmap(QPixmap::fromImage(qsgbm));
*/
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
    this->menuStack->setCurrentIndex(LAPLACIANBOX);
}

void MainWindow::onMenuClick() {
    this->menuStack->setCurrentIndex(MAINBOX);
}

