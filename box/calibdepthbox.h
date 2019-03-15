#ifndef CALIBDEPTHBOX_H
#define CALIBDEPTHBOX_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <vector>

#include "process/calibdepthprocess.h"

class CalibDepthBox : public QGroupBox
{
    Q_OBJECT

public:
    CalibDepthBox(const QString &title, QWidget* parent = nullptr);
    virtual ~CalibDepthBox();
    QPushButton* getBackToMainButton() { return _backToMain; }

private slots:
    void onImageChange(int);
    void onNumCornersHChange(int);
    void onNumCornersVChange(int);
    void onCalibrationDo();
    void onUndistortDo();
    void onDepthMapDo();

private:
    void createSlider(void);

    QGridLayout* _calibGrid;
    QPushButton* _backToMain;

    CalibDepthProcess* _process;

    QComboBox* _picture;

    QLabel* _numCornersHLabel;
    QSpinBox* _numCornersHBox;
    QLabel* _numCornersVLabel;
    QSpinBox* _numCornersVBox;

    QPushButton* _undistortButton;
    QPushButton* _calibrationButton;
    QPushButton* _depthMapButton;

};

#endif // CALIBDEPTHBOX_H
