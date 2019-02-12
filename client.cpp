#include "client.h"
#include "widget.h"

extern Widget* widget;

Client::Client(QString strHost, quint16 nPort, QWidget *pwgt) :QWidget(pwgt), host(strHost), port(nPort)
{
    nextBlockSize = 0;
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);

    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(slotError(QAbstractSocket::SocketError)));

}

void Client::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!nextBlockSize) {
            if (socket->bytesAvailable() < sizeof(quint16))
                break;
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize)
            break;

        QString str;
        in >> str;
        widget->setRecords(str);
        nextBlockSize = 0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(socket->errorString())
                    );
    qDebug() << strError;
    widget->errorConnection(true);
}

void Client::sendToServer(QString request)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << request;

    out.device()->seek(0);
    out << quint16(static_cast<unsigned int>(arrBlock.size()) - sizeof(quint16));

    socket->write(arrBlock);
}
