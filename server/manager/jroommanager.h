#ifndef JROOMMANAGER_H
#define JROOMMANAGER_H

#include "../common/jroom.h"
#include <Global/Global>

#include <QObject>
#include <QList>
#include <QMap>

class JApplicationManager;
class JServerApplicationBase;

class JRoomManager : public QObject
{
    Q_OBJECT
public:
	static JRoomManager* getInstance();
	JCode addUser(JID userId);
	JCode removeUser(JID userId);
	JID addRoom(JRoom room);
	JID getRoomByUserId(JID userId)const;
    int getUserAt(JID userId)const;
	QList<JRoom> getRoomList()const;
    QList<JID> getUserListInRoom(JID roomId)const;
    JCode enterRoom(JID userId,JID roomId);
    JRoom getRoom(JID roomId)const;
    //JCode escapeRoom(JID userId,JID roomId); no such function , cause enter room -1 means escape.

    // about applicaton
    JServerApplicationBase* getApplication(JID roomId)const;
    void receiveRoomChat(JID userId,const QString& text);
signals:
	void roomAdded(const JRoom& room);
	void roomRemoved(JID roomId);
    void roomUpdated(const JRoom& room);
private:
	explicit JRoomManager(QObject *parent = 0);
	JApplicationManager* m_applicationManager;
	QMap<JID,JID> m_UserToRoom;
	QMap<JID,JRoom> m_rooms;
};

#endif // JROOMMANAGER_H
