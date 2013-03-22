#include "GPlotXY.h"

//! [Initialize the parameters]
GPlotXY::GPlotXY(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_InputBucketY("Y-axis input", this)
	, m_InputBucketX("X-axis input", this)
	, m_ExternalNBucket("External N bucket", this)
	, m_UpdateOnY("Update on Y", this)
	, m_UpdateOnX("Update on X", this)
	, m_DisableX("Disable X", this)
	, m_OutputBucket("Output bucket", this)
	, m_OutputY("Y-axis output", this, GParam::ReadOnly)
	, m_OutputX("X-axis output", this, GParam::ReadOnly)
	, m_OutputNumUpdates("NumUpdates output", this, GParam::ReadOnly)
	, m_MaxHistory("MaxHistory", this)
	, m_Title("Title", this)
	, m_LabelX("LabelX", this)
	, m_LabelY("LabelY", this)
	, m_XIsTime("XIsTime", this)
	, m_AllowMouseRescale("AllowMouseRescale", this)
	, m_XAutoscale("XAutoscale", this)
	, m_YAutoscale("YAutoscale", this)
	, m_YIncludeZero("YIncludeZero", this)
	, m_YSymmetricZero("YSymmetricZero", this)
	, m_YMin("YMin", this)
	, m_YMax("YMax", this)
	, m_XMin("XMin", this)
	, m_XMax("XMax", this)
	, m_XType("XType", this)
	, m_YType("YType", this)
	, m_BkgndColor("BkgndColor", this)
	, m_YColor("YColor", this)
	, m_XGridColor("XGridColor", this)
	, m_YGridColor("YGridColor", this)
	, m_XGridOn("XGridOn", this)
	, m_YGridOn("YGridOn", this)
	, m_NoLine("No Line", this)
	, m_DotSize("Dot Size", this)
	, m_XIsTimeFormat("XIsTimeFormat", this)
	, m_XWhichTime("XWhichTime", this)
	, m_FilterY("Filter Y", this)
	, m_FilterYN("Filter Y N", this)
	, m_ExportDelay("Export Delay", this)
	, m_ExternalN("External N", this)
{
//! [Initialize the parameters]
/*
Note: All parameters defined with "this" device as parent (see above) will be saved automatically 
when the device state is saved to file. The name used to save the values is the same as the one provided 
for the name (the first argument, e.g. "num. samples").
*/
//! [Extra initialization the parameters]
	m_NumUpdates = 0;// No updates have occurred yet! 
	m_MaxHistory = 1000;// Default value (if no saved value read from file).
	m_MaxHistory.SetHardLimits(1, 1e6);// Set limiting values.
	m_OutputBucket.Freeze(true);// Do not want drag/drop of new variables in this bucket. 
	m_UpdateOnY = true;
	m_UpdateOnX = false;
	m_DisableX = false;
	m_Title = "";
	m_LabelX = "";
	m_LabelY = "";
	m_XIsTime = false;
	m_TimeAtClear = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;//Capture current time.
	m_AllowMouseRescale = false;
	m_XAutoscale = true;
	m_YAutoscale = true;
	m_YIncludeZero = false;
	m_YMin = -10.0;
	m_YMax = 10.0;
	m_XMin = 1.0;
	m_XMax = 100.0;
	m_XType = false;//linear axes types.
	m_YType = false;
	m_BkgndColor = "#FFFFFF";//White background.
	m_YColor = "#0000FF";//Blue curve.
	m_XGridColor = "#E0E0E0";//Grey grid lines. 
	m_YGridColor = "#E0E0E0";
	m_XGridOn = true;
	m_YGridOn = true;
	m_NoLine = false;
	m_DotSize = 1;
	m_XIsTimeFormat = "mm:ss";
	m_XWhichTime = false;
	m_FilterY = false;//By default, do not filter Y-axis values. 
	m_FilterYN = 10;//default value. 
	m_FilterYN.SetHardLimits(1, 1e6);//hard limits. 
	m_ExportDelay = 100;//default value (ms).
	m_ExportDelay.SetHardLimits(0, 1e4);//hard limits.
	m_ExternalN = false;//By default, use internal N for filtering input.  

	// Connections:  
	// -- Make updates to the input bucket trigger EventNewValueY(): 
	connect(&m_InputBucketY, SIGNAL(ValueUpdated(double)), this, SLOT(EventNewValueY(double)));
	connect(&m_InputBucketX, SIGNAL(ValueUpdated(double)), this, SLOT(EventNewValueX(double)));
	// -- After saved GParam values are loaded, make sure propagate changes from default values: 
	connect(this, SIGNAL(ParamJustInterpretSettings()), this, SLOT(InitSavedSettings()));
}
//! [Extra initialization the parameters]

GPlotXY::~GPlotXY()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GPlotXY. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GPlotXY::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// Add a vertical layout to arrange all the displayed widgets: 
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	
	// Add a horizontal layout for the Y-axis input, Settings button, and Clear button: 
	QHBoxLayout* pHlay = new QHBoxLayout();
	pVlay->addLayout(pHlay);
	// -- Insert widget (input param bucket) to set X-axis input: 
	GParamBucketTreeWidget* pXBWid = m_InputBucketX.ProvideParamBucketTreeWidget(theDeviceWidget);
	pXBWid->UseHighLightDecay(false);
	pHlay->addWidget(pXBWid);
	// -- Insert widget (input param bucket) to set Y-axis input: 
	GParamBucketTreeWidget* pYBWid = m_InputBucketY.ProvideParamBucketTreeWidget(theDeviceWidget);
	pYBWid->UseHighLightDecay(false);
	pHlay->addWidget(pYBWid);
	// -- Insert an expandable space
	pHlay->addStretch();

	// Insert Settings and Clear buttons: 
	QPushButton* settingsButton = new QPushButton(tr("Settings"));
	QPushButton* clearButton = new QPushButton(tr("Clear"));
	QDialogButtonBox* boxButtons = new QDialogButtonBox(Qt::Horizontal);
	boxButtons->addButton(settingsButton, QDialogButtonBox::ActionRole);
	boxButtons->addButton(clearButton, QDialogButtonBox::ActionRole);
	pHlay->addWidget(boxButtons);
	// -- Connect these buttons to trigger their respective functions: 
	connect(settingsButton, SIGNAL(clicked()), this, SLOT(Settings()));
	connect(clearButton, SIGNAL(clicked()), this, SLOT(Clear()));
	
	// Add a plot using the QCustomPlot library: 
	// -- Use stretch = 1 so the plot expands to use all the remaining vertical space.
	m_Plot = new QCustomPlot(theDeviceWidget);
	pVlay->addWidget(m_Plot, 1);
	//m_Plot->addGraph();
	m_Curve = new QCPCurve(m_Plot->xAxis,m_Plot->yAxis);
	m_Plot->addPlottable(m_Curve);

	// -- Initial graph customization: 
	m_Plot->setupFullAxesBox();//Adds right and top axes with ticks but no labels. 
	//		Make left and bottom axes always transfer their ranges to right and top axes:
	connect(m_Plot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_Plot->xAxis2, SLOT(setRange(QCPRange)));
	connect(m_Plot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_Plot->yAxis2, SLOT(setRange(QCPRange)));
	
	// -- Update the entire graph:  
	UpdateGraphAll();
	
	//-------------------------------------------------------------------
	// Setup the Settings dialog box: 
	m_Dialog = new QDialog(theDeviceWidget);
	// -- Setup Ok, Apply, and Cancel buttons: 
	QDialogButtonBox* DialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
	connect(DialogButtons, SIGNAL(accepted()), this, SLOT(SettingsOk()));
	connect(DialogButtons->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(SettingsApply()));
	connect(DialogButtons, SIGNAL(rejected()), this, SLOT(SettingsCancel()));
	// -- Setup General, Scaling, and Display tabs:  
	QTabWidget* tabWidget = new QTabWidget;
	QDialog* GeneralTab = new QDialog(tabWidget);
	QDialog* ScalingTab = new QDialog(tabWidget);
	QDialog* DisplayTab = new QDialog(tabWidget);
	QDialog* SpecialTab = new QDialog(tabWidget);
	//QDialog* AboutTab = new QDialog(tabWidget);
	tabWidget->addTab(GeneralTab, tr("General"));
	tabWidget->addTab(ScalingTab, tr("Scaling"));
	tabWidget->addTab(DisplayTab, tr("Display"));
	tabWidget->addTab(SpecialTab, tr("Special"));
	//tabWidget->addTab(AboutTab, tr("About"));
	// -- Setup layout for the dialog box:
	QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->setSizeConstraint(QLayout::SetNoConstraint);
    dialogLayout->addWidget(tabWidget);
    dialogLayout->addWidget(DialogButtons);
	m_Dialog->setLayout(dialogLayout);
    m_Dialog->setWindowTitle(tr("GPlot1D Settings"));
	
	// Populate the General Tab: 
	QLabel* titleLabel = new QLabel(tr("Plot title:"));
	titleLineEdit = new QLineEdit;
	titleLineEdit->setText(m_Title.StringValue());
	QLabel* labelXLabel = new QLabel(tr("X-axis label (units?):"));
	labelXLineEdit = new QLineEdit;
	labelXLineEdit->setText(m_LabelX.StringValue());
	QLabel* labelYLabel = new QLabel(tr("Y-axis label (units?):"));
	labelYLineEdit = new QLineEdit;
	labelYLineEdit->setText(m_LabelY.StringValue());
	QLabel* maxHistoryLabel = new QLabel(tr("Maximum length of saved data:"));
	maxHistorySpinBox = new QSpinBox;
	maxHistorySpinBox->setRange(1,1e6);//Otherwise max value is 99! 
	maxHistorySpinBox->setValue(m_MaxHistory.IntValue());
	QLabel* yUpdateLabel = new QLabel(tr("Update on new Y value?"));
	yUpdateCheckBox = new QCheckBox;
	yUpdateCheckBox->setChecked(m_UpdateOnY);
	QLabel* xUpdateLabel = new QLabel(tr("Update on new X value?"));
	xUpdateCheckBox = new QCheckBox;
	xUpdateCheckBox->setChecked(m_UpdateOnX);
	QLabel* xDisableLabel = new QLabel(tr("Disable X input?"));
	xDisableCheckBox = new QCheckBox;
	xDisableCheckBox->setChecked(m_DisableX);
	QLabel* xIsTimeLabel = new QLabel(tr("Use time for X data?"));
	xIsTimeCheckBox = new QCheckBox;
	xIsTimeCheckBox->setChecked(m_XIsTime);
	QLabel* xWhichTimeLabel = new QLabel(tr("Use time since Clear (vs actual)?"));
	xWhichTimeCheckBox = new QCheckBox;
	xWhichTimeCheckBox->setChecked(m_XWhichTime);
	QLabel* xIsTimeFormatLabel = new QLabel(tr("X-axis time display format:"));
	xIsTimeFormatLineEdit = new QTextEdit;
	xIsTimeFormatLineEdit->setMaximumHeight(60);
	xIsTimeFormatLineEdit->setText(m_XIsTimeFormat.StringValue());
	xIsTimeFormatLineEdit->setToolTip("Example QDateTime format:\nddd MMM. dd, yyyy\nHH:mm:ss.zzz");
	// -- arrange all these items
	QFormLayout* GeneralTabLayout = new QFormLayout;
	GeneralTabLayout->addRow(titleLabel, titleLineEdit);
	GeneralTabLayout->addRow(labelYLabel, labelYLineEdit);
	GeneralTabLayout->addRow(labelXLabel, labelXLineEdit);
	GeneralTabLayout->addRow(maxHistoryLabel, maxHistorySpinBox);
	GeneralTabLayout->addRow(yUpdateLabel, yUpdateCheckBox);
	GeneralTabLayout->addRow(xUpdateLabel, xUpdateCheckBox);
	GeneralTabLayout->addRow(xDisableLabel, xDisableCheckBox);
	GeneralTabLayout->addRow(xIsTimeLabel, xIsTimeCheckBox);
	GeneralTabLayout->addRow(xWhichTimeLabel, xWhichTimeCheckBox);
	GeneralTabLayout->addRow(xIsTimeFormatLabel, xIsTimeFormatLineEdit);
	// -- set the layout, finally...
	GeneralTab->setLayout(GeneralTabLayout);
	
	// Populate the Scaling tab: 
	// -- Add check box to allow axis rescaling with a mouse: 
	QLabel* allowMouseRescaleLabel = new QLabel(tr("Allow mouse to rescale?"));
	allowMouseRescaleCheckBox = new QCheckBox;
	allowMouseRescaleCheckBox->setChecked(m_AllowMouseRescale);
	// -- Start arrange all these items:
	QGridLayout* ScalingTabLayout = new QGridLayout;
	ScalingTabLayout->addWidget(allowMouseRescaleLabel,0,0);
	ScalingTabLayout->addWidget(allowMouseRescaleCheckBox,0,1);
	// -- Add y-axis options: 
	QGroupBox* yScaleBox = new QGroupBox(tr("Y-axis"));
	QGridLayout* yScaleGrid = new QGridLayout;
	QLabel* yTypeLabel = new QLabel(tr("Type:"));
	yTypeComboBox = new QComboBox;
	yTypeComboBox->insertItem(1,"Linear");
	yTypeComboBox->insertItem(2,"Logarithmic");
	yTypeComboBox->setCurrentIndex(m_YType.BoolValue());
	QLabel* yAutoscaleLabel = new QLabel(tr("Autoscale?"));
	yAutoscaleCheckBox = new QCheckBox;
	yAutoscaleCheckBox->setChecked(m_YAutoscale);  
	QLabel* yIncludeZeroLabel = new QLabel(tr("Include zero?"));
	yIncludeZeroCheckBox = new QCheckBox;
	yIncludeZeroCheckBox->setChecked(m_YIncludeZero);
	QLabel* ySymmetricZeroLabel = new QLabel(tr("Symmetric about zero?"));
	ySymmetricZeroCheckBox = new QCheckBox;
	ySymmetricZeroCheckBox->setChecked(m_YSymmetricZero);
	QLabel* yMaxLabel = new QLabel(tr("Manual maximum:"));
	yMaxSpinBox = new QDoubleSpinBox;
	yMaxSpinBox->setRange(-1e6,1e6);//Otherwise max value is 99! 
	yMaxSpinBox->setValue(m_YMax.DoubleValue());
	QLabel* yMinLabel = new QLabel(tr("Manual minimum:"));
	yMinSpinBox = new QDoubleSpinBox;
	yMinSpinBox->setRange(-1e6,1e6);//Otherwise max value is 99! 
	yMinSpinBox->setValue(m_YMin.DoubleValue());
	// -- arrange y-axis options: 
	yScaleGrid->addWidget(yTypeLabel,0,0);
	yScaleGrid->addWidget(yTypeComboBox,0,1);
	yScaleGrid->addWidget(yAutoscaleLabel,1,0);
	yScaleGrid->addWidget(yAutoscaleCheckBox,1,1);
	yScaleGrid->addWidget(yIncludeZeroLabel,2,0);
	yScaleGrid->addWidget(yIncludeZeroCheckBox,2,1);
	yScaleGrid->addWidget(ySymmetricZeroLabel,3,0);
	yScaleGrid->addWidget(ySymmetricZeroCheckBox,3,1);
	yScaleGrid->addWidget(yMaxLabel,4,0);
	yScaleGrid->addWidget(yMaxSpinBox,4,1);
	yScaleGrid->addWidget(yMinLabel,5,0);
	yScaleGrid->addWidget(yMinSpinBox,5,1);
	yScaleBox->setLayout(yScaleGrid);
	// -- Add x-axis options: 
	QGroupBox* xScaleBox = new QGroupBox(tr("X-axis"));
	QGridLayout* xScaleGrid = new QGridLayout;
	QLabel* xTypeLabel = new QLabel(tr("Type:"));
	xTypeComboBox = new QComboBox;
	xTypeComboBox->insertItem(1,"Linear");
	xTypeComboBox->insertItem(2,"Logarithmic");
	xTypeComboBox->setCurrentIndex(m_XType.BoolValue());
	QLabel* xAutoscaleLabel = new QLabel(tr("Autoscale?"));
	xAutoscaleCheckBox = new QCheckBox;
	xAutoscaleCheckBox->setChecked(m_XAutoscale);
	//NOTE: Skip y-axis options that don't make sense for the x-axis.  
	QLabel* xMaxLabel = new QLabel(tr("Manual maximum:"));
	xMaxSpinBox = new QDoubleSpinBox;
	xMaxSpinBox->setRange(-1e6,1e6);//Otherwise max value is 99! 
	xMaxSpinBox->setValue(m_XMax.DoubleValue());
	QLabel* xMinLabel = new QLabel(tr("Manual minimum:"));
	xMinSpinBox = new QDoubleSpinBox;
	xMinSpinBox->setRange(-1e6,1e6);//Otherwise max value is 99! 
	xMinSpinBox->setValue(m_XMin.DoubleValue());
	// -- arrange x-axis options: 
	xScaleGrid->addWidget(xTypeLabel,0,0);
	xScaleGrid->addWidget(xTypeComboBox,0,1);
	xScaleGrid->addWidget(xAutoscaleLabel,1,0);
	xScaleGrid->addWidget(xAutoscaleCheckBox,1,1);
	xScaleGrid->addWidget(xMaxLabel,2,0);
	xScaleGrid->addWidget(xMaxSpinBox,2,1);
	xScaleGrid->addWidget(xMinLabel,3,0);
	xScaleGrid->addWidget(xMinSpinBox,3,1);
	xScaleBox->setLayout(xScaleGrid);
	// -- finish assembling the Scaling tab
	ScalingTabLayout->addWidget(yScaleBox,1,0,6,2);
	ScalingTabLayout->addWidget(xScaleBox,7,0,4,2);
	ScalingTab->setLayout(ScalingTabLayout);
	
	// Populate the Display tab: 
	QGridLayout* DisplayTabLayout = new QGridLayout;
	QLabel* bkgndColorLabel = new QLabel(tr("Background:"));
	QPushButton* bkgndColorButton = new QPushButton(tr("Change color"));
	connect(bkgndColorButton, SIGNAL(clicked()), this, SLOT(setBkgndColor()));
	QLabel* yColorLabel = new QLabel(tr("Data curve:"));
	QPushButton* yColorButton = new QPushButton(tr("Change color"));
	connect(yColorButton, SIGNAL(clicked()), this, SLOT(setYColor()));
	QLabel* noLineLabel = new QLabel(tr("Use dots instead of a line?"));
	noLineCheckBox = new QCheckBox;
	noLineCheckBox->setChecked(m_NoLine); 
	QLabel* dotSizeLabel = new QLabel(tr("Dot size:"));
	dotSizeSpinBox = new QSpinBox;
	dotSizeSpinBox->setRange(1,1e2);
	dotSizeSpinBox->setValue(m_DotSize.IntValue());
	QLabel* yGridOnLabel = new QLabel(tr("Y-axis grid on?"));
	yGridOnCheckBox = new QCheckBox;
	yGridOnCheckBox->setChecked(m_YGridOn); 
	QLabel* yGridColorLabel = new QLabel(tr("Y-axis grid color:"));
	QPushButton* yGridColorButton = new QPushButton(tr("Change color"));
	connect(yGridColorButton, SIGNAL(clicked()), this, SLOT(setYGridColor()));
	QLabel* xGridOnLabel = new QLabel(tr("X-axis grid on?"));
	xGridOnCheckBox = new QCheckBox;
	xGridOnCheckBox->setChecked(m_XGridOn); 
	QLabel* xGridColorLabel = new QLabel(tr("X-axis grid color:"));
	QPushButton* xGridColorButton = new QPushButton(tr("Change color"));
	connect(xGridColorButton, SIGNAL(clicked()), this, SLOT(setXGridColor()));
	// -- arrange items
	DisplayTabLayout->addWidget(bkgndColorLabel,0,0);
	DisplayTabLayout->addWidget(bkgndColorButton,0,1);
	DisplayTabLayout->addWidget(yColorLabel,1,0);
	DisplayTabLayout->addWidget(yColorButton,1,1);
	DisplayTabLayout->addWidget(noLineLabel,2,0);
	DisplayTabLayout->addWidget(noLineCheckBox,2,1);
	DisplayTabLayout->addWidget(dotSizeLabel,3,0);
	DisplayTabLayout->addWidget(dotSizeSpinBox,3,1);
	DisplayTabLayout->addWidget(yGridOnLabel,4,0);
	DisplayTabLayout->addWidget(yGridOnCheckBox,4,1);
	DisplayTabLayout->addWidget(yGridColorLabel,5,0);
	DisplayTabLayout->addWidget(yGridColorButton,5,1);
	DisplayTabLayout->addWidget(xGridOnLabel,6,0);
	DisplayTabLayout->addWidget(xGridOnCheckBox,6,1);
	DisplayTabLayout->addWidget(xGridColorLabel,7,0);
	DisplayTabLayout->addWidget(xGridColorButton,7,1);
	DisplayTab->setLayout(DisplayTabLayout);
	// Could add line styles...
	
	// Populate the Special tab: 
	QGridLayout* SpecialTabLayout = new QGridLayout;
	//	-- Setup filter data area:
	QGroupBox* filterBox = new QGroupBox(tr("Filter data"));
	QGridLayout* filterGrid = new QGridLayout;
	QLabel* filterYLabel = new QLabel(tr("Record every Nth Y update since Clear?"));
	filterYCheckBox = new QCheckBox;
	filterYCheckBox->setChecked(m_FilterY); 
	QLabel* filterYNLabel = new QLabel(tr("N (internal):"));
	filterYSpinBox = new QSpinBox;
	filterYSpinBox->setRange(1,1e6);//Otherwise max value is 99! 
	filterYSpinBox->setValue(m_FilterYN.IntValue());
	QLabel* externalNLabel = new QLabel(tr("Use external N?"));
	externalNCheckBox = new QCheckBox;
	externalNCheckBox->setChecked(m_ExternalN); 
	QLabel* externalNBucketLabel = new QLabel(tr("N (external):"));
	GParamBucketTreeWidget* pExternalNBWid = m_ExternalNBucket.ProvideParamBucketTreeWidget(theDeviceWidget);
	pExternalNBWid->setTitle("");
	pExternalNBWid->UseHighLightDecay(false);
	//	-- layout widgets...
	filterGrid->addWidget(filterYLabel,0,0);
	filterGrid->addWidget(filterYCheckBox,0,1);
	filterGrid->addWidget(filterYNLabel,1,0);
	filterGrid->addWidget(filterYSpinBox,1,1);
	filterGrid->addWidget(externalNLabel,2,0);
	filterGrid->addWidget(externalNCheckBox,2,1);
	filterGrid->addWidget(externalNBucketLabel,3,0);
	filterGrid->addWidget(pExternalNBWid,3,1);
	filterBox->setLayout(filterGrid);
	//	-- Setup export data area: 
	QGroupBox* exportBox = new QGroupBox(tr("Export data"));
	QGridLayout* exportGrid = new QGridLayout;
	GParamBucketWidget* pOutWid = m_OutputBucket.ProvideParamBucketWidget(theDeviceWidget);
	pOutWid->setTitle("");
	m_OutputBucket.AddParam(&m_OutputX);//Link bucket to respective GParam's. 
	m_OutputBucket.AddParam(&m_OutputY);
	m_OutputBucket.AddParam(&m_OutputNumUpdates);
	pOutWid->UseHighLightDecay(false);
	//	-- setup Export button: 
	QLabel* exportLabel = new QLabel(tr("Cycle through plotted values below:"));
	QPushButton* exportButton = new QPushButton(tr("Export"));
	connect(exportButton, SIGNAL(clicked()), this, SLOT(Export()));
	QLabel* exportDelayLabel = new QLabel(tr("Delay between updating values (ms):"));
	exportDelaySpinBox = new QSpinBox;
	exportDelaySpinBox->setRange(0,1e4);//Otherwise max value is 99! 
	exportDelaySpinBox->setValue(m_ExportDelay.IntValue());
	//	-- layout widgets...
	exportGrid->addWidget(exportLabel,0,0);
	exportGrid->addWidget(exportButton,0,1);
	exportGrid->addWidget(exportDelayLabel,1,0);
	exportGrid->addWidget(exportDelaySpinBox,1,1);
	exportGrid->addWidget(pOutWid,2,0,2,2);
	exportBox->setLayout(exportGrid);
	//	-- Finish setting up the Special tab: 
	SpecialTabLayout->addWidget(filterBox,1,0,2,2);
	SpecialTabLayout->addWidget(exportBox,3,0,3,2);
	SpecialTab->setLayout(SpecialTabLayout);


	// Populate the About tab: 
	// Use this to describe what this Plugin does? 
	// -- Setup a text description of what this Profile does: 
	//QLabel* topLabel = new QLabel(tr("Testing 1 2 3"));
	//topLabel->setWordWrap(true);

	// End setup of Settings dialog box.  
	//-------------------------------------------------------------------
	
	//SettingsOk();//troubleshooting, not needed anymore. 
}
//[PopulateDeviceWidgetImplementation]

