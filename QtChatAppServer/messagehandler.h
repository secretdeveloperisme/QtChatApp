#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "message.h"

#include <QString>
class MessageHandler
{
public:
    MessageHandler();
    static Message parseRawMessage(const QByteArray &rawBytes, bool &result);

private:
};

#endif // MESSAGEHANDLER_H
