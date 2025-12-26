#ifndef QEDITABLEVALUE_H
#define QEDITABLEVALUE_H

#include <QStackedWidget>
#include <QIcon>
#include <QVariant>

namespace Ui
{
	class QEditableValue;
}

/**
 * Widget for an editable value (which looks like a label until we click
 * on it, then it turns into a editable line edit allowing to change this
 * value).
 */
class QEditableValue : public QStackedWidget
{
	Q_OBJECT

	/**
	 * the title property
	 */
	Q_PROPERTY(QString title MEMBER title READ getTitle WRITE setTitle)

	/**
	 * possible value types
	 */
	Q_ENUMS(ValueType)

	/**
	 * the value type property
	 */
	Q_PROPERTY(ValueType type MEMBER type READ getType WRITE setType)

	/**
	 * The value property
	 */
	Q_PROPERTY(QVariant value MEMBER value READ getValue WRITE setValue NOTIFY valueChanged)

	/**
	 * The title label icon property
	 */
	Q_PROPERTY(QIcon icon MEMBER icon READ getIcon WRITE setIcon)

	public:
		/**
		 * possible value types
		 */
		enum ValueType
		{
			INT,
			DOUBLE,
			STRING
		};

		/**
		 * Constructor
		 * @param parent parent widget [default = NULL]
		 * @param title title for the label [default = "title"]
		 * @param type the type of value
		 * @param value value for the button/line editor [default =
		 * QString::number(0)]
		 */
		explicit QEditableValue(QWidget * parent = nullptr,
								const QString & title = "",
								const ValueType type = INT,
								const QVariant & value = QString::number(0));

		/**
		 * Destructor.
		 */
		virtual ~QEditableValue() override;

		/**
		 * Title accessor
		 * @return the title
		 */
		QString getTitle() const;

		/**
		 * Value type accessor
		 * @return  the value type
		 */
		ValueType getType() const;

		/**
		 * Title label icon accessor
		 * @return the icon of the title label
		 */
		QIcon getIcon() const;

		/**
		 * Value accessor
		 * @return the current value in a QVariant
		 */
		QVariant getValue() const;

		/**
		 * Title mutator
		 * @param title the new title to set
		 */
		void setTitle(const QString & title);

		/**
		 * Value type mutator
		 * @param type the new type to set
		 */
		void setType(const ValueType type);

		/**
		 * Title label mutator
		 * @param icon the icon to set on the title label
		 */
		void setIcon(const QIcon & icon);

	signals:
		/**
		 * Signal emitted when value changes
		 * @param value the new value as a QVariant
		 */
		void valueChanged(const QVariant & value);

		/**
		 * Signal emitted when value changes
		 * @param value the new value as an int
		 */
		void intValueChanged(const int value);

		/**
		 * Signal emitted when value changes
		 * @param value the new value as a double
		 */
		void doubleValueChanged(const double value);

		/**
		 * Signal emitted when value changes
		 * @param value the new value as a QString
		 */
		void stringValueChanged(const QString value);

	public slots:
		/**
		 * Value mutator
		 * @param value the new value to set as a QVariant
		 */
		void setValue(const QVariant & value);

		/**
		 * Value mutator
		 * @param value the new value to set as a integer
		 */
		void setIntValue(const int value);

		/**
		 * Value mutator
		 * @param value the new value to set as a double
		 */
		void setDoubleValue(const double value);

		/**
		 * Value mutator
		 * @param value the new value to set as a QString
		 */
		void setStringValue(const QString & value);

	private slots:
		/**
		 * Slot performed when valueButton clicked.
		 * Switches to editing
		 */
		void on_valueButton_clicked();

		/**
		 * Slot performed when editing value is finished.
		 * Switches back to flat button
		 */
		void on_valueEdit_editingFinished();

	private:
		/**
		 * the graphical layout
		 */
		Ui::QEditableValue * ui;
		/**
		 * Value title
		 */
		QString title;
		/**
		 * The type of value to manage
		 */
		ValueType type;
		/**
		 * the actual value
		 */
		QVariant value;
};

#endif // QEDITABLEVALUE_H
