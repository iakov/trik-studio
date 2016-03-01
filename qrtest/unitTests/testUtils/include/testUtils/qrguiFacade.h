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

#include <QtCore/QString>

#include <qrgui/models/models.h>
#include <qrgui/plugins/pluginManager/editorManager.h>
#include <qrgui/plugins/toolPluginInterface/systemEvents.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/mainWindowDockInterface.h>
#include <qrgui/editor/sceneCustomizationInterface.h>
#include <qrgui/textEditor/textManagerInterface.h>

#include <qrtest/unitTests/mocks/qrgui/plugins/toolPluginInterface/usedInterfaces/mainWindowInterpretersInterfaceMock.h>
#include <qrtest/unitTests/mocks/qrgui/plugins/toolPluginInterface/usedInterfaces/mainWindowDockInterfaceMock.h>
#include <qrtest/unitTests/mocks/qrgui/mainWindow/projectManager/projectManagementInterfaceMock.h>
#include <qrtest/unitTests/mocks/qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterMock.h>
#include <qrtest/unitTests/mocks/qrgui/view/sceneCustomizationInterfaceMock.h>
#include <qrtest/unitTests/mocks/qrgui/textEditor/textManagerInterfaceMock.h>

namespace qrTest {

class QrguiFacade
{
public:
	explicit QrguiFacade(QString const &modelName);

	qReal::gui::MainWindowInterpretersInterface &mainWindowInterpretersInterface();
	qReal::gui::MainWindowDockInterface &mainWindowDockInterface();
	qReal::GraphicalModelAssistInterface &graphicalModelAssistInterface();
	qReal::LogicalModelAssistInterface &logicalModelAssistInterface();
	qReal::ProjectManagementInterface &projectManagementInterface();
	qrRepo::RepoControlInterface &repoControlInterface();
	qReal::SystemEvents &systemEvents();
	qReal::gui::editor::SceneCustomizationInterface &sceneCustomizer();
	qReal::TextManagerInterface &textManager();

	void setActiveTab(qReal::Id const &id);

private:
	qReal::EditorManager mEditorManager;
	qReal::models::Models mModels;
	qReal::SystemEvents mSystemEvents;
	MainWindowInterpretersInterfaceMock mMainWindowInterpretersInterfaceMock;
	MainWindowDockInterfaceMock mMainWindowDockInterfaceMock;
	SceneCustomizationInterfaceMock mSceneCustomizationInterfaceMock;
	ProjectManagementInterfaceMock mProjectManagementInterfaceMock;
	ErrorReporterMock mErrorReporterMock;
	TextManagerInterfaceMock mTextManagerMock;

	qReal::Id mActiveTab;
	bool mWereErrors = false;
};

}
