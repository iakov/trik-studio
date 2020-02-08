/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "trikKitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h"

#include <QtCore/QJsonArray>
#include <thirdparty/qslog/QsLog.h>

#include <utils/canvas/textObject.h>

using namespace trik::robotModel::twoD::parts;
using namespace kitBase::robotModel;

const int realWidth = 238;
const int realHeight = 278;
const int textSize = 20;

Display::Display(const DeviceInfo &info
		, const PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: robotModel::parts::TrikDisplay(info, port)
	, mEngine(engine)
	, mBackground(Qt::transparent)
{
	mEngine.display()->setPainter(this);

	connect(this, &Display::backgroundChanged, this, [=](const QColor &color) {
		emit propertyChanged("background", color);
	});
	connect(this, &Display::smileChanged, this, [=](bool smiles, bool happy) {
		emit propertyChanged("smiles", smiles && happy);
		emit propertyChanged("sadSmiles", smiles && !happy);
	});
	connect(this, &Display::shapesSetChanged, this, [=]() {
		// This is a bit hacky, but shapes set may be modified pretty often, can be pretty large
		// and its serialization to JSON may take notable time, so we don't want to do it without real need.
		if (isSignalConnected(QMetaMethod::fromSignal(&Display::propertyChanged))) {
			emit propertyChanged("objects", toJson());
		}
	});

	qRegisterMetaType<QVector<int32_t>>("QVector<int32_t>");
}

QString Display::background() const
{
	return mBackground.name();
}

bool Display::smiles() const
{
	return mSmiles;
}

bool Display::sadSmiles() const
{
	return mSadSmiles;
}

void Display::drawPixel(int x, int y)
{
	Canvas::drawPixel(x, y);
	emit shapesSetChanged();
}

void Display::drawLine(int x1, int y1, int x2, int y2)
{
	Canvas::drawLine(x1, y1, x2, y2);
	emit shapesSetChanged();
}

void Display::drawRect(int x, int y, int width, int height, bool filled)
{
	Canvas::drawRect(x, y, width, height, filled);
	emit shapesSetChanged();
}

void Display::drawEllipse(int x, int y, int width, int height, bool filled)
{
	Canvas::drawEllipse(x, y, width, height, filled);
	emit shapesSetChanged();
}

void Display::drawArc(int x, int y, int width, int height, int startAngle, int spanAngle)
{
	Canvas::drawArc(x, y, width, height, startAngle, spanAngle);
	emit shapesSetChanged();
}

void Display::drawSmile(bool sad)
{
	if (mSmiles == !sad && mSadSmiles == sad) {
		return;
	}
	mCurrentImage = QImage(sad ? ":/icons/sadSmile.png" : ":/icons/smile.png");
	mSmiles = !sad;
	mSadSmiles = sad;
	mEngine.display()->repaintDisplay();
	emit smileChanged(true, !sad);
}

void Display::setBackground(const QColor &color)
{
	mBackground = color;
	emit backgroundChanged(color);
}

void Display::printText(int x, int y, const QString &text)
{
	const QPair<int, int> coords(x, y);
	if (mLabelsMap.contains(coords)) {
		mLabelsMap[coords]->setText(text);
	} else {
		utils::TextObject * const textObject = new utils::TextObject(x, y, text
			, mCurrentPenColor, mCurrentPenWidth);
		mObjects << textObject;
		mLabelsMap[coords] = textObject;
		mLabels << textObject;
	}

	emit shapesSetChanged();
}

void Display::clearScreen()
{
	// Background color is not cleared
	mCurrentImage = QImage();
	mSmiles = false;
	mSadSmiles = false;
	mLabelsMap.clear();
	Canvas::reset();

	emit smileChanged(false, false);
	emit shapesSetChanged();
}

void Display::setPainterColor(const QColor &color)
{
	Canvas::setPainterColor(color);
}

void Display::setPainterWidth(int penWidth)
{
	Canvas::setPainterWidth(penWidth);
}

void Display::paint(QPainter *painter, const QRect &outputRect)
{
	Q_UNUSED(outputRect)

	const QRect displayRect(0, 0, mEngine.display()->displayWidth(), mEngine.display()->displayHeight());

	painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	painter->save();
	painter->setPen(mBackground);
	painter->setBrush(mBackground);
	painter->drawRect(displayRect);
	painter->drawImage(displayRect, mCurrentImage);
	painter->restore();

	painter->save();	
	QFont font;
	font.setPixelSize(textSize);
	painter->setFont(font);
	painter->setPen(Qt::black);
	const qreal xScale = displayRect.width() / (realWidth * 1.0);
	const qreal yScale = displayRect.height() / (realHeight * 1.0);
	painter->scale(xScale, yScale);
	Canvas::paint(painter, {0, 0, realWidth, realHeight});
	painter->restore();
}

void Display::reset()
{
	clearScreen();
	setBackground(Qt::transparent);
	redraw();
}

void Display::redraw()
{
	if (mEngine.display()) {
		mEngine.display()->repaintDisplay();
	}
}

void Display::show(const QVector<int32_t> &array, int width, int height, const QString &format)
{
	auto fmt = QImage::Format_RGB32;
	auto *rawData = static_cast<const uchar *>(static_cast<const void *>(array.data()));

	// Reserve maximum possible size to avoid reallocation
	QVector<uchar> formattedData( (width + 3) * (height + 3) * 3 + 3);

	// QImage requires 32-bit aligned scan lines
	// Helper function to convert data
	auto copyAligned = [&](int perLine){
		auto scanLineSize = static_cast<int>((static_cast<unsigned>(perLine + 3)) & 0xFFFFFFFC);
		formattedData.resize(scanLineSize * height);
		auto dst = formattedData.begin();
		for (auto src = array.begin(); src < array.end(); src += perLine) {
			dst = std::copy(src, src + perLine, dst);
			dst += scanLineSize - perLine;
		}
		rawData = formattedData.constData();
	};

	if (!format.compare("rgb32", Qt::CaseInsensitive)) {
		/* do nothing */
	} else if (!format.compare("rgb888", Qt::CaseInsensitive)) {
		fmt = QImage::Format_RGB888;
		copyAligned(3 * width);
	} else if (format == "grayscale8") {
		fmt = QImage::Format_Grayscale8;
		copyAligned(width);
	} else {
		QLOG_ERROR() << "Unsupported format" << format;
		return;
	}

	// QImage doesn't create copy of a buffer and requires clean up function
	// Simple workaround -- create deep-copy using "copy" function
	mCurrentImage = QImage(rawData, width, height, fmt).copy();
	mEngine.display()->repaintDisplay();
}
