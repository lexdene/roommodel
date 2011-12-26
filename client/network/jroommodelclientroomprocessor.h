#ifndef JROOMMODELCLIENTROOMPROCESSOR_H
#define JROOMMODELCLIENTROOMPROCESSOR_H

#include "../../common/jroom.h"

#include <Processor/JClientNetworkDataProcessorBase>

class JRoomModelClientRoomProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
public:
	static JRoomModelClientRoomProcessor* getInstance();
    void sendHello(JID userId);
    void requestRoomList();
    void requestAddRoom(const JRoom& room);
    void requestEnterRoom(JID roomId);
    void requestRoomInfo(JID roomId);
    void sendRoomChat(const QString& text);
signals:
	void receiveHelloResult(JCode result);
	void receiveRoomList(const QList<JRoom>& roomlist);
    void receiveAddRoomResult(JID roomId);
    void receiveEnterRoomResult(JID roomId,JCode result);
    void receiveRoomInfo(const JRoom& room);
    void receiveRoomRemoved(JID roomId);
    void receiveRoomChat(JID userId,JID roomId,const QString& text);
private:
	explicit JRoomModelClientRoomProcessor(JSession* session,JSocketBase *socket);
protected:
	void process(const QByteArray& data);
	EProcessorType getProcessorType()const;

	virtual void processHello(JCode result);
	virtual void processRoomList(const QList<JRoom>& roomlist);
    virtual void processAddRoom(JID roomId);
    virtual void processEnterRoom(JID roomId,JCode code);
    virtual void processRoomInfo(const JRoom& room);
	virtual void processRoomRemoved(JID roomId);
};

#endif // JROOMMODELCLIENTROOMPROCESSOR_H
