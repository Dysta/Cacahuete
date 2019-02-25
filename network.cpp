#include "network.h"

Network::Network(const QString& host, quint16 port, QObject* parent)
    : QTcpSocket(parent), _host(host), _port(port)
{
    connect(this, SIGNAL(connected()),
            this, SLOT(onConnect()));
    connect(this, SIGNAL(readyRead()),
            this, SLOT(onRead()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(onDisconnect()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));

    this->connectToHost(this->_host, this->_port);
}

Network::~Network() {

}

void Network::onConnect() {
    std::cout << "successfully connected to host " << this->_host.toStdString()
              << " and port " << this->_port << std::endl;
}

void Network::onRead() {
    std::cout << "on read" << std::endl;
}

void Network::onDisconnect() {
    std::cout << "on disconnect" << std::endl;
}

void Network::onError(QAbstractSocket::SocketError er) {
    std::cout << "Error : " << this->errorString().toStdString() << std::endl;
}
