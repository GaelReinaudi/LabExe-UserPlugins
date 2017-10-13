#ifndef GIMAGESAVER_H
#define GIMAGESAVER_H

#include "device.h"
#include "LabExeImaging/GImageProcessor.h"


/////////////////////////////////////////////////////////////////////
//! \brief The GImageSaver class implements an image processor that saves images.
/*!
*/ 
class GImageSaver : public GImageProcessor
{
	Q_OBJECT

public:
	GImageSaver(QObject *parent, QString uniqueIdentifierName = "");
	~GImageSaver();


protected:
	//! Re-implemented
	void PopulateSettings( QSettings& inQsettings );
	//! Re-implemented
	void InterpretSettings( QSettings& fromQsettings );
	//! Reimplemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	void ProcessImageAOIed(const GImageDouble & aoiImage);

protected slots:
	//! pops up a dialog to select a folder
	void ChooseFolder();
	//! changes the folder
	void SetFolder(QString newFolder);

signals:
	//! emitted when the folder has been changed. updates the display
	void FolderUpdated(QString);

private:
	//! the folder to save images into
	QString m_Folder;
	GParamBool m_SaveDouble;//2015-06-24 Bart: if true, then enables code to save binary data with full double precision (very large file size!).
	GParamBool m_Save12bit;//2015-06-24 Bart: if true, then enables code to save ...
};

#endif // GIMAGESAVER_H
