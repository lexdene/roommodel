#include "jroommodelservergamedataprocessor.h"
#include "manager/jroommanager.h"
#include "manager/japplicationmanager.h"
#include "../common/jroomprotocol.h"

#include <Session/JSession>

JRoomModelServerGameDataProcessor::JRoomModelServerGameDataProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
}

void JRoomModelServerGameDataProcessor::process(const QByteArray& data)
{
    JID userId = getSession()->getUserId();
    if(userId < 0){
        return;
    }
	JRoomManager *rm = JRoomManager::getInstance();
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

JCode JRoomModelServerGameDataProcessor::sendGameData(const QByteArray& data)
{
    return sendData(data);
}
