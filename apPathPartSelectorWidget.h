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
#ifndef APPATHPARTSELECTORWIDGET_H
#define APPATHPARTSELECTORWIDGET_H

#include <QList>
#include <QWidget>
#include <QSignalMapper>
#include <QToolButton>

class QBoxLayout;

class apPathPartSelectorWidget : public QWidget
{
	Q_OBJECT

public:
	explicit apPathPartSelectorWidget( QWidget *parent = nullptr );

	void clear();

	QString getPath() const;

	void setPath( const QString& );

	void setSelection( const QString& );

signals:

	void signalSelected( QString );

private slots:

	void slotButtonClicked( QWidget* );

private:

	QList<QToolButton*> getButtons() const;

	QString selectedPath;

	QSignalMapper buttonMapper;

};

#endif // APPATHPARTSELECTORWIDGET_H
