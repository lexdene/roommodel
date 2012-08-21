#include "jclientapplicationbase.h"
#include "network/jroommodelclientgamedataprocessor.h"
#include "network/jroommodelclientsocket.h"

#include <Helper/JGameClientArgumentAnalyser>

JClientApplicationBase* JClientApplicationBase::s_instance;

JClientApplicationBase::JClientApplicationBase(QObject *parent) :
    QObject(parent)
{
    m_gamedataProcessor = JRoomModelClientGameDataProcessor::instance();
}

JClientApplicationBase* JClientApplicationBase::instance()
{
	return s_instance;
}

void JClientApplicationBase::setInstance(JClientApplicationBase* instance)
{
	s_instance = instance;
}

JID JClientApplicationBase::getMyUserId()const
{
    return JGameClientArgumentAnalyser::instance()->getUserId();
}

void JClientApplicationBase::sendData(const QByteArray& data)
{
    m_gamedataProcessor->sendGameData(data);
}
