#include "GImageSaver.h"
#include "GImageSaverWidget.h"
#include <QFileDialog>

GImageSaver::GImageSaver(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_Folder("F:\\images\\")
{
}

GImageSaver::~GImageSaver()
{
}

void GImageSaver::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
 	GImageSaverWidget* pWid = new GImageSaverWidget(this, theDeviceWidget);
 
 	QVBoxLayout* lay = new QVBoxLayout();
 	theDeviceWidget->AddSubLayout(lay);
 	lay->addWidget(pWid);
}

void GImageSaver::PopulateSettings( QSettings& inQsettings )
{
	GImageProcessor::PopulateSettings(inQsettings);
	inQsettings.setValue("folder", m_Folder);
}

void GImageSaver::InterpretSettings( QSettings& fromQsettings )
{
	GImageProcessor::InterpretSettings(fromQsettings);
	SetFolder(fromQsettings.value("folder").toString());
}

void GImageSaver::ProcessImageAOIed(const GImageDouble & aoiImage)
{
	IncrementCountProcessed();
	QString fileName = m_Folder;
 	fileName += "\\";
	fileName += QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss.zzz");
	fileName += ".png";

	QPixmap::fromImage(aoiImage).save(fileName);
}

void GImageSaver::ChooseFolder()
{
	QFileDialog* pDialog = new QFileDialog(0, "Select folder", m_Folder);
	pDialog->setFileMode(QFileDialog::Directory);
	pDialog->setOption(QFileDialog::ShowDirsOnly);
	pDialog->show();
	pDialog->setAttribute(Qt::WA_DeleteOnClose);

	connect(pDialog, SIGNAL(fileSelected(QString)), this, SLOT(SetFolder(QString)));
}

void GImageSaver::SetFolder( QString newFolder )
{
	m_Folder = newFolder;
	emit FolderUpdated(m_Folder);
}