#ifndef SOBELBOX_H
#define SOBELBOX_H

#include <iostream>
#include <QGroupBox>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include "process/sobelprocess.h"

class SobelBox : public QGroupBox
{
    Q_OBJECT
public:
    SobelBox(const QString &title, QWidget* parent = nullptr);
    virtual ~SobelBox();
    QPushButton* getBacktoMainButton() { return _backToMain; }

private slots:
    void onImageChange(int);
    void onSizeHChange(int);
    void onSizeLChange(int);
    void onSigmaXChange(int);
    void onSigmaYChange(int);
    void onBlurSwitch(int);
    void onDxChange(int);
    void onDyChange(int);
    void onAlphaChange(int);
    void onBetaChange(int);
    void onGammaChange(int);


private:
    void createSlider(void);

    QGridLayout* _sobelGrid;
    QPushButton* _backToMain;
    SobelProcess* _process;

    QComboBox* _picture;

    //Gaussian Blur
    QLabel* _enableBlurLabel;
    QSlider* _enableBlurSlider;
    QLabel* _sizeHLabel;
    QSlider* _sizeHSlider;
    QLabel* _sizeLLabel;
    QSlider* _sizeLSlider;
    QLabel* _sigmaXLabel;
    QSlider* _sigmaXSlider;
    QLabel* _sigmaYLabel;
    QSlider* _sigmaYSlider;

    // Sobel gradient
    QLabel* _dxLabel;
    QSlider* _dxSlider;
    QLabel* _dyLabel;
    QSlider* _dySlider;

    // Total gradient
    QLabel* _alphaLabel;
    QSlider* _alphaSlider;
    QLabel* _betaLabel;
    QSlider* _betaSlider;
    QLabel* _gammaLabel;
    QSlider* _gammaSlider;
};

#endif // SOBELBOX_H
