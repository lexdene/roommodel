#include "jroommodelserverroomprocessor.h"

#include "../common/jroom.h"
#include "../common/jroomprotocol.h"
#include "application/jserverapplicationbase.h"
#include "manager/jroommanager.h"
#include "jroommodelservergamedataprocessor.h"

#include <Session/JSession>
#include <Global/CodeError>
#include <Socket/JSocketBase>

#include <QDebug>
#include <QDataStream>

JRoomModelServerRoomProcessor::JRoomModelServerRoomProcessor(JSession* session,JSocketBase *socket) :
	JServerNetworkDataProcessorBase(session,socket)
{
    connect(socket,
            SIGNAL(disconnected()),
            SLOT(on_socket_disconnected()));
	m_roomManager = JRoomManager::getInstance();
    connect(m_roomManager,
            SIGNAL(roomAdded(JRoom)),
            SLOT(on_roommanager_roomAdded(JRoom)));
    connect(m_roomManager,
            SIGNAL(roomUpdated(JRoom)),
            SLOT(on_roommanager_roomUpdated(JRoom)));
}

void JRoomModelServerRoomProcessor::process(const QByteArray& data)
{
	QDataStream stream(data);
	JID protocol;
	stream>>protocol;
	switch(protocol){
	case ERP_Hello:
		{
			JID userId;
			stream>>userId;
			processHello(userId);
		}
		break;
	case ERP_RoomList:
		{
			processRoomList();
		}
		break;
	case ERP_AddRoom:
		{
			JRoom room;
			stream>>room;
			processAddRoom(room);
		}
		break;
	case ERP_EnterRoom:
		{
			JID roomId;
			stream>>roomId;
			processEnterRoom(roomId);
		}
		break;
    case ERP_RoomInfo:
        {
            JID roomId;
            stream>>roomId;
            processRoomInfo(roomId);
        }
        break;
	case ERP_RoomRemoved:
		qDebug()<<"JRoomModelServerRoomProcessor::process : client can not send this protocol : "<<protocol;
		break;
    case ERP_RoomChat:
        {
            QString text;
            stream>>text;
            processRoomChat(text);
        }
        break;
	default:
		qDebug()<<"JRoomModelServerRoomProcessor::process : unknown protocol : "<<protocol;
	}
}

EProcessorType JRoomModelServerRoomProcessor::getProcessorType()const
{
	return RoomProcessor;
}

void JRoomModelServerRoomProcessor::setPairedGameDataProcessor(JRoomModelServerGameDataProcessor* processor)
{
    m_gamedataProcessor = processor;
}

JRoomModelServerGameDataProcessor* JRoomModelServerRoomProcessor::getPairedGameDataProcessor()const
{
    return m_gamedataProcessor;
}

void JRoomModelServerRoomProcessor::processHello(JID userId)
{
	JCode code = m_roomManager->addUser(userId);
	if(ESuccess == code){
		getSession()->setUserId(userId);
	}
	replyHello(code);
}

void JRoomModelServerRoomProcessor::processRoomList()
{
	replyRoomList(m_roomManager->getRoomList());
}

void JRoomModelServerRoomProcessor::processAddRoom(const JRoom& room)
{
	JID roomId = m_roomManager->addRoom(room);
	replyAddRoom(roomId);
}

void JRoomModelServerRoomProcessor::processEnterRoom(JID roomId)
{
    JID userId = getSession()->getUserId();
    JID formerRoomId = m_roomManager->getRoomByUserId(userId);
    JCode code = m_roomManager->enterRoom(userId,roomId);
    if(ESuccess == code){
        JServerApplicationBase *formerapp = m_roomManager->getApplication(formerRoomId);
        if(NULL != formerapp){
            disconnect(formerapp,SIGNAL(roomChat(JID,JID,QString)),this,SLOT(on_application_roomChat(JID,JID,QString)));
            disconnect(formerapp,
                       SIGNAL(sendGameData(QByteArray)),
                       getPairedGameDataProcessor(),
                       SLOT(sendGameData(QByteArray)));
        }
        JServerApplicationBase *app = m_roomManager->getApplication(roomId);
        if(NULL != app){
            connect(app,SIGNAL(roomChat(JID,JID,QString)),SLOT(on_application_roomChat(JID,JID,QString)));
            connect(app,
                    SIGNAL(sendGameData(QByteArray)),
                    getPairedGameDataProcessor(),
                    SLOT(sendGameData(QByteArray)));
            app->afterEnterRoom(userId);
        }
    }
    replyEnterRoom(roomId,code);
}

void JRoomModelServerRoomProcessor::processRoomInfo(JID roomId)
{
    const JRoom& room = m_roomManager->getRoom(roomId);
    sendRoomInfo(room);
}

void JRoomModelServerRoomProcessor::processRoomChat(const QString& text)
{
    JID userId = getSession()->getUserId();
    m_roomManager->receiveRoomChat(userId,text);
}

void JRoomModelServerRoomProcessor::replyHello(JCode result)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_Hello;
	outstream<<result;
	sendData(outdata);
}

void JRoomModelServerRoomProcessor::replyRoomList(const QList<JRoom>& roomlist)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_RoomList;
	outstream<<roomlist;
	sendData(outdata);
}

void JRoomModelServerRoomProcessor::replyAddRoom(JID roomId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_AddRoom;
	outstream<<roomId;
	sendData(outdata);
}

void JRoomModelServerRoomProcessor::replyEnterRoom(JID roomId,JCode code)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_EnterRoom;
    outstream<<roomId;
	outstream<<code;
	sendData(outdata);
}

void JRoomModelServerRoomProcessor::sendRoomInfo(const JRoom& room)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomInfo;
    outstream<<room;
    sendData(outdata);
}

void JRoomModelServerRoomProcessor::sendRoomRemoved(JID roomId)
{
	QByteArray outdata;
	QDataStream outstream(&outdata,QIODevice::WriteOnly);
	outstream<<(JID)ERP_RoomRemoved;
	outstream<<roomId;
	sendData(outdata);
}

void JRoomModelServerRoomProcessor::sendRoomChat(JID userId,JID roomId,const QString& text)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(JID)ERP_RoomChat;
    outstream<<userId;
    outstream<<roomId;
    outstream<<text;
    sendData(outdata);
}

void JRoomModelServerRoomProcessor::on_roommanager_roomAdded(const JRoom& room)
{
    sendRoomInfo(room);
}

void JRoomModelServerRoomProcessor::on_roommanager_roomRemoved(JID roomId)
{
	sendRoomRemoved(roomId);
}

void JRoomModelServerRoomProcessor::on_roommanager_roomUpdated(const JRoom& room)
{
    sendRoomInfo(room);
}

void JRoomModelServerRoomProcessor::on_application_roomChat(JID userId,JID roomId,const QString& text)
{
    sendRoomChat(userId,roomId,text);
}

void JRoomModelServerRoomProcessor::on_socket_disconnected()
{
    JID userId = getSession()->getUserId();
    m_roomManager->enterRoom(userId,-1);
    m_roomManager->removeUser(userId);
}
