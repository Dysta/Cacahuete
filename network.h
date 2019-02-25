#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

class Network : public QTcpSocket
{
    Q_OBJECT

public:
    Network(const QString& host, quint16 port, QObject* parent = nullptr);
    ~Network();

private slots:
    void onConnect(void);
    void onRead(void);
    void onDisconnect(void);
    void onError(QAbstractSocket::SocketError er);

private:
    void send(const QByteArray& data);

    QString _host;
    quint16 _port;
};

#endif // NETWORK_H
