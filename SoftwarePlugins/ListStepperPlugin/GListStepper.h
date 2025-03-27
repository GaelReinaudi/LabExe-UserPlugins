#ifndef GListStepper_H
#define GListStepper_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GListStepper class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket.
When the input is updated, the device outputs the next value from a user-defined list.
The list of values is specified in a text box and can be comma, space, or newline separated.
The reset button restarts from the beginning of the list.
*/
//[inheritance]
class GListStepper : public GProgDevice
//[inheritance]
{
    Q_OBJECT

public:

//[constructor]
    //! Constructor
    GListStepper(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
    ~GListStepper();

public slots:
    //! Makes the stepper output the next value in the list
    void StartUpdateOutput();
    void UpdateOutput();
    //! Resets the stepper to the first value in the list
    void Reset();
    //! Updates the value list from text input
    void UpdateValueList();
    //! Generates equally spaced values and adds them to the list
    void GenerateLinspace();
    //! Randomizes the order of values in the list
    void RandomizeList();

//![PopulateDeviceWidget]
protected:
    //! Re-implemented to provide a new widget adequately connected to this GListStepper.
    void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [variablesInputBucket]
    //! the bucket for the input parameter
    GSingleParamBucket m_InputBucket;
    GSingleParamBucket m_OutputBucket;
//! [variablesInputBucket]
//! [variablesReset]
    //! a reset boolean that will provide a reset button
    GParamBool m_Reset;
    GParamBool m_Enable;
//! [variablesReset]
//! [variablesOutput]
    //! Values list text entry
    GParamString m_ValueListText;
    //! Time delay between trigger and output
    GParamDouble m_Delay;
    //! Current index in the list
    GParamInt m_CurrentIndex;
    //! Total number of values in the list
    GParamInt m_ValuesCount;
    //! Number of triggers needed to advance to the next value
    GParamInt m_TriggerInterval;
    //! Counter for the trigger events
    int m_TriggerCount;
//! [variablesOutput]
    //! List of values parsed from text input
    QList<double> m_ValueList;
    //! Start value for generated equally spaced sequence
    GParamDouble m_StartValue;
    //! End value for generated equally spaced sequence 
    GParamDouble m_EndValue;
    //! Number of points in the generated sequence
    GParamInt m_NumPoints;
    //! Input bucket to trigger sequence generation
    GSingleParamBucket m_GenerateLinspaceBucket;
    //! Input bucket to trigger list randomization
    GSingleParamBucket m_RandomizeListBucket;
//! [variables]

private slots:
    //! Called when the value list text is changed
    void ParseValueList(const QString& text);
};

#endif // GListStepper_H 