void GPlotXY::InitSavedSettings()
{	//This runs once after saved GParam values are loaded, to make sure 
	//that the saved values are used from the start.  
	SettingsCancel();//reloads values into Settings menu
	UpdateGraphAll();//resets the graph
}

void GPlotXY::Clear()
{
	// Clear saved values: 
	m_HistoryY.clear();
	m_HistoryX.clear();
	m_HistoryNumUpdates.clear();
	// Reset number of updates:
	m_NumUpdates = 0;
	//Capture current time.
	m_TimeAtClear = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

	//Update the graph: 
	//m_Plot->graph(0)->clearData();
	m_Curve->clearData();
	UpdateGraphData();//This replots the graph.  
}

void GPlotXY::EventNewValueX(double newValueX)
{	if(m_UpdateOnX&&!m_DisableX)
	{	//Increment the number of updates: 
		m_NumUpdates = m_NumUpdates + 1;
		
		// Prepend the new values to the list of data to plot:
		m_HistoryX.prepend(newValueX);
		m_HistoryY.prepend(m_InputBucketY.DoubleValue());
		m_HistoryNumUpdates.prepend(m_NumUpdates);
		
		// If the histories are too long, then drop their last entry until OK: 
		while((m_HistoryY.size() > m_MaxHistory) && (m_HistoryY.size() > 0))
		{	//Remove old data points from the graph, while deleting last X value from history:
			//m_Plot->graph(0)->removeData(m_HistoryX.takeLast());
			m_Curve->removeData(m_NumUpdates-m_MaxHistory);
			//Delete last values from the history:
			m_HistoryX.removeLast();
			m_HistoryY.removeLast();
			m_HistoryNumUpdates.removeLast();
			
			//This loop breaks if m_HistoryY is emptied! 
		}
		
		// Pass new data points to the graph:
		//m_Plot->graph(0)->addData(m_HistoryX.value(0),m_HistoryY.value(0));
		m_Curve->addData(m_NumUpdates,m_HistoryX.value(0),m_HistoryY.value(0));
		UpdateGraphData();//replot. 
	}
}

