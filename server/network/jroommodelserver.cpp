#include "jroommodelserver.h"
#include "jroommodelserverroomprocessor.h"
#include "jroommodelservergamedataprocessor.h"
#include "jroommodelserverdisconnectedprocessor.h"

#include <Socket/JSocket>

JRoomModelServer::JRoomModelServer(QObject *parent)
    :JServerBase(parent)
{
}

JSocket* JRoomModelServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JSocket* connection = new JSocket(socket,parent);
	connection->registerProcessor( JRoomModelServerRoomProcessor::instance() );
	connection->registerProcessor( JRoomModelServerGameDataProcessor::instance() );
	connection->registerProcessor( JRoomModelServerDisconnectedProcessor::instance() );
	return connection;
}
