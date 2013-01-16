#ifndef GEQUATIONDISPLAY_H
#define GEQUATIONDISPLAY_H

#include "GWebDisplay.h"
#include "param/GParamString.h"

class GExpressionDisplay : public GWebDisplay
{
	Q_OBJECT

public:
	GExpressionDisplay(QObject* parent = NULL);
	~GExpressionDisplay();

public slots:
	void ExpressionChanged(const QString& expression);

protected slots:
	//! Re-implemented.
//REMOVE_WEB_FOR_NOW	void ProcessWebPage(QWebPage* page);
};

#endif // GEQUATIONDISPLAY_H