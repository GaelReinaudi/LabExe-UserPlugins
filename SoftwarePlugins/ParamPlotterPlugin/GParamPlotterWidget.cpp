#include "GParamPlotterWidget.h"
#include "GParamPlotter.h"
#include "Param/GParamBucketWidget.h"
#include "GPlotPropertiesWidget.h"
#include "ui_GParamPlotterWidget.h"

GParamPlotterWidget::GParamPlotterWidget(GParamPlotter* pThePlotter, QWidget *parent)
	: QWidget(parent)
	, m_pPlotter(pThePlotter)
	, m_Plot(new QwtPlot(this))
	, m_TotalUpdates(0)
{
	ui = new Ui::GParamPlotterWidget();
	ui->setupUi(this);

	// the bucket for the param to plot
	GParamBucketTreeWidget* pYBWid = m_pPlotter->m_BucketParam.ProvideParamBucketTreeWidget(this);
	pYBWid->UseHighLightDecay(false);
	pYBWid->setTitle("");
	ui->pLayParam->insertWidget(0, pYBWid);

	// the plot in the layout
	ui->pLayPlot->insertWidget(0, m_Plot);

	m_Plot->setAutoReplot(true);
	m_Curve = new QwtPlotCurve; 
	m_Curve->attach(m_Plot);
	m_Grid = new QwtPlotGrid; 
	m_Grid->attach(m_Plot);
	m_PenMajor = new QPen; 
	m_Grid->setMajPen(*m_PenMajor);
	m_PenMinor = new QPen; 
	m_Grid->setMinPen(*m_PenMinor);
	m_PenCurve = new QPen; 
	m_Curve->setPen(*m_PenCurve);
	m_PenCurve->setWidth(3);

	// Sets the properties of the graph
	m_Plot->setTitle("");
	m_Plot->setAxisTitle(QwtPlot::xBottom, "");
	m_Plot->setAxisTitle(QwtPlot::yLeft, "");

	// Sets the QwtPlot to expand in both the vertical and horizontal directions
 	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(1);
	sizePolicy.setVerticalStretch(1);
	m_Plot->setSizePolicy(sizePolicy);
	// Initialize popup menu
	connect(ui->pSettingButton, SIGNAL(clicked()), m_pPlotter->m_PropertiesWindow, SLOT(show()));
	connect(ui->pSettingButton, SIGNAL(clicked()), m_pPlotter->m_PropertiesWindow, SLOT(raise()));
	connect(ui->pClearButton, SIGNAL(clicked()), this, SLOT(ClearPlot()));

	adjustSize();
}

GParamPlotterWidget::~GParamPlotterWidget()
{
	delete m_PenCurve;
	delete m_PenMinor;
	delete m_PenMajor;
	delete m_Grid;
	delete m_Curve;
	delete ui;
}

void GParamPlotterWidget::AddValue( const double & newValue )
{
	int maxDataToShow = m_pPlotter->m_PropertiesWindow->maxDataSpinBox->value();
	// deallocate some memory
	int dataSize = m_xData.size();
	if(dataSize > 2 * maxDataToShow) {
		m_xData.remove(0, dataSize - maxDataToShow);
		m_yData.remove(0, dataSize - maxDataToShow);
	}
	m_TotalUpdates++;
	m_xData.append(m_TotalUpdates);
	m_yData.append(newValue);
	dataSize = m_xData.size();
	int indexDataToShow = qMax(0, dataSize - maxDataToShow);
	int actualShowing = qMin(maxDataToShow, dataSize);
	m_Curve->setData(m_xData.data() + indexDataToShow, m_yData.data() + indexDataToShow, actualShowing);
}

void GParamPlotterWidget::ClearPlot()
{
	m_xData.clear();
	m_yData.clear();
	m_TotalUpdates = 0;
	m_Curve->setData(0, 0, 0);
}

void GParamPlotterWidget::SetNewValues( const GVectorDouble & newValues )
{
	int dataSize = newValues.size();
	if(m_xData.size() != dataSize) {
		m_xData.resize(dataSize);
	}
	for(int i = 0; i < dataSize; i++)
		m_xData[i] = i;

	int maxDataToShow = m_pPlotter->m_PropertiesWindow->maxDataSpinBox->value();
// 	// deallocate some memory
// 	if(dataSize > 2 * maxDataToShow) {
// 		m_xData.remove(0, dataSize - maxDataToShow);
// 		m_yData.remove(0, dataSize - maxDataToShow);
// 	}
	m_TotalUpdates++;
	m_yData = newValues;
	dataSize = m_xData.size();
	int indexDataToShow = qMax(0, dataSize - maxDataToShow);
	int actualShowing = qMin(maxDataToShow, dataSize);
	m_Curve->setData(m_xData.data() + indexDataToShow, m_yData.data() + indexDataToShow, actualShowing);
}