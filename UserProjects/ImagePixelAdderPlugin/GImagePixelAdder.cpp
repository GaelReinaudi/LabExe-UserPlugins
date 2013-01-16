#include "GImagePixelAdder.h"

GImagePixelAdder::GImagePixelAdder(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_SumPix("Sum", this, GParam::ReadOnly)
	, m_AvePix("Average", this, GParam::ReadOnly)
	, m_StdDevPix("Std.dev.", this, GParam::ReadOnly)
{
	m_SumPix.SetHardLimits(-9.9999999999e8, 9.9999999999e9);
	m_AvePix.SetHardLimits(-1e3, 1e4);
	m_StdDevPix.SetHardLimits(-1e3, 1e4);
	m_SumPix.SetDisplayDecimals(0);
	m_AvePix.SetDisplayDecimals(4);
	m_StdDevPix.SetDisplayDecimals(4);
}

GImagePixelAdder::~GImagePixelAdder()
{
}

void GImagePixelAdder::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QLabel* sumLabel = m_SumPix.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pSum = m_SumPix.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* aveLabel = m_AvePix.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pAve = m_AvePix.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* devLabel = m_StdDevPix.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pDev = m_StdDevPix.ProvideNewParamSpinBox(theDeviceWidget);

	// A QFormLayout, in which we place the label and the spinbox 
	QFormLayout* valueLayout = new QFormLayout();
	theDeviceWidget->AddSubLayout(valueLayout);
	valueLayout->addRow(sumLabel, pSum);
	valueLayout->addRow(aveLabel, pAve);
	valueLayout->addRow(devLabel, pDev);
}

void GImagePixelAdder::run()
{
}

void GImagePixelAdder::ProcessImageAOIed(const GImageDouble & aoiImage)
{
	IncrementCountProcessed();
	int Npix = aoiImage.size().width() * aoiImage.size().height();
	int hei = aoiImage.size().height();
	int wid = aoiImage.size().width();
	GDoubleArray & zArray = aoiImage.DoubleArray();
	double sum = 0;
	double sumSquare = 0;
	int pxTot = 0;
	for(int i = 0; i < Npix; i++) {
		double valPix = zArray[i];
		if(qIsNaN(valPix) || qIsInf(valPix))
			continue;
		pxTot++;
		sum += valPix;
		sumSquare += valPix * valPix;
	}
	if(!pxTot)
		return;
	double dNpixTot = double(pxTot);
	m_SumPix = sum;
	sum /= dNpixTot;
	sumSquare /= dNpixTot;
	m_AvePix = sum;
	m_StdDevPix = qSqrt(sumSquare - sum * sum);
}