#ifndef MESSAGEPACKET_H
#define MESSAGEPACKET_H

#include <QByteArray>
#include <QByteArrayView>

class MessagePacket
{
public:
    enum OPCODE { SEND = 0x12, REQUEST_MESSAGES, GET_MESSAGES, REQUEST_GROUPS, GET_GROUPS };
    const static QByteArrayView END_MESSAGE;
    const static QByteArrayView BEGIN_MESSGAGE;

    MessagePacket();
    MessagePacket(OPCODE opcode, const QByteArray &data);

    OPCODE getOpcode() const;
    void setOpcode(OPCODE newOpcode);

    QByteArray getData() const;
    void setData(const QByteArray &newData);
    QByteArray toRawPacket();

private:
    OPCODE opcode;
    QByteArray data;
};

#endif // MESSAGEPACKET_H
