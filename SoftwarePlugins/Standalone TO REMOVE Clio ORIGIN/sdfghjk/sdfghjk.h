#ifndef SDFGHJK_H
#define SDFGHJK_H

#include <QtGui/QMainWindow>
#include "ui_sdfghjk.h"
#include "GClioOrigin.h"

//class COriginClient;

//sdfghjk class inherits QMainWindow
class sdfghjk : public QMainWindow
{
	Q_OBJECT

public:
	sdfghjk(QWidget *parent = 0, Qt::WFlags flags = 0);
	~sdfghjk();

private:
	Ui::sdfghjkClass ui;
	GClioOrigin m_CliosOrigin;


public slots:
	void SendData();
};

#endif // SDFGHJK_H
