#include "GThorlabsTSP01.h"

#define TIMEOUT_MILLISEC   5000  // Communication timeout [ms]
#define NUM_MULTI_READING	10

//! [Initialize the parameters]
GThorlabsTSP01::GThorlabsTSP01(QString uniqueIdentifierName /* = "" */, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_InputBucket("Trigger", this)
	, m_OutputT1("TSP01 Internal Sensor (F)", this, GParam::ReadOnly)
	, m_OutputT2("TSP01 External Sensor TH1 (F)", this, GParam::ReadOnly)
	, m_OutputT3("TSP01 External Sensor TH2 (F)", this, GParam::ReadOnly)
	, m_OutputH("TSP01 Relative Humidity (%)", this, GParam::ReadOnly)
	, m_EnableTrigger("Enable Triggering?", this)
	, m_ManualTrigger("Manually Get New Values", this)
{
//! [Initialize the parameters]
/*
Note: All parameters defined with "this" device as parent (see above) will be saved automatically 
when the device state is saved to file. The name used to save the values is the same as the one provided 
for the name (the first argument, e.g. "num. samples").
*/
//! [Extra initialization the parameters]
	// Default value of the sample size for the first use.
	// It will be over-written if a previously saved value is read from a file.
	m_OutputT1 = -1;
	m_OutputT2 = -1;
	m_OutputT3 = -1;
	m_OutputH = -1;
	m_EnableTrigger = false;
	m_ManualTrigger = false;

	// Connects the input bucket to trigger reading the sensor values: 
	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(StartUpdateOutput()));
	connect(&m_ManualTrigger, SIGNAL(ValueUpdated(bool)), this, SLOT(ManualTriggered()));
}
//! [Extra initialization the parameters]

GThorlabsTSP01::~GThorlabsTSP01()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GThorlabsTSP01. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]


void GThorlabsTSP01::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputT1.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputT2.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputH.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the outputs.
  	QFormLayout* pFLay = new QFormLayout();
 	pVlay->addLayout(pFLay);
 	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
 	pFLay->addRow(m_OutputT1.ProvideNewLabel(theDeviceWidget), m_OutputT1.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_OutputT2.ProvideNewLabel(theDeviceWidget), m_OutputT2.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_OutputT3.ProvideNewLabel(theDeviceWidget), m_OutputT3.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_OutputH.ProvideNewLabel(theDeviceWidget), m_OutputH.ProvideNewParamSpinBox(theDeviceWidget));
// 	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
 	pVlay->addWidget(m_ManualTrigger.ProvideNewParamButton(theDeviceWidget));
	//QDialogButtonBox* boxButtons = new QDialogButtonBox(Qt::Vertical);
	//QPushButton* manualTriggerButton = new QPushButton(tr("Get New Values"));
	//connect(manualTriggerButton, SIGNAL(clicked()), this, SLOT(ManualTriggered()));
	//boxButtons->addButton(manualTriggerButton, QDialogButtonBox::ActionRole);
	//pVlay->addWidget(boxButtons);
 	pVlay->addWidget(m_EnableTrigger.ProvideNewParamCheckBox(theDeviceWidget));
 	// We add an expandable space.
 	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]


void GThorlabsTSP01::StartUpdateOutput()
{	
	//This function is called when the trigger input bucket is updated. 
	// Check if triggering enabled: 
	if(m_EnableTrigger)
	{	//Yes, let's update the outputs. 
		UpdateOutput();
	}
	
}

