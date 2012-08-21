#ifndef JROOMMODELSERVERROOMPROCESSOR_H
#define JROOMMODELSERVERROOMPROCESSOR_H

#include <Processor/JProcessor>

class JRoom;
class JRoomManager;
class JRoomModelServerGameDataProcessor;

/*!
	这个类最好只跟JRoomManager有关系。
	尽可能不直接跟JRoomApplication发生关系。
*/
class JRoomModelServerRoomProcessor : public JProcessor
{
    Q_OBJECT
public:
	static JRoomModelServerRoomProcessor* instance();
	void process(JSocket* socket , const QByteArray& data);
    JType getProcessorType()const;
private:
	void processHello(JSocket* socket , JID userId);
	void processRoomList(JSocket* socket);
    void processAddRoom(JSocket* socket , const JRoom& room);
	void processEnterRoom(JSocket* socket , JID roomId);
    void processRoomInfo(JSocket* socket , JID roomId);
    void processRoomChat(JSocket* socket , const QString& text);

	void replyHello(JSocket* socket , JCode result);
	void replyRoomList(JSocket* socket , const QList<JRoom>& roomlist);
    void replyAddRoom(JSocket* socket , JID roomId);
    void replyEnterRoom(JSocket* socket , JID roomId,JCode code);
    void sendRoomInfo(JSocket* socket , const JRoom& room);
    void sendRoomRemoved(JSocket* socket , JID roomId);
    void sendRoomChat(JSocket* socket , JID userId,JID roomId,const QString& text);
	explicit JRoomModelServerRoomProcessor(QObject* parent = 0);
private slots:
//	void on_roommanager_roomAdded(const JRoom& room);
//	void on_roommanager_roomRemoved(JID roomId);
//	void on_roommanager_roomUpdated(const JRoom& room);
//	void on_application_roomChat(JID userId,JID roomId,const QString& text);
};

#endif // JROOMMODELSERVERROOMPROCESSOR_H
