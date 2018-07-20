#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets>
#include <QTcpSocket>
#include <QDebug>

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(QString strHost, int nPort, QWidget* pwgt = 0);
    void sendToServer(QString request);

private:
    QTcpSocket* socket;
    quint16 nextBlockSize;
    QString& host;
    int port;

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
};

#endif // CLIENT_H
