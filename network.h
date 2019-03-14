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

#define MAX_BUFF_SIZE 700000


class MainWindow;

class Network : public QTcpSocket
{
    Q_OBJECT

public:
    Network(MainWindow* mw, const QString& host, quint16 port, QObject* parent = nullptr);
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

    QByteArray _data;
    QImage _picture;
};

#endif // NETWORK_H
