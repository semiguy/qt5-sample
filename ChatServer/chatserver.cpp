#include <QtWidgets>
#include <QRegExp>
#include "chatserver.h"

chatServer::chatServer(QObject *parent) : QTcpServer(parent)
{

}

void chatServer::incomingConnection(int socketfd)
{
    qDebug("chatServer::incomingConnection = socketfd[%d]", socketfd);

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    emit clients_signal(clients.count());

    QString str;
    str = QString("New Client from: %1").arg(client->peerAddress().toString());

    emit message_signal(str);

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void chatServer::readyRead()
{
    qDebug("chatServer::readyRead()");

    QTcpSocket *client = (QTcpSocket*)sender();

    while(client->canReadLine()) {
        QString line = QString::fromUtf8(client->readLine()).trimmed();

        QString str;
        str = QString("Read line %1").arg(line);

        emit message_signal(str);

        QRegExp meRegex("^/me:(.*)$");

        if(meRegex.indexIn(line) != -1) {
            QString user = meRegex.cap(1);
            users[client] = user;
            foreach(QTcpSocket *client, clients) {
                client->write(QString("Server: %1 connect").arg(user).toUtf8());
            }
            sendUserList();
        } else if(users.contains(client)) {
            QString message = line;
            QString user = users[client];

            QString str;
            str = QString("User: %1, Message: %2").arg(user).arg(message);
            emit message_signal(str);

            foreach(QTcpSocket *otherClient, clients) {
                otherClient->write(QString(user+":"+message+"\n").toUtf8());
            }
        } else {
            qWarning() << "Got bad message form client:" << client->peerAddress().toString() << line;
        }
    }
}

void chatServer::disconnected()
{
    qDebug("chatServer::disconnected()");

    QTcpSocket *client = (QTcpSocket*)sender();

    QString str;
    str = QString("Client disconnected:: %1").arg(client->peerAddress().toString());

    emit message_signal(str);

    clients.remove(client);

    emit clients_signal(clients.count());

    QString user = users[client];
    users.remove(client);

    sendUserList();

    foreach(QTcpSocket *client, clients) {
        client->write(QString("Server:%1 disconnect").arg(user).toUtf8());
    }
}

void chatServer::sendUserList()
{
    qDebug("chatServer::sendUserList()");

    QStringList userList;
    foreach(QString user, users.values()) {
        userList << user;
    }

    foreach(QTcpSocket *client, clients) {
        client->write(QString("/users:" + userList.join(",") + "\n").toUtf8());
    }
}
