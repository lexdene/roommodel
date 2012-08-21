#include "jroommodelserverroomprocessor.h"

#include "../common/jroom.h"
#include "../common/jroomprotocol.h"
#include "application/jserverapplicationbase.h"
#include "manager/jroommanager.h"
#include "jroommodelservergamedataprocessor.h"

#include <Session/JSession>
#include <Global/ErrorCode>
#include <Socket/JSocket>

#include <QDebug>
#include <QDataStream>

JRoomModelServerRoomProcessor::JRoomModelServerRoomProcessor(QObject* parent) :
	JProcessor(parent)
{
//    connect(JRoomManager::instance(),
//            SIGNAL(roomAdded(JRoom)),
//            SLOT(on_roommanager_roomAdded(JRoom)));
//    connect(JRoomManager::instance(),
//            SIGNAL(roomUpdated(JRoom)),
//            SLOT(on_roommanager_roomUpdated(JRoom)));
}

JRoomModelServerRoomProcessor* JRoomModelServerRoomProcessor::instance()
{
	static JRoomModelServerRoomProcessor instance;
	return &instance;
}

void JRoomModelServerRoomProcessor::process(JSocket* socket , const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	switch(protocol){
	case ERP_Hello:
		{
			JID userId;
			stream>>userId;
			processHello(socket,userId);
		}
		break;
	case ERP_RoomList:
		{
			processRoomList(socket);
		}
		break;
	case ERP_AddRoom:
		{
			JRoom room;
			stream>>room;
			processAddRoom(socket,room);
		}
		break;
	case ERP_EnterRoom:
		{
			JID roomId;
			stream>>roomId;
			processEnterRoom(socket,roomId);
		}
		break;
    case ERP_RoomInfo:
        {
            JID roomId;
            stream>>roomId;
            processRoomInfo(socket,roomId);
        }
        break;
	case ERP_RoomRemoved:
		qDebug()<<"JRoomModelServerRoomProcessor::process : client can not send this protocol : "<<protocol;
		break;
    case ERP_RoomChat:
        {
            QString text;
            stream>>text;
            processRoomChat(socket,text);
        }
        break;
	default:
		qDebug()<<"JRoomModelServerRoomProcessor::process : unknown protocol : "<<protocol;
	}
}

JType JRoomModelServerRoomProcessor::getProcessorType()const
{
	return RoomProcessor;
}

void JRoomModelServerRoomProcessor::processHello(JSocket* socket , JID userId)
{
	JCode code = JRoomManager::instance()->addUser(userId);
	if(ESuccess == code){
		socket->session()->setUserId(userId);
	}
	replyHello(socket , code);
}

void JRoomModelServerRoomProcessor::processRoomList(JSocket* socket)
{
	replyRoomList(socket,JRoomManager::instance()->getRoomList());
}

void JRoomModelServerRoomProcessor::processAddRoom(JSocket* socket , const JRoom& room)
{
	JID roomId = JRoomManager::instance()->addRoom(room);
	replyAddRoom(socket,roomId);
}

void JRoomModelServerRoomProcessor::processEnterRoom(JSocket* socket , JID roomId)
{
    JID userId = socket->session()->userId();
    JID formerRoomId = JRoomManager::instance()->getRoomByUserId(userId);
    JCode code = JRoomManager::instance()->enterRoom(userId,roomId);
    if(ESuccess == code){
        JServerApplicationBase *formerapp = JRoomManager::instance()->getApplication(formerRoomId);
        if(NULL != formerapp){
//            disconnect(formerapp,SIGNAL(roomChat(JID,JID,QString)),this,SLOT(on_application_roomChat(JID,JID,QString)));
//            disconnect(formerapp,
//                       SIGNAL(sendGameData(QByteArray)),
//                       getPairedGameDataProcessor(),
//                       SLOT(sendGameData(QByteArray)));
        }
        JServerApplicationBase *app = JRoomManager::instance()->getApplication(roomId);
        if(NULL != app){
//            connect(app,SIGNAL(roomChat(JID,JID,QString)),SLOT(on_application_roomChat(JID,JID,QString)));
//            connect(app,
//                    SIGNAL(sendGameData(QByteArray)),
//                    getPairedGameDataProcessor(),
//                    SLOT(sendGameData(QByteArray)));
            app->afterEnterRoom(userId);
        }
    }
    replyEnterRoom(socket,roomId,code);
}

void JRoomModelServerRoomProcessor::processRoomInfo(JSocket* socket , JID roomId)
{
    const JRoom& room = JRoomManager::instance()->getRoom(roomId);
    sendRoomInfo(socket,room);
}

void JRoomModelServerRoomProcessor::processRoomChat(JSocket* socket , const QString& text)
{
    JID userId = socket->session()->userId();
    JRoomManager::instance()->receiveRoomChat(userId,text);
}

void JRoomModelServerRoomProcessor::replyHello(JSocket* socket , JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_Hello;
	outstream<<result;
	sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::replyRoomList(JSocket* socket , const QList<JRoom>& roomlist)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_RoomList;
	outstream<<roomlist;
	sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::replyAddRoom(JSocket* socket , JID roomId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_AddRoom;
	outstream<<roomId;
	sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::replyEnterRoom(JSocket* socket , JID roomId,JCode code)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_EnterRoom;
    outstream<<roomId;
	outstream<<code;
	sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::sendRoomInfo(JSocket* socket , const JRoom& room)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomInfo;
    outstream<<room;
    sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::sendRoomRemoved(JSocket* socket , JID roomId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_RoomRemoved;
	outstream<<roomId;
	sendData(socket,outdata);
}

void JRoomModelServerRoomProcessor::sendRoomChat(JSocket* socket , JID userId,JID roomId,const QString& text)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomChat;
    outstream<<userId;
    outstream<<roomId;
    outstream<<text;
    sendData(socket,outdata);
}

//void JRoomModelServerRoomProcessor::on_roommanager_roomAdded(const JRoom& room)
//{
//    sendRoomInfo(room);
//}

//void JRoomModelServerRoomProcessor::on_roommanager_roomRemoved(JID roomId)
//{
//	sendRoomRemoved(roomId);
//}

//void JRoomModelServerRoomProcessor::on_roommanager_roomUpdated(const JRoom& room)
//{
//    sendRoomInfo(room);
//}

//void JRoomModelServerRoomProcessor::on_application_roomChat(JID userId,JID roomId,const QString& text)
//{
//    sendRoomChat(userId,roomId,text);
//}
