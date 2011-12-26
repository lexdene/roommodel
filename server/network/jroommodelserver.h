#ifndef JROOMMODELSERVER_H
#define JROOMMODELSERVER_H

#include <Socket/JServerBase>

class JRoomModelServer : public JServerBase{
    Q_OBJECT
public:
    explicit JRoomModelServer(QObject *parent = 0);
protected:
	JServerSocketBase* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JROOMMODELSERVER_H
