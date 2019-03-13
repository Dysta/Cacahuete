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
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    this->_mw->getLeftPicture()->save(&buffer, "PNG");
    this->write(arr);
}

void Network::onConnect() {
    std::cout << "successfully connected to host " << this->_host.toStdString()
              << " and port " << this->_port << std::endl;
    this->_mw->setNetworkSuccess(true);
}

void Network::onRead() {
    qDebug() << "\n\n====================";
    qDebug() << "current data : " << this->_data;
    if (this->_data.isEmpty()) qDebug() << "data  vide";//this->_data.clear();
    QTcpSocket* soc = qobject_cast<QTcpSocket *>(sender());
    if (soc == nullptr) return;

    qDebug() << soc->bytesAvailable();
    this->_data.append(soc->readAll());

    qDebug() << "data size = " << this->_data.size();

    this->_picture = QImage::fromData(this->_data, "PNG");
    QImage left = this->_picture.copy(0, 0, this->_picture.width()/2, this->_picture.height());
    QImage right = this->_picture.copy(this->_picture.width()/2, 0, this->_picture.width()/2, this->_picture.height());
    this->_mw->setOriLeftPucture(left.copy());
    this->_mw->setOriRightPucture(right.copy());
    this->_mw->copyImage();
    this->_mw->updateImage();
    //this->_data.clear();
}

void Network::onDisconnect() {
    std::cout << "on disconnect" << std::endl;
    this->_mw->setNetworkSuccess(false);
}

void Network::onError(QAbstractSocket::SocketError) {
    std::cout << "Error : " << this->errorString().toStdString() << std::endl;
}
