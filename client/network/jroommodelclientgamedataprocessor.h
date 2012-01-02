#ifndef JROOMMODELCLIENTGAMEDATAPROCESSOR_H
#define JROOMMODELCLIENTGAMEDATAPROCESSOR_H

#include <Processor/JClientNetworkDataProcessorBase>

class JRoomModelClientGameDataProcessor : public JClientNetworkDataProcessorBase
{
    Q_OBJECT
	explicit JRoomModelClientGameDataProcessor(JSession* session,JSocketBase *socket);
public:
	static JRoomModelClientGameDataProcessor* getInstance();
    JCode sendGameData(const QByteArray& data);
protected:
	void process(const QByteArray& data);
    JType getProcessorType()const;
};

#endif // JROOMMODELCLIENTGAMEDATAPROCESSOR_H
