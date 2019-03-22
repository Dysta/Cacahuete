#ifndef DISPARITYBOX_H
#define DISPARITYBOX_H

#include <iostream>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "process/disparityprocess.h"

class DisparityBox : public QGroupBox
{
    Q_OBJECT

public:
    DisparityBox(const QString &title, QWidget* parent = nullptr);
    virtual ~DisparityBox();
    QPushButton* getBackToMainButton() { return _backToMain; }

    DisparityProcess *getProcess() const;

private slots:
    void onModeChange(int index);
    void onButtonSendClic(bool);

    //SBM
    void onSBMnumDisparityChange(int);
    void onSBMblockSizeChange(int);
    void onPrefilterCapChange(int);
    void onPrefilterSizeChange(int);
    void onPrefilterTypeChange(int);
    void onRoi1Change(int);
    void onRoi2Change(int);
    void onTextureThresholdChange(int);
    void onSBMuniquenessRationChange(int);

    //SGBM
    void onMinDisparityChange(int);
    void onSGBMnumDisparityChange(int);
    void onSGBMblockSizeChange(int);
    void onP1Change(int);
    void onP2Change(int);
    void onDisp12MaxDiffChange(int);
    void onPreFilterChange(int);
    void onUniquenessRatioChange(int);
    void onSpeckleWindowsSizeChange(int);
    void onSpeckleRangeChange(int);
    void onSGBMmodeChange(int);


private:
    void createSlider(void);

    QGridLayout* _disparityGrid;
    QPushButton* _backToMain;
    QPushButton* _send;

    DisparityProcess* _process;

    QComboBox* _mode;

    //For SBM mode
    QLabel* _SBMnumDisparityLabel;
    QSlider* _SBMnumDisparitySlider;
    QLabel* _SBMblockSizeLabel;
    QSlider* _SBMblockSizeSlider;
    QLabel* _preFilterCapLabel;
    QSlider* _preFilterCapSlider;
    QLabel* _preFilterSizeLabel;
    QSlider* _preFilterSizeSlider;
    QLabel* _preFilterTypeLabel;
    QComboBox* _preFilterTypeCombo;
    QLabel* _roi1Label;
    QSlider* _roi1Slider;
    QLabel* _roi2Label;
    QSlider* _roi2Slider;
    QLabel* _textureThresholdLabel;
    QSlider* _textureThresholdSlider;
    QLabel* _SBMuniquenessRationLabel;
    QSlider* _SBMuniquenessRationSlider;


    //For SGBM mode
    QLabel* _minDisparityLabel;
    QSlider* _minDisparitySlider;
    QLabel* _SGBMnumDisparityLabel;
    QSlider* _SGBMnumDisparitySlider;
    QLabel* _SGBMblockSizeLabel;
    QSlider* _SGBMblockSizeSlider;
    QLabel* _p1Label;
    QSlider* _p1Slider;
    QLabel* _p2Label;
    QSlider* _p2Slider;
    QLabel* _disp12MaxDiffLabel;
    QSlider* _disp12MaxDiffSlider;
    QLabel* _preFilterLabel;
    QSlider* _preFilterSlider;
    QLabel* _uniquenessRatioLabel;
    QSlider* _uniquenessRatioSlider;
    QLabel* _speckleWindowsSizeLabel;
    QSlider* _speckleWindowsSizeSlider;
    QLabel* _speckleRangeLabel;
    QSlider* _speckleRangeSlider;
    QLabel* _SGBMmodeLabel;
    QComboBox* _SGBMmodeCombo;

};

#endif // DISPARITYBOX_H
