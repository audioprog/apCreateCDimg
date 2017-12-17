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
#ifndef APCOLLECTFILESOFDIRS_H
#define APCOLLECTFILESOFDIRS_H

#include <QAtomicInteger>
#include <QObject>
#include <QThread>

class privateApCollectFilesOfDirs : public QObject
{
	Q_OBJECT
	friend class apCollectFilesOfDirs;

signals:
	void signalAddFiles( QStringList );

public slots:
	void addDirs( QStringList );

	void slotEnd();

private:
	void end();

private:
	privateApCollectFilesOfDirs() = default;

	~privateApCollectFilesOfDirs() = default;

private:
	QStringList dirs;

	QAtomicInteger<bool> isToEnd = false;

	QAtomicInteger<bool> isWorking = false;
};

class privateApCollectFilesOfDirsSignals : public QObject
{
	Q_OBJECT

signals:
	void signalAddDirs( QStringList );
};

class apCollectFilesOfDirs : public QObject
{
	Q_OBJECT

public:
	apCollectFilesOfDirs();

	virtual ~apCollectFilesOfDirs();

signals:
	void signalAddFiles( QStringList );

public:
	void addDirs( QStringList );

private:
	privateApCollectFilesOfDirsSignals intSignals;

	privateApCollectFilesOfDirs intDirs;

	QThread intThread;
};

#endif // APCOLLECTFILESOFDIRS_H
