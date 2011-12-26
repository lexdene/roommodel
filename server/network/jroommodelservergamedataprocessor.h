#ifndef JROOMMODELSERVERGAMEDATAPROCESSOR_H
#define JROOMMODELSERVERGAMEDATAPROCESSOR_H

#include <Processor/JServerNetworkDataProcessorBase>

class JRoomModelServerGameDataProcessor : public JServerNetworkDataProcessorBase
{
    Q_OBJECT
public:
	explicit JRoomModelServerGameDataProcessor(JSession* session,JSocketBase *socket);
	void process(const QByteArray& data);
    EProcessorType getProcessorType()const;
public slots:
    JCode sendGameData(const QByteArray& data);
};

#endif // JROOMMODELSERVERGAMEDATAPROCESSOR_H
