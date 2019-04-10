#include "network.h"
#include "mainwindow.h"

Network::Network(MainWindow* mw, const QString& host, quint16 port, DisparityProcess* dispProcess, CalibDepthProcess* depthProcess, TrackerProcess* trackerProcess)
    : QTcpSocket((QObject*) mw), _mw(mw), _host(host), _port(port),
      _running(false), _sizeReceived(false)
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

    this->_disparityProcess = dispProcess;
    this->_depthProcess = depthProcess;
    this->_trackerProcess = trackerProcess;
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
    QMessageBox::information(this->_mw, "Information", "Connecté avec succes");
    this->_mw->setNetworkSuccess(true);

    this->_botControllWidget = new QWidget();
    this->_botControlLayout = new QGridLayout();

    this->_forwardButton = new QPushButton("^");
    this->_backwardButton = new QPushButton("v");
    this->_leftButton = new QPushButton("<");
    this->_rightButton = new QPushButton(">");
    this->_leftRotButton = new QPushButton("<<");
    this->_rightRotButton = new QPushButton(">>");

    this->_forwardButton->setShortcut(Qt::Key_Z);
    this->_backwardButton->setShortcut(Qt::Key_S);
    this->_leftButton->setShortcut(Qt::Key_Q);
    this->_rightButton->setShortcut(Qt::Key_D);
    this->_leftRotButton->setShortcut(Qt::Key_A);
    this->_rightRotButton->setShortcut(Qt::Key_E);

    this->_botControlLayout->addWidget(this->_forwardButton, 0, 0, 1, 2);
    this->_botControlLayout->addWidget(this->_leftButton, 1, 0);
    this->_botControlLayout->addWidget(this->_rightButton, 1, 1);
    this->_botControlLayout->addWidget(this->_backwardButton, 2, 0, 1, 2);
    this->_botControlLayout->addWidget(this->_leftRotButton, 3, 0);
    this->_botControlLayout->addWidget(this->_rightRotButton, 3, 1);

    this->_botControllWidget->setWindowTitle("Controle du robot");
    this->_botControllWidget->setLayout(this->_botControlLayout);

    this->_botControllWidget->show();

    connect(this->_forwardButton, SIGNAL(clicked(bool)),
            this, SLOT(onForwardClic(bool)));
    connect(this->_backwardButton, SIGNAL(clicked(bool)),
            this, SLOT(onBackwardClic(bool)));
    connect(this->_leftButton, SIGNAL(clicked(bool)),
            this, SLOT(onLeftClic(bool)));
    connect(this->_rightButton, SIGNAL(clicked(bool)),
            this, SLOT(onRightClic(bool)));
    connect(this->_leftRotButton, SIGNAL(clicked(bool)),
            this, SLOT(onLeftRotClic(bool)));
    connect(this->_rightRotButton, SIGNAL(clicked(bool)),
            this, SLOT(onRightRotClic(bool)));
}

void Network::onRead() {
    QTcpSocket* soc = qobject_cast<QTcpSocket *>(sender());
    if (soc == nullptr) return;

    if (!_sizeReceived) {
        this->_dataSize = soc->read(4).toHex();
        this->_sizeReceived = true;
        this->_data.clear();
    }

    this->_data.append(soc->readAll());

    if (this->_data.size() > 0 && this->_data.size() == this->_dataSize.toInt(nullptr, 16)) {
        this->_picture = QImage::fromData(this->_data, "PNG");
        if (!this->_picture.isNull()) { // si l'image est chargé complètement
            this->onFinishRead();
        } else { // on a raté le chargement
            qDebug() << "raté";
        }
    }

    if (this->_data.size() >= MAX_BUFF_SIZE) this->_data.clear();
}

void Network::onDisconnect() {
    this->_mw->setNetworkSuccess(false);
    delete this->_botControlLayout;
    delete this->_botControllWidget;
}

void Network::onError(QAbstractSocket::SocketError) {
    QMessageBox::critical(this->_mw, "Erreur", this->errorString().toStdString().c_str());
}

void Network::onFinishRead() {
    QImage left = this->_picture.copy(0, 0, this->_picture.width()/2, this->_picture.height());
    QImage right = this->_picture.copy(this->_picture.width()/2, 0, this->_picture.width()/2, this->_picture.height());
    this->_mw->setOriLeftPucture(left.copy());
    this->_mw->setOriRightPucture(right.copy());
    this->_mw->copyImage();
    this->_mw->updateImage();

    this->_data.clear();
    this->_dataSize.clear();
    this->_sizeReceived = false;

    this->_disparityProcess->process();
    this->_depthProcess->depthMap();
    this->_trackerProcess->process();
}

void Network::onForwardClic(bool) {
    this->write("F");
}
void Network::onBackwardClic(bool) {
    this->write("B");
}
void Network::onLeftClic(bool) {
    this->write("L");
}
void Network::onRightClic(bool) {
    this->write("R");
}
void Network::onLeftRotClic(bool) {
    this->write("O");
}
void Network::onRightRotClic(bool) {
    this->write("A");
}
