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
#include "imageanalyzer.h"

#include <QColor>

ImageAnalyzer::ImageAnalyzer() {}

bool ImageAnalyzer::isPixelSet(QImage image, int x, int y)
{
	QColor pixel = QColor(image.pixel(x, y));

	return (pixel.red() != 0 || pixel.green() != 0 || pixel.blue() != 0);
}

unsigned char ImageAnalyzer::readByte(QImage image, int x, int y)
{

	unsigned char result = 0x00;

	for (int i = 0; i < 8; i++) {

		int y_new = y + i;

		if (isPixelSet(image, x, y_new)) {
			result |= (1 << i);
		}
	}

	return result;
}

std::list<unsigned char> *ImageAnalyzer::readImage(QImage image, bool invert)
{

	std::list<unsigned char> *data = new std::list<unsigned char>();

	int imgWidth  = image.width();
	int imgHeight = image.height();

	for (int y = 0; y < imgHeight; y += 8) {

		for (int x = 0; x < imgWidth; x++) {

			unsigned char byte = readByte(image, x, y);

			if (invert) {
				byte ^= 0xFF;
			}

			data->push_back(byte);
		}
	}

	return data;
}
