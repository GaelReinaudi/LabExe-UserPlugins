#include "GDropAttributeWidget.h"
#include <QtGui>
#include "GDropAreaWidget.h"

GDropAttributeWidget::GDropAttributeWidget(QWidget *parent)
	: QWidget(parent)
{
	abstractLabel = new QLabel(tr("This area accepts drags from other "
		"applications and displays the MIME types "
		"provided by the drag object."));
	abstractLabel->setWordWrap(true);
	abstractLabel->adjustSize();
	//! [constructor part1]

	//! [constructor part2]
	dropArea = new GDropAreaWidget;
	connect(dropArea, SIGNAL(changed(const QMimeData*)), this, SLOT(updateFormatsTable(const QMimeData*)));
	//! [constructor part2]

	//! [constructor part3]
	QStringList labels;
	labels << tr("Format") << tr("Content");

	formatsTable = new QTableWidget;
	formatsTable->setColumnCount(2);
	formatsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	formatsTable->setHorizontalHeaderLabels(labels);
	formatsTable->horizontalHeader()->setStretchLastSection(true);
	//! [constructor part3]

	//! [constructor part5]
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(abstractLabel);
	mainLayout->addWidget(dropArea);
	mainLayout->addWidget(formatsTable);
	setLayout(mainLayout);

//	setMinimumSize(350, 500);
}

GDropAttributeWidget::~GDropAttributeWidget()
{

}

void GDropAttributeWidget::updateFormatsTable(const QMimeData *mimeData)
{
	formatsTable->setRowCount(0);
	if (!mimeData)
		return;
	//! [updateFormatsTable() part1]

	//! [updateFormatsTable() part2]        
	foreach (QString format, mimeData->formats()) {
		QTableWidgetItem *formatItem = new QTableWidgetItem(format);
		formatItem->setFlags(Qt::ItemIsEnabled);
		formatItem->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
		//! [updateFormatsTable() part2]

		//! [updateFormatsTable() part3]
		QString text;
		if (format == "text/plain") {
			text = mimeData->text().simplified();
		} else if (format == "text/html") {
			text = mimeData->html().simplified();
		} else if (format == "text/uri-list") {
			QList<QUrl> urlList = mimeData->urls();
			for (int i = 0; i < urlList.size() && i < 32; ++i)
				text.append(urlList[i].toString() + " ");
		} else {
			QByteArray data = mimeData->data(format);
			for (int i = 0; i < data.size() && i < 32; ++i) {
				QString hex = QString("%1").arg(uchar(data[i]), 2, 16,
					QChar('0'))
					.toUpper();
				text.append(hex + " ");
			}
		}
		//! [updateFormatsTable() part3]   

		//! [updateFormatsTable() part4]
		int row = formatsTable->rowCount();
		formatsTable->insertRow(row);
		formatsTable->setItem(row, 0, new QTableWidgetItem(format));
		formatsTable->setItem(row, 1, new QTableWidgetItem(text));
	}

	formatsTable->resizeColumnToContents(0);
}
