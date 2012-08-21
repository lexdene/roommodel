#include "jroommanager.h"

#include "../common/jroomerrorcode.h"
#include "japplicationmanager.h"
#include "application/jserverapplicationbase.h"

#include <QDebug>

JRoomManager* JRoomManager::instance()
{
	static JRoomManager* instance = NULL;
	if(NULL == instance){
		static QObject o;
		instance = new JRoomManager(&o);
	}
	return instance;
}

JCode JRoomManager::addUser(JID userId)
{
	if(m_UserToRoom.contains(userId)){
		return EUserIdDuplicated;
	}
	m_UserToRoom.insert(userId,-1);
	return ESuccess;
}

JCode JRoomManager::removeUser(JID userId)
{
	if(!m_UserToRoom.contains(userId)){
		return EUserIdNotExist;
	}
	m_UserToRoom.remove(userId);
	return ESuccess;
}

JID JRoomManager::addRoom(JRoom room)
{
	JID roomId;
	const JID beginId = 1000;
	const JID endId = 65536;
	for(roomId = beginId;roomId<endId;++roomId){
		if(!m_rooms.contains(roomId)){
			break;
		}
	}
	if(roomId < endId){
		room.setRoomId(roomId);
		JCode code = m_applicationManager->addRoom(room);
		if(ESuccess == code){
			m_rooms.insert(room.getRoomId(),room);
		}
        emit roomAdded(room);
		return room.getRoomId();
	}else{
		return -1;
	}
}

JID JRoomManager::getRoomByUserId(JID userId)const
{
	return m_UserToRoom.value(userId,-1);
}

int JRoomManager::getUserAt(JID userId)const
{
    JID roomId = getRoomByUserId(userId);
    if(roomId < 0 ) return -1;
    QList<JID> userlist = getUserListInRoom(roomId);
    for(int i=0;i<userlist.length();++i){
        if(userlist.at(i) == userId){
            return i;
        }
    }
    return -1;
}

QList<JRoom> JRoomManager::getRoomList()const
{
	return m_rooms.values();
}

QList<JID> JRoomManager::getUserListInRoom(JID roomId)const
{
    const JRoom& room = m_rooms.value(roomId);
    Q_ASSERT(m_UserToRoom.keys(roomId).length() == room.getUserList().length());
    return room.getUserList();
}

JCode JRoomManager::enterRoom(JID userId,JID roomId)
{
    JCode code;
    if(roomId<0){
        JID formerRoomId = m_UserToRoom[userId];
        code = m_applicationManager->escapeRoom(userId,formerRoomId);
        if(ESuccess == code){
            m_UserToRoom[userId]=roomId;
            JRoom& room = m_rooms[formerRoomId];
            //room.rNum()--;
            room.removeUser(userId);
            emit roomUpdated(room);
        }
    }else{
        if(m_UserToRoom[userId]<0){
            code = m_applicationManager->enterRoom(userId,roomId);
            if(ESuccess == code){
                m_UserToRoom[userId]=roomId;
                JRoom& room = m_rooms[roomId];
                //room.rNum()++;
                room.addUser(userId);
                emit roomUpdated(room);
            }
        }else{
            code = EEnterRoomAlreadyInRoom;
        }
    }
	return code;
}

JRoom JRoomManager::getRoom(JID roomId)const
{
    return m_rooms.value(roomId);
}

JServerApplicationBase* JRoomManager::getApplication(JID roomId)const
{
    return m_applicationManager->getApplication(roomId);
}

void JRoomManager::receiveRoomChat(JID userId,const QString& text)
{
    JID roomId = getRoomByUserId(userId);
    JServerApplicationBase* app = getApplication(roomId);
    if(NULL == app)
    {
        qDebug()<<"JRoomManager::receiveRoomChat : application is NULL : roomId="<<roomId;
        return;
    }
    app->receiveRoomChat(userId,text);
}

JRoomManager::JRoomManager(QObject *parent) :
    QObject(parent)
{
	m_applicationManager = JApplicationManager::getInstance();
}
