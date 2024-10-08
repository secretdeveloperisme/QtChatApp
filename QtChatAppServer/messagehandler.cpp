#include "messagehandler.h"

#include <QJsonDocument>
#include <message.h>

MessageHandler::MessageHandler() {}

Message MessageHandler::parseRawMessage(const QByteArray &rawBytes, bool &result)
{
    qDebug() << "MessageHandler::parseRawMessage begin";
    if (rawBytes.length() > 0) {
        qDebug() << "MessageHandler::parseRawMessage: SEND package";
        qDebug() << "MessageHandler::parseRawMessage: rawJson " << rawBytes;
        QJsonDocument document = QJsonDocument::fromJson(rawBytes);
        Message message = Message::fromJson(document);
        result = true;
        return message;
    }
    result = false;
    return {};
}
