#ifndef GPLAINTEXTLOGGERWIDGET_H
#define GPLAINTEXTLOGGERWIDGET_H

#include <QWidget>
#include "ui_GPlainTextLoggerWidget.h"

class GPlainTextLogger;

class GPlainTextLoggerWidget : public QWidget, public Ui::GPlainTextLoggerWidget
{
	Q_OBJECT

public:
	GPlainTextLoggerWidget(GPlainTextLogger* pPlainTextLogger, QWidget *parent = 0);
	~GPlainTextLoggerWidget();

private:
	GPlainTextLogger* m_pLogger;

// 	friend GPlainTextLogger;
};

#endif // GPLAINTEXTLOGGERWIDGET_H
