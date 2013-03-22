#include "GWebDisplay.h"

GWebDisplay::GWebDisplay( QObject *parent)
	: QObject(parent)
{
//REMOVE_WEB_FOR_NOW 	m_WebPage = new QWebPage;
}

GWebDisplay::~GWebDisplay()
{

}

QWidget* GWebDisplay::ProvideNewWebDisplayWidget( QWidget* parentWidget )
{
	QWidget* widToReturn = new QWidget(parentWidget) ;
	QBoxLayout* pDeviceLayout = new QVBoxLayout;
	widToReturn->setLayout(pDeviceLayout);

// 	QWebView* pView = new QWebView;
// 	pView->setPage(m_WebPage);
// 	pView->show();
// 
// 	pDeviceLayout->insertWidget(0, pView);
// 
// 	widToReturn->setMinimumHeight(50);
	return widToReturn;
}

// void GWebDisplay::ProcessWebPage(QWebPage* page)
// {
// }

void GWebDisplay::Load( const QUrl& url )
{
// 	m_WebPage_2 = new QWebPage;
// 	connect(m_WebPage_2, SIGNAL(loadFinished(bool)), this, SLOT(EventWebPageLoaded(bool)));
// 	m_WebPage_2->mainFrame()->setUrl(url);
}


void GWebDisplay::SetUrl( const QUrl& url )
{
// 	if(url == m_WebPage->mainFrame()->url())
// 		return;
// 	m_WebPage->mainFrame()->setUrl(url);
}

void GWebDisplay::EventWebPageLoaded( bool okay )
{
// 	ProcessWebPage(m_WebPage_2);
}