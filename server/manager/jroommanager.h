#ifndef JROOMMANAGER_H
#define JROOMMANAGER_H

#include "../common/jroom.h"
#include <Global/Global>

#include <QObject>
#include <QList>
#include <QMap>
#include <QSet>

class JApplicationManager;
class JServerApplicationBase;
class JSocket;

class JRoomManager : public QObject
{
    Q_OBJECT
public:
	static JRoomManager* instance();
	JCode addUser(JID userId);
	JCode removeUser(JID userId);
	JID addRoom(JRoom room);
	JID getRoomByUserId(JID userId)const;
    int getUserAt(JID userId)const;
	QList<JRoom> getRoomList()const;
    QList<JID> getUserListInRoom(JID roomId)const;
    JCode enterRoom(JID userId,JID roomId,JSocket* socket);
    JRoom getRoom(JID roomId)const;

    // about applicaton
    JServerApplicationBase* getApplication(JID roomId)const;
    
    // about socket
    QSet<JSocket*> getSocketListInRoom(JID roomId);
signals:
	void roomAdded(const JRoom& room);
	void roomRemoved(JID roomId);
	void roomUpdated(const JRoom& room);
private:
	explicit JRoomManager(QObject *parent = 0);
	JApplicationManager* m_applicationManager;
	QMap<JID,JID> m_UserToRoom;
	QMap<JID,JRoom> m_rooms;
	QMap<JID,QSet<JSocket*> > m_socketListInRoom;
};

#endif // JROOMMANAGER_H
