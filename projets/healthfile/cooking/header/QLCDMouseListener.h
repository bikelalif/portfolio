#ifndef QLCDMOUSELISTENER_H
#define QLCDMOUSELISTENER_H

#include <QObject>
#include <QEvent>
#include <QPointF>

/**
 * Mouse Event filter to:
 *	- increment or decrement count whith mouse wheel up or down events
 *	- starts and stop count with a simple click on the LCD panel
 *	- reset the count at the end with a 3 fingers left swipe on the trackpad
 * @author David Roussel
 */
class QLCDMouseListener : public QObject
{
	Q_OBJECT

	public:
		/**
		 * Default Scale Factor for mouse wheel measured deltas
		 * 	- 0.5 seems enough on Mac OS X
		 * 	- Windows OS seems to require a MUCH SMALLER scale factor
		 * 	- Don't know about other unixes (you'll have to try)
		 */
		static const float defaultScaleFactor;

		/**
		 * minimum swipe length (and/or maximum swipe height) in order to
		 * consider a three finger left swipe
		 */
		static const double swipeSize;

	protected:
		/**
		 * Scale factor for wheel measured steps :
		 */
		float scaleFactor;

		/**
		 * Mid point of touch event starting points
		 */
		QPointF startMidPoint;

		/**
		 * Mid point of touch event ending points (should be on the left of
		 * startMidPoint)
		 */
		QPointF endMidPoint;

		/**
		 * Number of touch points during gesture (should be the same at gesture
		 * start and gesture end)
		 */
		size_t touchPointsNumber;

		/**
		 * indicates if a gesture have been started when a QEvent::TouchBegin
		 * occurs so we can record #startMidPoint and wait for #endMidPoint
		 */
		bool gestureStarted;

	public:
		/**
		 * Mouse Listener constructor
		 * @param scaleFactor scale factor to apply to measured deltas of the
		 * mouse wheel
		 * @param parent the parent object.
		 */
		explicit QLCDMouseListener(const float scaleFactor = defaultScaleFactor,
								   QObject * parent = nullptr);

	protected:
		/**
		 * Event filter to capture the events we're interested in:
		 * 	- QWheelEvents in order to send #sendDelta signal with mouse wheel
		 * 		vertical scrolls.
		 * 	- QMouseEvents in order to send #sendClick signal to start or stop
		 * 		the current countdown with left button click.
		 * @par Algorithm:
		 * 	QWheelEvents, QMouseEvents and QTouchEvents are captured and
		 *  processed to look for vertical scrolls, simple left button click and
		 *  three fingers left swipe (respectively)
		 * @param obj the event source object as defined by
		 * @code
		 *	// for Touch events to be processed the Qt::WA_AcceptTouchEvents
		 *	// attribute needs to be set on the source widget.
		 *	sourceObject->setAttribute(Qt::WA_AcceptTouchEvents);
		 * 	sourceObject->installEventFilter(thisQLCDMouseListener);
		 * @endcode
		 * @param event the event triggered by the source object
		 * @return true if the event has been handled and should not be handled
		 * further, false otherwise. When other events (neither QWheelEvent or
		 * QMouseEvent occurs they are passed to regular
		 * QObject::eventFilter(obj, event)
		 */
		bool eventFilter(QObject * obj, QEvent * event) override;

	signals:
		/**
		 * Signal send when vertical mouse wheel scrolls occurs
		 * @param delta the delta measured on the mouse wheel
		 */
		void sendDelta(int delta);

		/**
		 * Signal send when left mouse button click occurs
		 */
		void sendClick();

		/**
		 * Signal sent when a three finger left swipe is detected
		 */
		void sendSwipeLeft();
};

#endif // QLCDMOUSELISTENER_H
