#ifndef JAPPLICATIONMANAGER_H
#define JAPPLICATIONMANAGER_H

#include <Global/Global>

#include <QObject>
#include <QMap>

class JRoom;
class JServerApplicationFactoryBase;
class JServerApplicationBase;

class JApplicationManager : public QObject
{
    Q_OBJECT
public:
	static JApplicationManager* getInstance();
	JCode enterRoom(JID userId,JID roomId);
    JCode escapeRoom(JID userId,JID roomId);
	JCode addRoom(JRoom& room);
    void processGameData(JID roomId,int at,const QByteArray& data);

    JServerApplicationBase* getApplication(JID roomId)const;
private:
	explicit JApplicationManager(QObject *parent = 0);
	QMap<JID,JServerApplicationBase*> m_apps;
};

#endif // JAPPLICATIONMANAGER_H