void GPlotXY::EventNewValueY(double newValueY)
{	if(m_UpdateOnY)
	{	//Increment the number of updates: 
		m_NumUpdates = m_NumUpdates + 1;
		m_HistoryNumUpdates.prepend(m_NumUpdates);
		
		int externalNvalue = qMax(1, int(m_ExternalNBucket.DoubleValue() + 0.5));
		if(!m_FilterY || (!m_ExternalN && m_NumUpdates % m_FilterYN == 0) || (m_ExternalN && m_NumUpdates % externalNvalue == 0))
		{	//If filtering, then update only on Nth update.  

			// Prepend the new value to the list of Y-axis data to plot:
			m_HistoryY.prepend(newValueY);
			
			if(m_DisableX)
			{	//Ignore the x input param bucket: 
				// Prepend a value to the list of X-axis data: 
				if(m_XIsTime)
				{	if(m_XWhichTime)
					{	//User would like to use the elapsed time (ms) since last Clear():
						m_HistoryX.prepend(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 - m_TimeAtClear);//Precision is 1 ms.
					}
					else
					{	//User would like to use the actual time (ms):
						m_HistoryX.prepend(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);//Precision is 1 ms.
					}
				}
				else
				{	//Default behavior is to use a "number of updates" for x-axis values:
					m_HistoryX.prepend(m_NumUpdates);
				}
			}
			else
			{	//Use the x input param bucket:
				m_HistoryX.prepend(m_InputBucketX.DoubleValue());
			}
			
			// If the histories are too long, then drop their last entry until OK: 
			while((m_HistoryY.size() > m_MaxHistory) && (m_HistoryY.size() > 0))
			{	//Remove old data points from the graph, while deleting last X value from history:
				//m_Plot->graph(0)->removeData(m_HistoryX.takeLast());
				m_Curve->removeData(m_NumUpdates-m_MaxHistory);
				//Delete last values from the history:
				m_HistoryX.removeLast();
				m_HistoryY.removeLast();
				m_HistoryNumUpdates.removeLast();
				
				//This loop breaks if m_HistoryY is emptied! 
			}

			// Pass new data points to the graph:
			//m_Plot->graph(0)->addData(m_HistoryX.value(0),m_HistoryY.value(0));
			m_Curve->addData(m_NumUpdates,m_HistoryX.value(0),m_HistoryY.value(0));
			UpdateGraphData();//replot. 
		}
	}
}

