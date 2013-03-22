#ifndef GPARAMPLOTTER_H
#define GPARAMPLOTTER_H

#include "device.h"
#include "param.h"

class GPlotPropertiesWidget;

/////////////////////////////////////////////////////////////////////
//! \brief The GParamPlotter class defines a device with an interface to plot the values of a GParamNum. 
//! Graphing functionality is implemented using Qwt in the GParamPlotterWidget. Properties of the graph are set using the GPlotPropertiesWidget class.
/*!	
*/
class GParamPlotter : public GProgDevice
{
	Q_OBJECT

public:
	GParamPlotter(QObject *parent, QString uniqueIdentifierName);
	~GParamPlotter();


protected:
	//! Re-implemented. 
	void PopulateSettings(QSettings& inQsettings);
	//! Re-implemented. 
	void InterpretSettings(QSettings& fromQsettings);
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget );

private:
	//! the param bucket for the param to plot
	GSingleParamBucket m_BucketParam;
	friend class GParamPlotterWidget;
	//! Pointer to the properties window.
	GPlotPropertiesWidget *m_PropertiesWindow;
};

#endif // GPARAMPLOTTER_H
