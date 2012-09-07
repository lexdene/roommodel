#ifndef JSERVERAPPLICATIONBASE_H
#define JSERVERAPPLICATIONBASE_H

#include <Global/Global>

#include <QObject>

class JServerApplicationBase : public QObject
{
public:
	explicit JServerApplicationBase(JID roomId,QObject *parent = 0);
	JID getRoomId()const;
	virtual JCode enterRoom(JID userId)=0;
    virtual void afterEnterRoom(JID userId)=0;
	virtual JCode escapeRoom(JID userId)=0;
	virtual void afterEscapeRoom(JID userId)=0;
    virtual void processGameData(int at , const QByteArray& data)=0;
protected:
	// api
    void sendGameData(const QByteArray& data)const;
private:
    JID m_roomId;
};

#endif // JSERVERAPPLICATIONBASE_H
