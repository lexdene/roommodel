#ifndef JROOMMODELSERVERDISCONNECTEDPROCESSOR_H
#define JROOMMODELSERVERDISCONNECTEDPROCESSOR_H

#include <Processor/JProcessor>

class JRoomModelServerDisconnectedProcessor : public JProcessor
{
	Q_OBJECT
public:
	static JRoomModelServerDisconnectedProcessor* instance();
	void process(JSocket* socket , const QByteArray& data);
	JType getProcessorType()const;
private:
	explicit JRoomModelServerDisconnectedProcessor(QObject* parent = 0);
};

#endif /* JROOMMODELSERVERDISCONNECTEDPROCESSOR_H */

