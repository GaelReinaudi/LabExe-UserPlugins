#include "GParamPlotter.h"
#include "GParamPlotterWidget.h"
#include "GPlotPropertiesWidget.h"

GParamPlotter::GParamPlotter(QObject *parent, QString uniqueIdentifierName)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_BucketParam("Input", this)
{
	m_PropertiesWindow = new GPlotPropertiesWidget(this);
}

GParamPlotter::~GParamPlotter()
{
	if(m_PropertiesWindow)
		delete m_PropertiesWindow;
}

void GParamPlotter::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);

	GParamPlotterWidget* pPlotWid = new GParamPlotterWidget(this, theDeviceWidget);
	m_PropertiesWindow->SetPlottingWidget(pPlotWid);
	pLay->addWidget(pPlotWid);
	// connect the updating of the value
	connect(&m_BucketParam, SIGNAL(ValueUpdated(double)), pPlotWid, SLOT(AddValue(double)), Qt::QueuedConnection);
	connect(&m_BucketParam, SIGNAL(ManyValuesAvailable(GVectorDouble)), pPlotWid, SLOT(SetNewValues(GVectorDouble)), Qt::QueuedConnection);
	// the plot should use the available space
	theDeviceWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void GParamPlotter::PopulateSettings( QSettings& inQsettings )
{
	GProgDevice::PopulateSettings(inQsettings);
	inQsettings.beginGroup("display");
	m_PropertiesWindow->SaveDeviceSettings(inQsettings, false);
	inQsettings.endGroup();
}

void GParamPlotter::InterpretSettings( QSettings& fromQsettings )
{
	GProgDevice::InterpretSettings(fromQsettings);
	fromQsettings.beginGroup("display");
	m_PropertiesWindow->ReadDeviceSettings(fromQsettings, false);
	fromQsettings.endGroup();
}