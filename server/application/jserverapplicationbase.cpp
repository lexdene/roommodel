#include "jserverapplicationbase.h"

#include "../common/jroomerrorcode.h"

JServerApplicationBase::JServerApplicationBase(JID roomId,QObject *parent) :
    QObject(parent)
{
	m_roomId = roomId;
}

JID JServerApplicationBase::getRoomId()const
{
	return m_roomId;
}

JCode JServerApplicationBase::enterRoom(JID userId)
{
	if(userId<0){
		return EUserIdNotExist;
	}else{
		return ESuccess;
	}
}

void JServerApplicationBase::processGameData(int , const QByteArray&)
{
}

void JServerApplicationBase::receiveRoomChat(JID userId,const QString& text)
{
    emit roomChat(userId,getRoomId(),text);
}
