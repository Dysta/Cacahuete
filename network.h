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
#include "process/calibdepthprocess.h"
#include "process/trackerprocess.h"


#define MAX_BUFF_SIZE 500000

class MainWindow;

class Network : public QTcpSocket
{
    Q_OBJECT

public:
    /**
     * @brief create a Network client object
     * @param mw the parent/mainwindow
     * @param host
     * @param port
     * @param dispProcess the disparity process
     * @param depthProcess the depth process
     * @param trackerProcess the tracker process
     */
    Network(MainWindow* mw, const QString& host, quint16 port, DisparityProcess* dispProcess, CalibDepthProcess* depthProcess, TrackerProcess* trackerProcess);
    ~Network();
    /**
     * @brief isCreated
     * @return true if the network successfully created and running
     */
    bool isCreated() { return _running; }
    /**
     * @brief send send the attribut _picture to the server (unused)
     */
    void send();

private slots:
    /**
     * @brief onConnect slot called when the client is connected to the server
     */
    void onConnect(void);
    /**
     * @brief onRead slot called when data is availble in the socket
     */
    void onRead(void);
    /**
     * @brief onDisconnect slot called when the clien disconnect from the server
     */
    void onDisconnect(void);
    /**
     * @brief onError slot called when a error occured on the client
     * @param er the socket error
     */
    void onError(QAbstractSocket::SocketError er);
    /**
     * @brief onForwardClic slot called when the forward button is clicked
     */
    void onForwardClic(bool);
    /**
     * @brief onBackwardClic slot called when the backward button is clicked
     */
    void onBackwardClic(bool);
    /**
     * @brief onLeftClic slot called when the left button is clicked
     */
    void onLeftClic(bool);
    /**
     * @brief onRightClic slot called when the right button is clicked
     */
    void onRightClic(bool);
    /**
     * @brief onLeftRotClic slot called when the left rotate button is clicked
     */
    void onLeftRotClic(bool);
    /**
     * @brief onRightRotClic slot called when the right rotate button is clicked
     */
    void onRightRotClic(bool);

private:    
    void onFinishRead(void);

    MainWindow* _mw;
    DisparityProcess* _disparityProcess;
    CalibDepthProcess* _depthProcess;
    TrackerProcess* _trackerProcess;

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
