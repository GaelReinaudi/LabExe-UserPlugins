#include "GImage2DGaussFitter.h"
#include "AlgLib/src/interpolation.h"
using namespace alglib;

const QString fitFieldString("fit");

GImage2DGaussFitter::GImage2DGaussFitter(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_pEllipse(new QGraphicsEllipseItem(0.0, 0.0, 0.0, 0.0, m_pAoiItem))
	, m_Offset("Offset", this)
	, m_Ampl("Ampl", this)
	, m_SigmaX("sigX", this)
	, m_SigmaY("sigY", this)
	, m_X0("X0", this)
	, m_Y0("Y0", this)
	, m_IniOffset("iniOffset", this)
	, m_IniAmpl("iniAmpl", this)
	, m_IniSigmaX("iniSigX", this)
	, m_IniSigmaY("iniSigY", this)
	, m_IniX0("iniX0", this)
	, m_IniY0("iniY0", this)
	, m_Variables("variables", this, GParam::ReadOnly)//, &m_Offset, &m_Ampl, &m_X0, &m_Y0, &m_SigmaX, &m_SigmaY)
	, m_InitialValues("fitted", 0, GParam::ReadOnly)//, &m_IniOffset, &m_IniAmpl, &m_IniX0, &m_IniY0, &m_IniSigmaX, &m_IniSigmaY)
	, m_FitMask(6)
{
	m_Variables.RemoveExtraField("trig");
	m_Variables.AddExtraFieldBool(fitFieldString);

	m_Variables.AddParam(&m_Offset);
	m_Variables.AddParam(&m_Ampl);
	m_Variables.AddParam(&m_X0);
	m_Variables.AddParam(&m_Y0);
	m_Variables.AddParam(&m_SigmaX);
	m_Variables.AddParam(&m_SigmaY);

	m_InitialValues.AddParam(&m_IniOffset);
	m_InitialValues.AddParam(&m_IniAmpl);
	m_InitialValues.AddParam(&m_IniX0);
	m_InitialValues.AddParam(&m_IniY0);
	m_InitialValues.AddParam(&m_IniSigmaX);
	m_InitialValues.AddParam(&m_IniSigmaY);

	m_pEllipse->setPen(QPen(Qt::yellow));
}

GImage2DGaussFitter::~GImage2DGaussFitter()
{
	wait(5000);
	terminate();
}

void GImage2DGaussFitter::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QHBoxLayout* play = new QHBoxLayout();
	theDeviceWidget->AddSubLayout(play);

// 	play->addWidget(m_InitialValues.ProvideNewWidget(theDeviceWidget));
	play->addWidget(m_Variables.ProvideNewParamWidget(theDeviceWidget));
}

void Gaus2D_func(const real_1d_array &c, const real_1d_array &X, double &func, void *ptr) 
{
	const double & x = X[0];
	const double & y = X[1];
	const double & Offset = c[0];
	const double & Ampl = c[1];
	const double & x0 = c[2];
	const double & y0 = c[3];
	const double & sigma_x = c[4];
	const double & sigma_y = c[5];

	const double t1 = sigma_y * sigma_y;
	const double t2 = x * x;
	const double t7 = x0 * x0;
	const double t9 = sigma_x * sigma_x;
	const double t10 = y * y;
	const double t15 = y0 * y0;
	const double t23 = exp(-0.5000000000e0 * (t1 * t2 - 0.2e1 * t1 * x * x0 + t1 * t7 + t9 * t10 - 0.2e1 * t9 * y * y0 + t9 * t15) / t9 / t1);

	func = Offset + Ampl * t23;
}

