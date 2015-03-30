#include "ev3GeneratorBase/ev3MasterGeneratorBase.h"
#include "ev3GeneratorCustomizer.h"

using namespace ev3;

Ev3MasterGeneratorBase::Ev3MasterGeneratorBase(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const interpreterBase::robotModel::RobotModelManagerInterface &robotModelManager
		, qrtext::LanguageToolboxInterface &textLanguage
		, const qReal::Id &diagramId
		, const QString &generatorName)
	: MasterGeneratorBase(repo, errorReporter, robotModelManager, textLanguage, diagramId)
	, mGeneratorName(generatorName)
{
}

generatorBase::GeneratorCustomizer *Ev3MasterGeneratorBase::createCustomizer()
{
	return new Ev3GeneratorCustomizer(mRepo, mErrorReporter
			, mRobotModelManager, *createLuaProcessor(), mGeneratorName);
}
