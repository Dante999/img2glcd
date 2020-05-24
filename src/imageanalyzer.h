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
#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QImage>

class ImageAnalyzer {

      private:
	ImageAnalyzer();
	static bool          isPixelSet(QImage image, int x, int y);
	static unsigned char readByte(QImage image, int x, int y);

      public:
	static std::list<unsigned char> *readImage(QImage image, bool invert);
};

#endif // IMAGEANALYZER_H
