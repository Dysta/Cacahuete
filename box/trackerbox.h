#ifndef TRACKERBOX_H
#define TRACKERBOX_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QGroupBox>

#include "process/trackerprocess.h"

class TrackerBox : public QGroupBox
{
    Q_OBJECT

public:
    TrackerBox(const QString &title, QWidget* parent = nullptr);
    virtual ~TrackerBox();

    QCheckBox* _useTracking;
    TrackerProcess* _process;

private slots:
    void onTrackChange(int);

private:
    void createSlider(void);

    QGridLayout* _trackGrid;
};

#endif // TRACKERBOX_H
