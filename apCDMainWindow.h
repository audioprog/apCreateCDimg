/* (C) 2017 audioprog@users.noreply.github.com

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
#ifndef APCDMAINWINDOW_H
#define APCDMAINWINDOW_H


#include "apCompress.h"


#include <QMainWindow>
#include <QTimer>


namespace Ui {
class apCDMainWindow;
}

class apCDMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit apCDMainWindow(QWidget *parent = 0);
	~apCDMainWindow();

private slots:
	void on_actionAktuelles_Jahr_triggered();

	void slotDirsDropped( QStringList );

	void slotFilesDropped( QStringList );

	void slotSelectSource();

private:
	Ui::apCDMainWindow *ui;

	apCompress compress;

	QTimer progressTimer;
};

#endif // APCDMAINWINDOW_H
