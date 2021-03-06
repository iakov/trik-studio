/* Copyright 2018 CyberTech Labs Ltd.
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

#include <qrgui/plugins/toolPluginInterface/toolPluginInterface.h>

namespace subprogramsImporterExporter {

/// Plugin to export/import subprograms from/to models.
class SubprogramsImporterExporterPlugin : public QObject, public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "subprogramsImporterExporter.SubprogramsImporterExporterPlugin")

public:
	SubprogramsImporterExporterPlugin();
	~SubprogramsImporterExporterPlugin() override;

	QList<qReal::ActionInfo> actions() override;
	void init(qReal::PluginConfigurator const &configurator) override;

private slots:
	void exportToFile() const;
	void importToProject() const;
	void saveToCollectionTriggered() const;
	void importFromCollectionTriggered() const;
	void clearCollectionTriggered() const;

private:
	QMenu mMenu;
	QAction mFirstSeparatorAction;
	QAction mSecondSeparatorAction;
	QAction mImportToProjectAction;
	QAction mExportAction;
	QAction mSaveToCollection;
	QAction mImportFromCollection;
	QAction mClearCollection;

	qrRepo::RepoControlInterface *mRepo; // Doesn't have ownership
	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterpretersInterface; // Doesn`t have ownership
	qReal::GraphicalModelAssistInterface *mGraphicalModel; // Doesn`t have ownership
	qReal::LogicalModelAssistInterface *mLogicalModel; // Doesn`t have ownership
	qReal::ProjectManagementInterface *mProjectManager; // Doesn`t have ownership

	QStringList currentlySavedSubprograms() const;
	QMap<QString, bool> markLeftExistedInRight(const QStringList &left, const QStringList &right) const;

	bool checkOpenedProject() const;
	bool checkSubprogramsForUniqueNames() const;
	void innerSubprograms(const qReal::Id &id, qReal::IdList &list) const;
};

}
