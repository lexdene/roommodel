#include "jroommodelclientgamedataprocessor.h"
#include "jroommodelclientsocket.h"
#include "../common/jroomprotocol.h"
#include "application/jclientapplicationbase.h"

JRoomModelClientGameDataProcessor::JRoomModelClientGameDataProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JRoomModelClientGameDataProcessor* JRoomModelClientGameDataProcessor::getInstance()
{
	static JRoomModelClientGameDataProcessor* instance = NULL;
	if(NULL == instance){
		JRoomModelClientSocket* socket = JRoomModelClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance = new JRoomModelClientGameDataProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

JCode JRoomModelClientGameDataProcessor::sendGameData(const QByteArray& data)
{
    return sendData(data);
}

void JRoomModelClientGameDataProcessor::process(const QByteArray& data)
{
	JClientApplicationBase* app = JClientApplicationBase::getInstance();
	app->processGameData(data);
}

JType JRoomModelClientGameDataProcessor::getProcessorType()const
{
	return GameDataProcessor;
}
