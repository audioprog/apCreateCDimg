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
#include "apCompress.h"

#include <QFile>
#include <QProcess>

apCompress::~apCompress()
{
	if ( ! this->proc.isNull())
	{
		this->proc->deleteLater();
	}
}

void apCompress::addFile(const QString& nextFile)
{
	if (this->currentFile == nextFile)
	{
		return;
	}

	if (this->toCompress.contains(nextFile))
	{
		return;
	}

	this->toCompress.append(nextFile);

	this->allFilesCount++;

	this->ensureProcess();
}

void apCompress::addFileList(const QStringList& nextFiles)
{
	for (const QString& file : nextFiles)
	{
		this->addFile(file);
	}
}

int apCompress::getAllFileCount() const
{
	return this->allFilesCount;
}

QString apCompress::getCurrentFile() const
{
	return this->currentFile;
}

int apCompress::getFinishedCount() const
{
	return this->finished.count();
}

int apCompress::getPercentCurrentFile() const
{
	return this->percentCurrentFile;
}

void apCompress::detectPercentCurrentProc(const QString& text)
{
	int indexC = text.indexOf('(');

	if (indexC > -1)
	{
		int indexEnd = text.indexOf("%)|", indexC + 1);
		if (indexEnd > -1)
		{
			QString percent = text.mid(indexC + 1, indexEnd - indexC - 1);

			this->percentCurrentFile = percent.toInt();
		}
	}
}

void apCompress::convertNextFile()
{
	if (this->toCompress.isEmpty())
	{
		emit signalFinished();

		return;
	}

	QString nextFile = this->toCompress.takeFirst();

	this->currentFile = nextFile;

	QString v = "5";

	if (nextFile.endsWith(".wav", Qt::CaseInsensitive) && QFile(nextFile).size() > 120 * 1024 * 1024)
	{
		v = "7";
	}
	else if (nextFile.endsWith(".mp3") && QFile(nextFile).size() > 11500 * 1024)
	{
		v = "7";
	}
	else if (nextFile.contains("lied", Qt::CaseInsensitive) || nextFile.contains("musik", Qt::CaseInsensitive))
	{
		v = "3";
	}

	//   -V 7 -q 0 <source> <target>
	this->proc->start("lame.exe", QStringList() << "--vbr-new" << "-V" << v << "-q" << "0" << nextFile << nextFile.section('/', 0, -2) + "/k " + nextFile.section('/', -1).section('.', 0, -2) + ".mp3");
}

void apCompress::ensureProcess()
{
	if (this->proc.isNull())
	{
		this->proc = new QProcess;

		QObject::connect(this->proc.data(), QOverload<int>::of(&QProcess::finished), this->proc.data(), [this]()
		{
			this->signalFileFinished(this->currentFile);

			this->percentCurrentFile = 0;

			this->finished << this->currentFile;

			this->currentFile.clear();

			this->convertNextFile();
		});

		QObject::connect(this->proc.data(), &QProcess::readyReadStandardError, this, [this]()
		{
			QString text = this->proc->readAllStandardError();

			this->detectPercentCurrentProc(text);
		});

		QObject::connect(this->proc.data(), &QProcess::readyReadStandardOutput, this, [this]()
		{
			QString text = this->proc->readAllStandardOutput();

			this->detectPercentCurrentProc(text);
		});

		this->convertNextFile();
	}
}
