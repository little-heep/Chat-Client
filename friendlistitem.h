#ifndef FRIENDLISTITEM_H
#define FRIENDLISTITEM_H

#include <QListWidgetItem>
#include <allstructs.h>

class FriendListItem : public QListWidgetItem
{
public:
    FriendListItem(const FriendInfo &info);


    const FriendInfo &info() const { return m_info; }

    QString getid();

private:
    FriendInfo m_info;
};

#endif // FRIENDLISTITEM_H
