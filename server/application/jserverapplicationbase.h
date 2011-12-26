#ifndef JSERVERAPPLICATIONBASE_H
#define JSERVERAPPLICATIONBASE_H

#include <Global/Global>

#include <QObject>

class JServerApplicationBase : public QObject
{
    Q_OBJECT
public:
	explicit JServerApplicationBase(JID roomId,QObject *parent = 0);
	JID getRoomId()const;
	virtual JCode enterRoom(JID userId)=0;
    virtual void afterEnterRoom(JID userId)=0;
	virtual JCode escapeRoom(JID userId)=0;
    virtual void processGameData(int at , const QByteArray& data)=0;

    // api :
    void receiveRoomChat(JID userId,const QString& text);
signals:
    void roomChat(JID userId,JID roomId,const QString& text);
    /// 由于是多播内容，所以只能用信号
    void sendGameData(const QByteArray& data);
private:
    JID m_roomId;
};

#endif // JSERVERAPPLICATIONBASE_H
