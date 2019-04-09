#ifndef TRACKERBOX_H
#define TRACKERBOX_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QGroupBox>
#include <QSlider>

#include "process/trackerprocess.h"

class TrackerBox : public QGroupBox
{
    Q_OBJECT

public:
    TrackerBox(const QString &title, QWidget* parent = nullptr);
    virtual ~TrackerBox();


    TrackerProcess *getProcess() const;

private slots:
    void onTrackChange();
    void onHsizeChange(int);
    void onHranges1Change(int);
    void onHranges2Change(int);
    void onVminChange(int);
    void onVmaxChange(int);
    void onSminChange(int);

private:
    void createSlider(void);

    QGridLayout* _trackGrid;


    QCheckBox* _useTracking;
    TrackerProcess* _process;

    QLabel* _switchHsizeLabel;
    QSlider* _switchHsizeSlider;
    QLabel* _switchHranges1Label;
    QSlider* _switchHranges1Slider;
    QLabel* _switchHranges2Label;
    QSlider* _switchHranges2Slider;

    QLabel* _switchVminLabel;
    QSlider* _switchVminSlider;
    QLabel* _switchVmaxLabel;
    QSlider* _switchVmaxSlider;
    QLabel* _switchSminLabel;
    QSlider* _switchSminSlider;
};

#endif // TRACKERBOX_H
