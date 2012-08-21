#ifndef JROOMMODELCLIENTSOCKET_H
#define JROOMMODELCLIENTSOCKET_H

#include <Socket/JSocket>

class JRoomModelClientSocket : public JSocket
{
    Q_OBJECT
    explicit JRoomModelClientSocket(QObject *parent = 0);
public:
	static JRoomModelClientSocket* instance();
};

#endif // JROOMMODELCLIENTSOCKET_H
