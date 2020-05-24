/*******************************************************************************
 *
 * img2glcd
 * Copyright (C) 2020 Matthias Escher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QList>
#include <QString>
#include <stdio.h>

#include "imageanalyzer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->setWindowTitle("img2glcd");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_loadFileButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
	    this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

	ui->filePathLabel->setText(fileName);
}

void MainWindow::on_startButton_clicked()
{
	QString filename     = ui->filePathLabel->text();
	bool    invertPixels = ui->invertPixelsCheckBox->isChecked();

	QPixmap pixMap = QPixmap(filename);

	std::list<unsigned char> *data =
	    ImageAnalyzer::readImage(pixMap.toImage(), invertPixels);

	ui->resultTextBrowser->setText("");

	ui->resultTextBrowser->append(
	    QString("#define WIDTH %1").arg(pixMap.width()));

	ui->resultTextBrowser->append(
	    QString("#define HEIGHT %1").arg(pixMap.height()));

	ui->resultTextBrowser->append("");

	QString buffer = "";

	for (unsigned char c : *data) {

		static int i = 0;

		buffer.append(
		    QString("0x%1, ").arg(c, 2, 16, QLatin1Char('0')));

		if (i == 8) {
			ui->resultTextBrowser->append(buffer);
			i = 0;
			buffer.clear();
		}
		else {
			i++;
		}
	}
}
