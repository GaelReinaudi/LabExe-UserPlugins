#include "GListStepper.h"
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QTimer>
#include <algorithm>

//! [Initialize the parameters]
GListStepper::GListStepper(QObject *parent, QString uniqueIdentifierName /* = "" */)
    : GProgDevice(parent, uniqueIdentifierName)
    , m_InputBucket("Trigger", this)
    , m_OutputBucket("Output", this)
    , m_Reset("Reset", this)
    , m_Enable("Enable", this)
    , m_ValueListText("List", this)
    , m_Delay("Delay (s)", this)
    , m_CurrentIndex("Index", this, GParam::ReadOnly)
    , m_ValuesCount("Num Values", this, GParam::ReadOnly)
    , m_TriggerInterval("Trig / N", this)
    , m_TriggerCount(0)
    , m_StartValue("Start", this)
    , m_EndValue("End", this)
    , m_NumPoints("Num Points", this)
    , m_GenerateLinspaceBucket("Generate", this)
    , m_RandomizeListBucket("Shuffle", this)
{
//! [Initialize the parameters]
/*
Note: All parameters defined with "this" device as parent (see above) will be saved automatically 
when the device state is saved to file. The name used to save the values is the same as the one provided 
for the name (the first argument, e.g. "num. samples").
*/
//! [Extra initialization the parameters]
    m_Enable = true;
    // Set up delay parameter
    m_Delay.SetTypicalStep(0.01);
    m_Delay.SetHardLimits(0.00, 99.9);
    m_Delay.SetDisplayDecimals(3);
    
    // Set up trigger interval parameter
    m_TriggerInterval.SetHardLimits(1, 1000);
    m_TriggerInterval = 1;
    
    // Set up linspace parameters
    m_StartValue.SetDisplayDecimals(3);
    m_StartValue = 0.0;
    
    m_EndValue.SetDisplayDecimals(3);
    m_EndValue = 10.0;
    
    m_NumPoints.SetHardLimits(2, 1000);
    m_NumPoints = 11;
    
    // Set default value list text with example
    m_ValueListText = "1,2 3 4 , bad5\n 5,6 7 bad7 8 9\n10";
    
    // Initialize read-only parameters
    m_CurrentIndex = 0;
    m_ValuesCount = 0;
    
    // Parse the default value list
    ParseValueList(m_ValueListText.StringValue());
    
    // Connect signals
    connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(StartUpdateOutput()));
    connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));
    connect(&m_ValueListText, SIGNAL(ValueUpdated(const QString&)), this, SLOT(ParseValueList(const QString&)));
    connect(&m_GenerateLinspaceBucket, SIGNAL(ValueUpdated(double)), this, SLOT(GenerateLinspace()));
    connect(&m_RandomizeListBucket, SIGNAL(ValueUpdated(double)), this, SLOT(RandomizeList()));
    
    // Initialize with first value if list is not empty
    if (!m_ValueList.isEmpty()) {
        m_OutputBucket.SetParamValue(m_ValueList.first());
    }
}
//! [Extra initialization the parameters]

GListStepper::~GListStepper()
{
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GListStepper. 
Layouts are used to make the widget react correctly to re-sizing.
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GListStepper::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget)
{
    // We add a vertical layout to hold together all the widgets that we are going to display.
    QVBoxLayout* pVlay = new QVBoxLayout();
    theDeviceWidget->AddSubLayout(pVlay);
    
    // We insert widgets provided by the input and output param buckets.
    pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
    pVlay->addWidget(m_OutputBucket.ProvideNewParamWidget(theDeviceWidget));
    
    // We add a form layout that will hold the numerical settings.
    QFormLayout* pFLay = new QFormLayout();
    pVlay->addLayout(pFLay);
    
    // Add parameters to form layout
    pFLay->addRow(m_Delay.ProvideNewLabel(theDeviceWidget), m_Delay.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_TriggerInterval.ProvideNewLabel(theDeviceWidget), m_TriggerInterval.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_CurrentIndex.ProvideNewLabel(theDeviceWidget), m_CurrentIndex.ProvideNewParamSpinBox(theDeviceWidget));
    pFLay->addRow(m_ValuesCount.ProvideNewLabel(theDeviceWidget), m_ValuesCount.ProvideNewParamSpinBox(theDeviceWidget));
    
    // Add the reset button and enable checkbox
    pVlay->addWidget(m_Reset.ProvideNewParamButton(theDeviceWidget));
    pVlay->addWidget(m_Enable.ProvideNewParamCheckBox(theDeviceWidget));
    
    // Add linspace generator controls
    QGroupBox* generatorBox = new QGroupBox("Sequence Generator", theDeviceWidget);
    pVlay->addWidget(generatorBox);
    
    QVBoxLayout* genLayout = new QVBoxLayout();
    generatorBox->setLayout(genLayout);
    
    QFormLayout* genFormLayout = new QFormLayout();
    genLayout->addLayout(genFormLayout);
    
    // Add linspace parameters
    genFormLayout->addRow(m_StartValue.ProvideNewLabel(theDeviceWidget), m_StartValue.ProvideNewParamSpinBox(theDeviceWidget));
    genFormLayout->addRow(m_EndValue.ProvideNewLabel(theDeviceWidget), m_EndValue.ProvideNewParamSpinBox(theDeviceWidget));
    genFormLayout->addRow(m_NumPoints.ProvideNewLabel(theDeviceWidget), m_NumPoints.ProvideNewParamSpinBox(theDeviceWidget));
    
    // Add input buckets for generating and randomizing (instead of buttons)
    QHBoxLayout* bucketLayout = new QHBoxLayout();
    genLayout->addLayout(bucketLayout);
    
    bucketLayout->addWidget(m_GenerateLinspaceBucket.ProvideNewParamWidget(theDeviceWidget));
    bucketLayout->addWidget(m_RandomizeListBucket.ProvideNewParamWidget(theDeviceWidget));
    
    // Add label for value list at the bottom
    QHBoxLayout* valueListLabelLayout = new QHBoxLayout();
    pVlay->addLayout(valueListLabelLayout);
    valueListLabelLayout->addWidget(m_ValueListText.ProvideNewLabel(theDeviceWidget));
    
    // Add the text editor for value list at the bottom with stretching
    QWidget* valueListWidget = m_ValueListText.ProvideNewParamTextEdit(theDeviceWidget);
    valueListWidget->setMinimumHeight(100); // Set minimum height for better visibility
    valueListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Make it expand in both directions
    pVlay->addWidget(valueListWidget, 1); // Add with stretch factor of 1
}
//[PopulateDeviceWidgetImplementation]

