#include "network.h"
#include "mainwindow.h"

Network::Network(MainWindow* mw, const QString& host, quint16 port, QObject* parent)
    : QTcpSocket(parent), _mw(mw), _host(host), _port(port), _running(false)
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

void Network::send() {
    QByteArray arr = QByteArray::fromRawData((const char *) this->_mw->getPicture()->bits(), this->_mw->getPicture()->bytesPerLine());
    this->write(arr);
}

void Network::onConnect() {
    std::cout << "successfully connected to host " << this->_host.toStdString()
              << " and port " << this->_port << std::endl;
    this->_mw->setNetworkSuccess(true);
    this->write("ready to receive");
}

void Network::onRead() {
    std::cout << std::endl << "on read" << std::endl;
    QTcpSocket* soc = qobject_cast<QTcpSocket *>(sender());
    if (soc == nullptr) return;

    while (soc->bytesAvailable() > 0) {
        this->_data.append(soc->readAll());
    }

    qDebug() << "\n\ndata receive : " << this->_data;
    this->_picture = QImage::fromData(this->_data, "PNG");
    this->_mw->setOriPucture(this->_picture.copy());
    this->_mw->copyImage();
    this->_mw->updateImage();
}

void Network::onDisconnect() {
    std::cout << "on disconnect" << std::endl;
    this->_mw->setNetworkSuccess(false);
}

void Network::onError(QAbstractSocket::SocketError) {
    std::cout << "Error : " << this->errorString().toStdString() << std::endl;
}
