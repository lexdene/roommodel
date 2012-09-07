#include "jroommodelclientstartup.h"
#include "network/jroommodelclientsocket.h"

#include <Socket/JMainClientSocket>
#include <Util/SHost>
#include <Helper/JConnectHelper>
#include <Helper/JGameClientArgumentAnalyser>

#include <QApplication>
#include <QStringList>

JRoomModelClientStartup::JRoomModelClientStartup(const QApplication& app)
    :m_app(app)
{
}

bool JRoomModelClientStartup::startup()
{
    JGameClientArgumentAnalyser *gcaa = JGameClientArgumentAnalyser::instance();
    if(!gcaa->processArgument(m_app.arguments())){
        qDebug()<<"process argument failed.";
        return false;
    }
    // connect to main client
    JMainClientSocket *mc_socket = JMainClientSocket::instance();
    JConnectHelper mc_connectHelper(mc_socket);
    mc_connectHelper.connectToHost(gcaa->getMainServer());
    if(!mc_connectHelper.waitForConnected(1000)){
        qDebug()<<"main client socket connect failed ."<<mc_connectHelper.getConnectError();
        return false;
    }
    // connect to game server
    JRoomModelClientSocket* rm_socket = JRoomModelClientSocket::instance();
    JConnectHelper rm_connectHelper(rm_socket);
    rm_connectHelper.connectToHost(gcaa->getGameServer());
    if(!rm_connectHelper.waitForConnected(1000)){
        qDebug()<<"room model client socket connect failed ."<<rm_connectHelper.getConnectError();
        return false;
    }
    return true;
}
