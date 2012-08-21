#ifndef JROOMMODELSERVERGAMEDATAPROCESSOR_H
#define JROOMMODELSERVERGAMEDATAPROCESSOR_H

#include <Processor/JProcessor>

class JRoomModelServerGameDataProcessor : public JProcessor
{
    Q_OBJECT
public:
	static JRoomModelServerGameDataProcessor* instance();
	void process(JSocket* socket , const QByteArray& data);
    JType getProcessorType()const;
public slots:
    JCode sendGameData(JSocket* socket , const QByteArray& data);
private:
	explicit JRoomModelServerGameDataProcessor(QObject* parent = 0);
};

#endif // JROOMMODELSERVERGAMEDATAPROCESSOR_H
