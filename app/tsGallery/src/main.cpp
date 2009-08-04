#include "QWidgetStartup.h"

#include <TSCore/TouchSheep.h>

#include <QApplication>

int main(int argc, char **argv){
	QApplication app(argc, argv);
	
	TouchSheep *ts = new TouchSheep("video5.mpg", 30, 10, 256, 30);
	
	QWidgetStartup *qWidgetStartup = new QWidgetStartup(ts);
	
	qWidgetStartup->show();
	
	ts->start();
	
	app.exec();
}