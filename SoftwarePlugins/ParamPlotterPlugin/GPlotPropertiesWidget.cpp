#include "GPlotPropertiesWidget.h"
#include "GParamPlotterWidget.h"

GPlotPropertiesWidget::GPlotPropertiesWidget(GParamPlotter *pParentPlotter)
	: m_Plotter(pParentPlotter)
	, m_PlotWidget(0)
{
	setupUi(this);

	// Initialize color pickers
	colorpickerMajor->setStandardColors();
	colorpickerMinor->setStandardColors();
	colorpickerCurve->setStandardColors();
	colorpickerBackground->setStandardColors(); colorpickerBackground->setCurrentColor(colorpickerBackground->color(1));

	// Initialize signals/slots
	connect(pushApply, SIGNAL(clicked()), this, SLOT(Apply()));
	connect(pushOkay, SIGNAL(clicked()), this, SLOT(Okay()));
	connect(pushCancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	connect(radioXAutoOff, SIGNAL(clicked()), this, SLOT(DisableAutoscalingX()));
	connect(radioXAll, SIGNAL(clicked()), this, SLOT(EnableAutoscalingX()));
// 	connect(radioYAutoOff, SIGNAL(clicked()), this, SLOT(DisableAutoscalingY()));
// 	connect(radioYAuto, SIGNAL(clicked()), this, SLOT(EnableAutoscalingY()));
	connect(checkAutoScaleY, SIGNAL(toggled(bool)), this, SLOT(SetAutoscalingY(bool)));
}

GPlotPropertiesWidget::~GPlotPropertiesWidget()
{

}

void GPlotPropertiesWidget::SetPlottingWidget( GParamPlotterWidget* pPlotterWidget )
{
	m_PlotWidget = pPlotterWidget;
	Apply();
}

void GPlotPropertiesWidget::Apply()
{
	UpdateAxesAndScaling();
	UpdateCurveAndCanvas();
	UpdateGrid();
	UpdateTitlesAndLables();
}

void GPlotPropertiesWidget::Cancel()
{
	hide();
}

void GPlotPropertiesWidget::Okay()
{
	UpdateAxesAndScaling();
	UpdateCurveAndCanvas();
	UpdateGrid();
	UpdateTitlesAndLables();
	hide();
}

void GPlotPropertiesWidget::DisableAutoscalingX()
{
	spinXMax->setEnabled(true);
	spinXMin->setEnabled(true);
	spinXMajor->setEnabled(true);
	spinXMinor->setEnabled(true);
}

void GPlotPropertiesWidget::EnableAutoscalingX()
{
	spinXMax->setEnabled(false);
	spinXMin->setEnabled(false);
	spinXMajor->setEnabled(false);
	spinXMinor->setEnabled(false);
}

void GPlotPropertiesWidget::SetAutoscalingY(bool doAutoscaling)
{
	if(doAutoscaling) {
		spinYMax->setEnabled(false);
		spinYMin->setEnabled(false);
		spinYMajor->setEnabled(false);
		spinYMinor->setEnabled(false);
	}
	else {
		spinYMax->setEnabled(true);
		spinYMin->setEnabled(true);
		spinYMajor->setEnabled(true);
		spinYMinor->setEnabled(true);
	}
}

void GPlotPropertiesWidget::UpdateAxesAndScaling()
{
	if(!m_PlotWidget) {
		qWarning() << "The GPlotPropertiesWidget object has not been assigned a GParamPlotterWidget to modify";
		return;
	}
	QwtScaleEngine *XScaleEngine = NULL;
	QwtScaleEngine *YScaleEngine = NULL;

	// x-Axis
	if (comboXScale->currentIndex() == 0) { // linear
		XScaleEngine = new QwtLinearScaleEngine; 
	} 
	else { // Logarithmic
		XScaleEngine = new QwtLog10ScaleEngine; 
	} 
	m_PlotWidget->m_Plot->setAxisScaleEngine(QwtPlot::xBottom, XScaleEngine);

	if (radioXAutoOff->isChecked())
	{
		m_PlotWidget->m_Plot->setAxisScaleDiv(
			QwtPlot::xBottom, 
			XScaleEngine->divideScale(spinXMin->value(), spinXMax->value(), spinXMajor->value(), spinXMinor->value())
		);
		m_PlotWidget->m_Plot->updateAxes();
	}
	else if (radioXAll->isChecked())
	{
		m_PlotWidget->m_Plot->updateAxes();
		m_PlotWidget->m_Plot->setAxisAutoScale(QwtPlot::xBottom);
	}

	// y-Axis
	if (comboYScale->currentIndex() == 0) { YScaleEngine = new QwtLinearScaleEngine; } // linear
	else { YScaleEngine = new QwtLog10ScaleEngine; } // Logarithmic
	m_PlotWidget->m_Plot->setAxisScaleEngine(QwtPlot::yLeft, YScaleEngine);

	if(checkAutoScaleY->isChecked()) {
		m_PlotWidget->m_Plot->updateAxes();
		m_PlotWidget->m_Plot->setAxisAutoScale(QwtPlot::yLeft);
	}
	else {
		m_PlotWidget->m_Plot->setAxisScaleDiv(
			QwtPlot::yLeft, 
			YScaleEngine->divideScale(spinYMin->value(), spinYMax->value(), spinYMajor->value(), spinYMinor->value())
			);
		m_PlotWidget->m_Plot->updateAxes();
	}
}

void GPlotPropertiesWidget::UpdateCurveAndCanvas()
{
	if(!m_PlotWidget) {
		qWarning() << "The GPlotPropertiesWidget object has not been assigned a GParamPlotterWidget to modify";
		return;
	}
	m_PlotWidget->m_PenCurve->setStyle( (Qt::PenStyle) (comboPenCurve->currentIndex()+1) );
	m_PlotWidget->m_PenCurve->setColor( colorpickerCurve->currentColor() );
	m_PlotWidget->m_Curve->setPen(*m_PlotWidget->m_PenCurve);
	m_PlotWidget->m_Plot->setCanvasBackground( colorpickerBackground->currentColor() );
}

void GPlotPropertiesWidget::UpdateGrid()
{
	if(!m_PlotWidget) {
		qWarning() << "The GPlotPropertiesWidget object has not been assigned a GParamPlotterWidget to modify";
		return;
	}
	m_PlotWidget->m_Grid->enableX(checkXMajor->isChecked()); 
	m_PlotWidget->m_Grid->enableXMin(checkXMinor->isChecked()); 
	m_PlotWidget->m_Grid->enableY(checkYMajor->isChecked()); 
	m_PlotWidget->m_Grid->enableYMin(checkYMinor->isChecked()); 
	m_PlotWidget->m_PenMajor->setStyle( (Qt::PenStyle) (comboPenMajor->currentIndex()+1) );
	m_PlotWidget->m_PenMajor->setColor( colorpickerMajor->currentColor() );
	m_PlotWidget->m_Grid->setMajPen(*m_PlotWidget->m_PenMajor);
	m_PlotWidget->m_PenMinor->setStyle( (Qt::PenStyle) (comboPenMinor->currentIndex()+1) );
	m_PlotWidget->m_PenMinor->setColor( colorpickerMinor->currentColor() );
	m_PlotWidget->m_Grid->setMinPen(*m_PlotWidget->m_PenMinor);
}

void GPlotPropertiesWidget::UpdateTitlesAndLables()
{
	if(!m_PlotWidget) {
		qWarning() << "The GPlotPropertiesWidget object has not been assigned a GParamPlotterWidget to modify";
		return;
	}
	m_PlotWidget->m_Plot->setAxisTitle(QwtPlot::xBottom, lineXLabel->text());
	m_PlotWidget->m_Plot->setAxisTitle(QwtPlot::yLeft, lineYLabel->text());
	m_PlotWidget->m_Plot->setTitle(lineGraphTitle->text());
}

void GPlotPropertiesWidget::PopulateSettings( QSettings& inQsettings )
{
	inQsettings.setValue("autoScaleY"				, checkAutoScaleY->isChecked()			);
	inQsettings.setValue("force0inRange"			, checkForceZeroInRange->isChecked()	);
	inQsettings.setValue("minY"						, spinYMin->value()						);
	inQsettings.setValue("maxY"						, spinYMax->value()						);
	inQsettings.setValue("checkXMajor"				, checkXMajor->isChecked()				);
	inQsettings.setValue("checkXMinor"				, checkXMinor->isChecked()				);
	inQsettings.setValue("checkYMajor"				, checkYMajor->isChecked()				);
	inQsettings.setValue("checkYMinor"				, checkYMinor->isChecked()				);
	inQsettings.setValue("colorpickerMajor"			, colorpickerMajor->currentColor()		);
	inQsettings.setValue("colorpickerMinor"			, colorpickerMinor->currentColor()		);
	inQsettings.setValue("colorpickerCurve"			, colorpickerCurve->currentColor()		);
	inQsettings.setValue("colorpickerBackground"	, colorpickerBackground->currentColor()	);
	inQsettings.setValue("maxDataSpinBox"			, maxDataSpinBox->value()				);
}

void GPlotPropertiesWidget::InterpretSettings( QSettings& fromQsettings )
{
	checkAutoScaleY->setChecked(			fromQsettings.value("autoScaleY", false			).toBool());
	checkForceZeroInRange->setChecked(		fromQsettings.value("force0inRange", false		).toBool());
	spinYMin->setValue(						fromQsettings.value("minY", 0.0).toDouble()		);
	spinYMax->setValue(						fromQsettings.value("maxY", 100.0).toDouble()	);
	checkXMajor->setChecked(				fromQsettings.value("checkXMajor", false		).toBool());
	checkXMinor->setChecked(				fromQsettings.value("checkXMinor", false		).toBool());
	checkYMajor->setChecked(				fromQsettings.value("checkYMajor", false		).toBool());
	checkYMinor->setChecked(				fromQsettings.value("checkYMinor", false		).toBool());
	colorpickerMajor->setCurrentColor(		fromQsettings.value("colorpickerMajor"			).value<QColor>());
	colorpickerMinor->setCurrentColor(		fromQsettings.value("colorpickerMinor"			).value<QColor>());
	colorpickerCurve->setCurrentColor(		fromQsettings.value("colorpickerCurve"			).value<QColor>());
	colorpickerBackground->setCurrentColor(	fromQsettings.value("colorpickerBackground"		).value<QColor>());
	maxDataSpinBox->setValue(				fromQsettings.value("maxDataSpinBox", 200		).toInt());
	Apply();
}