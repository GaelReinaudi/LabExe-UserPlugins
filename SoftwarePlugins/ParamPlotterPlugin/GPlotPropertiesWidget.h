#ifndef GPLOTPROPERTIESWIDGET_H
#define GPLOTPROPERTIESWIDGET_H

#include <QWidget>
#include <qwt/qwt_scale_engine.h>
#include "ui_GPlotPropertiesWidget.h"
#include "ToolBox/GSerializable.h"

class GParamPlotter;
class GParamPlotterWidget;

/////////////////////////////////////////////////////////////////////
//! \brief The GPlotPropertiesWidget class defines an interface to set the properties of a GParamPlotter.
/*!	
It actually needs to be assigned to a GParamPlotterWidget by using SetPlottingWidget(). This 
implies that it will change the parameters of only one plotting widget. But this should not be a problem 
since the widget is not expected to be more than one per GParamPlotter.
*/
class GPlotPropertiesWidget : public QWidget, public GSerializable, public Ui::GPlotPropertiesWidget
{
	Q_OBJECT

public:
	GPlotPropertiesWidget(GParamPlotter *pParentPlotter);
	~GPlotPropertiesWidget();

	//! Sets the plot-widget that is going to be controlled by this GPlotPropertiesWidget
	void SetPlottingWidget(GParamPlotterWidget* pPlotterWidget);

protected:
	//! Reimplemented.
	virtual void PopulateSettings(QSettings& inQsettings);
	//! Reimplemented.
	virtual void InterpretSettings(QSettings& fromQsettings);

protected slots:
	//! Slot which handles the Apply button being pushed. Updates but doesn't close the window.
	void Apply();
	//! Slot which handles the Cancel button being pushed. Closes the window but doesn't update.
	void Cancel();
	//! Slot which handles the Okay button being pushed. Updates and closes the window.
	void Okay();
	//! Slot which enables elements necessary for manual scaling on the x-axis.
	void DisableAutoscalingX();
	//! Slot which disables elements necessary for manual scaling on the x-axis.
	void EnableAutoscalingX();
// 	//! Slot which enables elements necessary for manual scaling on the y-axis.
// 	void DisableAutoscalingY();
// 	//! Slot which disables elements necessary for manual scaling on the y-axis.
// 	void EnableAutoscalingY();
	//! Sets the plot auto-scaling 
	void SetAutoscalingY(bool doAutoscaling);

private:
	//! Updates the axes and scaling properties.
	void UpdateAxesAndScaling();
	//! Updates the curve and canvas properties.
	void UpdateCurveAndCanvas();
	//! Updates the grid properties.
	void UpdateGrid();
	//! Updates the titles and label properties.
	void UpdateTitlesAndLables();

private:
	//! Pointer to the GParamPlotter to which this is linked.
	GParamPlotter* m_Plotter;
	//! Pointer to the GParamPlotterWidget it will modify.
	GParamPlotterWidget* m_PlotWidget;

//	friend class GParamPlotterWidget;

};

#endif // GPLOTPROPERTIESWIDGET_H
