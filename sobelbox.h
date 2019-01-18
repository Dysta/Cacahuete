#ifndef SOBELBOX_H
#define SOBELBOX_H

#include <iostream>
#include <QGroupBox>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>

class SobelBox : public QGroupBox
{
    Q_OBJECT
public:
    SobelBox(const QString &title, QWidget* parent = nullptr);
    virtual ~SobelBox();

private:
    QGridLayout* _sobelGrid;
    QPushButton* _backToMain;

    //QSlider* _
};

#endif // SOBELBOX_H
