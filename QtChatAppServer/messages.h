#ifndef MESSAGES_H
#define MESSAGES_H

#include "message.h"

#include <QJsonArray>
#include <QList>

class Messages
{
    QList<Message> messages;

public:
    Messages();
    quint64 size();
    void addMessage(const Message &message);
    QJsonDocument toJson();
    static Messages fromJson(QJsonDocument document);
};

#endif // MESSAGES_H
