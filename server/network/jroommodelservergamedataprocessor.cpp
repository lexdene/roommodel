#include "jroommodelservergamedataprocessor.h"
#include "manager/jroommanager.h"
#include "manager/japplicationmanager.h"
#include "../common/jroomprotocol.h"

#include <Socket/JSocket>
#include <Session/JSession>

JRoomModelServerGameDataProcessor::JRoomModelServerGameDataProcessor(QObject* parent) :
	JProcessor(parent)
{
}

JRoomModelServerGameDataProcessor* JRoomModelServerGameDataProcessor::instance()
{
	static JRoomModelServerGameDataProcessor instance;
	return &instance;
}

void JRoomModelServerGameDataProcessor::process(JSocket* socket , const QByteArray& data)
{
    JID userId = socket->session()->userId();
    if(userId < 0){
        return;
    }
	JRoomManager *rm = JRoomManager::instance();
    JID roomId = rm->getRoomByUserId(userId);
    if(roomId < 0){
        return;
    }
	JApplicationManager* am = JApplicationManager::getInstance();
    int at = rm->getUserAt(userId);
    am->processGameData(roomId,at,data);
}

JType JRoomModelServerGameDataProcessor::getProcessorType()const
{
	return GameDataProcessor;
}

JCode JRoomModelServerGameDataProcessor::sendGameData(JSocket* socket , const QByteArray& data)
{
    return sendData(socket , data);
}
