#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#if QT_VERSION < 0x050000
	#include <QSound>
#else
	#include <QSoundEffect>
#endif
#include <QGraphicsDropShadowEffect>
#include <QTranslator>

#include "QCountDown.h"
#include "QAppSettings.h"
#include "QLCDMouseListener.h"
#include "QEditableValue.h"

namespace Ui
{
	class MainWindow;
}

/**
 * Main window for Countdown
 * @author David Roussel
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

	private:
	/**
	 * The main window UI
	 */
	Ui::MainWindow * ui;

	/**
	 * the clock used to count down
	 */
	QCountDown * clock;

	/**
	 * Settings to store application parameters such as:
	 * 	- count down initialCount
	 * 	- bellSoundFilePath
	 * 	- tickSoundFilePath
	 * 	- soundOn status
	 * 	- styleIndex
	 * 	- language
	 */
	QAppSettings * settings;

	/**
	 * Application Icon (overrides settings in .pro file but this icon
	 * can then be automatically used in any "About" messagebox).
	 */
	QIcon appIcon;

	/**
	 * Is the count down currently running ?
	 * @note used to inhibit some functionalities while running, such as
	 * changing count initial value.
	 */
	bool running;

	/**
	 * Has count down ended ?
	 * @note used to handle simple click on the LCD panel in conjunction
	 * with #running to start/stop/continue count down or reset count down
	 * when it is finished.
	 */
	bool ended;

	/**
	 * currently running but paused
	 */
	bool paused;

	/**
	 * the sound played when count is done
	 */
#if QT_VERSION < 0x050000
	QSound * timeUpSound;
#else
	QSoundEffect * timeUpSound;
#endif
	/**
	 * The sound played each seconds
	 */
#if QT_VERSION < 0x050000
	QSound * tickSound;
#else
	QSoundEffect * tickSound;
