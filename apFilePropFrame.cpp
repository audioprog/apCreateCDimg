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
#include "apFilePropFrame.h"

#include <qevent.h>
#include <QFileInfo>
#include <QMimeData>

apFilePropFrame::apFilePropFrame(QWidget* parent)
	: QFrame(parent)
{
	this->setFrameStyle(QFrame::Box);

	this->setAcceptDrops(true);
}

void apFilePropFrame::addExtenstion(const QString& filter1)
{
	this->extensionFilter << filter1;
}

void apFilePropFrame::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->urls().isEmpty())
	{
		event->ignore();
		return;
	}

	event->acceptProposedAction();
}

void apFilePropFrame::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->mimeData()->urls().isEmpty())
	{
		event->ignore();
		return;
	}

	event->acceptProposedAction();
}

void apFilePropFrame::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->urls().isEmpty())
	{
		event->ignore();
		return;
	}

	QStringList files;
	QStringList dirs;

	for (const QUrl& url : event->mimeData()->urls())
	{
		if ( ! url.isLocalFile())
		{
			continue;
		}

		QString fileName = url.toLocalFile();

		if (QFileInfo(fileName).isFile())
		{
			for  (const QString& ext1 : this->extensionFilter)
			{
				if (fileName.endsWith("." + ext1))
				{
					files << fileName;

					break;
				}
			}
		}
		else
		{
			dirs << fileName;
		}
	}

	if (files.isEmpty() && dirs.isEmpty())
	{
		event->ignore();
	}
	else
	{
		event->accept();

		emit signalFilesDropped(files);
		emit signalDirsDropped(dirs);
	}
}
