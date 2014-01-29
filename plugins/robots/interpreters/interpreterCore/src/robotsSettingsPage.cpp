#include "robotsSettingsPage.h"
#include "ui_robotsSettingsPage.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

#include <qrkernel/settingsManager.h>
#include <qrutils/graphicsWatcher/sensorsGraph.h>
#include "robotModelManager.h"

using namespace interpreterCore;
using namespace qReal;

RobotsSettingsPage::RobotsSettingsPage(KitPluginManager &kitPluginManager, QWidget *parent)
		: PreferencesPage(parent)
		, mUi(new Ui::PreferencesRobotSettingsPage)
		, mKitPluginManager(kitPluginManager)
{
	mIcon = QIcon(":/icons/preferences/robot.png");
	mUi->setupUi(this);

	// TODO: remove it
//	mKitPluginManager.selectKit(mKitPluginManager.kitIds()[0]);
	initializeKitRadioButtons();

//	QWidget * const extensionWidget = mKitPluginManager.selectedKit().settingsWidget();
//	if (extensionWidget) {
//		static_cast<QVBoxLayout *>(mUi->settingsExtensionFrame->layout())->insertWidget(0, extensionWidget);
//	}

	restoreSettings();
	saveSelectedRobotModel();
}

RobotsSettingsPage::~RobotsSettingsPage()
{
	delete mUi;
}

void RobotsSettingsPage::save()
{
	saveSelectedRobotModel();
	// SettingsManager::setValue("bluetoothPortName", selectedPortName());
	// SettingsManager::setValue("valueOfCommunication", selectedCommunication());
	SettingsManager::setValue("enableNoiseOfSensors", mUi->enableSensorNoiseCheckBox->isChecked());
	SettingsManager::setValue("enableNoiseOfEngines", mUi->enableEnginesNoiseCheckBox->isChecked());
	SettingsManager::setValue("approximationLevel", mUi->approximationLevelSpinBox->value());
	SettingsManager::setValue("sensorUpdateInterval", mUi->sensorUpdateSpinBox->value());
	SettingsManager::setValue("autoscalingInterval", mUi->autoScalingSpinBox->value());
	SettingsManager::setValue("textUpdateInterval", mUi->textUpdaterSpinBox->value());
	SettingsManager::setValue("nxtFlashToolRunPolicy", mUi->runningAfterUploadingComboBox->currentIndex());
//	mSensorsWidget->save();
	emit saved();
}

void RobotsSettingsPage::restoreSettings()
{
	if (mKitButtons->checkedButton()) {
		// This will force reinitialization even if selection didn`t change
		mKitButtons->checkedButton()->setChecked(false);
	}

	QString const selectedKit = SettingsManager::value("SelectedRobotKit").toString();
	QAbstractButton * const selectedKitButton = mUi->constructorKitGroupBox->findChild<QAbstractButton *>(selectedKit);
	if (selectedKitButton) {
		selectedKitButton->setChecked(true);
	}
//	enums::robotModelType::robotModelTypeEnum typeOfRobotModel =
//			static_cast<enums::robotModelType::robotModelTypeEnum>(SettingsManager::value("robotModel").toInt());
//	initRobotModelType(typeOfRobotModel);

//	QString const typeOfCommunication = SettingsManager::value("valueOfCommunication").toString();
//	initTypeOfCommunication(typeOfCommunication);

	mUi->enableSensorNoiseCheckBox->setChecked(SettingsManager::value("enableNoiseOfSensors").toBool());
	mUi->enableEnginesNoiseCheckBox->setChecked(SettingsManager::value("enableNoiseOfEngines").toBool());
	mUi->approximationLevelSpinBox->setValue(SettingsManager::value("approximationLevel").toInt());

	int const sensorsUpdateDefault = utils::sensorsGraph::SensorsGraph::readSensorDefaultInterval;
	int const autoscalingDefault = utils::sensorsGraph::SensorsGraph::autoscalingDefault;
	int const textUpdateDefault = utils::sensorsGraph::SensorsGraph::textUpdateDefault;
	mUi->sensorUpdateSpinBox->setValue(SettingsManager::value("sensorUpdateInterval", sensorsUpdateDefault).toInt());
	mUi->autoScalingSpinBox->setValue(SettingsManager::value("autoscalingInterval", autoscalingDefault).toInt());
	mUi->textUpdaterSpinBox->setValue(SettingsManager::value("textUpdateInterval", textUpdateDefault).toInt());

	mUi->runningAfterUploadingComboBox->setCurrentIndex(SettingsManager::value("nxtFlashToolRunPolicy").toInt());
}

void RobotsSettingsPage::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange: {
		mUi->retranslateUi(this);
		break;
	}
	default:
		break;
	}
}

void RobotsSettingsPage::onKitRadioButtonToggled(bool checked)
{
	if (!checked) {
		return;
	}

	QAbstractButton * const kitButton = static_cast<QAbstractButton *>(sender());
	QLabel * const emptyCaseLabel = new QLabel(tr("No robot models available for ") + kitButton->text(), this);
	showRadioButtonGroup(mUi->typeOfModelGroupBox, mKitRobotModels[kitButton], emptyCaseLabel);

	checkSelectedRobotModelButtonFor(kitButton);
}

