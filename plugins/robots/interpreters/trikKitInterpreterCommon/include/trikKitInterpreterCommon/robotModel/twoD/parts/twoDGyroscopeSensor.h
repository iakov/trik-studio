/* Copyright 2007-2019 CyberTech Labs Ltd.
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

#pragma once

#include <twoDModel/robotModel/parts/gyroscope.h>
#include "trikKitInterpreterCommon/declSpec.h"

namespace trik {
namespace robotModel {
namespace twoD {
namespace parts {

class ROBOTS_TRIK_KIT_INTERPRETER_COMMON_EXPORT GyroscopeSensor : public twoDModel::robotModel::parts::Gyroscope
{
	Q_OBJECT

public:
	GyroscopeSensor(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, twoDModel::engine::TwoDModelEngineInterface &engine);

private:
	QVector<int> convert(const QVector<int> &data) const override;
};

}
}
}
}
