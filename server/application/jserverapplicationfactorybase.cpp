#include "jserverapplicationfactorybase.h"
#include "jserverapplicationbase.h"

JServerApplicationFactoryBase* JServerApplicationFactoryBase::s_instance;

JServerApplicationFactoryBase::JServerApplicationFactoryBase(QObject *parent) :
    QObject(parent)
{
}

void JServerApplicationFactoryBase::setInstance(JServerApplicationFactoryBase* instance)
{
	s_instance = instance;
}

JServerApplicationFactoryBase* JServerApplicationFactoryBase::getInstance()
{
	return s_instance;
}
