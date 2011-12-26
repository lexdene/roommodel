#include "jroommodelclientsocket.h"

#include <QTcpSocket>
#include <QCoreApplication>

JRoomModelClientSocket::JRoomModelClientSocket(QObject *parent) :
	JClientSocketBase(new QTcpSocket(QCoreApplication::instance()),parent)
{
}

JRoomModelClientSocket* JRoomModelClientSocket::getInstance()
{
	static JRoomModelClientSocket* instance = NULL;
	if(NULL == instance){
		instance = new JRoomModelClientSocket(
					QCoreApplication::instance()
					);
	}
	return instance;
}
