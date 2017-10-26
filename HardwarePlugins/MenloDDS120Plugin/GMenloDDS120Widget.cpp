#include "GMenloDDS120Widget.h"
#include "ui_GMenloDDS120Widget.h"
#include <stdio.h>
#include <QMutexLocker>
//#include "hled.h"


GMenloDDS120Widget::GMenloDDS120Widget(GMenloDDS120* pTheController, QWidget *parent)
	: QWidget(parent)
	, m_pController(pTheController)
{
	ui = new Ui::GMenloDDS120Widget();
	led = new HLed(this);
	//ledClock = new HLed(this);
	
	//ui->pLEDLayout->insert(

	ui->setupUi(this);
	//QFormLayout* pFLay1 = new QFormLayout();
	//ui->portNameLayout->addLayout(pFLay1);
	//pFLay1->addRow(m_pController->m_PortName.ProvideNewLabel(this), m_pController->m_PortName.ProvideNewParamLineEdit(this));
	
	
	ui->pLay->addWidget(m_pController->m_ListPorts.ProvideNewParamButton(this));
	//ui->pLay->addWidget(m_pController->m_ComPortSettings.ProvideNewParamButton(this));
	//ui->pLay->addWidget(m_pController->m_SetComPort.ProvideNewParamLineEdit(this));

	ui->pLEDLayout->addWidget(led);
	//ui->pClockLEDLayout->addWidget(ledClock);
	ui->portNameLayout->addWidget(m_pController->m_SetComPort.ProvideNewParamLineEdit(this));
	//ui->pLay->addWidget(led);
	//led->setColor(Qt::red);
	//led->blink();
	//ui->led->setColor(Qt::red);
	//ui->led->setColor(Qt::red);
	
	ui->pLay->addWidget(m_pController->m_Settings.ProvideNewParamButton(this));
	
	QFormLayout* pFLay = new QFormLayout();
	ui->pLay->addLayout(pFLay);

	pFLay->addRow(m_pController->m_FreqSine.ProvideNewLabel(this), m_pController->m_FreqSine.ProvideNewParamSpinBox(this));
	//pFLay->addRow(m_pController->m_SetExtRef.ProvideNewLabel(this), m_pController->m_SetExtRef.ProvideNewParamRadioButtons(this, "Internal", "Lock to external (10 MHz)"));

	//m_pController->m_FreqSine.SetDisplayDecimals(11);
	//m_pController->m_FreqSine.SetHardLimits(0.25, 350);
	//m_pController->m_FreqSine.SetParamValue(20000000);//! 20 MHz (now working?)
	
	//ui->pLay->addWidget(m_pController->m_Reset.ProvideNewParamButton(this));
	

	connect(m_pController, SIGNAL(LEDisGreen()), this, SLOT(ConnectedLED()));	
	connect(m_pController, SIGNAL(LEDisRed()), this, SLOT(DisconnectedLED()));

	//connect(m_pController, SIGNAL(ClockLEDisGreen()), this, SLOT(ConnectedClockLED()));	
	//connect(m_pController, SIGNAL(ClockLEDisRed()), this, SLOT(DisconnectedClockLED()));

	connect(m_pController, SIGNAL(StatusUpdate(QString)), ui->pStatusEdit, SLOT(appendPlainText(QString)));
//connect(m_pController->m_SetComPort, SIGNAL(ValueUpdated()), m_pController, SLOT(ConnectToPort()));
	
	//connect(&m_pController->m_PortName, SIGNAL(ValueUpdated(QString)), this, SLOT(WidgetClearCursor()));
	
}

GMenloDDS120Widget::~GMenloDDS120Widget()
{
	delete ui;
}

void GMenloDDS120Widget::ConnectedLED()
{
	led->setColor(Qt::green);
	led->turnOn();
}
// void GMenloDDS120Widget::ConnectedClockLED()
// {
// 	ledClock->setColor(Qt::green);
// 	ledClock->turnOn();
// }


void GMenloDDS120Widget::DisconnectedLED()
{
	led->setColor(Qt::red);
	led->blink();
}
// void GMenloDDS120Widget::DisconnectedClockLED()
// {
// 	ledClock->setColor(Qt::red);
// 	ledClock->blink();
// }


void GMenloDDS120Widget::WidgetClearCursor()
{
	//ui->pStatusEdit->appendPlainText("TEST");
	//ui->pPortNameLineEdit->setReadOnly(true);
	//ui->pPortNameLineEdit->repaint();
}