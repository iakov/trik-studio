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

#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QThread>
#include <QDebug>
#include "twoDModel/engine/model/timeline.h"
#include "modelTimer.h"

using namespace twoDModel::model;

Timeline::Timeline(QObject *parent)
	: QObject(parent)
{
	static volatile auto registered = false;
	if (!registered) {
		// For queued signals with argument of this type
		qRegisterMetaType<qReal::interpretation::StopReason>();
		registered = true;
	}

	connect(&mTimer, &QTimer::timeout, this, &Timeline::onTimer);
	mTimer.setInterval(0);
}

Timeline::~Timeline()
{
	stop(qReal::interpretation::StopReason::error);
}

static int gTicks  = 0;
static int gFrames = 0;
static qint64 gStart = 0;

void Timeline::start()
{
	if (!mIsStarted) {
		mIsStarted = true;
		gStart = QDateTime::currentMSecsSinceEpoch();
		emit started();
		emit tick(); /// hack so that constraints init-on would start immediatly
		/// ideally they should be triggered on started()
		gotoNextFrame();
	}
}

void Timeline::stop(qReal::interpretation::StopReason reason)
{
	if (mIsStarted) {
		mIsStarted = false;
		emit beforeStop(reason);
		mTimer.stop();
		emit stopped(reason);
	}
}

void Timeline::onTimer()
{
	if (!mIsStarted) {
		mTimer.stop();
		return;
	}

	for (int i = 0; i < ticksPerCycle; ++i) {
		QCoreApplication::sendPostedEvents();
		if (mIsStarted) {
			mTimestamp += timeInterval;
			++gTicks;
			emit tick();
			++mCyclesCount;
			if (mCyclesCount >= mSpeedFactor) {
				mTimer.stop();
				mCyclesCount = 0;
				auto msFromFrameStart = static_cast<int>(QDateTime::currentMSecsSinceEpoch()
						- mFrameStartTimestamp);
				auto pauseBeforeFrameEnd = mFrameLength - msFromFrameStart - 1;
				QTimer::singleShot(std::max(pauseBeforeFrameEnd, 0), this, &Timeline::gotoNextFrame);
				return;
			}
		}
	}
}
void Timeline::gotoNextFrame()
{
	mFrameStartTimestamp = QDateTime::currentMSecsSinceEpoch();
	++gFrames;
	if (0 == gFrames % 100) {
		auto FPS =  1000 * gFrames / (mFrameStartTimestamp - gStart + 1);
		qDebug() << "Frames:" << gFrames << "; Ticks:" << gTicks << "; FPS:" << FPS;
	}
	emit nextFrame();
	if (!mTimer.isActive()) {
		mTimer.start();
	}
}

utils::AbstractTimer *Timeline::produceTimerImpl()
{
	return new ModelTimer(this);
}

int Timeline::speedFactor() const
{
	return mSpeedFactor;
}

bool Timeline::isStarted() const
{
	return mIsStarted;
}

quint64 Timeline::timestamp() const
{
	return mTimestamp;
}

utils::AbstractTimer *Timeline::produceTimer()
{
	return produceTimerImpl();
}

void Timeline::setImmediateMode(bool immediateMode)
{
	mFrameLength = immediateMode ? 0 : defaultFrameLength;
}

void Timeline::setSpeedFactor(int factor)
{
	if (mSpeedFactor != factor) {
		mSpeedFactor = factor;
		emit speedFactorChanged(factor);
	}
}
