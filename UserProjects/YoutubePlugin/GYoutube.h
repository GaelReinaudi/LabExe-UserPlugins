#ifndef GYoutube_H
#define GYoutube_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GYoutube class implements a GProgDevice.
/*!
This soft device allows you to type or drop the url of a Youtube video.
*/
class GYoutube : public GProgDevice
{
	Q_OBJECT

public:
	GYoutube(QObject *parent, QString uniqueIdentifierName = "");
	~GYoutube();

public slots:

protected:
	//! Re-implemented to provide a new widget adequately connected to this GYoutube.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented to catch a url.
	void DragEnterEvent(QDragEnterEvent *event, GDeviceWidget* pOnWidget); 
	//! Re-implemented to catch a url.
	void DropEvent(QDropEvent *event, GDeviceWidget* pOnWidget);

signals:
	//! Emitted when the URL has changed.
	void VideoUrlChanged(QString url);

private:
	//! the output of the filter
	GParamString m_VideoUrl;
	//! the playing state
	GParamBool m_WasPlaying;

	friend class GYoutubeWebWidget;
};

#endif // GYoutube_H
