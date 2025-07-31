#include "friendlistitem.h"

FriendListItem::FriendListItem(const FriendInfo &info)
    : QListWidgetItem(), m_info(info) {
    // 设置显示文本
    setText(info.name);

    // 设置图标（头像）


}

QString FriendListItem::getid()
{
    return m_info.userID;
}
