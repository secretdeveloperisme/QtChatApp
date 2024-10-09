#include "messagepacket.h"

const QByteArrayView MessagePacket::BEGIN_MESSGAGE{"\n\r"};
const QByteArrayView MessagePacket::END_MESSAGE{"\r\n"};

MessagePacket::MessagePacket() {}

MessagePacket::MessagePacket(MessagePacket::OPCODE opcode, const QByteArray &data)
    : opcode(opcode)
    , data(data)
{}

MessagePacket::OPCODE MessagePacket::getOpcode() const
{
    return opcode;
}

void MessagePacket::setOpcode(OPCODE newOpcode)
{
    opcode = newOpcode;
}

QByteArray MessagePacket::getData() const
{
    return data;
}

void MessagePacket::setData(const QByteArray &newData)
{
    data = newData;
}

QByteArray MessagePacket::toRawPacket()
{
    QByteArray rawPacket;
    rawPacket.append(BEGIN_MESSGAGE);
    rawPacket.append(opcode);
    rawPacket.append(data);
    rawPacket.append(END_MESSAGE);
    return rawPacket;
}
