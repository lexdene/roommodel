#include "jclientapplicationbase.h"
#include "network/jroommodelclientgamedataprocessor.h"

#include <Helper/JGameClientArgumentAnalyser>

JClientApplicationBase* JClientApplicationBase::s_instance;

JClientApplicationBase::JClientApplicationBase(QObject *parent) :
    QObject(parent)
{
    m_gamedataProcessor = JRoomModelClientGameDataProcessor::getInstance();
}

JClientApplicationBase* JClientApplicationBase::getInstance()
{
	return s_instance;
}

void JClientApplicationBase::setInstance(JClientApplicationBase* instance)
{
	s_instance = instance;
}

JID JClientApplicationBase::getMyUserId()const
{
    return JGameClientArgumentAnalyser::getInstance()->getUserId();
}

void JClientApplicationBase::sendData(const QByteArray& data)
{
    m_gamedataProcessor->sendGameData(data);
}
