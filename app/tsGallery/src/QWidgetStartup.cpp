#include "QWidgetStartup.h"

#include "TSListenerGallery.h"
#include "TSVideoDisplay.h"

#include <TSCore/TouchSheep.h>

#include <QVBoxLayout>

QWidgetStartup::QWidgetStartup(TouchSheep* ts){
	touchSheep = ts;
	
	initComponents();
	
	connect(tsListenerGallery, SIGNAL(newFrame(TSImage*)), tsVideoDisplay, SLOT(showFrame(TSImage*)));
}

void QWidgetStartup::initComponents(){
	tsListenerGallery = new TSListenerGallery();
	touchSheep->addTSListener(tsListenerGallery);
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	tsVideoDisplay = new TSVideoDisplay();
	layout->addWidget(tsVideoDisplay);
	
	setLayout(layout);
}