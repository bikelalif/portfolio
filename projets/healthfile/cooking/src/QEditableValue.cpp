#include <QDebug>

#include "QEditableValue.h"
#include "ui_QEditableValue.h"

/*
 * Constructor
 * @param title title for the label [default = "title"]
 * @param value value for the button/line editor [default = QString::number(0)]
 * @param parent parent widget [default = NULL]
 */
QEditableValue::QEditableValue(QWidget *parent,
							   const QString &title,
							   const QEditableValue::ValueType type,
							   const QVariant & value) :
	QStackedWidget(parent),
	ui(new Ui::QEditableValue),
	title(title),
	type(type),
	value(value)
{
	ui->setupUi(this);

	// Setup title and value
	setTitle(title);
	setType(type);
	setValue(value);
}

/*
 * Destructor.
 */
QEditableValue::~QEditableValue()
{
	delete ui;
}

/*
 * Value accessor
 * @return the current value in a QVariant
 */
QVariant QEditableValue::getValue() const
{
	return value;
}

/*
 * Title accessor
 * @return the title
 */
QString QEditableValue::getTitle() const
{
	return title;
}

/*
 * Value type accessor
 * @return  the value type
 */
enum QEditableValue::ValueType QEditableValue::getType() const
{
	return type;
}

/*
 * Title label icon accessor
 * @return the icon of the title label
 */
QIcon QEditableValue::getIcon() const
{
	return ui->valueButton->icon();
}


/*
 * Title mutator
 * @param title the new title to set
 */
void QEditableValue::setTitle(const QString & title)
{
	this->title = title;
	ui->label1->setText(this->title);
	ui->label2->setText(this->title);
}

/*
 * Value type mutator
 * @param type the new type to set
 */
void QEditableValue::setType(const enum QEditableValue::ValueType type)
{
	this->type = type;
}

/*
 * Title label mutator
 * @param icon the icon to set on the title label
 */
void QEditableValue::setIcon (const QIcon & icon)
{
	ui->valueButton->setIcon(icon);
}


/*
 * Value mutator
 * @param value the new value to set as a QVariant
 */
void QEditableValue::setValue(const QVariant & value)
{
	this->value = value;
	QString stringValue = this->value.toString();
	ui->valueButton->setText(stringValue);
	ui->valueEdit->setText(stringValue);
}

/*
 * Value mutator
 * @param value the new value to set as a integer
 */
void QEditableValue::setIntValue(const int value)
{
	setValue(QVariant::fromValue<int>(value));
}

/*
 * Value mutator
 * @param value the new value to set as a double
 */
void QEditableValue::setDoubleValue(const double value)
{
	setValue(QVariant::fromValue<double>(value));
}

/*
 * Value mutator
 * @param value the new value to set as a QString
 */
void QEditableValue::setStringValue(const QString & value)
{
	setValue(QVariant::fromValue<QString>(value));
}

/*
 * Slot performed when valueButton clicked
 */
void QEditableValue::on_valueButton_clicked()
{
	setCurrentIndex(1);
}

void QEditableValue::on_valueEdit_editingFinished()
{
	qDebug("QEditableValue::on_valueEdit_editingFinished start ...");
	// Get the new text
	QString textValue = ui->valueEdit->text();
	bool conversionOk = false;
	int intValue;
	double doubleValue;

	// set new value
	switch (type)
	{
		case INT:
			intValue = textValue.toInt(&conversionOk);
			if (conversionOk)
			{
				setIntValue(intValue);
				emit intValueChanged(intValue);
			}
			break;
		case DOUBLE:
			doubleValue = textValue.toDouble(&conversionOk);
			if (conversionOk)
			{
				setDoubleValue(doubleValue);
				emit doubleValueChanged(doubleValue);
			}
			break;
		case STRING:
			setStringValue(textValue);
			emit valueChanged(QVariant(textValue));
			break;
		default:
			break;
	}

	if (!conversionOk)
	{
		qDebug() << "QEditableValue::on_valueEdit_editingFinished: conversion from text failed";
	}
	qDebug("Value changed to %s", textValue.toStdString().c_str());

	// switch back to current index 0
	setCurrentIndex(0);

	qDebug("QEditableValue::on_valueEdit_editingFinished end");
}
