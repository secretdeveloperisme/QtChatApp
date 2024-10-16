#include "messagehandler.h"

#include "messagepacket.h"

#include <QJsonDocument>
#include <message.h>

MessageHandler::MessageHandler() {}

Message MessageHandler::parseRawMessage(const QByteArray &rawBytes, bool &result)
{
    if (rawBytes.length() > 0) {
        if (rawBytes[0] == MessagePacket::SEND) {
            qDebug() << "MessageHandler::parseRawMessage: SEND package";
            QJsonDocument document = QJsonDocument::fromJson(rawBytes.mid(1, rawBytes.length() - 1));
            Message message = Message::fromJson(document);
            result = true;
            return message;
        }
    }
    result = false;
    return {};
}
