#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "messagelistmodel.h"
#include <message.h>
#include <qtypes.h>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient(QObject *parent = nullptr);

    bool init();
    void setMessageListModel(MessageListModel *messageListModel);

    Q_INVOKABLE bool sendMessage(quint64 ownerId,
                                 const QString &onwerName,
                                 quint64 groupId,
                                 const QString &groupName,
                                 const QString &content);
    Q_INVOKABLE bool loadMessageByGroupId(quint64 groupId);

signals:
    void receivedMessage(quint64 ownerId,
                         const QString &onwerName,
                         quint64 groupId,
                         const QString &groupName,
                         const QString &content);
private:
    const static QHostAddress serverAddress;
    const static quint16 serverPort;
    quint64 userId;
    quint64 groupId;
    QTcpSocket *client;
    bool isConnected;
    MessageListModel *messageListModel;

private slots:
    void onReadyRead();
    void onDisconnected();
    void onConnected();
};

#endif // CHATCLIENT_H