void GPlotXY::UpdateGraphAll()
{	
	// Make the plot pretty...
	m_Plot->setTitle(m_Title);
	m_Plot->xAxis->setLabel(m_LabelX);
	m_Plot->yAxis->setLabel(m_LabelY);
	m_Plot->setColor(QColor(m_BkgndColor));//Background color -- there has to be a better way!  This changes the color outside the plotted area.  
	//m_Plot->graph(0)->setPen(QPen(QColor(m_YColor)));//Curve color
	m_Curve->setPen(QPen(QColor(m_YColor)));//Curve color
	m_Plot->xAxis->setGrid(m_XGridOn);//Grids on/off
	m_Plot->yAxis->setGrid(m_YGridOn);
	m_Plot->xAxis->setGridPen(QPen(QColor(m_XGridColor), 1, Qt::DotLine));//Grid colors 
	m_Plot->yAxis->setGridPen(QPen(QColor(m_YGridColor), 1, Qt::DotLine));

	if(m_XIsTime)
	{	// Configure bottom axis to show date and time instead of number:
		m_Plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
		m_Plot->xAxis->setDateTimeFormat(m_XIsTimeFormat.StringValue());// formatting of displayed time values. 
	}
	else
	{	m_Plot->xAxis->setTickLabelType(QCPAxis::ltNumber);
	}

	if(m_AllowMouseRescale)
	{	// Make axis range moveable by mouse interaction (click and drag):
		m_Plot->setRangeDrag(Qt::Horizontal | Qt::Vertical);
		m_Plot->setRangeZoom(Qt::Horizontal | Qt::Vertical);
	}
	else
	{	m_Plot->setRangeDrag(0 | 0);
		m_Plot->setRangeZoom(0 | 0);
	}

	//Things that used to be in UpdateGraphData()
	// Set linear or logarithmic axis scales: 
	if(!m_XType)
	{	m_Plot->xAxis->setScaleType(QCPAxis::stLinear);
		m_Plot->xAxis2->setScaleType(QCPAxis::stLinear);
	}
	else
	{	m_Plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
		m_Plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
	}
	if(!m_YType)
	{	m_Plot->yAxis->setScaleType(QCPAxis::stLinear);
		m_Plot->yAxis2->setScaleType(QCPAxis::stLinear);
	}
	else
	{	m_Plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
		m_Plot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
	}
	
	//Choose between line or points for data curve:
	if(m_NoLine)
	{	m_Curve->setLineStyle(QCPCurve::lsNone);
		m_Curve->setScatterStyle(QCP::ssDisc);
		m_Curve->setScatterSize(m_DotSize);
	}
	else
	{	m_Curve->setLineStyle(QCPCurve::lsLine);
		m_Curve->setScatterStyle(QCP::ssNone);
	}

	// Update the data and the axes scaling: 
	UpdateGraphData();
	//NOTE: Did this last b/c it replots, so if did this first, many things wouldn't update. 
}

