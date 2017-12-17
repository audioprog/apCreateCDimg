/* (C) 2017 web.n.work.ls(at)mailbox(.)org

   This is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License version
   2.1 as published by the Free Software Foundation.

   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301  USA

   Alternatively, this file is available under the Mozilla Public
   License Version 1.1.  You may obtain a copy of the License at
   http://www.mozilla.org/MPL/
*/
#include "apPathPartSelectorWidget.h"

#include <QBoxLayout>

apPathPartSelectorWidget::apPathPartSelectorWidget(QWidget* parent)
	: QWidget(parent)
{
	new QHBoxLayout(this);

	connect(&this->buttonMapper, QOverload<QWidget*>::of(&QSignalMapper::mapped), this, &apPathPartSelectorWidget::slotButtonClicked);
}

void apPathPartSelectorWidget::clear()
{
	QList<QWidget*> widgets;

	for (int i = 0; i < this->layout()->count(); i++)
	{
		QLayoutItem* item = this->layout()->itemAt(i);
		QWidget* widget = item->widget();
		if (widget)
		{
			widgets << widget;
		}
	}

	for (QWidget* widget : widgets)
	{
		this->layout()->removeWidget(widget);
		widget->deleteLater();
	}
}

void apPathPartSelectorWidget::getPath() const
{
	QList<QToolButton*> buttons = this->getButtons();

	QString path;

	for (QToolButton* button : buttons)
	{
		path += button->text();
	}

	return path;
}

void apPathPartSelectorWidget::setPath(const QString& newPath)
{
	this->clear();

	QString intNewPath = QString(newPath).replace('\\', '/');

	QStringList names = intNewPath.split('/');

	if ( ! (intNewPath + "/").startsWith(this->selectedPath + "/"))
	{
		this->selectedPath = names.first();
	}
	QStringList selected = this->selectedPath.split('/');

	for (int i = 0; i < names.count(); i++)
	{
		QString name = names.at(i);

		QString stylesh = "QToolButton { ";
		if (i < selected.count())
		{
			if (selected.at(i) == name)
			{
				stylesh += "border-top: 2px solid black; border-bottom: 2px solid black; ";
			}
			if (names.first() == name)
			{
				stylesh += "border-left: 2px solid black; ";
			}
			else
			{
				name = "/" + name;
			}
			if (selected.last() == name)
			{
				stylesh += "border-right: 2px solid black; ";
			}
		}
		else
		{
			stylesh += "border: none; ";
		}

		QToolButton* button = new QToolButton(name);

		button->setStyleSheet(stylesh + "}");

		this->layout()->addWidget(button);
	}
}

void apPathPartSelectorWidget::slotButtonClicked(QWidget* widget)
{
	QToolButton* button = qobject_cast<QToolButton*>(widget);
	if (button)
	{
		QList<QToolButton*> buttons = this->getButtons();
	}
}

QList<QToolButton*> apPathPartSelectorWidget::getButtons()
{
	QList<QToolButton*> toReturn;

	for (int i = 0; i < this->layout()->count(); i++)
	{
		QLayoutItem* item = this->layout()->itemAt(i);
		QToolButton* button = qobject_cast<QToolButton*>(item->widget());
		if (button)
		{
			toReturn << button;
		}
	}

	return toReturn;
}
