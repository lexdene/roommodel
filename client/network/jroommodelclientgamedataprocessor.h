#ifndef JROOMMODELCLIENTGAMEDATAPROCESSOR_H
#define JROOMMODELCLIENTGAMEDATAPROCESSOR_H

#include <Processor/JProcessor>

class JRoomModelClientGameDataProcessor : public JProcessor
{
    Q_OBJECT
public:
	static JRoomModelClientGameDataProcessor* instance();
    JCode sendGameData(const QByteArray& data);
protected:
	void process(JSocket* socket , const QByteArray& data);
    JType getProcessorType()const;
private:
	explicit JRoomModelClientGameDataProcessor(QObject* parent = 0);
};

#endif // JROOMMODELCLIENTGAMEDATAPROCESSOR_H
