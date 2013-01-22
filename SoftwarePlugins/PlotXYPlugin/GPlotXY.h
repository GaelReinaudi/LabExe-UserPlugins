#ifndef GPlotXY_H
#define GPlotXY_H

#include "device.h"
#include "param.h"
#include "QCustomPlot/qcustomplot.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GPlotXY class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GPlotXY : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GPlotXY(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GPlotXY();

public slots:
	//! Empty the history of the input parameter, refresh graph.
	void Clear();
	//! Opens a dialog box for the user to modify the graph properties.
	void Settings();
	//! Settings dialog box Ok button triggers this.
	void SettingsOk();
	//! Settings dialog box Cancel button triggers this.
	void SettingsApply();
	//! Settings dialog box Apply button triggers this.
	void SettingsCancel();
	//! Settings dialog box "Change color" buttons triggers these:
	void setBkgndColor();
	void setYColor();
	void setYGridColor();
	void setXGridColor();
	//! Cycles stored x&y-axis values through GParams so they can be exported to other plugins. 
	void Export();
//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GPlotXY.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! Input buckets: 
	GSingleParamBucket m_InputBucketY;//! Bucket for the Y-axis input parameter. 
	GSingleParamBucket m_InputBucketX;//! Bucket for the X-axis input parameter. 
	//! Output buckets (in Special tab of Settings window): 
	GParamBucket m_OutputBucket;//! Bucket for exporting saved x&y-axis values. 
	GParamDouble m_OutputY;//! Value exported for y-axis in bucket. 
	GParamDouble m_OutputX;//! Value exported for x-axis in bucket. 
	GParamDouble m_OutputNumUpdates;//! Value exported for data point count.  
	//! Updating behavior
	GParamBool m_UpdateOnY;//! yes = update on new Y value (default = yes.)
	GParamBool m_UpdateOnX;//! yes = update on new X value (default = no.)
	GParamBool m_DisableX;//! yes = behave like GPlot1D (default = no.)

	//! History of the input parameter: 
	int m_NumUpdates;//! Number of updates to the y-axis data (can serve as plot abcissa).
	QList<double> m_HistoryY;//! Saved y-axis data for the input parameter (the actual history).
	QList<double> m_HistoryX;//! Saved x-axis data for plotting the input parameter.
	QList<int> m_HistoryNumUpdates;//! Saved number of updates (provides ordering of X and Y values). 
	GParamInt m_MaxHistory;//! Maximum number of values to save.
	double m_TimeAtClear;//! Allows x-axis data to be elapsed time (ms) from last Clear();
	
	//! Plot variables: 
	QCustomPlot* m_Plot;//! The plot itself. 
	QCPCurve* m_Curve;//! Parametric plot (not graph).
	GParamString m_Title;//! Plot title.
	GParamString m_LabelX;//! Label for the x axis.
	GParamString m_LabelY;//! Label for the y axis.
	GParamBool m_XIsTime;//! yes = use time for x-axis value; no = use number of updates (default);
	GParamBool m_XWhichTime;//! yes = use elapsed time, no = actual time for x-axis (default).
	GParamBool m_AllowMouseRescale;//! yes = allow mouse to rescale axes. 
	GParamBool m_XAutoscale;//! yes = autoscale the x-axis. 
	GParamBool m_YAutoscale;//! yes = autoscale the y-axis. 
	GParamBool m_YIncludeZero;//! yes = autoscale the Y-axis, but make sure bounds include zero.
	GParamBool m_YSymmetricZero;//! yes = autoscale the Y-axis, but make sure bounds are symmetric about zero.
	GParamDouble m_YMin;//! y-axis minimum value without autoscale. 
	GParamDouble m_YMax;//! y-axis maximum value without autoscale. 
	GParamDouble m_XMin;//! X-axis minimum value without autoscale. 
	GParamDouble m_XMax;//! x-axis maximum value without autoscale. 
	GParamBool m_XType;//! false = linear scalse; true = logarithmic scale for x-axis. 
	GParamBool m_YType;//! false = linear scalse; true = logarithmic scale for y-axis. 
	GParamString m_BkgndColor;//! RGB string for the background color of the plot (for saving).  
	GParamString m_YColor;//! RGB string for the background color of the plot (for saving).  
	GParamString m_XGridColor;//! RGB string for x-axis grid lines.
	GParamString m_YGridColor;//! RGB string for y-axis grid lines.
	GParamBool m_NoLine;//! yes = use scatter points instead of a line.
	GParamBool m_XGridOn;//! yes = show x-axis default grid lines.
	GParamBool m_YGridOn;//! yes = show Y-axis default grid lines.
	GParamString m_XIsTimeFormat;//! Formatting instructions for when x-axis is time. 
	GParamBool m_FilterY;//! yes = filter the y-axis by keeping only the N-th update.
	GParamInt m_FilterYN;//! Keep "N"'th update of y-axis input if m_FilterY = true. 
	GParamInt m_ExportDelay;//! Time in ms to wait between updating values during export. 
	GParamBool m_ExternalN;//! Use internal or external value for N?
	GSingleParamBucket m_ExternalNBucket;//! Bucket for external N value. 
	GParamInt m_DotSize;//! Dot size for displaying curve as dots instead of line. 

	//! Settings dialog box variables:
	QDialog* m_Dialog;
	QLineEdit* titleLineEdit;
	QLineEdit* labelXLineEdit;
	QLineEdit* labelYLineEdit;
	QTextEdit* xIsTimeFormatLineEdit;
	QSpinBox* maxHistorySpinBox;
	QCheckBox* yUpdateCheckBox;
	QCheckBox* xUpdateCheckBox;
	QCheckBox* xDisableCheckBox;
	QCheckBox* xIsTimeCheckBox;
	QCheckBox* xWhichTimeCheckBox;
	QCheckBox* allowMouseRescaleCheckBox;
	QCheckBox* xAutoscaleCheckBox;
	QCheckBox* yAutoscaleCheckBox;
	QCheckBox* yIncludeZeroCheckBox;
	QCheckBox* ySymmetricZeroCheckBox;
	QDoubleSpinBox* yMinSpinBox;
	QDoubleSpinBox* yMaxSpinBox;
	QDoubleSpinBox* xMinSpinBox;
	QDoubleSpinBox* xMaxSpinBox;
	QComboBox* yTypeComboBox;
	QComboBox* xTypeComboBox;
	QCheckBox* yGridOnCheckBox;
	QCheckBox* xGridOnCheckBox;
	QCheckBox* noLineCheckBox;
	QSpinBox* dotSizeSpinBox;
	QCheckBox* filterYCheckBox;
	QSpinBox* filterYSpinBox;
	QSpinBox* exportDelaySpinBox;
	QCheckBox* externalNCheckBox;

private slots:
	//! Called when a new value for the input parameter Y arrives.
	void EventNewValueY(double newValue);
	//! Called when a new value for the input parameter Y arrives.
	void EventNewValueX(double newValue);
	//! Refresh the graph (all settings):
	void UpdateGraphAll();
	//! Refresh the data and axes on the graph only: 
	void UpdateGraphData();
	void InitSavedSettings();
};

#endif // GPlotXY_H