void GPlotXY::UpdateGraphData()
{	
	// Pass data points to the graph:
	//OLD,SLOW WAY:  m_Plot->graph(0)->setData(m_HistoryX.toVector(),m_HistoryY.toVector());
	//Now add data and delete points in EventNewValueY() and Clear().
	
	// Scale the axes:
	//-- First, autoscale by default: 
	//m_Plot->graph(0)->rescaleAxes();
	m_Curve->rescaleAxes();
	//-- Manually scale the axes as needed:
	if(!m_XAutoscale)
	{	m_Plot->xAxis->setRange(m_XMin,m_XMax);
	}
	if(!m_YAutoscale)
	{	m_Plot->yAxis->setRange(m_YMin,m_YMax);
	}
	//-- Extra features for the y-axis when autoscaled and linear:
	if(m_YAutoscale && !m_YType && (m_YIncludeZero || m_YSymmetricZero))
	{	QCPRange yRange = m_Plot->yAxis->range();// capture the lower and upper bounds
		if(m_YIncludeZero && !(yRange.contains(0.0)))
		{	//Set the smaller amplitude bound to zero
			if(abs(yRange.lower) < abs(yRange.upper))
			{	m_Plot->yAxis->setRange(0,yRange.upper);
			}
			else
			{	m_Plot->yAxis->setRange(yRange.lower,0);
			}
		}
		if(m_YSymmetricZero)
		{	//Mirror the larger amplitude bound
			if(abs(yRange.lower) < abs(yRange.upper))
			{	m_Plot->yAxis->setRange(-yRange.upper,yRange.upper);
			}
			else
			{	m_Plot->yAxis->setRange(yRange.lower,-yRange.lower);
			}
		}
		//NOTE: If both are true above, then defaults to "symmetric about zero".  
	}
	
	
	m_Plot->replot();//Make these changes! 
}

