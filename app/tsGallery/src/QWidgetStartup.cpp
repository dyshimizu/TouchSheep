#include "QWidgetStartup.h"

#include "TSListenerGallery.h"
#include "TSVideoDisplay.h"

#include <TSCore/TouchSheep.h>

#include <QVBoxLayout>
#include <QPushButton>

QWidgetStartup::QWidgetStartup(TouchSheep* ts){
	touchSheep = ts;
	
	initComponents();
	
	connect(tsListenerGallery, SIGNAL(newFrame(TSImage*)), tsVideoDisplay, SLOT(showFrame(TSImage*)));
	connect(qPushButtonMark, SIGNAL(clicked()), this, SLOT(qPushButtonMarkClick()));
}

void QWidgetStartup::initComponents(){
	tsListenerGallery = new TSListenerGallery();
	touchSheep->addTSListener(tsListenerGallery);
	
	qPushButtonMark = new QPushButton("Marcar");
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	tsVideoDisplay = new TSVideoDisplay();
	layout->addWidget(tsVideoDisplay);
	layout->addWidget(qPushButtonMark);
	
	setLayout(layout);
}

void QWidgetStartup::qPushButtonMarkClick(){
	touchSheep->addTSMarker(300, 220, 340, 260, 1);
}
