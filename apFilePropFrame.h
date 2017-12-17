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
#ifndef APFILEPROPFRAME_H
#define APFILEPROPFRAME_H

#include <QFrame>

class apFilePropFrame : public QFrame
{
	Q_OBJECT

public:
	apFilePropFrame( QWidget* parent = Q_NULLPTR );

signals:

	void signalFilesDropped( QStringList );

	void signalDirsDropped( QStringList );

public:

	void addExtenstion( const QString& filter1 );

	// QWidget interface
protected:

	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;

private:
	QStringList extensionFilter;
};

#endif // APFILEPROPFRAME_H
