#ifndef QCOUNTDOWN_H
#define QCOUNTDOWN_H

#include <QThread>
#include <QTimer>

/**
 * Threaded Countdown
 * @author David Roussel
 * @note I would have preffered to use a regular thread to thread this process,
 * but I can't seem to find the right way to do it with QT, so meanwhile, we'll
 * have to subclass QThread even if I don't like it.
 */
class QCountDown : public QThread
{
	Q_OBJECT
	public:
		/**
		 * Maximum value for countdown: 9999
		 */
		static const int maxCount;

		/**
		 * Minimum value for countdown: 1
		 */
		static const int minCount;

	private:
		/**
		 * Initial countdown value
		 */
		int iSeconds;

		/**
		 * current countdown value
		 */
		int iSecondsAccum;

		/**
		 * Initial countdown default value [10]
		 */
		static const int defaultCount;

		/**
		 * Seconds timer to count seconds.
		 * the timer is set with interval 1000 ms.
		 */
		QTimer timer;

	public:
		/**
		 * Countdown constructor
		 * @param count the initial count value [default value is #defaultCount]
		 * @param parent parent object [default value is NULL]
		 */
		explicit QCountDown(const int count = defaultCount,
							QObject *parent = nullptr);

		/**
		 * Countdown destructor.
		 * Stops the #timer and quits the run loop if still running
		 */
		~QCountDown() override;

		/**
		 * Gets the initial count value
		 * @return the initial count value
		 */
		int getCount() const;

		/**
		 * Execution loop of this thread.
		 * runs #exec to launch an event loop
		 */
		void run() override;

	signals:
		/**
		 * Signal emitted every second to tell the actual countdown value
		 */
		void secondChanged(const int value);

		/**
		 * Signal emitted when countdown is finished
		 */
		void timeIsUp();

	public slots:
		/**
		 * Slot to Start (or continues) the countdown by starting the timer
		 */
		void start();

		/**
		 * Slot to Stop the countdown
		 */
		void stop();

		/**
		 * Slot to Reset the countdown to initial value
		 */
		void reset();

		/**
		 * Slot to Set countdown initial value
		 * @param duration the new countdown initial value
		 */
		void setCount(const int duration);

	private slots:
		/**
		 * Slot to count down.
		 * Connected to the #timer.timeout() signal which happens every seconds.
		 */
		void countSeconds();
};

#endif // QCOUNTDOWN_H
