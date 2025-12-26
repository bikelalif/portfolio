#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QDebug>

#include "QAppSettings.h"
#include "QCountDown.h"
#include "MainWindow.h"

/**
 * Setup the correct working directory in order to locate resources and files
 * in subdirectories such as sounds (located in sound/...)
 *	- if system is windows and programm have been generated in a debug
 *		or relase subdirectory, then move up one time
 *	- if system is macOS the real executable is located in
 *		CookingClock.app/Contents/MacOS/ subdirectory, so move up 3 times to get
 *		to the right working directory
 */
void setWorkingDirectory();

/**
 * Main program
 * @param argc argument count
 * @param argv arguments values
 * @return the QApplication result.
 */
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/*
	 * Set correct working directory to find resources
	 */
	setWorkingDirectory();

	/*
	 * Loads settings (if any, otherwise use default values defined in Settings)
	 */
	QAppSettings settings(&app);
	settings.load();

//	/*
//	 * Check main thread
//	 */
//	qDebug("%s thread = %ld",
//		   app.applicationName().toStdString().c_str(),
//		   (long unsigned int)QThread::currentThread());

	/*
	 * Creates and launch objects
	 */
	QCountDown * clock = new QCountDown(settings.getInitialCount(), &app);

	MainWindow w(clock, &settings);
	w.show();

	int returnValue = app.exec();

	/*
	 * Save settings
	 */
	settings.save();

	return returnValue;

	// when app is destroyed it will also destroy it's children : i.e. clock & settings
}

/*
 * Setup the correct working directory in order to locate resources
 * in subdirectories such as sounds (located in sound/...)
 *	- if system is windows and programm have been generated in a debug
 *		or relase subdirectory, then move up one time
 *	- if system is macOS the real executable is located in
 *		CookingClock.app/Contents/MacOS/ subdirectory, so move up 3 times to get
 *		to the right working directory
 */
void setWorkingDirectory()
{
	QDir dir(QCoreApplication::applicationDirPath());

	qDebug() << "Current directory name is " << dir.dirName();

	#if defined(Q_OS_WIN)
		if (dir.dirName().toLower() == "debug" ||
			dir.dirName().toLower() == "release")
		{
			dir.cdUp();
		}
	#elif defined(Q_OS_MACOS)
		if (dir.dirName() == "MacOS")
		{
			dir.cdUp();
			dir.cdUp();
			dir.cdUp();
		}
	#endif

	QDir::setCurrent(dir.absolutePath());
}
