#include "mainbox.h"

MainBox::MainBox(const QString &title, QWidget* parent)
    : QGroupBox(title, parent)
{
    this->laplacianButton = new QPushButton("Laplacian");
    this->sobelButton     = new QPushButton("Sobel");
    this->disparityButton = new QPushButton("Disparity");

    this->homeGrid = new QGridLayout();
    this->homeGrid->addWidget(this->laplacianButton, 0, 0);
    this->homeGrid->addWidget(this->sobelButton, 1, 0);
    this->homeGrid->addWidget(this->disparityButton, 3, 0);

    setLayout(this->homeGrid);
}
