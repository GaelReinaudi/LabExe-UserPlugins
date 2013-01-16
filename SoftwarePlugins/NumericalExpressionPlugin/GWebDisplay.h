#ifndef GWEBDISPLAY_H
#define GWEBDISPLAY_H
#include "labexe_global.h"

#include "device/GProgDevice.h"
// #include <QWebElement>
// #include <QWebFrame>
// #include <QWebPage>
// #include <QWebView>

class GWebDisplay : public QObject
{
	Q_OBJECT

public:
	GWebDisplay(QObject *parent);
	~GWebDisplay();

	//! Creates a GWebProcessor and then loads the manipulated web page.
	void Load(const QUrl& url);

	//! Re-implemented.
	QWidget* ProvideNewWebDisplayWidget(QWidget* parentWidget);

protected:
	//! Loads the web page.
	void SetUrl(const QUrl& url);

protected slots:
//REMOVE_WEB_FOR_NOW	virtual void ProcessWebPage(QWebPage* page);

private slots:
	void EventWebPageLoaded(bool okay);

private:
//REMOVE_WEB_FOR_NOW	QWebPage* m_WebPage;
//REMOVE_WEB_FOR_NOW	QWebPage* m_WebPage_2;
};

#endif // GWEBDISPLAY_H