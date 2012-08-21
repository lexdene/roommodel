#ifndef JROOMMODELSERVER_H
#define JROOMMODELSERVER_H

#include <Server/JServerBase>

class JRoomModelServer : public JServerBase{
    Q_OBJECT
public:
    explicit JRoomModelServer(QObject *parent = 0);
protected:
	JSocket* getConnection(QTcpSocket* socket,QObject* parent)const;
};

#endif // JROOMMODELSERVER_H
