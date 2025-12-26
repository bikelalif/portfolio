#include <cmath>	// for log10
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QDebug>
#if QT_VERSION < 0x060000
	#include <QAudioDeviceInfo>
#else
	#include <QAudioDevice>
	#include <QMediaDevices>
#endif
#ifdef Q_OS_MACOS
#if QT_VERSION >= 0x050000 && QT_VERSION < 0x060000
		#include <QMacToolBar>
		#include <QMacToolBarItem>
	#endif
#endif

#include "QLCDMouseListener.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

/*
 * Main window constructor
 * @param clock the clock used to count down
 * @param settings application settings
 * @param parent the parent object
 * @pre clock & settings are assumed to be non NULL otherwise terrible
 * things may happend (maybe the end of the world as we know it)
 */
MainWindow::MainWindow(QCountDown * clock,
					   QAppSettings * settings,
					   QWidget * parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	clock(clock),
	settings(settings),
	appIcon(QString(":/icons/icons/clock-512.png")),
	running(false),
	ended(false),
	paused(false),
#if QT_VERSION < 0x050000
	timeUpSound(new QSound(this->settings->getBellSoundFilePath(), this)),
	tickSound(new QSound(this->settings->getTickSoundFilePath(), this)),
#else
	timeUpSound(new QSoundEffect(this)),
	tickSound(new QSoundEffect(this)),
#endif
	count(clock->getCount()), // or count(settings->getInitialCount())
	lcdDigits(nbDigits(static_cast<unsigned>(count))),
	soundAvailable(true), // rechecked later
	localSound(settings->isSoundOn()),
	soundConnected(false),
	palette(nullptr),
	// effect(new QGraphicsDropShadowEffect(this)),
	effect(nullptr),
	mouseListener(nullptr),
	countValueEdit(new QEditableValue(this,"",QEditableValue::INT,
				   QVariant::fromValue<int>(clock->getCount())))
{
	// ------------------------------------------------------------------------
	// Setup UI
	// ------------------------------------------------------------------------
	ui->setupUi(this);

	countValueEdit->setIcon(ui->actionSetCount->icon());
	ui->statusBar->addPermanentWidget(countValueEdit);

#if QT_VERSION >= 0x050000
	timeUpSound->setSource(
		QUrl::fromLocalFile(this->settings->getBellSoundFilePath()));
	tickSound->setSource(
		QUrl::fromLocalFile(this->settings->getTickSoundFilePath()));
#endif

	// ------------------------------------------------------------------------
	// Setup window icon (overrides settings in .pro files, but this icon can
	// then be automatically used in any "About" Messagebox)
	// ------------------------------------------------------------------------
	if (!appIcon.isNull())
	{
		setWindowIcon(appIcon);
	}

// Doesn't work yet
//#ifdef Q_OS_MACOS
//	#if QT_VERSION >= 0x050000
//	// Use Qt Mac extras for native toolbar with Qt 5 (
//	QMacToolBar *toolBar = new QMacToolBar(this);
//	QMacToolBarItem *toolBarItem = toolBar->addItem(ui->actionStart->icon(),
//													ui->actionStart->text());
//	connect(toolBarItem, SIGNAL(activated()), this, SLOT(actionStart_triggered()));

//	this->window()->winId(); // create window->windowhandle()
//	toolBar->attachToWindow(this->window()->windowHandle());
//	#endif
//#endif
	// ------------------------------------------------------------------------
	// Signals/slots connections
	// ------------------------------------------------------------------------
	// connects UI and clock
	connect(this, SIGNAL(start()), clock, SLOT(start()));
	connect(this, SIGNAL(stop()), clock, SLOT(stop()));
	connect(ui->actionReset, SIGNAL(triggered()), clock, SLOT(reset()));

	connect(ui->actionUp, SIGNAL(triggered()),
			this, SLOT(incrementInitialCount()));

	connect(ui->actionDown, SIGNAL(triggered()),
			this, SLOT(decrementInitialCount()));

	connect(countValueEdit, SIGNAL(intValueChanged(int)),
			this, SLOT(setInitialCount(int)));

	connect(this, SIGNAL(initialCountChanged(int)),
			clock, SLOT(setCount(int)));
	connect(this, SIGNAL(initialCountChanged(int)),
			countValueEdit, SLOT(setIntValue(int)));

	connect(clock, SIGNAL(secondChanged(int)),
			ui->lcdNumber, SLOT(display(int)));
	connect(clock, SIGNAL(timeIsUp()), this, SLOT(end()));

	connect(this, SIGNAL(sendMessage(QString,int)), ui->statusBar,
			SLOT(showMessage(QString,int)));

	// connect to settings before using it
	connect(this, SIGNAL(initialCountChanged(int)),
			settings, SLOT(setInitialCount(int)));

	connect(this, SIGNAL(bellSoundFilePathChanged(QString)),
			settings, SLOT(setBellSoundFilePath(QString)));

	connect(this, SIGNAL(bellSoundFilePathReset()),
			settings, SLOT(resetBellSoundFilePath()));

	connect(this, SIGNAL(tickSoundFilePathChanged(QString)),
			settings, SLOT(setTickSoundFilePath(QString)));

	connect(this, SIGNAL(tickSoundFilePathReset()),
			settings, SLOT(resetTickSoundFilePath()));

	connect(this, SIGNAL(soundStatusChanged(bool)),
			settings, SLOT(setSoundOn(bool)));

	connect(this, SIGNAL(lcdStyleIndexChanged(uint)),
			settings, SLOT(setLCDStyleIndex(uint)));

	connect(this, SIGNAL(toolbarStyleIndexChanged(uint)),
			settings, SLOT(setToolbarStyleIndex(uint)));

	connect(this, SIGNAL(languageChanged(QLocale)),
			settings, SLOT(setLanguage(QLocale)));

	// ------------------------------------------------------------------------
	// Setting drop shadow effect on lcd
	// ------------------------------------------------------------------------

	effect = new QGraphicsDropShadowEffect(ui->lcdNumber);

#ifdef Q_WS_MAC
	/*
	 * The Qt::WA_PaintOutsidePaintEvent is supposed to have no effect on
	 * Mac OS, but the program crashes with QT4 if you don't set this true
	 * on Mac OS X
	 */
	setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
#endif

	ui->lcdNumber->setGraphicsEffect(effect);

	// ------------------------------------------------------------------------
	// Setting lcd background palette
	// ------------------------------------------------------------------------
	palette = new QPalette(ui->centralWidget->palette());

	switch (settings->getLCDStyleIndex())
	{
		case 1:
			setLEDStyle(palette, effect);
			break;
		case 0:
		default:
			setLCDStyle(palette, effect);
			break;
	}

	ui->centralWidget->setPalette(*palette);
	ui->centralWidget->setAutoFillBackground(true);

	// ------------------------------------------------------------------------
	// Setting toolbar style
	// ------------------------------------------------------------------------
	switch(settings->getToolbarStyleIndex())
	{
		case 1:
			ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
			break;
		case 0:
		default:
			ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
			break;
	}

	// ------------------------------------------------------------------------
	// Setup sound (if available)
	// ------------------------------------------------------------------------
#if QT_VERSION < 0x050000
	soundAvailable = QSound::isAvailable();
#else
	#if QT_VERSION < 0x060000
		soundAvailable = !QAudioDeviceInfo::defaultOutputDevice().isNull();
	#else // QT_VERSION >= 0x060000
		soundAvailable = !QAudioDevice(QMediaDevices::defaultAudioOutput()).isNull();
	#endif
#endif

	if (!soundAvailable)
	{
		emit soundStatusChanged(false);
		ui->actionSound->setEnabled(false);
	}

	if (!settings->isSoundOn())
	{
		ui->actionSound->setChecked(true);
	}

	// ------------------------------------------------------------------------
	// Setup widgets
	// ------------------------------------------------------------------------
	setWindowTitle(tr("Cooking Clock", "Window title"));

	ui->lcdNumber->setDigitCount(lcdDigits);
	ui->lcdNumber->display(count);

	// ------------------------------------------------------------------------
	// setup mouse listener for lcdNumber
	//	- mouse click starts/stops the count by triggering actionStart
	//	- mouse wheel adjusts the initial count (when count is not running)
	// ------------------------------------------------------------------------
	mouseListener = new QLCDMouseListener(QLCDMouseListener::defaultScaleFactor,
										  this);
	ui->lcdNumber->setAttribute(Qt::WA_AcceptTouchEvents);
	ui->lcdNumber->installEventFilter(mouseListener);
	connect(mouseListener, SIGNAL(sendClick()), this, SLOT(runControl()));
	connect(mouseListener, SIGNAL(sendDelta(int)),
			this, SLOT(changeInitialCount(int)));
	connect(mouseListener, SIGNAL(sendSwipeLeft()), this, SLOT(resetControl()));
}

/*
 * Main window destructor.
 */
MainWindow::~MainWindow()
{
	/*
	 * auto released resources with parenting
	 *	- timeUpSound
	 *	- tickSound
	 *	- effect
	 *	- mouseListener
	 */

	// release resources
	delete ui;
	delete palette;
}

/*
 * Change event overloading in order to retranslate the UI when a
 * QEvent::LanguageChange occurs
 * @param event the change event
 */
void MainWindow::changeEvent(QEvent * event)
{
	// qDebug() << "changeEvent(...)";
	if (event->type() == QEvent::LanguageChange)
	{
		ui->retranslateUi(this);
	}

	// regular event processing
	emit QMainWindow::changeEvent(event);
}


/*
 * Slot trigerred to increment or decrement initial countdown.
 * @note this slot changes the current count only when countdown
 * is not currently running
 */
void MainWindow::changeInitialCount(int delta)
{
	if (!running)
	{
		int newCount = count + delta;
		if (newCount > QCountDown::minCount && newCount < QCountDown::maxCount)
		{
			count = newCount;
			lcdDigits = nbDigits(static_cast<unsigned>(count));
			if (lcdDigits != ui->lcdNumber->digitCount())
			{
				ui->lcdNumber->setDigitCount(lcdDigits);
			}
		}
		emit initialCountChanged(count);
	}
}

/*
 * Slot triggered by mouse click to start/stop countdown
 * [or reset it when count down is finished]
 */
void MainWindow::runControl()
{
	if (!ended)
	{
		ui->actionStart->trigger();
	}
//	else // ended
//	{
//		ui->actionReset->trigger();
//	}
}

/*
 * Slot triggered when a threefinger left swipe is detected to reset the
 * count at the end of count.
 */
void MainWindow::resetControl()
{
	if (ended || paused)
	{
		ui->actionReset->trigger();
	}
}

/*
 * Slot trigerred to set (not modify) initial countdown directly
 * @param value the new count value to set
 */
void MainWindow::setInitialCount(int value)
{
	if (!running)
	{
		if (value > QCountDown::minCount && value < QCountDown::maxCount)
		{
			count = value;
			lcdDigits = nbDigits(static_cast<unsigned>(count));
			if (lcdDigits != ui->lcdNumber->digitCount())
			{
				ui->lcdNumber->setDigitCount(lcdDigits);
			}
		}
		emit initialCountChanged(count);
	}
}


/*
 * Slot trigerred to increment initial countdown
 */
void MainWindow::incrementInitialCount()
{
	if (count < QCountDown::maxCount)
	{
		count++;
		lcdDigits = nbDigits(static_cast<unsigned>(count));
		if (lcdDigits != ui->lcdNumber->digitCount())
		{
			ui->lcdNumber->setDigitCount(lcdDigits);
		}
	}
	emit initialCountChanged(count);
}

/*
 * Slot trigerred to decrement initial countdown
 */
void MainWindow::decrementInitialCount()
{
	if (count > QCountDown::minCount)
	{
		count--;
		lcdDigits = nbDigits(static_cast<unsigned>(count));
		if (lcdDigits != ui->lcdNumber->digitCount())
		{
			ui->lcdNumber->setDigitCount(lcdDigits);
		}
	}
	emit initialCountChanged(count);
}

/*
 * Slot triggered at the end of the count down
 */
void MainWindow::end()
{
	ended = true;

	ui->actionStart->setChecked(false);
	ui->actionStart->setEnabled(false);
	ui->actionReset->setEnabled(true);

	emit sendMessage(tr("time's up"), 5000);

	// bounce/blink the application icon in the dock/taskbar when the
	// application is not front window at the time of the end of count down
	QApplication::alert(this);
}


/*
 * Slot performed when start button is pushed (used with mac toolbar)
 */
void MainWindow::actionStart_triggered()
{
	running = true;
	paused = false;
	setupLocalSound(localSound);
	ui->actionUp->setEnabled(false);
	ui->actionDown->setEnabled(false);
	ui->actionSetCount->setEnabled(false);
	emit start();
}

/*
 * Slot performed when start/pause action is triggered
 * @param checked indicates if button toggles from on to off or off
 * to on
 */
void MainWindow::on_actionStart_triggered(bool checked)
{
	if (checked)
	{
		running = true;
		paused = false;
		setupLocalSound(localSound);
		ui->actionUp->setEnabled(false);
		ui->actionDown->setEnabled(false);
		ui->actionSetCount->setEnabled(false);
		emit start();
	}
	else
	{
		if (running)
		{
			paused = true;
		}
		emit stop();
	}
}

/*
 * Slot performed when count reset action is triggered
 */
void MainWindow::on_actionReset_triggered()
{
	running = false;
	ended = false;
	paused = false;

	setupLocalSound(false);
}

/*
 * Slot performed when quit action is triggered
 */
void MainWindow::on_actionQuit_triggered()
{
	clock->quit();
	close();
}

/*
 * Slot performed when about action is triggered
 */
void MainWindow::on_actionAbout_triggered()
{
	/*
	 * Icons used in this application comes from VisualPharm and are free
	 * to use as long as the "About dialog" contains credits and a link
	 * to the visualpharm website
	 */
	QMessageBox::about(
		this,
		tr("About"),
		tr("Cooking Clock v2.1<br>by <a "
		   "href=\"mailto:david.roussel@ensiie.fr?subject=About%20Cooking%"
		   "20Clock%20v2.0\">David Roussel</a><br>A simple timer "
		   "application<br><br>Icons by <a "
		   "href=\"http://www.visualpharm.com/\">visualpharm</a>"));
}

/*
 * Slot performed when sound action is triggered (on or off)
 * @param checked indicates if sound should be on or off
 * @warning sound is on by default (when check is false)
 */
void MainWindow::on_actionSound_triggered(bool checked)
{
	localSound = !checked;
	setupLocalSound(localSound);
	emit soundStatusChanged(localSound);
}

/*
 * Slot performed when tick sound selection action is triggered
 */
void MainWindow::on_actionTickSound_triggered()
{
	if (soundAvailable)
	{
		if (localSound && soundConnected)
		{
			disconnect(clock, SIGNAL(secondChanged(int)),
					   tickSound, SLOT(play()));
		}

		QFileInfo currentFileInfo(settings->getTickSoundFilePath());
		QString fileName = QFileDialog::getOpenFileName(this,
				 tr("Open Tick Sound"), currentFileInfo.absolutePath(),
				 tr("Sound Files (*.aiff *.wav)"));

		if (fileName.length() > 0)
		{
			emit tickSoundFilePathChanged(fileName);
			delete tickSound;
#if QT_VERSION < 0x050000
			tickSound = new QSound(fileName, this);
#else
			tickSound = new QSoundEffect(this);
			tickSound->setSource(QUrl::fromLocalFile(fileName));
#endif
			if (localSound && soundConnected)
			{
				connect(clock, SIGNAL(secondChanged(int)),
						tickSound, SLOT(play()));
			}
		}
	}
}

/*
 * Slot performed when bell sound selection action is triggered
 */
void MainWindow::on_actionBellSound_triggered()
{
	if (soundAvailable)
	{
		if (localSound && soundConnected)
		{
			disconnect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
		}

		QFileInfo currentFileInfo(settings->getBellSoundFilePath());
		QString fileName = QFileDialog::getOpenFileName(this,
				 tr("Open Bell Sound"), currentFileInfo.absolutePath(),
				 tr("Sound Files (*.aiff *.wav)"));

		if (fileName.length() > 0)
		{
			emit bellSoundFilePathChanged(fileName);
			delete timeUpSound;
#if QT_VERSION < 0x050000
			timeUpSound = new QSound(fileName, this);
#else
			timeUpSound = new QSoundEffect(this);
			timeUpSound->setSource(QUrl::fromLocalFile(fileName));
#endif
			if (localSound && soundConnected)
			{
				connect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
			}
		}
	}
}

/*
 * Slot performed when resetting sounds to defaults
 */
void MainWindow::on_actionReset_Sounds_triggered()
{
	QMessageBox confirmDialog(QMessageBox::Question,
							  tr("Reset sounds to default"),
							  tr("Are you sure you want to reset sounds to defaults ?"),
							  QMessageBox::Ok | QMessageBox::Cancel,
							  this,
							  Qt::Sheet);

	confirmDialog.setWindowModality(Qt::WindowModal);

	int result = confirmDialog.exec();

	if (result == QMessageBox::Ok)
	{
		if (localSound && soundConnected)
		{
			disconnect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
			disconnect(clock, SIGNAL(secondChanged(int)), tickSound, SLOT(play()));
		}

		emit bellSoundFilePathReset();
		emit tickSoundFilePathReset();

		delete timeUpSound;
		delete tickSound;

#if QT_VERSION < 0x050000
		timeUpSound = new QSound(settings->getBellSoundFilePath(), this);
		tickSound = new QSound(settings->getTickSoundFilePath(), this);
#else
		timeUpSound = new QSoundEffect(this);
		timeUpSound->setSource(QUrl::fromLocalFile(settings->getBellSoundFilePath()));
		tickSound = new QSoundEffect(this);
		tickSound->setSource(QUrl::fromLocalFile(settings->getTickSoundFilePath()));
#endif
		if (localSound && soundConnected)
		{
			connect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
			connect(clock, SIGNAL(secondChanged(int)), tickSound, SLOT(play()));
		}
	}
}

/*
 * Slot performed when settting count directly with a QInputDialog box
 */
void MainWindow::on_actionSetCount_triggered()
{
	QInputDialog valueDialog(this, Qt::Sheet);
	valueDialog.setWindowModality(Qt::WindowModal);
	valueDialog.setInputMode(QInputDialog::IntInput);
	valueDialog.setIntMinimum(QCountDown::minCount);
	valueDialog.setIntMaximum(QCountDown::maxCount);
	valueDialog.setIntValue(clock->getCount());
	valueDialog.setIntStep(1);
	valueDialog.setLabelText(tr("count down value"));
	valueDialog.setOkButtonText(tr("OK"));
	valueDialog.setCancelButtonText(tr("Cancel"));

	int result = valueDialog.exec();

	if (result == QDialog::Accepted)
	{
		count = valueDialog.intValue();
		lcdDigits = nbDigits(static_cast<unsigned>(count));
		if (lcdDigits != ui->lcdNumber->digitCount())
		{
			ui->lcdNumber->setDigitCount(lcdDigits);
		}

		emit initialCountChanged(count);
	}
}

/*
 * Slot performed when LCD style is selected
 */
void MainWindow::on_actionLCD_Style_triggered()
{
	setLCDStyle(palette, effect);
	ui->centralWidget->setPalette(*palette);
}

/*
 * Slot performed whe LED style is selected
 */
void MainWindow::on_actionLED_Style_triggered()
{
	setLEDStyle(palette, effect);
	ui->centralWidget->setPalette(*palette);
}

/*
 * Slot performed when icons only are selected for the toolbar
 */
void MainWindow::on_actionIcons_Only_triggered()
{
	setToolbarStyle(0);
}

/*
 * Slot performed when icons and text are slected for the toolbar
 */
void MainWindow::on_actionText_and_Icons_triggered()
{
	setToolbarStyle(1);
}

/*
 * Slot performed when english language is selected
 */
void MainWindow::on_actionEnglish_triggered()
{
	// QLocale locale(QLocale::English);
	emit languageChanged(QLocale(QLocale::English));
}

/*
 * Slot performed when french language is selected
 */
void MainWindow::on_actionFrench_triggered()
{
//	QLocale locale(QLocale::French);
	emit languageChanged(QLocale(QLocale::French));
}

/*
 * Computes the number of digits required for a count value
 * @param value the value of the count
 * @return the number of digits for this value
 */
int MainWindow::nbDigits(const unsigned int value)
{
	return (value > 0 ? static_cast<int>(log10(static_cast<double>(value))) + 1 : 1);
}

/*
 * Set sound on/off
 * @param value the new sound status
 */
void MainWindow::setupLocalSound(const bool value)
{
	if (soundAvailable)
	{
		if (value)
		{
			if (!soundConnected)
			{
				soundConnected = connect(clock, SIGNAL(secondChanged(int)),
										 tickSound, SLOT(play()));
				connect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
			}
		}
		else
		{
			if (soundConnected)
			{
				soundConnected = !disconnect(clock, SIGNAL(secondChanged(int)),
											 tickSound, SLOT(play()));
				disconnect(clock, SIGNAL(timeIsUp()), timeUpSound, SLOT(play()));
			}
		}
	}
	else
	{
		qDebug("Sorry, no sound availaible on your platform");
	}
}

/*
 * Set LCD style
 * @param palette the palette to apply
 * @param effect the effect to apply
 */
void MainWindow::setLCDStyle(QPalette * palette,
							 QGraphicsDropShadowEffect * effect)
{
	qreal offset = 10.0;
	qreal radius = 2.0 * offset;
	qreal slope = 12.0;
#ifdef Q_OS_WIN
	// Blueish colors from menu bars
	QColor startColor(165, 170, 185); // darken by shadow
	QColor endColor(227, 235, 255); // full color
#else
	// Greenish colors from Mac OS calculator
	QColor startColor(137, 140, 127); // darken by shadow
	QColor endColor(203, 208, 183); // full color
#endif

	/*
	 * LCD colors
	 */
	if (palette != nullptr)
	{
//		palette->setBrush(QPalette::Window,
//						  QBrush(QColor::fromRgba(qRgba(203, 208, 183, 255))));
		QLinearGradient gradient(0.0, 0.0, 0.0, radius);
		for (qreal x = 0.0; x < 1.0; x+=1.0/radius)
		{
			gradient.setColorAt(x, sigmoidInterpolate(startColor,
													  endColor,
													  slope,
													  x));
		}
		palette->setBrush(QPalette::Window, QBrush(gradient));

		palette->setBrush(QPalette::WindowText,
						  QBrush(QColor::fromRgba(qRgba(0, 0, 0, 180))));
	}
	else
	{
		qDebug() << "setLCDStyle : Null palette";
	}

	/*
	 * Drop Shadow effect on LCD numbers
	 */
	if (effect != nullptr)
	{
		effect->setBlurRadius(radius);
		effect->setXOffset(2.0);
		effect->setYOffset(offset);
		effect->setColor(QColor::fromRgb(63, 63, 63, 180));
	}
	else
	{
		qDebug() << "setLCDStyle : Null effect";
	}

	emit lcdStyleIndexChanged(0);
}

/*
 * Set LED style
 * @param palette the palette to apply
 * @param effect the effect to apply
 */
void MainWindow::setLEDStyle(QPalette * palette,
							 QGraphicsDropShadowEffect * effect)
{
	/*
	 * LED colors
	 */
	if (palette != nullptr)
	{
//		palette->setBrush(QPalette::Window,
//						  QBrush(QColor::fromRgba(qRgba(0, 0, 0, 255))));
		QLinearGradient gradient(0.0, 0.0, 0.0, 20.0);
		gradient.setColorAt(0.0,  QColor::fromRgb(180, 180, 180));
		gradient.setColorAt(1.0, QColor::fromRgb(0, 0, 0));
		palette->setBrush(QPalette::Window, QBrush(gradient));
		palette->setBrush(QPalette::WindowText,
						  QBrush(QColor::fromRgba(qRgba(255, 0, 0, 255))));
	}

	/*
	 * Glow effect on LED numbers
	 */
	if (effect != nullptr)
	{
		effect->setBlurRadius(40);
		effect->setXOffset(0.0);
		effect->setYOffset(0.0);
		effect->setColor(QColor::fromRgb(192, 96, 96, 255)); // 221
	}

	emit lcdStyleIndexChanged(1);
}

/*
 * Set toolbar buttons style and update it
 * @param index the style index:
 *	- 0 icons only
 *	- 1 icons and text below
 */
void MainWindow::setToolbarStyle(uint const index)
{
	switch(index)
	{
		case 1:
			ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
			break;
		case 0:
		default:
			ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
			break;
	}

	// updates the whole window since toolbar size might have changed
	ui->mainToolBar->updateGeometry();
	updateGeometry();

	if (settings->getToolbarStyleIndex() != index)
	{
		emit toolbarStyleIndexChanged(index);
	}
}

/*
 * Color Sigmoid interpolation from start value to end value
 * @param from start value
 * @param to end value
 * @param slope value [best between 12 and 20]
 * @param delta interpolation parameter [varies from 0.0 to 1.0]
 * @return the color correspondonding to delta interpolation parameter
 */
QColor MainWindow::sigmoidInterpolate(const QColor & from,
									  const QColor & to,
									  const qreal slope,
									  const qreal delta )
{
	// Calculate interpolator value using sigmoid function.
	qreal sigmoid = 1.0 / (1.0 + exp(-slope * (delta - 0.5)));

	// Calculate resultant interpolation.
	return QColor::fromRgbF((from.redF() * (1.0 - sigmoid)) +
							(to.redF() * sigmoid),
							(from.greenF() * (1.0 - sigmoid)) +
							(to.greenF() * sigmoid),
							(from.blueF() * (1.0 - sigmoid)) +
							(to.blueF() * sigmoid));
}
