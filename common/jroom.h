#ifndef JROOM_H
#define JROOM_H

#include <Global/Global>

#include <QString>
#include <QList>

class QDataStream;

class JRoom
{
public:
    JRoom();
	void setRoomId(JID roomId);
	JID getRoomId()const;
    void setTitle(const QString& title);
    const QString& getTitle()const;
	int getNum()const;
    void setMax(int nmax);
	int getMax()const;
    const QList<JID>& getUserList()const;
    void addUser(JID userId);
    void removeUser(JID userId);
private:
	JID m_roomId;
    QString m_title;
	int m_max;
    QList<JID> m_userlist;
	friend QDataStream& operator>>(QDataStream& ,JRoom&);
	friend QDataStream& operator<<(QDataStream& ,const JRoom&);
};


#endif // JROOM_H
