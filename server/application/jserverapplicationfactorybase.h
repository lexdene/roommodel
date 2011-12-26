#ifndef JSERVERAPPLICATIONFACTORYBASE_H
#define JSERVERAPPLICATIONFACTORYBASE_H

#include <QObject>
class JServerApplicationBase;

class JServerApplicationFactoryBase : public QObject
{
	Q_OBJECT
public:
	static void setInstance(JServerApplicationFactoryBase*);
	static JServerApplicationFactoryBase* getInstance();
	virtual JServerApplicationBase* createApplication(int roomId)=0;
protected:
	explicit JServerApplicationFactoryBase(QObject *parent = 0);
private:
	static JServerApplicationFactoryBase* s_instance;
};

#endif // JSERVERAPPLICATIONFACTORYBASE_H
