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
//#include "GNovatech409BWidget.h"


/////////////////////////////////////////////////////////////////////
//! \brief The GNovatech409B class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GNovatech409B : public GProgDevice
{
	Q_OBJECT

public:
	GNovatech409B(QObject *parent, QString uniqueIdentifierName = "");
	~GNovatech409B();

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
	void SetNovaTechFreq0(double freq0);
	void SetNovaTechFreq1(double freq1);
	void SetNovaTechFreq2(double freq2);
	void SetNovaTechFreq3(double freq3);
	void SetPortName(QString portName);
	void PortListCall();
	void ResetNovaTech();
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
	void LEDisRed();//Used to indicate device is disconnected.
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
	GParamBool m_Reset;
	GParamBool m_ComPortSettings;

	GParamBool m_ListPorts;
	GParamDouble m_Freq0;
	GParamDouble m_Freq1;
	GParamDouble m_Freq2;
	GParamDouble m_Freq3;

	GParamInt m_BaudIndex;
	GParamInt m_FlowIndex;
	GParamInt m_ParIndex;
	GParamInt m_DataIndex;
	GParamInt m_StopIndex;

	GParamInt m_FirstTime;

	QByteArray m_CurrentStatus;
	QByteArray m_Bytes;

	PortSettingsWidget m_SettingsWidget;
	//GNovatech409BWidget m_ControllerWidget;
	//bool stillBuilding;
	//bool m_FirstTime;


	friend class GNovatech409BWidget;
	GNovatech409BWidget* m_pControllerWidget;
};

#endif // GSERIALPORT_H
