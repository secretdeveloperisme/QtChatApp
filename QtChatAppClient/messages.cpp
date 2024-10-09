#include "messages.h"
#include <QJsonObject>
#include <qjsondocument.h>

Messages::Messages() {}

quint64 Messages::size()
{
    return messages.size();
}

QList<Message> Messages::getMessages()
{
    return messages;
}

void Messages::addMessage(const Message &message)
{
    messages.append(message);
}

QJsonDocument Messages::toJson()
{
    QJsonArray jsonArray;

    if (messages.isEmpty()) {
        return {};
    }
    foreach (Message message, messages) {
        jsonArray.append(message.toJson().object());
    }
    QJsonDocument document;
    document.setArray(jsonArray);

    return document;
}

Messages Messages::fromJson(QJsonDocument document)
{
    Messages messages;
    QJsonArray jsonArray = document.array();
    for (int i = 0; i < jsonArray.size(); i++) {
        QJsonValue value = jsonArray.at(i);
        QJsonObject object = value.toObject();
        Message message = Message::fromJsonObject(object);
        messages.addMessage(message);
    }
    return messages;
}
