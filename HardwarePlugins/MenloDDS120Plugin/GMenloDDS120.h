#ifndef GSERIALPORT_H
#define GSERIALPORT_H

#include "device.h"
#include "param.h"
//#include "qExtSerialPort/qextserialport.h"
//#include "qExtSerialPort/qextserialenumerator.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "PortSettingsWidget.h"
#include "hled.h"
//#include "GMenloDDS120Widget.h"


/////////////////////////////////////////////////////////////////////
//! \brief The GMenloDDS120 class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GMenloDDS120 : public GProgDevice
{
	Q_OBJECT

public:
	GMenloDDS120(QObject *parent, QString uniqueIdentifierName = "");
	~GMenloDDS120();

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
	//void ResetNovaTech();
	//void SetClockSource(bool clockSource);
	void ShowPortSettings();

	void GetFrequency();
	//void ReadCurrentSettings(QByteArray settings);
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
	//void ClockLEDisGreen();
	void LEDisRed();//Used to indicate device is disconnected.
	//void ClockLEDisRed();
private:
	//! Lists the ports
	QStringList PortList();

private:
	QextSerialPort* m_pExtSerialPort;
	GParamInt m_PortStatus;		//! Serial port status: 1 = setup and ready; -1 = LabExe just started, no action yet; 0 = closed; 2 = error;

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
	//GMenloDDS120Widget m_ControllerWidget;
	//bool stillBuilding;
	//bool m_FirstTime;


	friend class GMenloDDS120Widget;
	GMenloDDS120Widget* m_pControllerWidget;
};

#endif // GSERIALPORT_H
