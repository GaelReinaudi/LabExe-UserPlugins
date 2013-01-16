#include "GPlainTextLoggerWidget.h"
#include "GPlainTextLogger.h"

GPlainTextLoggerWidget::GPlainTextLoggerWidget(GPlainTextLogger* pPlainTextLogger, QWidget *parent /*= 0*/)
	: QWidget(parent)
	, m_pLogger(pPlainTextLogger)
{
	setupUi(this);
	if(!m_pLogger)
		return;

	connect(pButtonFolder, SIGNAL(clicked()), m_pLogger, SLOT(ChooseFolder()));
	connect(m_pOpenLogFileButton, SIGNAL(clicked()), m_pLogger, SLOT(OpenLogFile()));
	connect(m_pOpenFolderButton, SIGNAL(clicked()), m_pLogger, SLOT(OpenFolder()));
	connect(m_pTrashContentButton, SIGNAL(clicked()), m_pLogger, SLOT(TrashContent()));

// 	connect(pSettingsButton, SIGNAL(clicked()), m_pLogger, SLOT(ShowExtraSettingsWidget()));

	pFolderLayout->addWidget(m_pLogger->m_FolderPath.ProvideNewLabel(this));
	pFolderLayout->addWidget(m_pLogger->m_FolderPath.ProvideNewParamLineEdit(this));
	pFolderFileLayout->addRow(m_pLogger->m_FileName.ProvideNewLabel(this), m_pLogger->m_FileName.ProvideNewParamLineEdit(this));
	pUpdateLayout->addWidget(m_pLogger->m_ShouldLogOnTimer.ProvideNewParamCheckBox(this));
	pUpdateLayout->addWidget(m_pLogger->m_SecondTimer.ProvideNewLabel(this));
	pUpdateLayout->addWidget(m_pLogger->m_SecondTimer.ProvideNewParamSpinBox(this));
	pUpdateLayout->addStretch();
	pUpdateLayout->addWidget(m_pLogger->m_ShouldLogOnUpdate.ProvideNewParamCheckBox(this));

	pBucketLayout->addWidget(m_pLogger->m_Bucket.ProvideNewParamWidget(this));
	pBucketLayout->addWidget(m_pLogger->m_BucketColNames.ProvideParamBucketWidget(this, Qt::Horizontal));

	pFirstColLayout1->addWidget(m_pLogger->m_CurrentIndexUpdate.ProvideNewLabel(this));
	pFirstColLayout1->addWidget(m_pLogger->m_CurrentIndexUpdate.ProvideNewParamWidget(this));
	pFirstColLayout1->addWidget(m_pLogger->m_SecUpdate.ProvideNewLabel(this));
	pFirstColLayout1->addWidget(m_pLogger->m_SecUpdate.ProvideNewParamWidget(this));
	pFirstColLayout1->addStretch();
	pFirstColLayout1->addWidget(m_pLogger->m_FirstColName.ProvideNewLabel(this));
	pFirstColLayout1->addWidget(m_pLogger->m_FirstColName.ProvideNewParamLineEdit(this));

	pFirstColLayout2->addWidget(m_pLogger->m_FirstColFormula.ProvideNewLabel(this));
	pFirstColLayout2->addWidget(m_pLogger->m_FirstColFormula.ProvideNewParamLineEdit(this));
	pFirstColLayout2->addWidget(m_pLogger->m_FirstColValue.ProvideNewLabel(this));
	pFirstColLayout2->addWidget(m_pLogger->m_FirstColValue.ProvideNewParamWidget(this));
}

GPlainTextLoggerWidget::~GPlainTextLoggerWidget()
{

}
