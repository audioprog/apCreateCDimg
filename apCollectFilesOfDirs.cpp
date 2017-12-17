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

#include "apCollectFilesOfDirs.h"

#include <QApplication>

void privateApCollectFilesOfDirs::addDirs(QStringList dirList)
{
	for (const QString& dir : dirList)
	{
		//
	}

	if (this->isToEnd)
	{
		this->moveToThread(QApplication::instance()->thread());
	}
}

void privateApCollectFilesOfDirs::slotEnd()
{
	if (this->isWorking)
	{
		this->isToEnd = true;
	}
	else
	{
		this->moveToThread(QApplication::instance()->thread());
	}
}

void privateApCollectFilesOfDirs::end()
{
	this->isToEnd = true;

	if ( ! this->isWorking)
	{
		this->metaObject()->invokeMethod(this, SLOT(slotEnd()));
	}
}

apCollectFilesOfDirs::apCollectFilesOfDirs()
{
	this->intThread.start();

	this->intDirs.moveToThread(&this->intThread);

	connect(&this->intSignals, &privateApCollectFilesOfDirsSignals::signalAddDirs, &this->intDirs, &privateApCollectFilesOfDirs::addDirs, Qt::QueuedConnection);
	connect(&this->intDirs, &privateApCollectFilesOfDirs::signalAddFiles, this, &apCollectFilesOfDirs::signalAddFiles, Qt::QueuedConnection);
}

apCollectFilesOfDirs::~apCollectFilesOfDirs()
{
	this->intDirs.end();
}

void apCollectFilesOfDirs::addDirs(QStringList dirList)
{
	this->intSignals.signalAddDirs(dirList);
}
