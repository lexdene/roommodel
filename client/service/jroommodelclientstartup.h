#ifndef JROOMMODELCLIENTSTARTUP_H
#define JROOMMODELCLIENTSTARTUP_H

class QApplication;

class JRoomModelClientStartup
{
public:
    JRoomModelClientStartup(const QApplication& app);
    bool startup();
private:
    const QApplication& m_app;
};

#endif // JROOMMODELCLIENTSTARTUP_H
