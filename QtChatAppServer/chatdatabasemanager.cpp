#include "chatdatabasemanager.h"

ChatDatabaseManager::ChatDatabaseManager()
{
    if (!connect()) {
        qDebug() << "Database connection failed!";
    } else {
        if (!createTables()) {
            qDebug() << "Failed to create tables!";
        }
    }
}

ChatDatabaseManager::~ChatDatabaseManager()
{
    db.close();
}

bool ChatDatabaseManager::addUser(const QString &username)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CHAT_USERS (username) VALUES (:username)");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to insert user:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ChatDatabaseManager::addGroup(const QString &groupName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CHAT_GROUPS (name) VALUES (:name)");
    query.bindValue(":name", groupName);

    if (!query.exec()) {
        qDebug() << "Failed to insert group:" << query.lastError().text();
        return false;
    }
    return true;
}

bool ChatDatabaseManager::addMessage(const Message &message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO chat_messages (content, createdDate, user_id, group_id) "
                  "VALUES (:content, :createdDate, :user_id, :group_id)");
    query.bindValue(":content", message.getContent());
    query.bindValue(":createdDate", message.getCreatedDate());
    query.bindValue(":user_id", message.getOwnerId());
    query.bindValue(":group_id", message.getGroupId());

    if (!query.exec()) {
        qDebug() << "Failed to insert message:" << query.lastError().text();
        return false;
    }
    return true;
}

void ChatDatabaseManager::getMessagesByGroup(int groupId)
{
    QSqlQuery query;
    query.prepare(
        "SELECT content, createdDate, user_id FROM chat_messages WHERE group_id = :group_id");
    query.bindValue(":group_id", groupId);

    if (!query.exec()) {
        qDebug() << "Failed to fetch messages:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString content = query.value(0).toString();
        QString createdDate = query.value(1).toString();
        int userId = query.value(2).toInt();

        qDebug() << "User ID:" << userId << "Message:" << content << "Date:" << createdDate;
    }
}

bool ChatDatabaseManager::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // Changed to SQLite
    db.setDatabaseName("chat_app.db");         // SQLite stores data in a file

    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
        return false;
    }
    return true;
}

bool ChatDatabaseManager::createTables()
{
    QSqlQuery query;
    QString createChatUsers = "CREATE TABLE IF NOT EXISTS CHAT_USERS ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "username TEXT NOT NULL UNIQUE)";

    QString createChatGroups = "CREATE TABLE IF NOT EXISTS CHAT_GROUPS ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT NOT NULL UNIQUE)";

    QString createChatMessages = "CREATE TABLE IF NOT EXISTS CHAT_MESSAGES ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "content TEXT NOT NULL, "
                                 "createdDate TEXT, "
                                 "user_id INTEGER NOT NULL, "
                                 "group_id INTEGER NOT NULL, "
                                 "FOREIGN KEY (user_id) REFERENCES CHAT_USERS(id), "
                                 "FOREIGN KEY (group_id) REFERENCES CHAT_GROUPS(id))";

    if (!query.exec(createChatUsers)) {
        qDebug() << "Failed to create CHAT_USERS table:" << query.lastError().text();
        return false;
    }

    if (!query.exec(createChatGroups)) {
        qDebug() << "Failed to create CHAT_GROUPS table:" << query.lastError().text();
        return false;
    }

    if (!query.exec(createChatMessages)) {
        qDebug() << "Failed to create chat_messages table:" << query.lastError().text();
        return false;
    }

    return true;
}