void GThorlabsTSP01::UpdateOutput()
{	//OK, let's get new measurements from the TSP01 device. 
	
	ViStatus    err;
	ViChar      *rscPtr;
	ViSession   instrHdl = VI_NULL;
	//attempt to find device
	if((err = find_instruments(ViString(TLTSP_FIND_PATTERN_01), &rscPtr)))
	{	error_exit(VI_NULL, err);
		return;
	}
	if(rscPtr == NULL) 
	{	// No instrument found
		//qDebug()<<"TSP01: No instrument found."; 
		return;
	}
	
	//Instrument found
	//qDebug()<<"TSP01: Found the instrument!"; 
	
	// Open session to TSP01 instrument
	//qDebug() << "TSP01: Opening session to " << rscPtr;
	if((err = TLTSP_init(rscPtr, VI_ON, VI_ON, &instrHdl))) 
	{	error_exit(instrHdl, err);
		return;
	}

	//For some reason Visual Studio doesn't like the next line, so commented it out! 
	//viSetAttribute(instrHdl, VI_ATTR_TMO_VALUE, TIMEOUT_MILLISEC);
	

	//Read humidity value
	err = VI_SUCCESS; 
	ViReal64 data_value;
	//qDebug()<<"TSP01: Attempting to get humidity value...";
	err = TLTSP_getHumidityData (instrHdl, TLTSP_ATTR_SET_VAL, &data_value); 
	if(!err) 
	{	//qDebug() << data_value;
		m_OutputH.SetParamValue(data_value);
	}
	else
	{	//qDebug() << "TSP01: Error getting humidity value";
		m_OutputH.SetParamValue(-1);//Make the error visible to the user. 
	}

	//Read temperature values
	err = VI_SUCCESS; 
	//qDebug()<<"TSP01: Attempting to get temperature values...";
	err = TLTSP_getTemperatureData (instrHdl, TLTSP_MEAS_TEMP1, TLTSP_ATTR_SET_VAL, &data_value);    
	if(!err) 
	{	//qDebug() << data_value;
		m_OutputT1.SetParamValue(data_value*1.8+32.0);//manually convert Celsius to Fahrenheit. 
	}
	else
	{	//qDebug() << "TSP01: Error getting temp value 1";
		m_OutputT1.SetParamValue(-1);//Make the error visible to the user. 
	}
	err = VI_SUCCESS; 
	err = TLTSP_getTemperatureData (instrHdl, TLTSP_MEAS_TEMP2, TLTSP_ATTR_SET_VAL, &data_value);    
	if(!err) 
	{	//qDebug() << data_value;
		m_OutputT2.SetParamValue(data_value*1.8+32.0);//manually convert Celsius to Fahrenheit. 
	}
	else
	{	//qDebug() << "TSP01: Error getting temp value 2";
		m_OutputT2.SetParamValue(-1);//Make the error visible to the user. 
		//This happens if TH1 unplugged.
	}
	err = VI_SUCCESS; 
	err = TLTSP_getTemperatureData (instrHdl, TLTSP_MEAS_TEMP3, TLTSP_ATTR_SET_VAL, &data_value);    
	if(!err) 
	{	//qDebug() << data_value;
		m_OutputT3.SetParamValue(data_value*1.8+32.0);//manually convert Celsius to Fahrenheit. 
	}
	else
	{	//qDebug() << "TSP01: Error getting temp value 3";
		m_OutputT3.SetParamValue(-1);//Make the error visible to the user. 
		//This happens if TH1 unplugged.
	}

	
	
	//Close session:
	//qDebug() << "TSP01: closing session.";
	// Close instrument hande if open
	if(instrHdl != VI_NULL) TLTSP_close(instrHdl);
	
}

void GThorlabsTSP01::ManualTriggered()
{	
	UpdateOutput();
}

/*---------------------------------------------------------------------------
  Exit with error message
---------------------------------------------------------------------------*/
void GThorlabsTSP01::error_exit(ViSession instrHdl, ViStatus err)
{
   ViChar buf[TLTSP_ERR_DESCR_BUFFER_SIZE];
   
   // Print error
   TLTSP_errorMessage (instrHdl, err, buf);
   //qDebug() << "TSP01 ERROR: " << buf;
   //fprintf(stderr, "ERROR: %s\n", buf);
   
   // Close instrument hande if open
   if(instrHdl != VI_NULL) TLTSP_close(instrHdl);
}


