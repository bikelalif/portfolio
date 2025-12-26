#include <QDebug>

#include "QAppSettings.h"

// --------------------------------------------------------------------
// Settings constants
// --------------------------------------------------------------------
/*
 * Organisation name
 */
const QString QAppSettings::organisationName("ensiie.fr");

/*
 * Application name
 */
const QString QAppSettings::applicationName("CookingClock");

/*
 * Default initial coutn down value
 */
const int QAppSettings::defaultCount(10);

/*
 * Default sound status
 */
const bool QAppSettings::defaultSoundStatus(true);

/*
 * Default LCD style index
 */
const uint QAppSettings::defaultLCDStyleIndex(0);

/*
 * Default toolbar style index
 */
const uint QAppSettings::defaultToolbarStyleIndex(0);


/*
 * Default tick sound file path
 */
const QString QAppSettings::defaultTickSoundFilePath(":/sounds/sounds/Tink.wav");

/*
 * Default bell sound file path
 */
const QString QAppSettings::defaultTimeUpSoundFilePath(":/sounds/sounds/Glass.wav");

/*
 * Default locale (system.locale)
 */
const QLocale QAppSettings::defaultLocale(QLocale::system());

/*
 * Default app settings constructor.
 * Initialise preferences to default values and open settings from
 * file or registry
 */
QAppSettings::QAppSettings(const QApplication * app) :
	QObject(),
	initialCount(defaultCount),
	bellSoundFilePath(defaultTimeUpSoundFilePath),
	tickSoundFilePath(defaultTickSoundFilePath),
	soundOn(defaultSoundStatus),
	lcdStyleIndex(defaultLCDStyleIndex),
	toolbarStyleIndex(defaultToolbarStyleIndex),
	language(),
	app(app),
	translator(),
	settings(organisationName, applicationName)
{
	setLanguage(defaultLocale);
	status = settings.status();
}

/*
 * App settings destructor
 */
QAppSettings::~QAppSettings()
{
	bellSoundFilePath.clear();
	tickSoundFilePath.clear();
}

// --------------------------------------------------------------------
// Operations
// --------------------------------------------------------------------
/*
 * Load settings from #organisationName and #applicationName preference
 * file (or registry, or whatever depending on QSettings specifics for
 * this OS)
 * @return true if settings have been correctly accessed
 */
bool QAppSettings::load()
{
	if (status == QSettings::NoError)
	{
		// Loads locale first in order to set language for tr(...)
		QString defaultLocaleStr = defaultLocale.name().section('_', 0, 0);
		QString localeStr = settings.value("lang",
										   QVariant(defaultLocaleStr)).toString();
		if (localeStr != defaultLocaleStr)
		{
			setLanguage(QLocale(localeStr));
		}
		qDebug() << tr("Settings: locale is %1").arg(localeStr);


		bool check = true;
		initialCount = settings.value("count",
									  QVariant(defaultCount)).toInt(&check);
		if (!check)
		{
			qDebug() << tr("Settings: unable to convert count value to int");
			initialCount = defaultCount;
		}
		else
		{
			qDebug() << tr("Settings: count is %1").arg(initialCount);
		}

		bellSoundFilePath =
				settings.value("time_up_sound",
							   defaultTimeUpSoundFilePath).toString();
		qDebug() << tr("Settings: time up sound path is %1").arg(
						bellSoundFilePath.toStdString().c_str());

		tickSoundFilePath =
				settings.value("tick_sound",
							   defaultTickSoundFilePath).toString();
		qDebug() << tr("Settings: tick sound path is %1").arg(
						tickSoundFilePath.toStdString().c_str());

		soundOn = settings.value("sound",
								 QVariant(defaultSoundStatus)).toBool();
		qDebug()<< tr("Settings: sound is %1").arg(
					   soundOn ? tr("on","adjective") :
								 tr("off","adjective"));

		lcdStyleIndex = settings.value("style",
									QVariant(defaultLCDStyleIndex)).toUInt();
		qDebug() << tr("Settings: style index is %1").arg(lcdStyleIndex);

		toolbarStyleIndex = settings.value("toolbar",
									QVariant(defaultToolbarStyleIndex)).toUInt();

		return true;
	}
	else
	{
		qDebug() << tr("Error reading settings");
		return false;
	}
}

/*
 * Save current settings to file or registry or whatever QSettings
 * specifics for this OS
 */