void Gaus2D_grad(const real_1d_array &c, const real_1d_array &X, double &func, real_1d_array &grad, void *ptr) 
{
	// is this a GImage2DGaussFitter
	GImage2DGaussFitter* pGaussFitter = (GImage2DGaussFitter*)(ptr);
	if(!pGaussFitter)
		return;
	const double & x = X[0];
	const double & y = X[1];
	const double & Offset = c[0];
	const double & Ampl = c[1];
	const double & x0 = c[2];
	const double & y0 = c[3];
	const double & sigma_x = c[4];
	const double & sigma_y = c[5];

	const double t1 = sigma_y * sigma_y;
	const double t2 = x * x;
	const double t7 = x0 * x0;
	const double t9 = sigma_x * sigma_x;
	const double t10 = y * y;
	const double t15 = y0 * y0;
	const double t18 = 0.1e1 / t9;
	const double t20 = 0.1e1 / t1;
	const double t23 = exp(-0.5 * (t1 * t2 - 0.2e1 * t1 * x * x0 + t1 * t7 + t9 * t10 - 0.2e1 * t9 * y * y0 + t9 * t15) * t18 * t20);

	grad[0] = 1.0;
	grad[1] = t23;
	grad[2] = Ampl * (x - 0.1e1 * x0) * t23 * t18;
	grad[3] = Ampl * (y - 0.1e1 * y0) * t23 * t20;
	grad[4] = Ampl * (t2 - 0.2e1 * x * x0 + t7) / t9 / sigma_x * t23;
	grad[5] = Ampl * (t10 - 0.2e1 * y * y0 + t15) / t1 / sigma_y * t23;
	func = Offset + Ampl * t23;

	// mask
	for(int i = 0; i < 6 ; i++) {
		if(!pGaussFitter->m_FitMask[i]) {
			grad[i] = 0.0;
		}
	}
}
void Gaus2D_hess(const real_1d_array &c, const real_1d_array &X, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr) 
{
	const double & x = X[0];
	const double & y = X[1];
	const double & Offset	= c[0];
	const double & Ampl		= c[1];
	const double & x0		= c[2];
	const double & y0		= c[3];
	const double & sigma_x	= c[4];
	const double & sigma_y	= c[5];

	const double t2 = x - 0.1e1 * x0;
	const double t3 = sigma_y * sigma_y;
	const double t4 = x * x;
	const double t9 = x0 * x0;
	const double t11 = sigma_x * sigma_x;
	const double t12 = y * y;
	const double t17 = y0 * y0;
	const double t20 = 0.1e1 / t11;
	const double t22 = 0.1e1 / t3;
	const double t25 = exp(-0.5000000000e0 * (t3 * t4 - 0.2e1 * t3 * x * x0 + t3 * t9 + t11 * t12 - 0.2e1 * t11 * y * y0 + t11 * t17) * t20 * t22);
	const double t27 = t2 * t25 * t20;
	const double t29 = y - 0.1e1 * y0;
	const double t31 = t29 * t25 * t22;
	const double t33 = 0.2e1 * x * x0;
	const double t34 = t4 - t33 + t9;
	const double t36 = 0.1e1 / t11 / sigma_x;
	const double t38 = t34 * t36 * t25;
	const double t40 = 0.2e1 * y * y0;
	const double t41 = t12 - t40 + t17;
	const double t43 = 0.1e1 / t3 / sigma_y;
	const double t45 = t41 * t43 * t25;
	const double t46 = Ampl * t25;
	const double t49 = t11 * t11;
	const double t53 = Ampl * t2;
	const double t55 = t25 * t20;
	const double t57 = t53 * t29 * t55 * t22;
	const double t64 = t53 * t25 * (-0.2e1 * t11 + t4 - t33 + t9) / t49 / sigma_x;
	const double t67 = x * y;
	const double t81 = Ampl * t43 * t25 * (x * t12 - 0.2e1 * t67 * y0 + x * t17 - 0.1e1 * x0 * t12 + 0.2e1 * x0 * y * y0 - 0.1e1 * x0 * t17) * t20;
	const double t84 = t3 * t3;
	const double t103 = Ampl * t36 * t25 * (y * t4 - 0.2e1 * t67 * x0 + y * t9 - 0.1e1 * y0 * t4 + 0.2e1 * y0 * x * x0 - 0.1e1 * y0 * t9) * t22;
	const double t104 = Ampl * t29;
	const double t111 = t104 * t25 * (-0.2e1 * t3 + t12 - t40 + t17) / t84 / sigma_y;
	const double t112 = Ampl * t34;
	const double t121 = t112 * t36 * t45;
	const double t122 = Ampl * t41;

	hess[0][0] = 0.0e0;
	hess[0][1] = 0.0e0;
	hess[0][2] = 0.0e0;
	hess[0][3] = 0.0e0;
	hess[0][4] = 0.0e0;
	hess[0][5] = 0.0e0;
	hess[1][0] = 0.0e0;
	hess[1][1] = 0.0e0;
	hess[1][2] = t27;
	hess[1][3] = t31;
	hess[1][4] = t38;
	hess[1][5] = t45;
	hess[2][0] = 0.0e0;
	hess[2][1] = t27;
	hess[2][2] = t46 * (-0.1e1 * t11 + t4 - t33 + t9) / t49;
	hess[2][3] = t57;
	hess[2][4] = t64;
	hess[2][5] = t81;
	hess[3][0] = 0.0e0;
	hess[3][1] = t31;
	hess[3][2] = t57;
	hess[3][3] = t46 * (-0.1e1 * t3 + t12 - t40 + t17) / t84;
	hess[3][4] = t103;
	hess[3][5] = t111;
	hess[4][0] = 0.0e0;
	hess[4][1] = t38;
	hess[4][2] = t64;
	hess[4][3] = t103;
	hess[4][4] = t112 * t25 * (-0.3e1 * t11 + t4 - t33 + t9) / t49 / t11;
	hess[4][5] = t121;
	hess[5][0] = 0.0e0;
	hess[5][1] = t45;
	hess[5][2] = t81;
	hess[5][3] = t111;
	hess[5][4] = t121;
	hess[5][5] = t122 * t25 * (-0.3e1 * t3 + t12 - t40 + t17) / t84 / t3;
	grad[0] = 0.1e1;
	grad[1] = t25;
	grad[2] = t53 * t55;
	grad[3] = t104 * t25 * t22;
	grad[4] = t112 * t36 * t25;
	grad[5] = t122 * t43 * t25;
	func = Offset + Ampl * t25;
}

