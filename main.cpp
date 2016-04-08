// Qt
#include <QApplication>
// Own
#include "mainwindow.h"
#include "qlogger.h"
#include "test.h"
#include "tools.h"

int main(int argc, char *argv[])
{
	QLogger::QLoggerManager::getInstance()->addDestination("log.txt", THREAD_ID, "main", QLogger::DebugLevel);
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	// TEST SERIALIZATION
	Test test;
	Tools::saveJsonDataInFile(test.serialize(), "test.json");
	// END TEST

	QLogger::QLog_Debug(THREAD_ID, "Entering in Qt event loop");	
	return a.exec();
}
