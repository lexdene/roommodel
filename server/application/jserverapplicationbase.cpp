#include "jserverapplicationbase.h"

#include "../common/jroomerrorcode.h"
#include "../manager/jroommanager.h"
#include "../network/jroommodelservergamedataprocessor.h"

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

void JServerApplicationBase::sendGameData(const QByteArray& data)const{
	JRoomManager *rm = JRoomManager::instance();
	JRoomModelServerGameDataProcessor *processor = JRoomModelServerGameDataProcessor::instance();
	foreach(JSocket *socket,rm->getSocketListInRoom( getRoomId() ) ){
		processor->sendGameData( socket , data );
	}
}
