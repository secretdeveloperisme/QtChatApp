#ifndef MESSAGE_H
#define MESSAGE_H
#include <QDateTime>
#include <QString>
class Message
{
private:
    quint64 id;
    quint64 ownerId;
    QString ownerName;
    quint64 groupId;
    QString groupName;
    QString content;
    QDateTime createdDate;

public:
    Message();

    Message(quint64 ownerId, quint64 groupId, const QString &content, const QDateTime &createdDate);

    Message(quint64 ownerId,
            const QString &ownerName,
            quint64 groupId,
            const QString &groupName,
            const QString &content,
            const QDateTime &createdDate);
    Message(quint64 id,
            quint64 ownerId,
            const QString &ownerName,
            quint64 groupId,
            const QString &groupName,
            const QString &content,
            const QDateTime &createdDate);

    QJsonDocument toJson();
    static Message fromJson(const QJsonDocument &jsonDocument);

    //getter settter
    quint64 getId() const;
    void setId(quint64 newId);
    quint64 getOwnerId() const;
    void setOwnerId(quint64 newOwnerId);
    quint64 getGroupId() const;
    void setGroupId(quint64 newGroupId);
    QDateTime getCreatedDate() const;
    void setCreatedDate(const QDateTime &newCreatedDate);
    QString getContent() const;
    void setContent(const QString &newContent);
    QString getOwnerName() const;
    void setOwnerName(const QString &newOwnerName);
    QString getGroupName() const;
    void setGroupName(const QString &newGroupName);
};

#endif // MESSAGE_H
