#include "GDropAreaWidget.h"
#include <QtGui>

GDropAreaWidget::GDropAreaWidget(QWidget *parent /*= 0 */)
	: QLabel(parent)
{
	setMinimumSize(100, 100);
	setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
	setAlignment(Qt::AlignCenter);
	setAcceptDrops(true);
	setAutoFillBackground(true);
	clear();
}

GDropAreaWidget::~GDropAreaWidget()
{

}

//! [dragEnterEvent() function]
void GDropAreaWidget::dragEnterEvent(QDragEnterEvent *event)
{
	setText(tr("<drop content>"));
	setBackgroundRole(QPalette::Highlight);

	event->acceptProposedAction();
	emit changed(event->mimeData());
}
//! [dragEnterEvent() function]

//! [dragMoveEvent() function]
void GDropAreaWidget::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}
//! [dragMoveEvent() function]

//! [dropEvent() function part1]
void GDropAreaWidget::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	//! [dropEvent() function part1]

	//! [dropEvent() function part2]
	if (mimeData->hasImage()) {
		setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
	} else if (mimeData->hasHtml()) {
		setText(mimeData->html());
		setTextFormat(Qt::RichText);
	} else if (mimeData->hasText()) {
		setText(mimeData->text());    
		setTextFormat(Qt::PlainText);
	} else if (mimeData->hasUrls()) {
		QList<QUrl> urlList = mimeData->urls();
		QString text;
		for (int i = 0; i < urlList.size() && i < 32; ++i) {
			QString url = urlList.at(i).path();
			text += url + QString("\n");
		}
		setText(text);
	} else {
		setText(tr("Cannot display data"));
	}
	//! [dropEvent() function part2]

	//! [dropEvent() function part3]    
	setBackgroundRole(QPalette::Dark);
	event->acceptProposedAction();
}
//! [dropEvent() function part3]

//! [dragLeaveEvent() function]
void GDropAreaWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	clear();
	event->accept();
}
//! [dragLeaveEvent() function]

//! [clear() function]
void GDropAreaWidget::clear()
{
	setText(tr("<drop content>"));
	setBackgroundRole(QPalette::Dark);

	emit changed();
}
//! [clear() function]