void RobotsSettingsPage::checkSelectedRobotModelButtonFor(QAbstractButton * const kitButton)
{
	QString const kitId = kitButton->objectName();
	QString const key = "SelectedModelFor" + kitId;
	QString selectedRobotModel = SettingsManager::value(key).toString();
	if (selectedRobotModel.isEmpty()) {
		// Robot model for this kit was never selected. Falling back to default one
		interpreterBase::robotModel::RobotModelInterface *defaultRobotModel
				= mKitPluginManager.kitById(kitId).defaultRobotModel();
		selectedRobotModel = defaultRobotModel ? defaultRobotModel->name() : QString();
	}

	QAbstractButton * const robotModelButton = mUi->typeOfModelGroupBox
			->findChild<QAbstractButton *>(kitId + selectedRobotModel);
	if (selectedRobotModel.isEmpty() || !robotModelButton) {
		// No robot model was selected previously and no default robot model was specified.
		// Selecting first button in group
		QButtonGroup * const kitRobotModelButtons = mKitRobotModels[kitButton];
		if (!kitRobotModelButtons->buttons().isEmpty()) {
			kitRobotModelButtons->buttons()[0]->setChecked(true);
		}
	} else {
		robotModelButton->setChecked(true);
	}
}

void RobotsSettingsPage::onRobotModelRadioButtonToggled(bool checked)
{
	if (!checked) {
		return;
	}

	// TODO: notify plugins
}

void RobotsSettingsPage::initializeKitRadioButtons()
{
	QLabel * const emptyCaseLabel = new QLabel(tr("No constructor kit plugins loaded"), this);
	mKitButtons = new QButtonGroup(this);
	for (QString const &kitId : mKitPluginManager.kitIds()) {
		interpreterBase::KitPluginInterface const &kit = mKitPluginManager.kitById(kitId);
		QRadioButton * const kitRadioButton = new QRadioButton(kit.friendlyKitName(), this);
		kitRadioButton->hide();
		kitRadioButton->setObjectName(kitId);
		mKitButtons->addButton(kitRadioButton);
		connect(kitRadioButton, &QRadioButton::toggled, this, &RobotsSettingsPage::onKitRadioButtonToggled);
		mKitRobotModels[kitRadioButton] = initializeRobotModelsButtons(kitId, kitRadioButton);
	}

	showRadioButtonGroup(mUi->constructorKitGroupBox, mKitButtons, emptyCaseLabel);
}

QButtonGroup *RobotsSettingsPage::initializeRobotModelsButtons(QString const &kitId, QRadioButton * const kitButton)
{
	QButtonGroup * const result = new QButtonGroup(kitButton);
	for (auto &robotModel : mKitPluginManager.kitById(kitId).robotModels()) {
		QString const name = robotModel->name();
		QRadioButton * const button = new QRadioButton(name, this);
		button->setObjectName(kitId + name);
		button->hide();
		mButtonsToRobotModelsMapping[button] = robotModel;
		connect(button, &QRadioButton::toggled, this, &RobotsSettingsPage::onRobotModelRadioButtonToggled);
		result->addButton(button);
	}

	return result;
}

void RobotsSettingsPage::showRadioButtonGroup(QWidget * const container, QButtonGroup * const radioButtons
		, QWidget * const emptyCaseWidget)
{
	if (emptyCaseWidget) {
		emptyCaseWidget->setVisible(false);
	}

	if (container->layout()) {
		for (int i = 0; i < container->layout()->count(); ++i) {
			QLayoutItem * const item = container->layout()->itemAt(i);
			if (item && item->widget()) {
				item->widget()->hide();
			}
		}

		delete container->layout();
	}

	QVBoxLayout *layout = new QVBoxLayout(container);
	container->setLayout(layout);

	if (radioButtons->buttons().isEmpty()) {
		container->setVisible(emptyCaseWidget != nullptr);
		if (emptyCaseWidget) {
			container->layout()->addWidget(emptyCaseWidget);
			emptyCaseWidget->setVisible(true);
		}

		return;
	}

	for (QAbstractButton * const button : radioButtons->buttons()) {
		container->layout()->addWidget(button);
		button->setVisible(true);
		container->setVisible(true);
	}

	if (radioButtons->buttons().count() == 1) {
		container->setVisible(false);
		return;
	}

}

void RobotsSettingsPage::saveSelectedRobotModel()
{
	QAbstractButton * const selectedKitButton = mKitButtons->checkedButton();
	if (!selectedKitButton) {
		// TODO: inconsistent scenario
		return;
	}

	SettingsManager::setValue("SelectedRobotKit", selectedKitButton->objectName());
	QAbstractButton * const selectedRobotModelButton = mKitRobotModels[selectedKitButton]->checkedButton();
	// If null passed there default model will be used so it`s ok
	RobotModelManager::setRobotModel(mButtonsToRobotModelsMapping[selectedRobotModelButton]);
}
