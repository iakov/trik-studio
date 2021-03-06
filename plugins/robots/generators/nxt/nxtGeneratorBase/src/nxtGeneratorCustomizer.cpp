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

#include "nxtGeneratorCustomizer.h"

using namespace nxt;

NxtGeneratorCustomizer::NxtGeneratorCustomizer(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, generatorBase::lua::LuaProcessor &luaProcessor
		, const QString &generatorName
		, bool supportsSwitchUnstableToBreaks)
	: mFactory(repo, errorReporter, robotModelManager, luaProcessor, generatorName)
	, mSupportsSwitchUnstableToBreaks(supportsSwitchUnstableToBreaks)
{
}

generatorBase::GeneratorFactoryBase *NxtGeneratorCustomizer::factory()
{
	return &mFactory;
}

bool NxtGeneratorCustomizer::supportsSwitchUnstableToBreaks() const
{
	return mSupportsSwitchUnstableToBreaks;
}
