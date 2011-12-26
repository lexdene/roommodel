#include "jroommodelserver.h"
#include "jroommodelserverroomprocessor.h"
#include "jroommodelservergamedataprocessor.h"

#include <Socket/JServerSocketBase>

JRoomModelServer::JRoomModelServer(QObject *parent)
    :JServerBase(parent)
{
}

JServerSocketBase* JRoomModelServer::getConnection(QTcpSocket* socket,QObject* parent)const
{
	JServerSocketBase* connection = new JServerSocketBase(socket,parent);
	JSession* session = connection->getSession();
    JRoomModelServerRoomProcessor* roomProcessor = new JRoomModelServerRoomProcessor(session,connection);
    JRoomModelServerGameDataProcessor* gamedataProcessor = new JRoomModelServerGameDataProcessor(session,connection);
    roomProcessor->setPairedGameDataProcessor(gamedataProcessor);
	connection->registerProcessor(roomProcessor);
	connection->registerProcessor(gamedataProcessor);
	return connection;
}
