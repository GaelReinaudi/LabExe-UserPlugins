#ifndef GPARAMPLOTTERWIDGET_H
#define GPARAMPLOTTERWIDGET_H

#include <QWidget>

#include <QVarLengthArray>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_grid.h>
#include "param.h"

namespace Ui {class GParamPlotterWidget;};

class GParamPlotter;

/////////////////////////////////////////////////////////////////////
//! \brief The GParamPlotterWidget class defines the gui of a GParamPlotter device. 
/*!	
Graphing functionality is implemented using Qwt. Properties of the graph are set using 
the GPlotPropertiesWidget class.
*/
class GParamPlotterWidget : public QWidget
{
	Q_OBJECT

public:
	GParamPlotterWidget(GParamPlotter* pThePlotter, QWidget *parent = 0);
	~GParamPlotterWidget();

protected slots:
	//! Slot which plots new data adding the newValue.
	void AddValue(const double & newValue);
	//! Slot which plots the new data in newValues. It erases old values.
	void SetNewValues(const GVectorDouble & newValues);
	//! Removes all data from the plot.
	void ClearPlot();

private:
	Ui::GParamPlotterWidget *ui;
	//! the plotter
	GParamPlotter* m_pPlotter;

private:
	//! Pointer to the Qwt graph.
	QwtPlot *m_Plot;
	//! Pointer to the Qwt curve. Used to display data on the graph.
	QwtPlotCurve *m_Curve;
	//! Pointer to the Qwt grid. Used to control gridlines on the graph.
	QwtPlotGrid *m_Grid;
	//! Pointer to the pen which describes the graphical properties of the curve.
	QPen *m_PenCurve;
	//! Pointer to the pen which describes the graphical properties of the major gridlines.
	QPen *m_PenMajor;
	//! Pointer to the pen which describes the graphical properties of the minor gridlines.
	QPen *m_PenMinor;
	//! Pointer to the context menu element which opens the properties window.
	QAction *m_Properties;
	//! Variable length array containing the x components of the data.
	GVectorDouble m_xData;
	//! Variable length array containing the x components of the data.
	GVectorDouble m_yData;
	//! count of incoming updates
	int m_TotalUpdates;

	friend class GPlotPropertiesWidget;

};

#endif // GPARAMPLOTTERWIDGET_H
