#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QImage>
#include <QString>

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

private:

    MainWindow* _mw;

    QString _host;
    quint16 _port;
    bool _running;

    QByteArray _data;
    QImage _picture;
};

#endif // NETWORK_H
