#include "GExpressionDisplay.h"

GExpressionDisplay::GExpressionDisplay( QObject* parent /*=NULL*/ )
	: GWebDisplay(parent)
{
}

GExpressionDisplay::~GExpressionDisplay()
{

}

// void GExpressionDisplay::ProcessWebPage(QWebPage* page)
// {
// 	QWebElement imgElement = page->mainFrame()->documentElement().findFirst("img[id=i_0100_1]");
// 	SetUrl( QUrl(imgElement.attribute("src")) );
// 	GWebDisplay::ProcessWebPage(page);
// }

void GExpressionDisplay::ExpressionChanged( const QString& expression )
{	
	// DO NOT MESS AROUND WITH THIS CODE! IT IS VERY TEMPERMENTAL.
	QString encodedExpression = QUrl::toPercentEncoding(expression, "*", "+/()[]{}");
	QByteArray encodedUrl = ("http://www.wolframalpha.com/input/?i=" + encodedExpression).toAscii();
	Load(QUrl::fromEncoded(encodedUrl));
}