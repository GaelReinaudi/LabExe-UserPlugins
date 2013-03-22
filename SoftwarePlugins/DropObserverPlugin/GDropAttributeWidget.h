#ifndef GDROPATTRIBUTEWIDGET_H
#define GDROPATTRIBUTEWIDGET_H

#include <QWidget>
class QLabel;
class QMimeData;
class QPushButton;
class QTableWidget;
class GDropAreaWidget;

class GDropAttributeWidget : public QWidget
{
	Q_OBJECT

public:
	GDropAttributeWidget(QWidget *parent);
	~GDropAttributeWidget();

public slots:
	void updateFormatsTable(const QMimeData *mimeData);

private:
	GDropAreaWidget *dropArea;
	QLabel *abstractLabel;
	QTableWidget *formatsTable;
	
};

#endif // GDROPATTRIBUTEWIDGET_H
