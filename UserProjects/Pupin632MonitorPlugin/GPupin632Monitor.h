#ifndef GPupin632Monitor_H
#define GPupin632Monitor_H

#include "device.h"
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GPupin632Monitor class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class GPupin632Monitor : public GProgDevice
{
	Q_OBJECT

public:
	GPupin632Monitor(QObject *parent, QString uniqueIdentifierName = "");

    void StartReadingPages(QObject * parent, QString TheLabUrl, QString TheGoogleUrl);
    double Get_SE_Temp();
    double Get_N_Temp();
    double Get_W_Temp();
    double Get_AIR_Temp();
    double Get_NYC_Temp();
    double Get_Humidity_Setpoint();
    double Get_Humidity_Discharge();
    double Get_Humidity_Space();
    void UpdateReadings();
    //void WriteValuesToFile(QString filename = "");

    ~GPupin632Monitor();
    public slots:
        void GetTheHtmlCode(bool ok);
        void UpdateMonitor();
        //void UpdateLoadProgress(int value);
        //void setProgressTo0();


protected:
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
    QWebView* TheWebView;
    QString Thehtml;
    QString m_OurLabUrl;

    QWebView* TheGoogleWebView;
    QString TheGooglehtml;
    QString m_OurGoogleUrl;

    GParamDouble m_tempSE;
    GParamDouble m_tempN;
    GParamDouble m_tempW;
    GParamDouble m_tempAIR;
    GParamDouble m_tempNYC;
    GParamDouble m_humSet;
    GParamDouble m_humDisch;
    GParamDouble m_humSpace;

    double m_lastTempNYC;

private slots:
};

#endif // GPupin632Monitor_H
