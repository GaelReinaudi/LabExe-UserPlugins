#include "GPxiChannel.h"
#include "GDAQmxModule.h"

GPxiChannel::GPxiChannel(QString uniqueIdentifierName, QObject* parentDevice)
	: GHardDevice(uniqueIdentifierName, parentDevice)
{
	ReName(DefaultShortName());
}

GPxiChannel::~GPxiChannel()
{

}

QString GPxiChannel::DefaultShortName() const
{
	QString thename = Name();
	if(!ParentModule())
		return thename;
	int chassisNum = ParentModule()->ChassisNumber();
	int slotNum = ParentModule()->SlotNumber();
	return QString("S%1-").arg(slotNum) + thename.split("/").last();
}

GDAQmxModule* GPxiChannel::ParentModule() const
{
	if(!parent() || !parent()->inherits("GDAQmxModule"))
		return 0;
	return dynamic_cast<GDAQmxModule*>(parent());
}