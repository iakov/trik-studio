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

#pragma once

#include <generatorBase/masterGeneratorBase.h>

#include "trikGeneratorBase/trikGeneratorBaseDeclSpec.h"

namespace trik {

/// Master generator base implementation for every generator from TRIK kit
class ROBOTS_TRIK_GENERATOR_BASE_EXPORT TrikMasterGeneratorBase : public generatorBase::MasterGeneratorBase
{
	Q_OBJECT
public:
	TrikMasterGeneratorBase(const qrRepo::RepoApi &repo
			, qReal::ErrorReporterInterface &errorReporter
			, const utils::ParserErrorReporter &parserErrorReporter
			, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
			, qrtext::LanguageToolboxInterface &textLanguage
			, const qReal::Id &diagramId
			, const QStringList &pathsToTemplates);

protected:
	generatorBase::GeneratorCustomizer *createCustomizer() override;

private:
	const QStringList mPathsToTemplates;
};

}
