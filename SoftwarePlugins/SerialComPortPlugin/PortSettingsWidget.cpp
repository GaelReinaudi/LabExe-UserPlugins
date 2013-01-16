#include "portsettingswidget.h"

PortSettingsWidget::PortSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.baudBox->addItem("BAUD 110");
	ui.baudBox->addItem("BAUD 300");
	ui.baudBox->addItem("BAUD 600");
	ui.baudBox->addItem("BAUD 1200");
	ui.baudBox->addItem("BAUD 2400");
	ui.baudBox->addItem("BAUD 4800");
	ui.baudBox->addItem("BAUD 9600");
	ui.baudBox->addItem("BAUD 19200");
	ui.baudBox->addItem("BAUD 38400");
	ui.baudBox->addItem("BAUD 57600");
	ui.baudBox->addItem("BAUD 115200");

	ui.flowBox->addItem("Off");
	ui.flowBox->addItem("Hardware");
	ui.flowBox->addItem("Software");

	ui.parityBox->addItem("Space Parity");
	ui.parityBox->addItem("Mark Parity");
	ui.parityBox->addItem("No Parity");
	ui.parityBox->addItem("Even Parity");
	ui.parityBox->addItem("Odd Parity");

	ui.dataBox->addItem("5");
	ui.dataBox->addItem("6");
	ui.dataBox->addItem("7");
	ui.dataBox->addItem("8");

	ui.stopBox->addItem("1");
	ui.stopBox->addItem("1.5");
	ui.stopBox->addItem("2");
	
}

PortSettingsWidget::~PortSettingsWidget()
{

}
