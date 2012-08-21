#include "jroommodelclientsocket.h"

#include "jroommodelclientroomprocessor.h"
#include "jroommodelclientgamedataprocessor.h"

JRoomModelClientSocket::JRoomModelClientSocket(QObject *parent) :
	JSocket(0,parent)
{
}

JRoomModelClientSocket* JRoomModelClientSocket::instance()
{
	static JRoomModelClientSocket* instance = NULL;
	if(NULL == instance){
		static QObject parent;
		instance = new JRoomModelClientSocket(
					&parent
					);
		instance->registerProcessor( JRoomModelClientRoomProcessor::instance() );
		instance->registerProcessor( JRoomModelClientGameDataProcessor::instance() );
	}
	return instance;
}
