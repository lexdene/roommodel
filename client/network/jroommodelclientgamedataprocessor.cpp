#include "jroommodelclientgamedataprocessor.h"
#include "jroommodelclientsocket.h"
#include "../common/jroomprotocol.h"
#include "application/jclientapplicationbase.h"

JRoomModelClientGameDataProcessor::JRoomModelClientGameDataProcessor(QObject* parent) :
	JProcessor(parent)
{
}

JRoomModelClientGameDataProcessor* JRoomModelClientGameDataProcessor::instance()
{
	static JRoomModelClientGameDataProcessor instance;
	return &instance;
}

JCode JRoomModelClientGameDataProcessor::sendGameData(const QByteArray& data)
{
    return sendData(JRoomModelClientSocket::instance(),data);
}

void JRoomModelClientGameDataProcessor::process(JSocket* , const QByteArray& data)
{
	JClientApplicationBase* app = JClientApplicationBase::instance();
	app->processGameData(data);
}

JType JRoomModelClientGameDataProcessor::getProcessorType()const
{
	return GameDataProcessor;
}
