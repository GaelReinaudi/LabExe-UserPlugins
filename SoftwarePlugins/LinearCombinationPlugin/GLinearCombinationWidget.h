#ifndef GLINEARCOMBINATIONWIDGET_H
#define GLINEARCOMBINATIONWIDGET_H
#include "ui_GLinearCombinationWidget.h"

#include <QWidget>

class GLinearCombination;

class GLinearCombinationWidget : public QWidget, public Ui::GLinearCombinationWidget
{
	Q_OBJECT

public:
	GLinearCombinationWidget(GLinearCombination* pTheLinearCombination, QWidget *parent = 0);
	~GLinearCombinationWidget();

protected slots:
	//! to show the editing widgets in the table
	void OpenPersistentTableEditor(QModelIndex theIndex);

private:
	//! the linear combination
	GLinearCombination* m_pLinComb;

};

#endif // GLINEARCOMBINATIONWIDGET_H
