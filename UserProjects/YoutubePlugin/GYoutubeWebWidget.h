#ifndef GYOUTUBEWEBWIDGET_H
#define GYOUTUBEWEBWIDGET_H

#include <QWidget>
#include "ui_GYoutubeWebWidget.h"
#include <QtWebKit>

class GYoutube;

class GYoutubeWebWidget : public QWidget, public Ui::GYoutubeWebWidget
{
	Q_OBJECT

public:
	GYoutubeWebWidget(GYoutube* pTheYoutubeDevice, QWidget *parent = 0);
	~GYoutubeWebWidget();


protected:
	//! Re-implemented to resize the view
	void resizeEvent(QResizeEvent* event);

	//! returns the web document being displayed in the view
	QWebElement document() const {return pWebView->page()->mainFrame()->documentElement();}

protected slots:
	void LoadVideo(QString url);
	void HideYoutubeElements();
	void FitPlayerToView();
	void TogglePlayStop();

private:
	GYoutube* m_pYoutube;
};

#endif // GYOUTUBEWEBWIDGET_H