void QAppSettings::save()
{
	qDebug() << tr("Settings: Saving initial count %1").arg(initialCount);
	settings.setValue("count", initialCount);

	qDebug() << tr("Settings: Saving sound state %1").arg(
					soundOn ? tr("on","adjective") :
							  tr("off","adjective"));
	settings.setValue("sound", soundOn);

	qDebug() << tr("Settings: Saving bell sound file path %1").arg(bellSoundFilePath);
	settings.setValue("time_up_sound", bellSoundFilePath);

	qDebug() << tr("Settings: Saving tick sound file path %1").arg(tickSoundFilePath);
	settings.setValue("tick_sound", tickSoundFilePath);

	qDebug() << tr("Settings: Saving LCD style index %1").arg(lcdStyleIndex);
	settings.setValue("style", lcdStyleIndex);

	qDebug() << tr("Settings: Saving Toolbar style index %1").arg(toolbarStyleIndex);
	settings.setValue("toolbar", toolbarStyleIndex);

	qDebug() << tr("Settings: Saving locale %1").arg(language.name());
	settings.setValue("lang", language.name());
}

// --------------------------------------------------------------------
// Getters
// --------------------------------------------------------------------
/*
 * Get current initial count
 * @return the current initial count
 */
int QAppSettings::getInitialCount() const
{
	return initialCount;
}

/*
 * Get current Bell sound file path
 * @return the current Bell sound file path
 */
QString QAppSettings::getBellSoundFilePath() const
{
	return bellSoundFilePath;
}

/*
 * Get current tick sound file path
 * @return the current tick sound file path
 */
QString QAppSettings::getTickSoundFilePath() const
{
	return tickSoundFilePath;
}

/*
 * Get current sound status
 * @return the current sound status
 */
bool QAppSettings::isSoundOn() const
{
	return soundOn;
}

/*
 * Get current style index
 * @return the current style index
 */
uint QAppSettings::getLCDStyleIndex() const
{
	return lcdStyleIndex;
}

/*
 * Get current toolbar buttons style index (icons only or text and
 * icons)
 * @return the current toolbar style index
 */
uint QAppSettings::getToolbarStyleIndex() const
{
	return toolbarStyleIndex;
}


/*
 * Get current language
 * @return the current language
 */
QLocale QAppSettings::getLanguage() const
{
	return language;
}

// --------------------------------------------------------------------
// Setters (slots)
// --------------------------------------------------------------------

/*
 * Set new initial count
 * @param initialCount the new initial count
 */
void QAppSettings::setInitialCount(const int initialCount)
{
	this->initialCount = initialCount;
}

/*
 * Set new bell sound file path
 * @param bellSoundFilePath the bell sound file path
 */
void QAppSettings::setBellSoundFilePath(const QString & bellSoundFilePath)
{
	this->bellSoundFilePath = bellSoundFilePath;
}

/*
 * Reset bell sound file path to default #defaultTimeUpSoundFilePath
 */
void QAppSettings::resetBellSoundFilePath()
{
	bellSoundFilePath = defaultTimeUpSoundFilePath;
}


/*
 * Set new tick sound file path
 * @param tickSoundFilePath the new tick sound file path
 */
void QAppSettings::setTickSoundFilePath(const QString & tickSoundFilePath)
{
	this->tickSoundFilePath = tickSoundFilePath;
}

/**
 * Reset tick sound file path to default #defaultTickSoundFilePath
 */
void QAppSettings::resetTickSoundFilePath()
{
	tickSoundFilePath = defaultTickSoundFilePath;
}


/*
 * Set new sound status
 * @param soundOn the new tick sound file path
 */
void QAppSettings::setSoundOn(const bool soundOn)
{
	this->soundOn = soundOn;
}

/*
 * Set new style index
 * @param styleIndex the new style index
 */
void QAppSettings::setLCDStyleIndex(const uint styleIndex)
{
	lcdStyleIndex = styleIndex;
}

/*
 * Set new Toolbar style index
 * @param styleIndex the new style index
 */
void QAppSettings::setToolbarStyleIndex(const uint styleIndex)
{
	toolbarStyleIndex = styleIndex;
}

/*
 * Set new language
 * Loads translation file and apply translation on application
 * @param language the new language
 */
void QAppSettings::setLanguage(const QLocale & language)
{
	this->language = language;

	// Get language 2 letters code (fr, en, etc.) in order to load the right language file
	QString localeStr = this->language.name().section('_', 0, 0);
	qDebug("locale string = %s", localeStr.toStdString().c_str());

	translator.load(QString(":/lang/CookingResources_") + localeStr);

	if (!translator.isEmpty())
	{
		app->installTranslator(&translator);
	}
	else
	{
		qDebug() << tr("Translation to %1 not found").arg(localeStr);
	}
}