/*---------------------------------------------------------------------------
  Find Instruments
---------------------------------------------------------------------------*/
#define COMM_TIMEOUT    3000
ViStatus GThorlabsTSP01::find_instruments(ViString findPattern, ViChar **resource)
{
   ViStatus       err;
   ViUInt32       findCnt;//, cnt;
   ViChar         *rscBuf, *rscPtr;
   static ViChar  rscStr[VI_FIND_BUFLEN];
   //ViUInt32       i, done;
                      
   //printf("Scanning for instruments ...\n");
   //qDebug()<<"TSP01 scanning for instruments";

   switch((err = TLTSP_getDeviceCount (VI_NULL, &findCnt)))
   {
      case VI_SUCCESS:
         break;

      case VI_ERROR_RSRC_NFOUND:
         //printf("No matching instruments found\n\n"); 
		 //qDebug()<<"TLSP01: No matching instruments found";
         return (err);
                 
      default:
         return (err);
   }

	if((err = TLTSP_getDeviceResourceString (VI_NULL, 0, rscStr))) 
		return(err); 
   
   if(findCnt < 2)
   {
      // Found only one matching instrument - return this
      *resource = rscStr;
      return (VI_SUCCESS);
   }

   // Found multiple instruments - get resource strings of all instruments into buffer
   if((rscBuf = (ViChar*)malloc(findCnt * VI_FIND_BUFLEN)) == NULL) return (VI_ERROR_SYSTEM_ERROR);
   rscPtr = rscBuf;
   strncpy_s(rscBuf, VI_FIND_BUFLEN, rscStr, VI_FIND_BUFLEN); // Copy first found instrument resource string
   rscPtr += VI_FIND_BUFLEN;

   //Found multiple instruments, let's just go with first one: 
   //qDebug() << "TLSP01: Found " << findCnt << " matching instruments! Let's use first one...";
   // Copy resource string to static buffer
   strncpy_s(rscStr, VI_FIND_BUFLEN, rscBuf + (0 * VI_FIND_BUFLEN), VI_FIND_BUFLEN);  
   *resource = rscStr;
   // Cleanup
   free(rscBuf);
   return (VI_SUCCESS);

// 
//    for(cnt = 1; cnt < findCnt; cnt++)
//    {
//       if((err = TLTSP_getDeviceResourceString (VI_NULL, cnt, rscPtr))) 
//       {
//          free(rscBuf);
//          return(err); 
//       }
//       rscPtr += VI_FIND_BUFLEN;
//    }
// 
//    // Display selection
//    done = 0;
//    do
//    {
// 	  qDebug() << "Found " << findCnt << " matching instruments: ";
// 	  //printf("Found %d matching instruments:\n\n", findCnt);
//       rscPtr = rscBuf;
//    
//       for(cnt = 0; cnt < findCnt; cnt++)
//       {
// 		 //printf("% d: %s\n", cnt, rscPtr);
//       	 qDebug() << cnt << " " << rscPtr;
// 		 rscPtr += VI_FIND_BUFLEN;
//       }
//    
//       //printf("\nPlease select: ");
// 		qDebug()<<"Please select:";
//       while((i = getchar()) == EOF);
//       i -= '0';      
//       fflush(stdin);
//       //printf("\n");
//       if((i < 0) || (i >= cnt))
//       {
//          //printf("Invalid selection\n\n");
// 		  qDebug() << "Invalid selection";
//       }     
//       else
//       {
//          done = 1;
//       }
//    }
//    while(!done);
//    
//    // Copy resource string to static buffer
//    strncpy_s(rscStr, VI_FIND_BUFLEN, rscBuf + (i * VI_FIND_BUFLEN), VI_FIND_BUFLEN);  
//    *resource = rscStr;
//    
//    // Cleanup
//    free(rscBuf);
//    return (VI_SUCCESS);
}