void GPlotXY::Settings()
{	//Restore all the values in the Settings dialog box to previous values: 
	titleLineEdit->setText(m_Title.StringValue());
	labelXLineEdit->setText(m_LabelX.StringValue());
	labelYLineEdit->setText(m_LabelY.StringValue());
	maxHistorySpinBox->setValue(m_MaxHistory.IntValue());
	yUpdateCheckBox->setChecked(m_UpdateOnY);
	xUpdateCheckBox->setChecked(m_UpdateOnX);
	xDisableCheckBox->setChecked(m_DisableX);
	xIsTimeCheckBox->setChecked(m_XIsTime);
	xWhichTimeCheckBox->setChecked(m_XWhichTime);
	allowMouseRescaleCheckBox->setChecked(m_AllowMouseRescale);
	yTypeComboBox->setCurrentIndex(m_YType.BoolValue());
	yAutoscaleCheckBox->setChecked(m_YAutoscale.BoolValue());  
	yIncludeZeroCheckBox->setChecked(m_YIncludeZero);
	ySymmetricZeroCheckBox->setChecked(m_YSymmetricZero);
	yMaxSpinBox->setValue(m_YMax.DoubleValue());
	yMinSpinBox->setValue(m_YMin.DoubleValue());
	xAutoscaleCheckBox->setChecked(m_XAutoscale.BoolValue());
	xMaxSpinBox->setValue(m_XMax.DoubleValue());
	xMinSpinBox->setValue(m_XMin.DoubleValue());
	noLineCheckBox->setChecked(m_NoLine);
	dotSizeSpinBox->setValue(m_DotSize.IntValue());
	xGridOnCheckBox->setChecked(m_XGridOn);
	yGridOnCheckBox->setChecked(m_YGridOn);
	xIsTimeFormatLineEdit->setText(m_XIsTimeFormat.StringValue());
	filterYCheckBox->setChecked(m_FilterY); 
	filterYSpinBox->setValue(m_FilterYN.IntValue());
	exportDelaySpinBox->setValue(m_ExportDelay.IntValue());
	externalNCheckBox->setChecked(m_ExternalN); 
	
	//Show the Settings dialog window. 
	m_Dialog->show();
}

