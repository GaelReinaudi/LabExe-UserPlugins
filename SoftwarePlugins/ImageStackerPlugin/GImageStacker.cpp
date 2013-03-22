#include "GImageStacker.h"

//! [Initialize the parameters]
GImageStacker::GImageStacker(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_SampleSize("num. samples", this)
	, m_InputBucket("input", this)
	, m_Output("out", this, GParam::ReadOnly)
	, m_Reset("Reset", this)
	, m_DisplayRailDown("Disp-min", this)
	, m_DisplayRailUp("Disp-max", this)
	, m_PicturesPutInHistorySinceLastStart(0)
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
	// this is an image provider
	m_IsImageProvider = true;
	m_DisplayRailUp = 1.0;
	m_DisplayRailDown.SetHardLimits(-99.9, 999.9);
	m_DisplayRailUp.SetHardLimits(-99.9, 999.9);

	m_SampleSize = 10;
	m_SampleSize.SetHardLimits(1, 999);
	// Connects the \e reset parameter to the function that does Reset() the average.
	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));

	QMetaObject::invokeMethod(this, "Reset", Qt::QueuedConnection);
}
//! [Extra initialization the parameters]

GImageStacker::~GImageStacker()
{
	Reset();
	//TryThread
	wait(2000);
	terminate();
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GImageStacker. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GImageStacker::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QLabel* downLabel = m_DisplayRailDown.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pDown = m_DisplayRailDown.ProvideNewParamSpinBox(theDeviceWidget); 
	QLabel* upLabel = m_DisplayRailUp.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pUp = m_DisplayRailUp.ProvideNewParamSpinBox(theDeviceWidget); 
	// A layout, in which we place the label and the spinbox 
	QFormLayout* downLayout = new QFormLayout();
	downLayout->addRow(downLabel, pDown);
	QFormLayout* upLayout = new QFormLayout();
	upLayout->addRow(upLabel, pUp);
	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addItem(downLayout);
	hLayout->addItem(upLayout);
//	theDeviceWidget->AddSubLayout(hLayout);

	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
// 	// We insert a widget provided by the input param bucket.
// 	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the numerical settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	pVlay->addLayout(hLayout);
	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pFLay->addRow(m_SampleSize.ProvideNewLabel(theDeviceWidget), m_SampleSize.ProvideNewParamSpinBox(theDeviceWidget));
// 	pFLay->addRow(m_Output.ProvideNewLabel(theDeviceWidget), m_Output.ProvideNewParamSpinBox(theDeviceWidget));
	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
	pVlay->addWidget(m_Reset.ProvideNewParamButton(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]

void GImageStacker::Reset()
{
	m_ImageMutex.lock();
	m_History.clear();
	m_PicturesPutInHistorySinceLastStart = 0;
	m_ImageMutex.unlock();

// 	// Send the input right to the output since it is the only value we have
// 	m_Output = m_InputBucket.DoubleValue();
}

void GImageStacker::ProcessImageAOIed(const GImageDouble & aoiImage)
{
	m_ImageMutex.lock();

	QDateTime timeThisPicture = aoiImage.DateTimeCreated();
// 	m_ImageIn.clear();
// 	m_ImageIn.insert(1.25874, aoiImage);
	m_LastReceivedPictureCreationDate = timeThisPicture;

	// prepends the new data to the beginning of the list
	m_History.prepend(aoiImage);
	m_PicturesPutInHistorySinceLastStart++;

	// quick way to implement the history by removing the unused parameters
	int maxSize = qMax(1, m_SampleSize.IntValue());
	while(m_History.count() > maxSize) {
		m_History.removeLast();
	}
	m_ImageMutex.unlock();

	start();
}

void GImageStacker::run()
{
	GImageDouble computedImage = StackUp(m_DisplayRailDown, m_DisplayRailUp);
	// emitting the signal
	emit OutputImageDouble(computedImage);
}

/////////////////////////////////////////////////////////////////////
/*!
It uses the incoming picture to sum it or multiply it with the stored m_StackedImage. 
\return: GImageDouble : The image representing the optical density
\param:  double RailDownForDisplay : the value of the optical density that corresponds to the value 0 for the QImage sent to the display.
\param:  double RailUp255ForDisplay : the value of the optical density that corresponds to the value 255 for the QImage sent to the display.
*////////////////////////////////////////////////////////////////////
GImageDouble GImageStacker::StackUp( double RailDownForDisplay, double RailUp255ForDisplay )
{
	if(m_History.isEmpty())
		return GImageDouble();

	// best way would be to throw exception if the average doesn't make sense
	int NValuesToConsider = qMax(1, m_SampleSize.IntValue());

	m_ImageMutex.lock();
	QSize imSize = m_History.first().size();
	QLinkedList<GImageDouble> copyHistory(m_History);
	int copyPictureSinceLast = m_PicturesPutInHistorySinceLastStart;
	m_PicturesPutInHistorySinceLastStart = 0;
	m_ImageMutex.unlock();

	int ValuesSummed = 0;
	// the image to return
	GImageDouble OpticalDensity(imSize.width(), imSize.height(), 0.0);

// 	m_ImageMutex.lock();
	// we average until we have enough samples
	QLinkedList<GImageDouble>::const_iterator im;
	for(im = copyHistory.constBegin(); im != copyHistory.constEnd(); ++im) {
		if(im->format() == QImage::Format_Invalid) {
			qWarning() << "The image seems to be invalid. 9115441";
			return GImageDouble();
		}
		if(im->size() != imSize) {
// 			qWarning() << "The image seems to be not the same size as the others. 9115442";
			Reset();
			return GImageDouble();
		}

		OpticalDensity += (*im);

		ValuesSummed++;
		if(ValuesSummed == NValuesToConsider)
			break;
	}
// 	m_ImageMutex.unlock();

	if(ValuesSummed == 0)
		return GImageDouble();

	OpticalDensity.FillQimageFromUsingDoubleArray(RailDownForDisplay, RailUp255ForDisplay);
	IncrementCountProcessed(copyPictureSinceLast);

	return OpticalDensity;
}