#ifndef JCLIENTAPPLICATIONBASE_H
#define JCLIENTAPPLICATIONBASE_H

#include <Global/Global>

#include <QObject>

class JRoom;
class JRoomModelClientGameDataProcessor;

class JClientApplicationBase : public QObject
{
    Q_OBJECT
public:
	static JClientApplicationBase* instance();
	static void setInstance(JClientApplicationBase* instance);
    virtual void processGameData(const QByteArray& data)=0;
    virtual void createRoomInfo(JRoom&)=0;

    // api
    JID getMyUserId()const;
protected:
	explicit JClientApplicationBase(QObject *parent = 0);
    void sendData(const QByteArray& data);
private:
	static JClientApplicationBase* s_instance;
    JRoomModelClientGameDataProcessor* m_gamedataProcessor;
};

#endif // JCLIENTAPPLICATIONBASE_H