void GImage2DGaussFitter::UpdateGraphicsItem()
{
	QSizeF theSize(2 * m_SigmaX, 2 * m_SigmaY);
	QPointF theTopLeft = QPointF(m_X0, m_Y0) - 0.5 * QPointF(theSize.width(), theSize.height());
	QRectF elrect(theTopLeft, theSize);
	m_pEllipse->setRect(elrect);
}

void function_to_call_after_each_iteration(const real_1d_array &c, double func, void *ptr) 
{
	// is this a GImage2DGaussFitter
	GImage2DGaussFitter* pGaussFitter = (GImage2DGaussFitter*)(ptr);
	if(!pGaussFitter)
		return;
	if(pGaussFitter->m_FitMask[0])
		pGaussFitter->m_Offset.SetParamValue(c[0], false);
	if(pGaussFitter->m_FitMask[1])
		pGaussFitter->m_Ampl.SetParamValue(c[1], false);
	if(pGaussFitter->m_FitMask[2])
		pGaussFitter->m_X0.SetParamValue(c[2], false);
	if(pGaussFitter->m_FitMask[3])
		pGaussFitter->m_Y0.SetParamValue(c[3], false);
	if(pGaussFitter->m_FitMask[4])
		pGaussFitter->m_SigmaX.SetParamValue(c[4], false);
	if(pGaussFitter->m_FitMask[5])
		pGaussFitter->m_SigmaY.SetParamValue(c[5], false);

	QTimer::singleShot(0, pGaussFitter, SLOT(UpdateGraphicsItem()));
}

void GImage2DGaussFitter::InputImage(QImage imageIn )
{
return;
}

void GImage2DGaussFitter::ProcessImageAOIed(const GImageDouble & aoiImage)
{
	m_CurrentImageIn = aoiImage;
	start();
}

void GImage2DGaussFitter::run()
{
	int hei = m_CurrentImageIn.size().height();
	int wid = m_CurrentImageIn.size().width();

	m_IniOffset	= 0.0;
	m_IniAmpl	= 200;
	m_IniX0		= wid / 2;
	m_IniY0		= hei / 2;
	m_IniSigmaX	= wid / 4;
	m_IniSigmaY	= hei / 4;

	// sets the fitting mask of the optimizer
	QVector<bool> mask = m_Variables.ExtraParamBoolMask(fitFieldString);
	for(int i = 0; i < 6 ; i++) {
		m_FitMask[i] = mask[i];
	}

	IncrementCountProcessed();
 	Fit(m_CurrentImageIn, this);
}

