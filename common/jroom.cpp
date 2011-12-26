#include "jroom.h"

#include <QDataStream>

JRoom::JRoom()
{
    m_roomId = -1;
	m_max=0;
}

void JRoom::setRoomId(JID roomId)
{
	m_roomId = roomId;
}

JID JRoom::getRoomId()const
{
	return m_roomId;
}

void JRoom::setTitle(const QString& title)
{
    m_title = title;
}

const QString& JRoom::getTitle()const
{
	return m_title;
}

//int& JRoom::rNum()
//{
//    return m_num;
//}

int JRoom::getNum()const
{
    return m_userlist.length();
}

void JRoom::setMax(int nmax)
{
    m_max = nmax;
}

int JRoom::getMax()const
{
	return m_max;
}

const QList<JID>& JRoom::getUserList()const
{
    return m_userlist;
}

void JRoom::addUser(JID userId)
{
    m_userlist.push_back(userId);
}

void JRoom::removeUser(JID userId)
{
    m_userlist.removeAll(userId);
}

QDataStream& operator>>(QDataStream& stream,JRoom& room)
{
	stream>>room.m_roomId;
    stream>>room.m_title;
	stream>>room.m_max;
    stream>>room.m_userlist;
	return stream;
}

QDataStream& operator<<(QDataStream& stream,const JRoom& room)
{
	stream<<room.m_roomId;
    stream<<room.m_title;
	stream<<room.m_max;
    stream<<room.m_userlist;
	return stream;
}
