#include "japplicationmanager.h"
#include "../common/jroom.h"
#include "../common/jroomerrorcode.h"

#include "application/jserverapplicationfactorybase.h"
#include "application/jserverapplicationbase.h"

JApplicationManager::JApplicationManager(QObject *parent) :
    QObject(parent)
{
}

JApplicationManager* JApplicationManager::getInstance()
{
	static JApplicationManager* instance = NULL;
	if(NULL == instance){
		static QObject o;
		instance = new JApplicationManager(&o);
	}
	return instance;
}

JCode JApplicationManager::enterRoom(JID userId,JID roomId)
{
	if(!m_apps.contains(roomId)){
		return ERoomIdNotExist;
	}
	JServerApplicationBase* app= m_apps.value(roomId);
	return app->enterRoom(userId);
}

JCode JApplicationManager::escapeRoom(JID userId,JID roomId)
{
    if(!m_apps.contains(roomId)){
        return ERoomIdNotExist;
    }
    JServerApplicationBase* app= m_apps.value(roomId);
    return app->escapeRoom(userId);
}

JCode JApplicationManager::addRoom(JRoom& room)
{
	JServerApplicationFactoryBase* appFactory = JServerApplicationFactoryBase::getInstance();
	if(NULL == appFactory){
		return EApplicationManager_AppFactoryIsNull;
	}
	m_apps.insert(room.getRoomId(),appFactory->createApplication(room.getRoomId()));
	return 0;
}

void JApplicationManager::processGameData(JID roomId,int at,const QByteArray& data)
{
	JServerApplicationBase* app = m_apps.value(roomId,NULL);
    if(NULL != app){
        app->processGameData(at,data);
	}
}

JServerApplicationBase* JApplicationManager::getApplication(JID roomId)const
{
    return m_apps.value(roomId,NULL);
}
