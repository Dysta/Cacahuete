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

class LaplacianBox : public QGroupBox
{
    Q_OBJECT

public:
    LaplacianBox(const QString &title, QWidget* parent = nullptr);
    virtual ~LaplacianBox();
    QPushButton* getBacktoMainButton() { return backToMain; }
    int getSizeH() { return _sizeH; }
    int getSizeL() { return _sizeL; }



private slots:
    void onSizeHChange(int);
    void onSizeLChange(int);
    void onSigmaXChange(int);
    void onSigmaYChange(int);
    void onBlurSwitch(int);

private:
    void createSizeSlider(void);

    // first widget witch is display
    QGridLayout* laplacianGrid;
    QPushButton* backToMain;


    QSlider* _switchBlurSlider;
    QLabel* _switchBlurLabel;
    bool _activeBlur;

    QSlider* _sizeHSlider; // cols
    QSlider* _sizeLSlider; // rows
    QLabel* _sizeHLabel;
    QLabel* _sizeLLabel;
    int _sizeH;
    int _sizeL;

    QSlider* _sigmaXSlider;
    QSlider* _sigmaYSlider;
    QLabel* _sigmaXLabel;
    QLabel* _sigmaYLabel;
    int _sigmaX;
    int _sigmaY;
};

#endif // LAPLACIANBOX_H