void GPlotXY::SettingsOk()
{	//Apply changes:
	SettingsApply();

	//Close the Settings dialog window. 
	m_Dialog->hide();	
}

void GPlotXY::SettingsApply()
{	//Save changes:
	m_Title = titleLineEdit->text();
	m_LabelX = labelXLineEdit->text();
	m_LabelY = labelYLineEdit->text();
	m_MaxHistory = maxHistorySpinBox->value();
	m_UpdateOnY = yUpdateCheckBox->isChecked();
	m_UpdateOnX = xUpdateCheckBox->isChecked();
	m_DisableX = xDisableCheckBox->isChecked();
	m_XIsTime = xIsTimeCheckBox->isChecked();
	m_XWhichTime = xWhichTimeCheckBox->isChecked();
	m_AllowMouseRescale = allowMouseRescaleCheckBox->isChecked();
	m_XType = xTypeComboBox->currentIndex();
	m_YType = yTypeComboBox->currentIndex();
	m_XAutoscale = xAutoscaleCheckBox->isChecked();
	m_YAutoscale = yAutoscaleCheckBox->isChecked();
	m_YIncludeZero = yIncludeZeroCheckBox->isChecked();
	m_YSymmetricZero = ySymmetricZeroCheckBox->isChecked();
	m_YMax = yMaxSpinBox->value();
	m_YMin = yMinSpinBox->value();
	m_XMax = xMaxSpinBox->value();
	m_XMin = xMinSpinBox->value();
	m_NoLine = noLineCheckBox->isChecked();
	m_DotSize = dotSizeSpinBox->value();
	m_XGridOn = xGridOnCheckBox->isChecked();
	m_YGridOn = yGridOnCheckBox->isChecked();
	m_XIsTimeFormat = xIsTimeFormatLineEdit->toPlainText();
	m_FilterY = filterYCheckBox->isChecked();
	m_FilterYN = filterYSpinBox->value();
	m_ExportDelay = exportDelaySpinBox->value();
	m_ExternalN = externalNCheckBox->isChecked();

	//Update graph:  
	UpdateGraphAll();	
}

