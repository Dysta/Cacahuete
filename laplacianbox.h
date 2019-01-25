#ifndef LAPLACIANBOX_H
#define LAPLACIANBOX_H

#include <iostream>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QSlider>
#include <QLabel>

#include "laplacianprocess.h"

class LaplacianBox : public QGroupBox
{
    Q_OBJECT

public:
    LaplacianBox(const QString &title, QWidget* parent = nullptr);
    virtual ~LaplacianBox();
    QPushButton* getBacktoMainButton() { return backToMain; }

private slots:
    void onSizeHChange(int);
    void onSizeLChange(int);
    void onSigmaXChange(int);
    void onSigmaYChange(int);
    void onBlurSwitch(int);

private:
    void createSlider(void);

    // first widget witch is display
    QGridLayout* laplacianGrid;
    QPushButton* backToMain;

    LaplacianProcess* _process;

    QSlider* _switchBlurSlider;
    QLabel* _switchBlurLabel;

    QSlider* _sizeHSlider; // cols
    QSlider* _sizeLSlider; // rows
    QLabel* _sizeHLabel;
    QLabel* _sizeLLabel;

    QSlider* _sigmaXSlider;
    QSlider* _sigmaYSlider;
    QLabel* _sigmaXLabel;
    QLabel* _sigmaYLabel;
};

#endif // LAPLACIANBOX_H
