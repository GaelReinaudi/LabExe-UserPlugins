#include "GNovatech409BWidget.h"
#include "ui_GNovatech409BWidget.h"
#include <stdio.h>
#include <QMutexLocker>
//#include "hled.h"


GNovatech409BWidget::GNovatech409BWidget(GNovatech409B* pTheController, QWidget *parent)
	: QWidget(parent)
	, m_pController(pTheController)
{
	ui = new Ui::GNovatech409BWidget();
	led = new HLed(this);
	
	//ui->pLEDLayout->insert(

	ui->setupUi(this);
	//QFormLayout* pFLay1 = new QFormLayout();
	//ui->portNameLayout->addLayout(pFLay1);
	//pFLay1->addRow(m_pController->m_PortName.ProvideNewLabel(this), m_pController->m_PortName.ProvideNewParamLineEdit(this));
	
	
	ui->pLay->addWidget(m_pController->m_ListPorts.ProvideNewParamButton(this));
	ui->pLay->addWidget(m_pController->m_ComPortSettings.ProvideNewParamButton(this));
	//ui->pLay->addWidget(m_pController->m_SetComPort.ProvideNewParamLineEdit(this));

	ui->pLEDLayout->addWidget(led);
	ui->portNameLayout->addWidget(m_pController->m_SetComPort.ProvideNewParamLineEdit(this));
	//ui->pLay->addWidget(led);
	//led->setColor(Qt::red);
	//led->blink();
	//ui->led->setColor(Qt::red);
	//ui->led->setColor(Qt::red);
	
	ui->pLay->addWidget(m_pController->m_Settings.ProvideNewParamButton(this));

	QFormLayout* pFLay = new QFormLayout();
	ui->pLay->addLayout(pFLay);

	pFLay->addRow(m_pController->m_Freq0.ProvideNewLabel(this), m_pController->m_Freq0.ProvideNewParamSpinBox(this));
	pFLay->addRow(m_pController->m_Freq1.ProvideNewLabel(this), m_pController->m_Freq1.ProvideNewParamSpinBox(this));
	pFLay->addRow(m_pController->m_Freq2.ProvideNewLabel(this), m_pController->m_Freq2.ProvideNewParamSpinBox(this));
	pFLay->addRow(m_pController->m_Freq3.ProvideNewLabel(this), m_pController->m_Freq3.ProvideNewParamSpinBox(this));
	
	m_pController->m_Freq0.SetDisplayDecimals(7);
	m_pController->m_Freq1.SetDisplayDecimals(7);
	m_pController->m_Freq2.SetDisplayDecimals(7);
	m_pController->m_Freq3.SetDisplayDecimals(7);
	
	ui->pLay->addWidget(m_pController->m_Reset.ProvideNewParamButton(this));
	

	connect(m_pController, SIGNAL(LEDisGreen()), this, SLOT(ConnectedLED()));	
	connect(m_pController, SIGNAL(LEDisRed()), this, SLOT(DisconnectedLED()));

	connect(m_pController, SIGNAL(StatusUpdate(QString)), ui->pStatusEdit, SLOT(appendPlainText(QString)));
//connect(m_pController->m_SetComPort, SIGNAL(ValueUpdated()), m_pController, SLOT(ConnectToPort()));
	
	//connect(&m_pController->m_PortName, SIGNAL(ValueUpdated(QString)), this, SLOT(WidgetClearCursor()));
	
}

GNovatech409BWidget::~GNovatech409BWidget()
{
	delete ui;
}

void GNovatech409BWidget::ConnectedLED()
{
	led->setColor(Qt::green);
	led->turnOn();
}

void GNovatech409BWidget::DisconnectedLED()
{
	led->setColor(Qt::red);
	led->blink();
}


void GNovatech409BWidget::WidgetClearCursor()
{
	//ui->pStatusEdit->appendPlainText("TEST");
	//ui->pPortNameLineEdit->setReadOnly(true);
	//ui->pPortNameLineEdit->repaint();
}