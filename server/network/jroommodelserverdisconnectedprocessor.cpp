#include "jroommodelserverdisconnectedprocessor.h"

#include "manager/jroommanager.h"

#include <Socket/JSocket>
#include <Session/JSession>
#include <Processor/ProcessorType>

JRoomModelServerDisconnectedProcessor* JRoomModelServerDisconnectedProcessor::instance()
{
	static JRoomModelServerDisconnectedProcessor instance;
	return &instance;
}

void JRoomModelServerDisconnectedProcessor::process(JSocket* socket , const QByteArray&)
{
	qDebug()<<__FUNCTION__<<__LINE__;
	JID userId = socket->session()->userId();
	qDebug()<<__FUNCTION__<<__LINE__;
	JRoomManager::instance()->enterRoom(userId,-1,socket);
	qDebug()<<__FUNCTION__<<__LINE__;
	JRoomManager::instance()->removeUser(userId);
	qDebug()<<__FUNCTION__<<__LINE__;
}

JType JRoomModelServerDisconnectedProcessor::getProcessorType()const
{
	return EPI_Disconnected;
}

JRoomModelServerDisconnectedProcessor::JRoomModelServerDisconnectedProcessor(QObject* parent)
	:JProcessor(parent)
{
}
