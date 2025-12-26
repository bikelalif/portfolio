#include "QCountDown.h"

/*
 * Initial countdown default value [10]
 */
const int QCountDown::defaultCount = 10;

/*
 * Maximum value for countdown: 9999
 */
const int QCountDown::maxCount = 9999;

/*
 * Minimum value for countdown: 1
 */
const int QCountDown::minCount = 1;

/*
 * Countdown constructor
 * @param count the initial count value [default value is #defaultCount]
 * @param parent parent object [default value is NULL]
 */
QCountDown::QCountDown(const int count, QObject *parent) :
	QThread(parent),
	iSeconds(count),
	iSecondsAccum(0)
{
	timer.setInterval(1000); //seconds timer
	connect(&timer, SIGNAL(timeout()), this, SLOT(countSeconds()));

//	qDebug("QCountDown created in thread = %ld",
//		(long unsigned int) QThread::currentThread());

	QThread::start();
}

/*
 * Countdown destructor.
 * Stops the #timer and quits the run loop if still running
 */
QCountDown::~QCountDown()
{
	stop();
	if (isRunning())
	{
		quit();
	}
}

/*
 * Gets the initial count value
 * @return the initial count value
 */
int QCountDown::getCount() const
{
	return iSeconds;
}

/*
 * Execution loop of this thread.
 * runs #exec to launch an event loop
 */
void QCountDown::run()
{
//	qDebug("QCountDown runs in thread = %ld",
//		(long unsigned int) QThread::currentThread());

	// Starts event loop
	exec();
}

/*
 * Slot to Start (or continues) the countdown by starting the timer
 */
void QCountDown::start()
{
	if (!timer.isActive())
	{
		emit secondChanged(iSeconds - iSecondsAccum);
		timer.start();
	}
}

/*
 * Slot to Stop the countdown
 */
void QCountDown::stop()
{
	if (timer.isActive())
	{
		timer.stop();
	}
}

/*
 * Slot to Reset the countdown to initial value
 */
void QCountDown::reset()
{
	iSecondsAccum = 0;
	emit secondChanged(iSeconds - iSecondsAccum);
}

/*
 * Slot to Set countdown initial value
 * @param duration the new countdown initial value
 */
void QCountDown::setCount(const int duration)
{
	if (duration > maxCount)
	{
		iSeconds = maxCount;
	}
	else if (duration < minCount)
	{
		iSeconds = minCount;
	}
	else
	{
		iSeconds = static_cast<int>(duration);
	}

	emit secondChanged(iSeconds);
}

/*
 * Slot to count down.
 * Connected to the #timer.timeout() signal which happens every seconds.
 */
void QCountDown::countSeconds()
{
//	qDebug("QCountDown count seconds in thread = %ld",
//		   (long unsigned int)QThread::currentThread());

	iSecondsAccum++;
	emit secondChanged(iSeconds - iSecondsAccum);

	if (iSecondsAccum >= iSeconds)
	{
		emit timeIsUp();
		timer.stop();
	}
}

