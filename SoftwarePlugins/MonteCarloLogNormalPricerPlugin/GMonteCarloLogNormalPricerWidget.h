#ifndef GMONTECARLOLOGNORMALPRICERWIDGET_H
#define GMONTECARLOLOGNORMALPRICERWIDGET_H

#include <QtWidgets>
#include "ui_GMonteCarloLogNormalPricerWidget.h"

class GMonteCarloLogNormalPricer;

class GMonteCarloLogNormalPricerWidget : public QWidget, public Ui::GMonteCarloLogNormalPricerWidget
{
	Q_OBJECT

public:
	GMonteCarloLogNormalPricerWidget(GMonteCarloLogNormalPricer* pPricer, QWidget *parent = 0);
	~GMonteCarloLogNormalPricerWidget();

private:
	GMonteCarloLogNormalPricer* m_pPricer;
};

#endif // GMONTECARLOLOGNORMALPRICERWIDGET_H
