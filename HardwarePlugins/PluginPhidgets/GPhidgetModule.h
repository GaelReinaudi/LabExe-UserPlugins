#ifndef GPhidgetModule_H
#define GPhidgetModule_H

#include "Device/GHardDevice.h"
class GPhidgetManager;

typedef struct _CPhidget *CPhidgetHandle;

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetModule class encapsulate a Phidget module.
/*!
It handles some phidget modules event events like:
- GModuleAttachHandler() is function called when a phidget gets attached. The phidget API 
knows that it has to call this function because I call this Phidget-API function:
\code CPhidget_set_OnAttach_Handler(TheCPhidgetHandle(), GModuleAttachHandler, this); \endcode

It derives from GDevice so that it can provide a gui. It also reimplements the IsAble() function that informs the workbench if the module is ready to work.
It defines the list of sub devices defined in the derived class. It will be used for display on a GDeviceShelf.
*/
class GPhidgetModule : public GHardDevice
{
	Q_OBJECT

public:
	GPhidgetModule(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetModule();

	//! Reimplemented from GDevice to add some stuff to check in order to qualify the device as "able".
	virtual bool IsAble() const;
	//! Returns the parent GPhidgetManager if any. (0 otherwise)
	GPhidgetManager* ParentManager() const;
	//! Returns the serial number of the phidget.
	int SerialNumber() const { return m_SerialNumber; }

protected:
	//! Has to be reimplemented to return the CPhidgetHandle used to control the phidget from the library
	virtual CPhidgetHandle TheCPhidgetHandle() const = 0;

protected slots:
	//! Called whenever the module was plugged in (and the computer detects it).
	virtual void ConfigureWhenPluggedIn() {}
	//! Performs a phidget configuration using the function from the common API (ie not yet specialized modules). 
	void CommonPhidgetInitialization();
	//! Has to be reimplemented to perform some initialization after the phidget has been created and opened. 
	virtual void DelayedPhidgetInitialization() = 0;

protected:
	//! the phidget serial number
	int m_SerialNumber;
	//! Tells if the device is able to work (is present and is properly controlled).
	bool m_IsAttached;

private:

	friend int __stdcall GModuleAttachHandler(CPhidgetHandle phid, void* pPhiMod);
	friend int __stdcall GModuleDetachHandler(CPhidgetHandle phid, void* pPhiMod);
	friend int __stdcall GModuleErrorHandler(CPhidgetHandle phid, void* pPhiMod, int ErrorCode, const char *Description);
};

#endif // GPhidgetModule_H
