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
#ifndef APCOMPRESS_H
#define APCOMPRESS_H

#include <QPointer>

class QProcess;

class apCompress : public QObject
{
	Q_OBJECT

public:
	virtual ~apCompress();

	void addFile( const QString& nextFile );

	void addFileList( const QStringList& nextFiles );

	int getAllFileCount() const;

	QString getCurrentFile() const;

	int getFinishedCount() const;

	int getPercentCurrentFile() const;

signals:
	void signalFinished();

	void signalFileFinished( QString );

private:
	void detectPercentCurrentProc( const QString& text );

	void convertNextFile();

	void ensureProcess();

private:
	QPointer<QProcess> proc;

	QStringList toCompress;

	QStringList finished;

	QString currentFile;

	int percentCurrentFile = 0;

	int allFilesCount = 0;
};

#endif // APCOMPRESS_H
