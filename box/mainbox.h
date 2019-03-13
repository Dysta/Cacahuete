#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class MainBox : public QGroupBox
{

public:
    MainBox(const QString &title, QWidget* parent = nullptr);
    QPushButton* getLaplacianButton() { return laplacianButton; }
    QPushButton* getSobelButton() { return sobelButton; }
    QPushButton* getDisparityButton() { return disparityButton; }
    QPushButton* getCailbDepthButton() { return calibDepthButton; }

private:
    // first widget witch is display
    QGridLayout* homeGrid;
    QPushButton* laplacianButton;
    QPushButton* sobelButton;
    QPushButton* disparityButton;
    QPushButton* calibDepthButton;
};

#endif // MAINMENU_H
