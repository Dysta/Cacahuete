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
    /**
     * @brief getProcess
     * @return
     */
    TrackerProcess *getProcess() const;
    /**
     * @brief getSwitchXSlider
     * @return
     */
    QSlider *getSwitchXSlider() const;
    /**
     * @brief getSwitchYSlider
     * @return
     */
    QSlider *getSwitchYSlider() const;

private slots:
    void onTrackChange();
    void onHsizeChange(int);
    void onHrangesChange(int);
    void onVminChange(int);
    void onVmaxChange(int);
    void onSminChange(int);
    void onXChange(int);
    void onYChange(int);
    void onWidthChange(int);
    void onHeightChange(int);

private:
    void createSlider(void);

    QGridLayout* _trackGrid;


    QCheckBox* _useTracking;
    TrackerProcess* _process;

    QLabel* _switchHsizeLabel;
    QSlider* _switchHsizeSlider;
    QLabel* _switchHrangesLabel;
    QSlider* _switchHrangesSlider;

    QLabel* _switchVminLabel;
    QSlider* _switchVminSlider;
    QLabel* _switchVmaxLabel;
    QSlider* _switchVmaxSlider;
    QLabel* _switchSminLabel;
    QSlider* _switchSminSlider;

    QLabel* _switchXLabel;
    QSlider* _switchXSlider;
    QLabel* _switchYLabel;
    QSlider* _switchYSlider;
    QLabel* _switchWidthLabel;
    QSlider* _switchWidthSlider;
    QLabel* _switchHeightLabel;
    QSlider* _switchHeightSlider;

};

#endif // TRACKERBOX_H
