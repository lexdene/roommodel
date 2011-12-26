#include "jroommodelclientroomprocessor.h"
#include "jroommodelclientsocket.h"
#include "../common/jroomprotocol.h"

JRoomModelClientRoomProcessor::JRoomModelClientRoomProcessor(JSession* session,JSocketBase *socket) :
	JClientNetworkDataProcessorBase(session,socket)
{
}

JRoomModelClientRoomProcessor* JRoomModelClientRoomProcessor::getInstance()
{
	static JRoomModelClientRoomProcessor* instance = NULL;
	if(NULL == instance){
		JRoomModelClientSocket* socket = JRoomModelClientSocket::getInstance();
		JSession* session = socket->getSession();
		instance = new JRoomModelClientRoomProcessor(session,socket);
		socket->registerProcessor(instance);
	}
	return instance;
}

void JRoomModelClientRoomProcessor::sendHello(JID userId)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_Hello;
    outstream<<userId;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::requestRoomList()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomList;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::requestAddRoom(const JRoom& room)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_AddRoom;
    outstream<<room;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::requestEnterRoom(JID roomId)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_EnterRoom;
    outstream<<roomId;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::requestRoomInfo(JID roomId)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomInfo;
    outstream<<roomId;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::sendRoomChat(const QString& text)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomChat;
    outstream<<text;
    sendData(outdata);
}

void JRoomModelClientRoomProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	switch(protocol){
	case ERP_Hello:
		{
			JCode result;
			stream>>result;
			processHello(result);
		}
		break;
	case ERP_RoomList:
		{
			QList<JRoom> roomlist;
			stream>>roomlist;
			processRoomList(roomlist);
		}
		break;
	case ERP_AddRoom:
		{
			JID roomId;
			stream>>roomId;
			processAddRoom(roomId);
		}
		break;
	case ERP_EnterRoom:
		{
            JID roomId;
			JCode code;
            stream>>roomId;
			stream>>code;
            processEnterRoom(roomId,code);
		}
		break;
    case ERP_RoomInfo:
		{
			JRoom room;
			stream>>room;
            processRoomInfo(room);
		}
		break;
	case ERP_RoomRemoved:
		{
			JID roomId;
			stream>>roomId;
			processRoomRemoved(roomId);
		}
        break;
    case ERP_RoomChat:
        {
            JID userId;
            JID roomId;
            QString text;
            stream>>userId;
            stream>>roomId;
            stream>>text;
            emit receiveRoomChat(userId,roomId,text);
        }
        break;
	default:
		qDebug()<<"JRoomModelClientRoomProcessor::process : unknown protocol : "<<protocol;
	}
}

EProcessorType JRoomModelClientRoomProcessor::getProcessorType()const
{
	return RoomProcessor;
}

void JRoomModelClientRoomProcessor::processHello(JCode result)
{
	emit receiveHelloResult(result);
}

void JRoomModelClientRoomProcessor::processRoomList(const QList<JRoom>& roomlist)
{
	emit receiveRoomList(roomlist);
}

void JRoomModelClientRoomProcessor::processAddRoom(JID roomId)
{
	emit receiveAddRoomResult(roomId);
}

void JRoomModelClientRoomProcessor::processEnterRoom(JID roomId,JCode code)
{
    emit receiveEnterRoomResult(roomId,code);
}

void JRoomModelClientRoomProcessor::processRoomInfo(const JRoom& room)
{
    emit receiveRoomInfo(room);
}

void JRoomModelClientRoomProcessor::processRoomRemoved(JID roomId)
{
	emit receiveRoomRemoved(roomId);
}
