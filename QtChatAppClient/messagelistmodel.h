#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "../QtChatAppServer/message.h"

class MessageListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MessageListModel(QObject *parent = nullptr);

    enum MessageRoles {
        IdRole = Qt::UserRole + 1,
        OwnerIdRole,
        OwnerNameRole,
        GroupIdRole,
        GroupNameRole,
        ContentRole,
        CreatedDateRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addMessage(const Message &message);

private:
    QVector<Message> m_messages;
};

#endif // MESSAGELISTMODEL_H
