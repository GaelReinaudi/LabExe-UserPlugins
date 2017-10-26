#ifndef GNovatech425A_H
#define GNovatech425A_H

#include "device.h"
#include "param.h"
//#include "qExtSerialPort/qextserialport.h"
//#include "qExtSerialPort/qextserialenumerator.h"
#include "qExtSerialPort/src/qextserialport.h"
#include "qExtSerialPort/src/qextserialenumerator.h"
#include "PortSettingsWidget.h"
#include "hled.h"
//#include "GNovatech425AWidget.h"


/////////////////////////////////////////////////////////////////////
//! \brief The GNovatech425A class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GNovatech425A : public GHardDevice
{
	Q_OBJECT

public:
	GNovatech425A(QString uniqueIdentifierName, QObject *parent);
	~GNovatech425A();

public:

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	virtual void LatterInitialization();
	//virtual void OnDataAvailable();

protected slots:
	//! Slot called when something is ready to read
	void onReadyRead();
	void onDsrChanged(bool status);

	//! Connect to whatever port is specified in the Port name variable
	void ConnectToPort();

	//! sdfsfsdfsdf
	void SetNovaTechFreq0(double freqSine);
	void SetPortName(QString portName);
	void PortListCall();
	void ResetNovaTech();
	void SetClockSource(bool clockSource);
	void ShowPortSettings();

	void QueryCurrentSettings();
	void ReadCurrentSettings(QByteArray settings);
	//void ConnectToPort();
	//void ComPortSettings();
	void setNewBaudRate();
	void setNewFlowControl();
	void setNewParity();
	void setNewDataBits();
	void setNewStopBits();

	QString ReturnPortName();

signals:
	void StatusUpdate(QString);//Used in order to write updates to the status box.
	void LEDisGreen();//Used to indicate device is connected.
	void ClockLEDisGreen();
	void LEDisRed();//Used to indicate device is disconnected.
	void ClockLEDisRed();
private:
	//! Lists the ports
	QStringList PortList();

private:
	QextSerialPort* m_pExtSerialPort;

	//! Port name
	GParamString m_PortName;
	GParamString m_SetComPort;
	//! String that is to be written to the m_pExtSerialPort
	//GParamString m_WriteString;
	GParamBool m_Settings;
	GParamBool m_DisplaySettings;
	GParamBool m_Reset;
	GParamBool m_ComPortSettings;

	GParamBool m_ListPorts;
	GParamDouble m_FreqSine;

	GParamInt m_BaudIndex;
	GParamInt m_FlowIndex;
	GParamInt m_ParIndex;
	GParamInt m_DataIndex;
	GParamInt m_StopIndex;

	GParamInt m_FirstTime;

	QByteArray m_CurrentStatus;
	QByteArray m_Bytes;

	GParamBool m_SetExtRef;//! 425A Novatech: 1 = internal clock, 0 = use 10 MHz external clock (requires 48-bit math correction!)

	PortSettingsWidget m_SettingsWidget;
	//GNovatech425AWidget m_ControllerWidget;
	//bool stillBuilding;
	//bool m_FirstTime;


	friend class GNovatech425AWidget;
	GNovatech425AWidget* m_pControllerWidget;
};

#endif // GNovatech425A_H
