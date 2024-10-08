// ChatServer.cpp
#include "chatserver.h"
#include <QDebug>
#include <QTextStream>
#include "messagehandler.h"
#include "messagepacket.h"
#include <qjsondocument.h>

QHostAddress ChatServer::address = QHostAddress::Any;
quint16 ChatServer::port = 8080;

ChatServer::ChatServer(QObject *parent)
    : QObject(parent)
    , server{new QTcpServer(this)}
{
    connect(server, &QTcpServer::newConnection, this, &ChatServer::incomingConnection);
}

bool ChatServer::startServer()
{
    if (!server->listen(address, port)) {
        qCritical() << "Could not start server";
        return false;
    }
    emit logMessage(QString("Server is listening on port %1").arg(port));
    return true;
}

bool ChatServer::stopServer()
{
    if (server->isListening()) {
        server->close();
        qDebug() << "Stop server....";
        emit logMessage("Stop server...");
        return true;
    }
    return false;
}

void ChatServer::incomingConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients << clientSocket;
    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::onClientDisconnected);

    qDebug() << "Client connected:" << clientSocket->peerAddress().toString();
    emit logMessage(QString("A new client has connected: %1: %2")
                        .arg(clientSocket->peerAddress().toString())
                        .arg(clientSocket->peerPort()));
}

void ChatServer::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;
    if (clientSocket->bytesAvailable() <= 0) {
        return;
    }
    char rawBuffer[1024];
    QByteArray buffer;
    QByteArray content;

    int readBytes{0};
    int indexOf{-1};
    while ((readBytes = clientSocket->read(rawBuffer, 1024)) > 0) {
        buffer.setRawData(rawBuffer, readBytes);
        if ((indexOf = buffer.indexOf(MessagePacket::END_MESSAGE)) > 0) {
            content.append(buffer, indexOf);
        } else {
            content.append(buffer, readBytes);
        }
    }
    if (buffer.isEmpty())
        return;
    bool result{false};
    qint8 messageType = content[0];
    switch (messageType) {
    case MessagePacket::OPCODE::GET_MESSAGES:
        databaseManager.getMessagesByGroup(1);
        break;
    case MessagePacket::OPCODE::SEND:
        Message message = MessageHandler::parseRawMessage(content.mid(1), result);
        if (!result) {
            qCritical() << "Cannot parse message from client";
            return;
        }

        qDebug() << "Received message:" << message.toJson();

        emit logMessage(QString("Received message from %1:%2")
                            .arg(clientSocket->peerAddress().toString())
                            .arg(clientSocket->peerPort()));
        if (!databaseManager.addMessage(message)) {
            qCritical() << "Could not insert message to database";
            return;
        }
        broadcastMessage(MessagePacket(MessagePacket::OPCODE::SEND, content).toRawPacket(),
                         clientSocket);
    }
}

void ChatServer::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
    emit logMessage(QString("Client disconnected: %1: %2")
                        .arg(clientSocket->peerAddress().toString())
                        .arg(clientSocket->peerPort()));
}

void ChatServer::broadcastMessage(const QByteArray &content, QTcpSocket *excludeClient)
{
    for (QTcpSocket *client : clients) {
        if (client != excludeClient) {
            client->write(content);
            client->flush();
        }
    }
}
