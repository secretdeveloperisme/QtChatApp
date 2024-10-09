#include "chatclient.h"
#include <QDataStream>
#include <QDebug>
#include <QHostAddress>
#include <QJsonDocument>
#include "messagehandler.h"
#include "messagepacket.h"
#include "messages.h"
#include "string.h"

const QHostAddress ChatClient::serverAddress{"127.0.0.1"};
const quint16 ChatClient::serverPort{8080};

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
    , client(new QTcpSocket(this))
    , isConnected(false)
{
    connect(client, &QTcpSocket::readyRead, this, &ChatClient::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ChatClient::onDisconnected);
    connect(client, &QTcpSocket::connected, this, &ChatClient::onConnected);
}

bool ChatClient::init()
{
    if (isConnected)
        return true;

    client->connectToHost(serverAddress, serverPort);

    if (!client->waitForConnected(5000)) {
        qDebug() << "Connection failed:" << client->errorString();
        return false;
    }

    isConnected = true;
    return true;
}

void ChatClient::setMessageListModel(MessageListModel *messageListModel)
{
    this->messageListModel = messageListModel;
}

Q_INVOKABLE bool ChatClient::sendMessage(quint64 ownerId,
                                         const QString &ownerName,
                                         quint64 groupId,
                                         const QString &groupName,
                                         const QString &content)
{
    if (!isConnected) {
        qDebug() << "Not connected to the server.";
        return false;
    }

    Message message{ownerId, ownerName, groupId, groupName, content, QDateTime::currentDateTime()};
    messageListModel->addMessage(message);
    MessagePacket packet{MessagePacket::SEND, message.toJson().toJson()};

    client->write(packet.toRawPacket());
    return client->waitForBytesWritten();
}

bool ChatClient::loadMessageByGroupId(quint64 groupId)
{
    QByteArray data;
    char bytes[8];
    memcpy(bytes, &groupId, sizeof(quint64));
    data.append(bytes);

    MessagePacket packet{MessagePacket::REQUEST_MESSAGES, data};

    client->write(packet.toRawPacket());
    return client->waitForBytesWritten();
}

void ChatClient::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;
    if (clientSocket->bytesAvailable() <= 0) {
        return;
    }
    char rawBuffer[1024]{0};

    QByteArray content;

    int readBytes{0};
    int indexOf{-1};

    bool firstSection = true;

    while (true) {
        if ((readBytes = clientSocket->read(rawBuffer, 1024)) <= 0)
            break;
        QByteArray buffer;
        buffer.setRawData(rawBuffer, readBytes);
        if (firstSection) {
            if (!buffer.startsWith(MessagePacket::BEGIN_MESSGAGE)) {
                qCritical() << "Invalid packet format";
                return;
            }
            firstSection = false;
            buffer = buffer.mid(2, buffer.length() - 2);
        }
        if ((indexOf = buffer.indexOf(MessagePacket::END_MESSAGE)) > 0) {
            content.append(buffer, indexOf);
        } else {
            content.append(buffer);
        }
    }
    if (content.isEmpty())
        return;
    bool result{false};
    quint8 opcode = content[0];
    QByteArray data = content.mid(1, content.length() - 1);

    switch (opcode) {
    case MessagePacket::OPCODE::GET_MESSAGES: {
        QJsonDocument messagesJson = QJsonDocument::fromJson(data);
        if (messagesJson.isArray()) {
            Messages messages = Messages::fromJson(messagesJson);
            for (auto message = messages.begin(); message != messages.end(); message++) {
                this->messageListModel->addMessage(*message);
            }
        }
        break;
    }

    case MessagePacket::OPCODE::SEND:
        Message message = MessageHandler::parseRawMessage(data, result);
        if (!result) {
            qCritical() << "Cannot parse message from client";
            return;
        }
        messageListModel->addMessage(message);
        emit receivedMessage(message.getOwnerId(),
                             message.getOwnerName(),
                             message.getGroupId(),
                             message.getGroupName(),
                             message.getContent());
        break;
    }
}

void ChatClient::onDisconnected()
{
    isConnected = false;
    qDebug() << "Disconnected from server.";
}

void ChatClient::onConnected()
{
    isConnected = true;
    qDebug() << "Connected to server.";
}
