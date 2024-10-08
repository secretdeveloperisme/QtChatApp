#ifndef MESSAGEPACKET_H
#define MESSAGEPACKET_H

#include <QByteArray>
#include <QByteArrayView>

class MessagePacket
{
public:
    enum OPCODE { SEND = 0x12, GET_MESSAGES = 0x13, GET_GROUPS = 0x14 };
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
