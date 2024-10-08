#include "messagelistmodel.h"

MessageListModel::MessageListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int MessageListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return QVariant();

    const Message &message = m_messages[index.row()];

    switch (role) {
    case IdRole:
        return message.getId();
    case OwnerIdRole:
        return message.getOwnerId();
    case OwnerNameRole:
        return message.getOwnerName();
    case GroupIdRole:
        return message.getGroupId();
    case GroupNameRole:
        return message.getGroupName();
    case ContentRole:
        return message.getContent();
    case CreatedDateRole:
        return message.getCreatedDate();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MessageListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[OwnerIdRole] = "ownerId";
    roles[OwnerNameRole] = "ownerName";
    roles[GroupIdRole] = "groupId";
    roles[GroupNameRole] = "groupName";
    roles[ContentRole] = "content";
    roles[CreatedDateRole] = "createdDate";
    return roles;
}

void MessageListModel::addMessage(const Message &message)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(message);
    endInsertRows();
}
