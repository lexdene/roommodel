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
	JID userId = socket->session()->userId();
	JRoomManager::instance()->enterRoom(userId,-1);
	JRoomManager::instance()->removeUser(userId);
}

JType JRoomModelServerDisconnectedProcessor::getProcessorType()const
{
	return EPI_Disconnected;
}

JRoomModelServerDisconnectedProcessor::JRoomModelServerDisconnectedProcessor(QObject* parent)
	:JProcessor(parent)
{
}
