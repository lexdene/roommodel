#ifndef JROOMMODELCLIENTSOCKET_H
#define JROOMMODELCLIENTSOCKET_H

#include <Socket/JClientSocketBase>

class JRoomModelClientSocket : public JClientSocketBase
{
    Q_OBJECT
    explicit JRoomModelClientSocket(QObject *parent = 0);
public:
	static JRoomModelClientSocket* getInstance();
};

#endif // JROOMMODELCLIENTSOCKET_H