void GListStepper::ParseValueList(const QString& text)
{
    m_ValueList.clear();
    
    // Split the text by commas, spaces, and newlines
    QStringList parts = text.split(QRegularExpression("[,\\s\\n]+"), Qt::SkipEmptyParts);
    
    // Convert each part to a double and add to the value list
    bool conversionOk;
    foreach (const QString& part, parts) {
        double value = part.trimmed().toDouble(&conversionOk);
        if (conversionOk) {
            m_ValueList.append(value);
        }
    }
    
    // Update the count
    m_ValuesCount = m_ValueList.size();
    
    // Reset the index
    Reset();
}

void GListStepper::StartUpdateOutput()
{
    if (m_Delay > 0.0) {
        QTimer::singleShot(int(m_Delay * 1000), this, SLOT(UpdateOutput()));
    } else {
        UpdateOutput();
    }
}

void GListStepper::UpdateOutput()
{
    if (!m_Enable || m_ValueList.isEmpty()) {
        return; // Do nothing if disabled or list is empty
    }
    
    // Increment the trigger counter
    m_TriggerCount++;
    
    // Only advance to the next value when the trigger counter reaches the interval
    if (m_TriggerCount >= m_TriggerInterval.IntValue()) {
        // Reset the trigger counter
        m_TriggerCount = 0;
        
        // Get the current index (constrained within the list bounds)
        int index = m_CurrentIndex.IntValue();
        
        // Output the current value
        if (index < m_ValueList.size()) {
            m_OutputBucket.SetParamValue(m_ValueList.at(index));
        }
        
        // Move to next index, wrap around if at the end
        index = (index + 1) % m_ValueList.size();
        m_CurrentIndex = index;
    }
}

void GListStepper::Reset()
{
    // Reset index to beginning of list
    m_CurrentIndex = 0;
    
    // Reset trigger counter
    m_TriggerCount = 0;
    
    // Set output to first value if list is not empty
    if (!m_ValueList.isEmpty()) {
        m_OutputBucket.SetParamValue(m_ValueList.first());
    }
}

void GListStepper::UpdateValueList()
{
    ParseValueList(m_ValueListText.StringValue());
}

void GListStepper::GenerateLinspace()
{
    // Get parameters
    double start = m_StartValue.DoubleValue();
    double end = m_EndValue.DoubleValue();
    int numPoints = m_NumPoints.IntValue();
    
    // Validate input
    if (numPoints < 2) {
        return; // Cannot generate with fewer than 2 points
    }
    
    // Create the sequence
    QString sequence;
    
    if (numPoints == 2) {
        sequence = QString::number(start) + "\n" + QString::number(end);
    } else {
        double step = (end - start) / (numPoints - 1);
        
        for (int i = 0; i < numPoints; i++) {
            double value = start + i * step;
            sequence += QString::number(value, 'g', 8);
            
            // Add a newline after each value except the last one
            if (i < numPoints - 1) {
                sequence += "\n";
            }
        }
    }
    
    // Update the text field with the generated sequence
    m_ValueListText = sequence;
    
    // The text update will trigger ParseValueList through signal/slot connection
}

void GListStepper::RandomizeList()
{
    // Get the current text
    QString currentText = m_ValueListText.StringValue();
    
    // If empty, nothing to randomize
    if (currentText.trimmed().isEmpty()) {
        return;
    }
    
    // Split the text into lines
    QStringList lines = currentText.split('\n', Qt::SkipEmptyParts);
    
    // If there's only one line, nothing to shuffle
    if (lines.size() <= 1) {
        return;
    }
    
    // Shuffle the lines using Fisher-Yates algorithm
    for (int i = lines.size() - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = QRandomGenerator::global()->bounded(i + 1);
        
        // Swap the lines at indices i and j
        if (i != j) {
            lines.swapItemsAt(i, j);
        }
    }
    
    // Rejoin the lines with newlines
    QString shuffledText = lines.join('\n');
    
    // Update the text field with the shuffled lines
    m_ValueListText = shuffledText;
    
    // The text update will trigger ParseValueList through signal/slot connection
} 