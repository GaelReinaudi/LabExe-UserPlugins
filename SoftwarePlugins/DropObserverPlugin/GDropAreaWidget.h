#ifndef GDROPAREAWIDGET_H
#define GDROPAREAWIDGET_H

#include <QLabel>
class QMimeData;

class GDropAreaWidget : public QLabel
{
	Q_OBJECT

public:
	GDropAreaWidget(QWidget *parent = 0);
	~GDropAreaWidget();

	public slots:
		void clear();

signals:
	void changed(const QMimeData *mimeData = 0);

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);
	
};

#endif // GDROPAREAWIDGET_H
