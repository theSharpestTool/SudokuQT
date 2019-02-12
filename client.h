#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QDebug>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(QString strHost, quint16 nPort, QWidget* pwgt = nullptr);
    void sendToServer(QString request);

private:
    QTcpSocket* socket;
    quint16 nextBlockSize;
    QString host;
    quint16 port;

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
};

#endif // CLIENT_H
