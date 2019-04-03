#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>

#include <QGridLayout>
#include <QTcpSocket>
#include <QByteArray>
#include <QImage>
#include <QString>
#include <QBuffer>
#include <QMessageBox>

#include "process/disparityprocess.h"
#include "box/calibdepthbox.h"
#include "process/calibdepthprocess.h"

#define MAX_BUFF_SIZE 500000

class MainWindow;

class Network : public QTcpSocket
{
    Q_OBJECT

public:
    Network(MainWindow* mw, const QString& host, quint16 port, DisparityProcess* dispProcess, CalibDepthProcess* depthProcess);
    ~Network();
    bool isCreated() { return _running; }
    void send();

private slots:
    void onConnect(void);
    void onRead(void);
    void onDisconnect(void);
    void onError(QAbstractSocket::SocketError er);

    void onForwardClic(bool);
    void onBackwardClic(bool);
    void onLeftClic(bool);
    void onRightClic(bool);
    void onLeftRotClic(bool);
    void onRightRotClic(bool);

private:    
    void onFinishRead(void);

    MainWindow* _mw;
    DisparityProcess* _disparityProcess;
    CalibDepthBox* _depthBox;
    CalibDepthProcess* _depthProcess;

    QWidget* _botControllWidget;
    QGridLayout* _botControlLayout;
    QPushButton* _forwardButton;
    QPushButton* _backwardButton;
    QPushButton* _leftButton;
    QPushButton* _rightButton;
    QPushButton* _leftRotButton;
    QPushButton* _rightRotButton;

    QString _host;
    quint16 _port;
    bool _running;

    bool _sizeReceived;

    QByteArray _data;
    QByteArray _dataSize;
    QImage _picture;
};

#endif // NETWORK_H
