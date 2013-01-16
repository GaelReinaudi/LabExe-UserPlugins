#include "GImageSaverWidget.h"
#include "GImageSaver.h"

GImageSaverWidget::GImageSaverWidget(GImageSaver* pImageSaver, QWidget *parent /*= 0*/)
	: QWidget(parent)
{
	setupUi(this);
	if(!pImageSaver)
		return;
	connect(pButtonFolder, SIGNAL(clicked()), pImageSaver, SLOT(ChooseFolder()));
	connect(pImageSaver, SIGNAL(FolderUpdated(QString)), pFolderLineEdit, SLOT(setText(QString)));
}

GImageSaverWidget::~GImageSaverWidget()
{

}
