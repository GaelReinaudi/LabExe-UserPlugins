#include "GYoutubeWebWidget.h"
#include "GYoutube.h"
#include <QtWebKit>
#include <QWebElement>

GYoutubeWebWidget::GYoutubeWebWidget(GYoutube* pTheYoutubeDevice, QWidget *parent)
	: QWidget(parent)
	, m_pYoutube(pTheYoutubeDevice)
{
	setupUi(this);
	if(!m_pYoutube)
		return;

	QLineEdit* pUrlLine = m_pYoutube->m_VideoUrl.ProvideNewParamLineEdit(this);
	pUrlLine->setAcceptDrops(false);
	pUrlLine->setDragEnabled(true);
	pUrlLayout->addRow(m_pYoutube->m_VideoUrl.ProvideNewLabel(this), pUrlLine);
	QNetworkProxyFactory::setUseSystemConfiguration (true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);

	// load when the url changes
	connect(&m_pYoutube->m_VideoUrl, SIGNAL(ValueUpdated(QString)), this, SLOT(LoadVideo(QString)), Qt::UniqueConnection);
	// removes some elements after loading
	connect(pWebView, SIGNAL(loadFinished(bool)), SLOT(HideYoutubeElements()), Qt::UniqueConnection);

	// sets the scrollbar to not appear
	pWebView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	pWebView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

	QTimer::singleShot(9000, this, SLOT(TogglePlayStop()));
}

GYoutubeWebWidget::~GYoutubeWebWidget()
{

}

void GYoutubeWebWidget::LoadVideo( QString url )
{
	if(url.isEmpty())
		return;

	if(!url.contains("www.youtube.com"))
		url.prepend("http://www.youtube.com/watch?v=");

//	qWarning() << pWebView->url() << url;
	if(pWebView->url() == url)
		return;

	pWebView->load(QUrl(url));
}

void GYoutubeWebWidget::HideYoutubeElements()
{
//	qWarning() << pWebView->url();
	m_pYoutube->m_VideoUrl = pWebView->url().toString();

	document().findFirst("#masthead-expanded-acct-sw-container").removeFromDocument();
	document().findFirst("#masthead-container").removeFromDocument();
	document().findFirst("#watch-headline-container").removeFromDocument();
	document().findFirst("#watch-main-container").removeFromDocument();
	document().findFirst("#watch-panel").removeFromDocument();
	document().findFirst("#watch-discussion").removeFromDocument();
	document().findFirst("#watch-sidebar").removeFromDocument();
	document().findFirst("#footer-container").removeFromDocument();
	document().findFirst("#playlist-bar.hid").removeFromDocument();
	document().findFirst("#shared-addto-menu").removeFromDocument();

	FitPlayerToView();
// 	QTimer::singleShot(10000, this, SLOT(HideYoutubeElements()));
}

void GYoutubeWebWidget::resizeEvent( QResizeEvent* event )
{
	QWidget::resizeEvent(event);
//   	pWebView->page()->setPreferredContentsSize(QSize(640, 640));

//	QTimer::singleShot(0, this, SLOT(FitPlayerToView()));
	FitPlayerToView();
}

void GYoutubeWebWidget::FitPlayerToView()
{
// 	pWebView->page()->mainFrame()->setZoomFactor(1.0);
	// gets the player element
	QWebElement playerElement = document().findFirst("#watch-player");
	QWebElement ContainerElement = document().findFirst("#watch-video");
	// gets its size from the css property values
	QString widthStr = playerElement.styleProperty("width", QWebElement::ComputedStyle);
	QString heightStr = ContainerElement.styleProperty("height", QWebElement::ComputedStyle);
	if(widthStr.isEmpty() || heightStr.isEmpty())
		return;
	// removes the "px" of e.g. "640px"
	double widthPx = widthStr.remove("px").toDouble();
	// for now the height is set manually to 390 since the zoom factor seems to influence this property when querying it from the css properties...
	double heightPx = 390.0;//heightStr.remove("px").toDouble();
	qDebug() << "widthPx"<< widthPx << "heightPx"<< heightPx;
	QSizeF sizePlayer(widthPx, heightPx);
	// to figure out the zooming we need we scale the size and infer from the new height or width
	QSizeF sizeView = pWebView->size();
// 	qDebug() << "sizeView"<< sizeView;
// 	qDebug() << "sizePlayer"<< sizePlayer;
 	sizePlayer.scale(sizeView, Qt::KeepAspectRatio);
//	qDebug() << "sizePlayer"<< sizePlayer;

	double zoom = sizePlayer.width() / widthPx;
// 	double zoom = sizeView.width() / sizePlayer.width();
// 	double zoomForX = sizeView.width() / widthPx;
// 	double zoomForY = sizeView.height() / heightPx;
// 	double zoom = zoomForX;
//  	qDebug() << zoomForX;
// 	qDebug() << zoomForY;
	pWebView->page()->mainFrame()->setZoomFactor(zoom);
}

void GYoutubeWebWidget::TogglePlayStop()
{
	QWebElement playerElement = document().findFirst("#watch-video");
	playerElement.setFocus();
	QKeyEvent eventSpace(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " ");
	QApplication::sendEvent(pWebView->page(), &eventSpace);
}
