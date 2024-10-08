
#ifndef CHATDATABASEMANAGER_H
#define CHATDATABASEMANAGER_H

#include "message.h"

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class ChatDatabaseManager
{
public:
    ChatDatabaseManager();

    ~ChatDatabaseManager();

    // Add a new user to the database
    bool addUser(const QString &username);

    // Add a new group to the database
    bool addGroup(const QString &groupName);

    // Add a new message
    bool addMessage(const Message &messsage);

    // Fetch messages by group
    void getMessagesByGroup(int groupId);

private:
    QSqlDatabase db;

    // Connect to the database
    bool connect();

    // Create tables
    bool createTables();
};

#endif // CHATDATABASEMANAGER_H
