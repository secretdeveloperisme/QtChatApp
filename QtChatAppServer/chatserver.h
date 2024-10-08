// ChatServer.h
#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "chatdatabasemanager.h"

#include <QList>
#include <QTcpServer>
#include <QTcpSocket>

class ChatServer : public QObject
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent = nullptr);
    Q_INVOKABLE bool startServer();
    Q_INVOKABLE bool stopServer();

signals:
    void logMessage(const QString &message);

private slots:
    void incomingConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    static QHostAddress address;
    static quint16 port;
    QTcpServer *server;
    QList<QTcpSocket *> clients;
    ChatDatabaseManager databaseManager;

    void broadcastMessage(const QByteArray &content, QTcpSocket *excludeClient = nullptr);
};

#endif // CHATSERVER_H