void GPlotXY::SettingsCancel()
{	//Restore all the values in the Settings dialog box to previous values: 
	titleLineEdit->setText(m_Title.StringValue());
	labelXLineEdit->setText(m_LabelX.StringValue());
	labelYLineEdit->setText(m_LabelY.StringValue());
	maxHistorySpinBox->setValue(m_MaxHistory.IntValue());
	yUpdateCheckBox->setChecked(m_UpdateOnY);
	xUpdateCheckBox->setChecked(m_UpdateOnX);
	xDisableCheckBox->setChecked(m_DisableX);
	xIsTimeCheckBox->setChecked(m_XIsTime);
	xWhichTimeCheckBox->setChecked(m_XWhichTime);
	allowMouseRescaleCheckBox->setChecked(m_AllowMouseRescale);
	yTypeComboBox->setCurrentIndex(m_YType.BoolValue());
	yAutoscaleCheckBox->setChecked(m_YAutoscale.BoolValue());  
	yIncludeZeroCheckBox->setChecked(m_YIncludeZero);
	ySymmetricZeroCheckBox->setChecked(m_YSymmetricZero);
	yMaxSpinBox->setValue(m_YMax.DoubleValue());
	yMinSpinBox->setValue(m_YMin.DoubleValue());
	xAutoscaleCheckBox->setChecked(m_XAutoscale.BoolValue());
	xMaxSpinBox->setValue(m_XMax.DoubleValue());
	xMinSpinBox->setValue(m_XMin.DoubleValue());
	noLineCheckBox->setChecked(m_NoLine);
	dotSizeSpinBox->setValue(m_DotSize.IntValue());
	xGridOnCheckBox->setChecked(m_XGridOn);
	yGridOnCheckBox->setChecked(m_YGridOn);
	xIsTimeFormatLineEdit->setText(m_XIsTimeFormat.StringValue());
	filterYCheckBox->setChecked(m_FilterY); 
	filterYSpinBox->setValue(m_FilterYN.IntValue());
	exportDelaySpinBox->setValue(m_ExportDelay.IntValue());
	externalNCheckBox->setChecked(m_ExternalN); 

	//Close the Settings dialog window. 
	m_Dialog->hide();
}

void GPlotXY::setBkgndColor()
{	QColorDialog* dummyDialog = new QColorDialog;
	QColor dummy = dummyDialog->getColor(QColor(m_BkgndColor));
	if(dummy.isValid())
	{	m_BkgndColor = dummy.name();//save new color in RGB string format "#RRGGBB".  
	}
	//Update graph instantly:  
	UpdateGraphAll();
}

void GPlotXY::setYColor()
{	QColorDialog* dummyDialog = new QColorDialog;
	QColor dummy = dummyDialog->getColor(QColor(m_YColor));
	if(dummy.isValid())
	{	m_YColor = dummy.name();//save new color in RGB string format "#RRGGBB".  
	}
	//Update graph instantly:  
	UpdateGraphAll();
}

void GPlotXY::setYGridColor()
{	QColorDialog* dummyDialog = new QColorDialog;
	QColor dummy = dummyDialog->getColor(QColor(m_YGridColor));
	if(dummy.isValid())
	{	m_YGridColor = dummy.name();//save new color in RGB string format "#RRGGBB".  
	}
	//Update graph instantly:  
	UpdateGraphAll();
}

void GPlotXY::setXGridColor()
{	QColorDialog* dummyDialog = new QColorDialog;
	QColor dummy = dummyDialog->getColor(QColor(m_XGridColor));
	if(dummy.isValid())
	{	m_XGridColor = dummy.name();//save new color in RGB string format "#RRGGBB".  
	}
	//Update graph instantly:  
	UpdateGraphAll();
}

void GPlotXY::Export()
{	//Push saved values in history to export GParamBucket values.
	//Ordering: starts with oldest, ends with newest values. 
	ulong msDelay = m_ExportDelay.IntValue();
	for (int i=m_HistoryX.size()-1; i>=0 ; i--)
	{	m_OutputX.SetParamValue(m_HistoryX.at(i));
		m_OutputY.SetParamValue(m_HistoryY.at(i));
		m_OutputNumUpdates.SetParamValue(m_HistoryNumUpdates.at(i));
		QThread::msleep(msDelay);//Delay, so values can be captured. 
	}
}