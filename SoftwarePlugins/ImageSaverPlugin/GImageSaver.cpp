#include "GImageSaver.h"
#include "GImageSaverWidget.h"
#include <QFileDialog>

GImageSaver::GImageSaver(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_Folder("F:\\images\\")
	, m_SaveDouble("Also save doubles? (HUGE FILES!)", this)
	, m_Save12bit("Also save 2-byte/px raw camera?", this)
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
 	

	QFormLayout* SavingOptionsA = new QFormLayout ();
	QFormLayout* SavingOptionsB = new QFormLayout ();
	QFormLayout* SavingOptionsForm = new QFormLayout ();
	SavingOptionsForm->addRow(m_Save12bit.ProvideNewParamCheckBox(theDeviceWidget), SavingOptionsB);
	SavingOptionsForm->addRow(m_SaveDouble.ProvideNewParamCheckBox(theDeviceWidget), SavingOptionsA);

	theDeviceWidget->AddSubLayout(SavingOptionsForm);

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
	//fileName += ".png";
	QPixmap::fromImage(aoiImage).save(fileName + "_8bit.png");//Gael's original implementation which saves 8-bit QImage.
	
	
	//Shared things for next two if() statements: 
	double* doubleArrayToSave = aoiImage.DoubleArray().data();//Get access to desired DoubleArray.
	uint ulength = aoiImage.width()*aoiImage.height();
	int length = aoiImage.width()*aoiImage.height();
	QString height;
	QString width;
	height.setNum(aoiImage.height());
	width.setNum(aoiImage.width());
	if(m_SaveDouble){
		//2015-06-24 Bart: Trying again to save DoubleArray directly to avoid converting to 8-bit QImage first. 
		//Data is exported as raw binary data file, without separating rows or columns. 
		//The row and column sizes are saved in the file name, so you can reassemble the image later. 
		//Each pixel data point is a double, which is saved as 8 characters. 
		//This works, but double's are huge with unused bytes, so 500x500 AOI ends up taking about 2 megabytes on disk. 
		QFile fileHQ;
		fileHQ.setFileName(fileName + "_Double[width=" + width + ";height=" + height + "].dat");
		fileHQ.open(QFile::WriteOnly);
		//debugging tests: passed! 
		//qDebug()<<"File length should be "<<length<<" times sizeof(doule) = "<<sizeof(double);
		//qDebug()<<"Attempting to save high quality file, num bytes written:"<< //next line goes here
		fileHQ.write((const char*) doubleArrayToSave, ulength*sizeof(double));//following internet's example here...
		fileHQ.flush();
		fileHQ.close();
	}
	if(m_Save12bit){
		//2015-06-24 Bart: Now trying to save high quality image without huge file size! 
		//Goal here is ONLY to save raw imported camera images with 2-bytes/pixel; this will NOT work with processed optical depth, etc. 
		//Essentially, this is the reverse process of what I did with GUEyeImageDistributor:BufferToTreat() for 12-bit images. 
		QFile file12bit;
		file12bit.setFileName(fileName + "_2BytesPerPixel[width=" + width + ";height=" + height + "].dat");
		file12bit.open(QFile::WriteOnly);
		//file12bit.write(ByteArrayToSave);
		QDataStream out(&file12bit);
		//ushort tempvalue;
		for(int iTot=0; iTot<length; iTot++){
			//out << doubleArrayToSave[iTot];//testing,exports double values, appears to work because filesize is as large as expected.
			//qDebug()<<doubleArrayToSave[iTot];//testing
			//memcpy(&tempvalue,&doubleArrayToSave[iTot],sizeof(ushort));//get 2 byte unit from double
			//out << tempvalue;
			//qDebug() << tempvalue;

			//Try just forcing conversion to ushort: SEEMS TO WORK? 
			out << (ushort)doubleArrayToSave[iTot];
			//qDebug()<<(ushort)doubleArrayToSave[iTot];//testing
		}
		file12bit.flush();
		file12bit.close();

		//Trying some random things: 
		//Try PNG with quality set to 100 (highest value, lowest compression.): 
		//QPixmap::fromImage(aoiImage).save(fileName + "_PixMap100.png",0,100);//This saves 735 kB vs 19 kB PNGs with same information b/c least compressed? 
		//Try PGM format:  Saves as 8-bit because loaded from aoiImage. Can do 2-byte if could import values in different way! 
		//QPixmap::fromImage(aoiImage).save(fileName + "_PixMap100fromImage.pgm",0,100);//This saves QImage as 8-bit PGM format (245 kB vs 19 kB default PNG). 
		//Doesn't work... 
		//QPixmap MapToSave; 
		//qDebug()<<"Try to load map from data: " << MapToSave.loadFromData((const uchar*) doubleArrayToSave, length*sizeof(double));
		//MapToSave.save(fileName + "_PixMap100fromData.pgm",0,100);
	}
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