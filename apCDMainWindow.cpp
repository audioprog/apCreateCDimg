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
#include "apCDMainWindow.h"
#include "ui_apCDMainWindow.h"

#include <QDir>

#include <qevent.h>
#include <QMimeData>

apCDMainWindow::apCDMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::apCDMainWindow)
{
    ui->setupUi(this);

	QObject::connect(&this->progressTimer, &QTimer::timeout, this, [this]()
	{
		ui->labelSingleLile->setText(this->compress.getCurrentFile());

		ui->progressBarSingleFile->setValue(this->compress.getPercentCurrentFile());

		ui->progressBarFiles->setMaximum(qMax(1, this->compress.getAllFileCount()));
		ui->progressBarFiles->setValue(this->compress.getFinishedCount());
	});

	QObject::connect(ui->frameFileDrop, &apFilePropFrame::signalDirsDropped, this, &apCDMainWindow::slotDirsDropped);
	QObject::connect(ui->frameFileDrop, &apFilePropFrame::signalFilesDropped, this, &apCDMainWindow::slotFilesDropped);

	this->progressTimer.start(500);
}

apCDMainWindow::~apCDMainWindow()
{
	delete ui;
}

void apCDMainWindow::on_actionAktuelles_Jahr_triggered()
{
	//
}

void apCDMainWindow::slotDirsDropped(QStringList dirList)
{
	//
}

void apCDMainWindow::slotFilesDropped(QStringList fileList)
{
	this->compress.addFileList(fileList);
}