void Fit( GImageDouble imageIn, GImage2DGaussFitter* ptr )
{
	QThread::currentThread()->setPriority(QThread::LowPriority);

	int Npix = imageIn.size().width() * imageIn.size().height();
	int hei = imageIn.size().height();
	int wid = imageIn.size().width();
	// the array of values
	GDoubleArray & zArray = imageIn.DoubleArray();
	// the array containing the coordinates of the points as described in the AlgLib documentation
	GDoubleArray x2Array(2 * Npix);
	int iTot = 0;
	for(int jLine = 0; jLine < hei; jLine++) {
		const uchar* scanL = imageIn.constScanLine(jLine);
		for(int iCol = 0; iCol < wid; iCol++) {
			x2Array[2 * iTot] = double(iCol);
			x2Array[2 * iTot + 1] = double(jLine);
			iTot++;
		}
	}
	// the array to set the weight of the point. For NaN and inf values, the weight is 0.0
	GDoubleArray wArray(Npix);
	for(int ind = 0; ind < Npix; ind++) {
		double & valPix = zArray[ind];
		if(qIsNaN(valPix) || qIsInf(valPix)) {
			zArray[ind] = 0.0; // put an acceptable value
			wArray[ind] = 0.0; // set the weigh to 0.0
		}
		else
			wArray[ind] = 1.0;
	}

	real_2d_array x;
	real_1d_array y;
	real_1d_array w;
	x.setcontent(Npix, 2, x2Array.constData());
	y.setcontent(Npix, zArray.constData());
	w.setcontent(Npix, wArray.constData());
	real_1d_array c;
	c.setlength(6);
	c[0] = ptr->m_FitMask[0] ? ptr->m_IniOffset	: ptr->m_Offset;
	c[1] = ptr->m_FitMask[1] ? ptr->m_IniAmpl	: ptr->m_Ampl;
	c[2] = ptr->m_FitMask[2] ? ptr->m_IniX0		: ptr->m_X0;
	c[3] = ptr->m_FitMask[3] ? ptr->m_IniY0		: ptr->m_Y0;
	c[4] = ptr->m_FitMask[4] ? ptr->m_IniSigmaX	: ptr->m_SigmaX;
	c[5] = ptr->m_FitMask[5] ? ptr->m_IniSigmaY	: ptr->m_SigmaY;

	double epsf = 0.0001;
	double epsx = 0.0001;
	ae_int_t maxits = 100;
	ae_int_t info;
	lsfitstate state;
	lsfitreport rep;
	double diffstep = 0.0001;

// STRANGE! fires "Warning: QObject::startTimer: timers cannot be started from another thread" 
// 	ptr->UpdateGraphicsItem();

	int whichOne = 2;
	switch (whichOne)
	{
	case 1:
		lsfitcreatewf(x, y, w, c, Npix, 2, 6, diffstep, state);
		lsfitsetcond(state, epsf, epsx, maxits);
		lsfitsetxrep(state, true);
		lsfitfit(state, Gaus2D_func, function_to_call_after_each_iteration, ptr);
		lsfitresults(state, info, c, rep);
		break;
	case 2:
		lsfitcreatewfg(x, y, w, c, Npix, 2, 6, false, state);
		lsfitsetcond(state, epsf, epsx, maxits);
		lsfitsetxrep(state, true);
		lsfitfit(state, Gaus2D_func, Gaus2D_grad, function_to_call_after_each_iteration, ptr);
		lsfitresults(state, info, c, rep);
		break;
	case 3:
		lsfitcreatewfg(x, y, w, c, Npix, 2, 6, true, state);
		lsfitsetcond(state, epsf, epsx, maxits);
		lsfitsetxrep(state, true);
		lsfitfit(state, Gaus2D_func, Gaus2D_grad, function_to_call_after_each_iteration, ptr);
		lsfitresults(state, info, c, rep);
		break;
	case 4:
		lsfitcreatewfgh(x, y, w, c, Npix, 2, 6, state);
		lsfitsetcond(state, epsf, epsx, maxits);
		lsfitsetxrep(state, true);
		lsfitfit(state, Gaus2D_func, Gaus2D_grad, Gaus2D_hess, function_to_call_after_each_iteration, ptr);
		lsfitresults(state, info, c, rep);
		break;
	}

	GVectorDouble finalValues(6);
	c[4] = qAbs(c[4]);
	c[5] = qAbs(c[5]);
	for(int i = 0; i < 6 ; i++) {	
		finalValues[i] = c[i];
	}
	QMetaObject::invokeMethod(ptr, "UpdateFinalResultValues", Qt::QueuedConnection, Q_ARG(GVectorDouble, finalValues));
}

void GImage2DGaussFitter::UpdateFinalResultValues( GVectorDouble finalValues ) 
{
	m_Variables.SetValues(finalValues, m_FitMask);
}