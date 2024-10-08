#include "message.h"
#include <QJsonObject>
#include <qjsondocument.h>

QJsonDocument Message::toJson()
{
    QJsonDocument json;
    QJsonObject object{{"id", static_cast<qint64>(id)},
                       {"onwerId", static_cast<qint64>(ownerId)},
                       {"ownerName", ownerName},
                       {"groupId", static_cast<qint64>(groupId)},
                       {"groupName", groupName},
                       {"content", content},
                       {"createdDate", createdDate.toUTC().toString()}};

    json.setObject(object);
    return json;
}

Message Message::fromJson(const QJsonDocument &jsonDocument)
{
    Message message;
    message.id = jsonDocument["id"].toInt();
    message.ownerId = jsonDocument["onwerId"].toInt();
    message.ownerName = jsonDocument["ownerName"].toString();
    message.groupId = jsonDocument["groupId"].toInt();
    message.groupName = jsonDocument["groupName"].toString();
    message.content = jsonDocument["content"].toString();
    message.createdDate = QDateTime::fromString(jsonDocument["createdDate"].toString());
    return message;
}

quint64 Message::getId() const
{
    return id;
}

void Message::setId(quint64 newId)
{
    if (id == newId)
        return;
    id = newId;
}

quint64 Message::getOwnerId() const
{
    return ownerId;
}

void Message::setOwnerId(quint64 newOwnerId)
{
    if (ownerId == newOwnerId)
        return;
    ownerId = newOwnerId;
}

quint64 Message::getGroupId() const
{
    return groupId;
}

void Message::setGroupId(quint64 newGroupId)
{
    if (groupId == newGroupId)
        return;
    groupId = newGroupId;
}

QDateTime Message::getCreatedDate() const
{
    return createdDate;
}

void Message::setCreatedDate(const QDateTime &newCreatedDate)
{
    if (createdDate == newCreatedDate)
        return;
    createdDate = newCreatedDate;
}

QString Message::getContent() const
{
    return content;
}

void Message::setContent(const QString &newContent)
{
    if (content == newContent)
        return;
    content = newContent;
}

Message::Message() {}

Message::Message(quint64 ownerId,
                 const QString &ownerName,
                 quint64 groupId,
                 const QString &groupName,
                 const QString &content,
                 const QDateTime &createdDate)
    : ownerId(std::move(ownerId))
    , ownerName(ownerName)
    , groupId(std::move(groupId))
    , groupName(groupName)
    , content(content)
    , createdDate(createdDate)
{}

Message::Message(quint64 id,
                 quint64 ownerId,
                 const QString &ownerName,
                 quint64 groupId,
                 const QString &groupName,
                 const QString &content,
                 const QDateTime &createdDate)
    : id(std::move(id))
    , ownerId(std::move(ownerId))
    , ownerName(ownerName)
    , groupId(std::move(groupId))
    , groupName(groupName)
    , content(content)
    , createdDate(createdDate)
{}
