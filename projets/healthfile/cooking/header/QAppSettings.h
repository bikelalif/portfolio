#ifndef QAPPSETTINGS_H
#define QAPPSETTINGS_H

#include <QString>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QApplication>

/**
 * Class to load store and save current application preferences
 * This class makes use of the QSettings class to load and save these
 * preferences
 * @author David Roussel
 */
class QAppSettings : public QObject
{
	Q_OBJECT
	/**
	 * The initial count property
	 */
	Q_PROPERTY(int count READ getInitialCount WRITE setInitialCount)
	/**
	 * The sound status (on/off)
	 */
	Q_PROPERTY(bool sound READ isSoundOn WRITE setSoundOn)
	/**
	 * The display style index:
	 * 	- 0: LCD style
	 * 	- 1: LED style
	 */
	Q_PROPERTY(int style READ getLCDStyleIndex WRITE setLCDStyleIndex)
	/**
	 * The toolbar buttons style index:
	 * 	- 0: icons only
	 * 	- 1: text under icons
	 */
	Q_PROPERTY(int toolbar READ getToolbarStyleIndex WRITE setToolbarStyleIndex)
	/**
	 * The language to apply to application
	 */
	Q_PROPERTY(QLocale lang READ getLanguage WRITE setLanguage)
	/**
	 * Path to the "tick" sound file used to mark seconds
	 */
	Q_PROPERTY(QString tick_sound READ getTickSoundFilePath WRITE setTickSoundFilePath RESET resetTickSoundFilePath)
	/**
	 * Path to the "bell" sound file used to mark the end of count down
	 */
	Q_PROPERTY(QString time_up_sound READ getBellSoundFilePath WRITE setBellSoundFilePath RESET resetBellSoundFilePath)

	private:
		// --------------------------------------------------------------------
		// Settings constants
		// --------------------------------------------------------------------
		/**
		 * Organisation name
		 */
		static const QString organisationName;

		/**
		 * Application name
		 */
		static const QString applicationName;

		/**
		 * Default initial coutn down value
		 */
		static const int defaultCount;

		/**
		 * Default sound status
		 */
		static const bool defaultSoundStatus;

		/**
		 * Default LCD style index
		 */
		static const uint defaultLCDStyleIndex;

		/**
		 * Default toolbar style index
		 */
		static const uint defaultToolbarStyleIndex;

		/**
		 * Default tick sound file path
		 */
		static const QString defaultTickSoundFilePath;

		/**
		 * Default bell sound file path
		 */
		static const QString defaultTimeUpSoundFilePath;

		/**
		 * Default locale (system.locale)
		 */
		static const QLocale defaultLocale;

		// --------------------------------------------------------------------
		// Settings values
		// --------------------------------------------------------------------
		/**
		 * Cound down initial count
		 */
		int initialCount;

		/**
		 * Path to end of count sound file
		 */
		QString bellSoundFilePath;

		/**
		 * Path to tick sound file
		 */
		QString tickSoundFilePath;

		/**
		 * sound status (on or off)
		 */
		bool soundOn;

		/**
		 * LCD style index (0 = LCD, 1 = LED)
		 */
		uint lcdStyleIndex;

		/**
		 * Toolbar style index (0 = icons only, 1 = text and icons)
		 */
		uint toolbarStyleIndex;

		/**
		 * Locale for translating application
		 */
		QLocale language;

		/**
		 * The application (in order to apply translation on)
		 */
		const QApplication * app;

		/**
		 * The translator to change language
		 */
		QTranslator translator;

		/**
		 * Settings to be read and written from file or registry
		 */
		QSettings settings;

		/**
		 * Settings status (defines if settings can be read and/or written)
		 */
		QSettings::Status status;
	public:
		/**
		 * Default app settings constructor.
		 * Initialise preferences to default values and open settings from
		 * file or registry
		 * @param app the application (to apply translation on)
		 */
		QAppSettings(const QApplication * app);

		/**
		 * App settings destructor
		 */
		virtual ~QAppSettings() override;

		// --------------------------------------------------------------------
		// Operations
		// --------------------------------------------------------------------
		/**
		 * Load settings from #organisationName and #applicationName preference
		 * file (or registry, or whatever depending on QSettings specifics for
		 * this OS)
		 * @return true if settings have been correctly accessed
		 */
		bool load();

		/**
		 * Save current settings to file or registry or whatever QSettings
		 * specifics for this OS
		 */
		void save();

		// --------------------------------------------------------------------
		// Getters
		// --------------------------------------------------------------------
		/**
		 * Get current initial count
		 * @return the current initial count
		 */
		int getInitialCount() const;

		/**
		 * Get current Bell sound file path
		 * @return the current Bell sound file path
		 */
		QString getBellSoundFilePath() const;

		/**
		 * Get current tick sound file path
		 * @return the current tick sound file path
		 */
		QString getTickSoundFilePath() const;

		/**
		 * Get current sound status
		 * @return the current sound status
		 */
		bool isSoundOn() const;

		/**
		 * Get current style index
		 * @return the current style index
		 */
		uint getLCDStyleIndex() const;

		/**
		 * Get current toolbar buttons style index (icons only or text and
		 * icons)
		 * @return the current toolbar style index
		 */
		uint getToolbarStyleIndex() const;

		/**
		 * Get current language
		 * @return the current language
		 */
		QLocale getLanguage() const;

	public slots:
		// --------------------------------------------------------------------
		// Setters (slots)
		// --------------------------------------------------------------------
		/**
		 * Set new initial count
		 * @param initialCount the new initial count
		 */
		void setInitialCount(const int initialCount);

		/**
		 * Set new bell sound file path
		 * @param bellSoundFilePath the bell sound file path
		 */
		void setBellSoundFilePath(const QString & bellSoundFilePath);

		/**
		 * Reset bell sound file path to default #defaultTimeUpSoundFilePath
		 */
		void resetBellSoundFilePath();

		/**
		 * Set new tick sound file path
		 * @param tickSoundFilePath the new tick sound file path
		 */
		void setTickSoundFilePath(const QString & tickSoundFilePath);

		/**
		 * Reset tick sound file path to default #defaultTickSoundFilePath
		 */
		void resetTickSoundFilePath();

		/**
		 * Set new sound status
		 * @param soundOn the new tick sound file path
		 */
		void setSoundOn(const bool soundOn);

		/**
		 * Set new LCD style index
		 * @param styleIndex the new style index
		 */
		void setLCDStyleIndex(const uint styleIndex);

		/**
		 * Set new Toolbar style index
		 * @param styleIndex the new style index
		 */
		void setToolbarStyleIndex(const uint styleIndex);

		/**
		 * Set new language
		 * Loads translation file and apply translation on application
		 * @param language the new language
		 */
		void setLanguage(const QLocale & language);
};

#endif // QAPPSETTINGS_H
