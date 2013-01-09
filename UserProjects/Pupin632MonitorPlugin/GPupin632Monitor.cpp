#include "GPupin632Monitor.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

GPupin632Monitor::GPupin632Monitor(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
    , m_tempSE("Temp SE (F)", this, GParam::ReadOnly)
    , m_tempN("Temp N (F)", this, GParam::ReadOnly)
    , m_tempW("Temp W (F)", this, GParam::ReadOnly)
    , m_tempAIR("Temp AIR (F)", this, GParam::ReadOnly)
    , m_tempNYC("Temp NYC (F)", this, GParam::ReadOnly)
    , m_humSet("Hum setpoint (%)", this, GParam::ReadOnly)
    , m_humDisch("Hum discharge (%)", this, GParam::ReadOnly)
    , m_humSpace("Hum space (%)", this, GParam::ReadOnly)
    , m_lastTempNYC(0)
	, m_OurLabUrl("http://128.59.169.94/pe/webAhu6001")
	, m_OurGoogleUrl("http://www.google.com/ig/api?weather=New+York+City")

{
    TheWebView = new QWebView();
    TheGoogleWebView = new QWebView();
    connect(TheWebView, SIGNAL(loadFinished(bool)), this, SLOT(GetTheHtmlCode(bool)));

	// if it is shelved, we only get the temperature once 
	if(IsShelvedInstance()) {
		QTimer::singleShot(1000, this, SLOT(UpdateMonitor()));
	}
	else { // else we can monitor every 60 seconds
		QTimer *timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(UpdateMonitor()));
		timer->start(60 * 1000);
	}
}

GPupin632Monitor::~GPupin632Monitor()
{

}

void GPupin632Monitor::StartReadingPages(QObject *parent, QString TheLabUrl, QString TheGoogleUrl)
{
    Thehtml = "";
    TheWebView->load(QUrl(TheLabUrl));
//	TheGooglehtml = "";
//	TheGoogleWebView->load(QUrl(TheGoogleUrl));
//	qDebug() << TheWebView->title();
}

void GPupin632Monitor::UpdateMonitor()
{
    StartReadingPages(0, m_OurLabUrl, m_OurGoogleUrl);
}

void GPupin632Monitor::GetTheHtmlCode( bool ok)
{
    if(!ok)
        return;
    Thehtml = TheWebView->page()->mainFrame()->toHtml();
    TheGooglehtml = TheGoogleWebView->page()->mainFrame()->toHtml();
    UpdateReadings();
}

double GPupin632Monitor::Get_SE_Temp()
{
    int indexSE = Thehtml.indexOf("W. Space Temp");
    int indexSEnum = Thehtml.indexOf("</td><td>", indexSE) + 9;
    QString stnum = Thehtml.mid(indexSEnum, 6);
    return stnum.toDouble();
}

double GPupin632Monitor::Get_N_Temp()
{
    int indexN = Thehtml.indexOf("N. Space Temp");
    int indexNnum = Thehtml.indexOf("</td><td>", indexN) + 9;
    QString stnum = Thehtml.mid(indexNnum, 6);
    return stnum.toDouble();
}

double GPupin632Monitor::Get_W_Temp()
{
    int indexW = Thehtml.indexOf("S.E. Space Temp");
    int indexWnum = Thehtml.indexOf("</td><td>", indexW) + 9;
    QString stnum = Thehtml.mid(indexWnum, 6);
    return stnum.toDouble();
}
double GPupin632Monitor::Get_AIR_Temp()
{
    int indexAIR = Thehtml.indexOf("Discharge Air Temp");
    int indexAIRnum = Thehtml.indexOf("</td><td>", indexAIR) + 9;
    QString stnum = Thehtml.mid(indexAIRnum, 6);
    return stnum.toDouble();
}

double GPupin632Monitor::Get_NYC_Temp()
{
    int indexLineOfTemp = TheGooglehtml.indexOf("temp_f data");
    int leftQuote = TheGooglehtml.indexOf("\"", indexLineOfTemp);
    int rightQuote = TheGooglehtml.indexOf("\"", leftQuote + 1);
    QString theTemperatureString = TheGooglehtml.mid(leftQuote + 1, (rightQuote - 1) - leftQuote);
    if(theTemperatureString != "") { m_lastTempNYC = theTemperatureString.toDouble(); }
    return m_lastTempNYC;
}

double GPupin632Monitor::Get_Humidity_Setpoint()
{
    int indexHUM = Thehtml.indexOf("Space Humidity Setpoint");
    int indexHUMnum = Thehtml.indexOf("</td><td>", indexHUM) + 9;
    QString stnum = Thehtml.mid(indexHUMnum, 3);
    //qDebug() << stnum.toDouble();
    return stnum.toDouble();
}

double GPupin632Monitor::Get_Humidity_Discharge()
{
    int indexHUMD = Thehtml.indexOf("Discharge Air Humidity");
    int indexHUMDnum = Thehtml.indexOf("</td><td>", indexHUMD) + 9;
    QString stnum = Thehtml.mid(indexHUMDnum, 3);
    //qDebug() << stnum.toDouble();
    return stnum.toDouble();
}

double GPupin632Monitor::Get_Humidity_Space()
{
    int indexHUMSp = Thehtml.indexOf("Space Humidity");
    int indexHUMSpnum = Thehtml.indexOf("</td><td>", indexHUMSp) + 9;
    QString stnum = Thehtml.mid(indexHUMSpnum, 3);
    return stnum.toDouble();
}

void GPupin632Monitor::UpdateReadings()
{
    m_tempW = Get_W_Temp();
    m_tempSE = Get_SE_Temp();
    m_tempN = Get_N_Temp();
    m_tempAIR = Get_AIR_Temp();
    m_tempNYC = Get_NYC_Temp();
    m_humSet = Get_Humidity_Setpoint();
    m_humDisch = Get_Humidity_Discharge();
    m_humSpace = Get_Humidity_Space();
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GPupin632Monitor. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GPupin632Monitor::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
    //connect(TheWebView, SIGNAL(loadProgress(int)), this, SLOT(UpdateLoadProgress(int)));
    QVBoxLayout* pVLay = new QVBoxLayout();
    theDeviceWidget->AddSubLayout(pVLay);
    QFormLayout* pFLay = new QFormLayout();
    pVLay->addLayout(pFLay);

    pFLay->addRow(m_tempSE.ProvideNewLabel(theDeviceWidget), m_tempSE.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_tempN.ProvideNewLabel(theDeviceWidget), m_tempN.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_tempW.ProvideNewLabel(theDeviceWidget), m_tempW.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_tempAIR.ProvideNewLabel(theDeviceWidget), m_tempAIR.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_humSet.ProvideNewLabel(theDeviceWidget), m_humSet.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_humDisch.ProvideNewLabel(theDeviceWidget), m_humDisch.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_humSpace.ProvideNewLabel(theDeviceWidget), m_humSpace.ProvideNewParamSpinBox(theDeviceWidget));
//	pFLay->addRow(m_tempNYC.ProvideNewLabel(theDeviceWidget), m_tempNYC.ProvideNewParamSpinBox(theDeviceWidget));
}
