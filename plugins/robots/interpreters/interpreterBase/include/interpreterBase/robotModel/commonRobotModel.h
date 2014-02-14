#pragma once

#include <QtCore/QScopedPointer>

#include "interpreterBase/robotModel/robotModelInterface.h"
#include "interpreterBase/robotModel/configuration.h"
#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace interpreterBase {
namespace robotModel {

class ROBOTS_INTERPRETER_BASE_EXPORT CommonRobotModel : public RobotModelInterface
{
	Q_OBJECT

public:
	CommonRobotModel();
	~CommonRobotModel() override;

	void init() final;

	void connectToRobot() override;

	/// Shall be implemented in descendants to stop all robot devices. Default implementation does nothing.
	void stopRobot() override;

	void disconnectFromRobot() override;

	ConfigurationInterface const &configuration() const final;

	QList<PortInfo> availablePorts() const override;
	QList<PortInfo> configurablePorts() const override;
	QList<PluggableDeviceInfo> allowedDevices(PortInfo const &port) const override;

	void configureDevices(QHash<PortInfo, PluggableDeviceInfo> const &devices) final;

	QList<PluggableDeviceInfo> convertibleBases() const override;

public slots:
	virtual void rereadSettings();

protected:
	void configureDevice(PortInfo const &port, PluggableDeviceInfo const &deviceInfo);

	void addAllowedConnection(PortInfo const &port, QList<PluggableDeviceInfo> const &devices);

	ConfigurationInterface &mutableConfiguration();

private slots:
	void onConnected(bool success);
	void onDisconnected();

private:
	/// Shall be implemented in descendants to add to configuration devices that can not be changed by user
	/// and shall be in a model every time (like Lego motors). Default implementation does nothing.
	/// @todo Unneeded. Shall be done in constructors of derived models.
	virtual void configureKnownDevices();

	virtual robotParts::PluggableDevice * createDevice(PortInfo const &port, PluggableDeviceInfo const &deviceInfo);

	QHash<PortInfo, QList<PluggableDeviceInfo>> mAllowedConnections;

	/// Devices configuration.
	Configuration mConfiguration;

	/// Model connection state.
	ConnectionState mState;
};

}
}