#endif

	/**
	 * the current count
	 */
	int count;

	/**
	 * The number of digits used in the LCD display.
	 * Depends on the value of initial count, e.g. 15 (2 digits),
	 * 134 (3 digits)
	 */
	int lcdDigits;

	/**
	 * Is sound available on this platform
	 */
	bool soundAvailable;

	/**
	 * Is local sound currently on
	 */
	bool localSound;

	/**
	 * Is sound currently connected ?
	 * So we won't have to connect it again
	 */
	bool soundConnected;

	/**
	 * Palette of LCD panel to customize LCD look
	 */
	QPalette * palette;

	/**
	 * Drop shadow effect for LCD panel
	 */
	QGraphicsDropShadowEffect * effect;

	/**
	 * Mouse Listener to listen to mouse wheel and click in LCD panel
	 */
	QLCDMouseListener * mouseListener;

	/**
	 * The count value show/edit to put at the end of statusBar
	 */
	QEditableValue * countValueEdit;

	public:
	/**
	 * Main window constructor
	 * @param clock the clock used to count down
	 * @param settings application settings
	 * @param parent the parent object
	 * @pre clock & settings are assumed to be non NULL otherwise terrible
	 * things may happend (maybe the end of the world as we know it)
	 */
	explicit MainWindow(QCountDown * clock,
						QAppSettings * settings,
						QWidget * parent = nullptr);

	/**
	 * Main window destructor.
	 */
	~MainWindow() override;

	/**
	 * Change event overloading in order to retranslate the UI when a
	 * QEvent::LanguageChange occurs
	 * @param event the change event
	 */
	void changeEvent(QEvent * event) override;

	signals:
	/**
	 * Signal to send message to status bar
	 * @param message the message to send
	 * @param timeout the number of milliseconds the message should stay on
	 */
	void sendMessage(const QString & message, int timeout);

	/**
	 * Signal to start (or restart) the countdown
	 */
	void start();

	/**
	 * Signal to pause the countdown
	 */
	void stop();

	/**
	 * Signal to send new initial count to QCountDown
	 * @param value the new initial count
	 */
	void initialCountChanged(const int value);

	/**
	 * Signal sent when bell sound changes
	 * @param filePath the file path to new bell sound
	 */
	void bellSoundFilePathChanged(const QString & filePath);

	/**
	 * Signal emitted when bell sound should be resetted to default
	 */
	void bellSoundFilePathReset();

	/**
	 * Signal sent when tick sound changes
	 * @param filePath the file path to new tick sound
	 */
	void tickSoundFilePathChanged(const QString & filePath);

	/**
	 * Signal emitted when tick sound should be resetted to default
	 */
	void tickSoundFilePathReset();

	/**
	 * Signal sent when sound status changes
	 * @param status the new sound status
	 */
	void soundStatusChanged(const bool status);

	/**
	 * Signal sent when LCD style index changes
	 * @param index the new style index
	 */
	void lcdStyleIndexChanged(const uint index);

	/**
	 * Signal sent when toolbar style index changes
	 * @param index the new style index
	 */
	void toolbarStyleIndexChanged(const uint index);

	/**
	 * Signal sent when language changes
	 * @param locale the language locale
	 */
	void languageChanged(const QLocale & locale);

	public slots:
	/**
	 * Slot triggered to change initial countdown by delta.
	 * @note typically triggered by mouse events (scroll or swipe)
	 * @note this slot changes the current count only when countdown
	 * is not currently running
	 */
	void changeInitialCount(int delta);

	/**
	 * Slot triggered by mouse click to start/stop countdown or reset it
	 * when count down is finished.
	 */
	void runControl();

	/**
	 * Slot triggered when a threefinger left swipe is detected to reset the
	 * count at the end of count.
	 */
	void resetControl();

	private slots:
	/**
	 * Slot trigerred to set (not modify) initial countdown directly
	 * @param value the new count value to set
	 */
	void setInitialCount(int value);

	/**
	 * Slot trigerred to increment initial countdown
	 */
	void incrementInitialCount();

	/**
	 * Slot trigerred to decrement initial countdown
	 */
	void decrementInitialCount();

	/**
	 * Slot triggered at the end of the count down
	 */
	void end();

	/**
	 * Slot performed when start button is pushed (used with mac toolbar)
	 */
	void actionStart_triggered();

	/**
	 * Slot performed when start/pause action is triggered
	 * @param checked indicates if button toggles from on to off or off
	 * to on
	 */
	void on_actionStart_triggered(bool checked);

	/**
	 * Slot performed when count reset action is triggered
	 */
	void on_actionReset_triggered();

	/**
	 * Slot performed when quit action is triggered
	 */
	void on_actionQuit_triggered();

	/**
	 * Slot performed when about action is triggered
	 */
	void on_actionAbout_triggered();

	/**
	 * Slot performed when sound action is triggered (on or off)
	 * @param checked indicates if sound should be on or off
	 * @warning sound is on by default (when check is false)
	 */
	void on_actionSound_triggered(bool checked);

	/**
	 * Slot performed when tick sound selection action is triggered
	 */
	void on_actionTickSound_triggered();

	/**
	 * Slot performed when bell sound selection action is triggered
	 */
	void on_actionBellSound_triggered();

	/**
	 * Slot performed when resetting sounds to defaults
	 */
	void on_actionReset_Sounds_triggered();

	/**
	 * Slot performed when settting count directly with a QInputDialog box
	 */
	void on_actionSetCount_triggered();

	/**
	 * Slot performed when LCD style is selected
	 */
	void on_actionLCD_Style_triggered();

	/**
	 * Slot performed when LED style is selected
	 */
	void on_actionLED_Style_triggered();

	/**
	 * Slot performed when icons only are selected for the toolbar
	 */
	void on_actionIcons_Only_triggered();

	/**
	 * Slot performed when icons and text are slected for the toolbar
	 */
	void on_actionText_and_Icons_triggered();

	/**
	 * Slot performed when english language is selected
	 */
	void on_actionEnglish_triggered();

	/**
	 * Slot performed when french language is selected
	 */
	void on_actionFrench_triggered();

	private:
	/**
	 * Computes the number of digits required for a count value
	 * @param value the value of the count
	 * @return the number of digits for this value
	 */
	int nbDigits(const unsigned int value);

	/**
	 * Set local sound on/off
	 * @param value the new sound status
	 */
	void setupLocalSound(const bool value);

	/**
	 * Set LED style
	 * @param palette the palette to apply
	 * @param effect the effect to apply
	 */
	void setLEDStyle(QPalette * palette, QGraphicsDropShadowEffect * effect);

	/**
	 * Set LCD style
	 * @param palette the palette to apply
	 * @param effect the effect to apply
	 */
	void setLCDStyle(QPalette * palette, QGraphicsDropShadowEffect * effect);

	/**
	 * Set toolbar buttons style and update it
	 * @param index the style index:
	 *	- 0 icons only
	 *	- 1 icons and text below
	 */
	void setToolbarStyle(uint const index);

	/**
	 * Color Sigmoid interpolation from start value to end value to simulate
	 * drop shadow effect
	 * @param from start value
	 * @param to end value
	 * @param slope value [best between 12 and 20]
	 * @param delta interpolation parameter [varies from 0.0 to 1.0]
	 * @return the color correspondonding to delta interpolation parameter
	 */
	QColor sigmoidInterpolate(const QColor & from,
							  const QColor & to,
							  const qreal slope,
							  const qreal delta);
};

#endif // MAINWINDOW_H
