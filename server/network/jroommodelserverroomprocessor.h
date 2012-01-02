#ifndef JROOMMODELSERVERROOMPROCESSOR_H
#define JROOMMODELSERVERROOMPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JRoom;
class JRoomManager;
class JRoomModelServerGameDataProcessor;

/*!
	这个类最好只跟JRoomManager有关系。
	尽可能不直接跟JRoomApplication发生关系。
*/
class JRoomModelServerRoomProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JRoomModelServerRoomProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
    JType getProcessorType()const;
    void setPairedGameDataProcessor(JRoomModelServerGameDataProcessor* processor);
    JRoomModelServerGameDataProcessor* getPairedGameDataProcessor()const;
private:
	void processHello(JID userId);
	void processRoomList();
    void processAddRoom(const JRoom& room);
	void processEnterRoom(JID roomId);
    void processRoomInfo(JID roomId);
    void processRoomChat(const QString& text);

	void replyHello(JCode result);
	void replyRoomList(const QList<JRoom>& roomlist);
    void replyAddRoom(JID roomId);
    void replyEnterRoom(JID roomId,JCode code);
    void sendRoomInfo(const JRoom& room);
    void sendRoomRemoved(JID roomId);
    void sendRoomChat(JID userId,JID roomId,const QString& text);
private:
	JRoomManager* m_roomManager;
    JRoomModelServerGameDataProcessor* m_gamedataProcessor;
private slots:
	void on_roommanager_roomAdded(const JRoom& room);
	void on_roommanager_roomRemoved(JID roomId);
	void on_roommanager_roomUpdated(const JRoom& room);
    void on_application_roomChat(JID userId,JID roomId,const QString& text);
    void on_socket_disconnected();
};

#endif // JROOMMODELSERVERROOMPROCESSOR_H
