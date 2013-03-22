#include "GYoutube.h"
#include "GYoutubeWebWidget.h"

GYoutube::GYoutube(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_VideoUrl("Video URL", this)
	, m_WasPlaying("playing", this)
{
 	m_VideoUrl = "hch3cZZywzE";
}

GYoutube::~GYoutube()
{

}

void GYoutube::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	QWidget* pWebView = new GYoutubeWebWidget(this, theDeviceWidget);
	pVlay->addWidget(pWebView);
}

void GYoutube::DragEnterEvent( QDragEnterEvent* event, GDeviceWidget* pOnWidget )
{
	// if it has a url we accept
	if(event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
	// if it is text it might still be a url
	else if(event->mimeData()->hasText())
		event->acceptProposedAction();
}

void GYoutube::DropEvent( QDropEvent* event, GDeviceWidget* pOnWidget )
{
	QString urlString;
	if(event->mimeData()->hasUrls()) {
		QList<QUrl> ListUrl = event->mimeData()->urls();
		QUrl theFirstUrl = ListUrl.value(0);
		// is it from youtube?
		if(theFirstUrl.toString().contains("youtube"))
			urlString = theFirstUrl.toString();
	}
	else if(event->mimeData()->hasText())
		urlString = event->mimeData()->text();
	
	if(urlString.isEmpty())
		return;
	
	m_VideoUrl = urlString;
}