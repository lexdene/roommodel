#ifndef JROOMMODELSERVERGAMEDATAPROCESSOR_H
#define JROOMMODELSERVERGAMEDATAPROCESSOR_H

#include <Processor/JProcessor>

class JRoomModelServerGameDataProcessor : public JProcessor
{
public:
	static JRoomModelServerGameDataProcessor* instance();
	void process(JSocket* socket , const QByteArray& data);
    JType getProcessorType()const;
    JCode sendGameData(JSocket* socket , const QByteArray& data);
private:
	explicit JRoomModelServerGameDataProcessor(QObject* parent = 0);
};

#endif // JROOMMODELSERVERGAMEDATAPROCESSOR_H
