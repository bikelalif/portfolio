#include <QWheelEvent>
#include <QMouseEvent>
#include <QTouchEvent>
#include <cmath>	// for fabs

#include "QLCDMouseListener.h"

/*
 * Default Scale Factor for mouse wheel measured deltas
 * 	- 0.5 seems enough on Mac OS X
 * 	- Windows OS seems to require a MUCH SMALLER scale factor
 * 	- Don't know about other unixes (you'll have to try)
 */
#if defined(Q_OS_MACOS)
	const float QLCDMouseListener::defaultScaleFactor(0.5);
#elif defined(Q_OS_WIN)
	const float QLCDMouseListener::defaultScaleFactor(0.05);
#else // Linux and other unixes
	const float QLCDMouseListener::defaultScaleFactor(1.0);
#endif

/*
 * minimum swipe length (and/or maximum swipe height) in order to
 * consider a three finger left swipe
 */
const double QLCDMouseListener::swipeSize = 50.0;

/*
 * Mouse Listener constructor
 * @param scaleFactor scale factor to apply to measured deltas of the
 * mouse wheel
 * @param parent the parent object.
 */
QLCDMouseListener::QLCDMouseListener(const float scaleFactor, QObject *parent) :
	QObject(parent),
	scaleFactor(scaleFactor),
	startMidPoint(),
	endMidPoint(),
	touchPointsNumber(0),
	gestureStarted(false)
{
}

/*
 * Event filter to capture the events we're interested in:
 * 	- QWheelEvents in order to send #sendDelta signal with mouse wheel
 * 		vertical scrolls.
 * 	- QMouseEvents in order to send #sendClick signal to start or stop
 * 		the current countdown with left button click.
 * @par Algorithm:
 * 	QWheelEvents and QMouseEvents are captured and processed to look for
 * 	vertical scrolls and simple left button click (respectively)
 * @param obj the event source object as defined by
 * @code
 * 	sourceObject->installEventFilter(thisQLCDMouseListener);
 * @endcode
 * @param event the event triggered by the source object
 * @return true if the event has been handled and should not be handled
 * further, false otherwise. When other events (neither QWheelEvent or
 * QMouseEvent occurs they are passed to regular
 * QObject::eventFilter(obj, event)
 */
bool QLCDMouseListener::eventFilter(QObject *obj, QEvent *event)
{
	QWheelEvent * we;
	QMouseEvent * me;
	QTouchEvent * te;
	QList<QTouchEvent::TouchPoint> touchPoints;
	QPointF midPoint(0.0, 0.0);
	size_t nbPoints = 0;

	switch(event->type())
	{
		// handle mouse wheel up/down
		case QEvent::Wheel:
		{
			we = static_cast<QWheelEvent *>(event);
			QPoint angleDelta = we->angleDelta();
			if (!angleDelta.isNull())
			{
				int yAngleDelta = angleDelta.y();
				if (fabs(yAngleDelta) > 0)
				{
					emit sendDelta(static_cast<int>(static_cast<float>(yAngleDelta)*scaleFactor));

					return true;
				}
			}

			return false;
		}
		// handle mouse click (left button)
		case QEvent::MouseButtonRelease:
			me = static_cast<QMouseEvent *>(event);
			if (me->button() == Qt::LeftButton)
			{
				emit sendClick();

				return true;
			}
			else
			{
				return false;
			}
		// handle three fingers swipe left
		case QEvent::TouchBegin:
		case QEvent::TouchUpdate:
		case QEvent::TouchEnd:
			te = static_cast<QTouchEvent *>(event);
			touchPoints = te->touchPoints();
			nbPoints = static_cast<size_t>(te->touchPoints().size());
			for (QList<QTouchEvent::TouchPoint>::const_iterator it =
				 touchPoints.cbegin(); it != touchPoints.cend(); ++it)
			{
				midPoint+=it->pos();
			}
			midPoint/=static_cast<qreal>(nbPoints);

			switch (te->type())
			{
				case QEvent::TouchBegin:
					qDebug("Touch begin at [%d](%f, %f)",
						   touchPoints.size(), midPoint.x(), midPoint.y());

					if (nbPoints >= 2)
					{
						touchPointsNumber = nbPoints;
						startMidPoint = midPoint;
						gestureStarted = true;
					}
					break;
				case QEvent::TouchUpdate:
					break;
				case QEvent::TouchEnd:
					qDebug("Touch end at [%d](%f, %f)",
						   touchPoints.size(), midPoint.x(), midPoint.y());
					if (gestureStarted)
					{
						endMidPoint = midPoint;
						gestureStarted = false;

						/*
						 * check swipe length:
						 *	- same number of touch points as gesture start
						 *	- swipe width > minSwipeWidth
						 *	- swipe height < maxSwipeHeight
						 */
						if ((nbPoints == touchPointsNumber) &&
							(startMidPoint.x() - endMidPoint.x() > swipeSize) &&
							(fabs(startMidPoint.y() - endMidPoint.y()) < swipeSize))
						{
							qDebug("Swipe length = %f, height = %f",
								   startMidPoint.x() - endMidPoint.x(),
								   startMidPoint.y() - endMidPoint.y());
							emit sendSwipeLeft();
						}
					}
					break;
				default:
					break;
			}
			return true;

//		case QEvent::NativeGesture:
//			/*
//			 * TODO process native gesture events rather than other gesture events
//			 */
//			break;

		default:
			// standard parent event processing
			return QObject::eventFilter(obj, event);
	}
}
