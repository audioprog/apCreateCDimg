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

	this->layout()->setSpacing(0);

	connect(&this->buttonMapper, QOverload<QWidget*>::of(&QSignalMapper::mapped), this, &apPathPartSelectorWidget::slotButtonClicked);
}

void apPathPartSelectorWidget::clear()
{
	QList<QWidget*> widgets;

	QList<QSpacerItem*> spacerItems;

	for (int i = 0; i < this->layout()->count(); i++)
	{
		QLayoutItem* item = this->layout()->itemAt(i);
		QWidget* widget = item->widget();
		if (widget)
		{
			widgets << widget;
		}
		else if (item->spacerItem())
		{
			spacerItems << item->spacerItem();
		}
	}

	for (QWidget* widget : widgets)
	{
		this->layout()->removeWidget(widget);
		widget->deleteLater();
	}

	for (QSpacerItem* spacer : spacerItems)
	{
		this->layout()->removeItem(spacer);

		delete spacer;
	}
}

QString apPathPartSelectorWidget::getPath() const
{
	QList<QToolButton*> buttons = this->getButtons();

	QString path;

	for (QToolButton* button : buttons)
	{
		QString buttonText = button->text();
		if (buttonText.startsWith("/ "))
		{
			buttonText = "/" + buttonText.mid(2);
		}
		path += buttonText;
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
			if (selected.last() == name)
			{
				stylesh += "border-right: 2px solid black; ";
			}
			if (names.first() == name)
			{
				stylesh += "border-left: 2px solid black; ";
			}
			else
			{
				name = "/ " + name;
			}
		}
		else
		{
			stylesh += "border: none; ";
			if (names.first() != name)
			{
				name = "/ " + name;
			}
		}

		QToolButton* button = new QToolButton();

		button->setText(name);

		button->setStyleSheet(stylesh + "}");

		this->buttonMapper.setMapping(button, button);
		connect(button, &QToolButton::clicked, &this->buttonMapper, QOverload<>::of(&QSignalMapper::map));

		this->layout()->addWidget(button);
	}

	this->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
}

void apPathPartSelectorWidget::setSelection(const QString& newSelectedPath)
{
	if (this->selectedPath != newSelectedPath)
	{
		this->selectedPath = QString(newSelectedPath).replace('\\', '/');

		QString oldPath = this->getPath();

		if (oldPath != this->selectedPath || ! oldPath.startsWith(this->selectedPath + "/"))
		{
			oldPath = this->selectedPath;
		}

		this->setPath(oldPath);

		if ( ! this->signalsBlocked())
		{
			emit signalSelected(this->selectedPath);
		}
	}
}

void apPathPartSelectorWidget::slotButtonClicked(QWidget* widget)
{
	QToolButton* button = qobject_cast<QToolButton*>(widget);
	if (button)
	{
		QList<QToolButton*> buttons = this->getButtons();

		bool isSelection = true;

		QString selected;

		for (int i = 0; i < buttons.count(); i++)
		{
			QString stylesh = "QToolButton { ";
			if (isSelection)
			{
				stylesh += "border-top: 2px solid black; border-bottom: 2px solid black; ";

				if (i == 0)
				{
					stylesh += "border-left: 2px solid black; ";
				}
				if (buttons.at(i) == button)
				{
					stylesh += "border-right: 2px solid black; ";

					isSelection = false;
				}

				QString buttonText = buttons.at(i)->text();
				if (buttonText.startsWith("/ "))
				{
					buttonText.remove(1, 1);
				}

				selected += buttonText;
			}
			else
			{
				stylesh += "border: none; ";
			}

			buttons.at(i)->setStyleSheet(stylesh + "}");
		}

		this->selectedPath = selected;

		if ( ! this->signalsBlocked())
		{
			emit signalSelected(this->selectedPath);
		}
	}
}

QList<QToolButton*> apPathPartSelectorWidget::getButtons() const
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
