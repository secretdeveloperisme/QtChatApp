#ifndef MESSAGES_H
#define MESSAGES_H

#include "message.h"

#include <QJsonArray>
#include <QList>

class Messages
{
public:
    Messages();
    quint64 size();
    QList<Message> getMessages();
    void addMessage(const Message &message);
    QJsonDocument toJson();
    static Messages fromJson(QJsonDocument document);

    using iterator = QList<Message>::iterator;
    using const_iterator = QList<Message>::const_iterator;

    iterator begin() { return messages.begin(); }
    iterator end() { return messages.end(); }

    const_iterator begin() const { return messages.begin(); }
    const_iterator end() const { return messages.end(); }

private:
    QList<Message> messages;
};

#endif // MESSAGES_H
