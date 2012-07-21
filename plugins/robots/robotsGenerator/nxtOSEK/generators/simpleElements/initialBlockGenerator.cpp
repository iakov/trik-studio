#include "initialBlockGenerator.h"
#include "../../nxtOSEKRobotGenerator.h"

using namespace robots::generator;

InitialBlockGenerator::InitialBlockGenerator()
{
}

QList<SmartLine> InitialBlockGenerator::convertElememtIntoDirectCommand(NxtOSEKRobotGenerator *nxtGen
		, qReal::Id const elementId, qReal::Id const logicElementId)
{
	QList<SmartLine> result;
	int const numberOfPorts = 4;
	for (int i = 1; i <= numberOfPorts; i++) {
		QString const curPort = "port_" + QString::number(i);
		QByteArray portValue = nxtGen->api()->stringProperty(logicElementId, curPort).toUtf8();

		switch (i) {
		case 1:
			nxtGen->setPortValue1(portValue);
			break;
		case 2:
			nxtGen->setPortValue2(portValue);
			break;
		case 3:
			nxtGen->setPortValue3(portValue);
			break;
		case 4:
			nxtGen->setPortValue4(portValue);
			break;
		}
		QString const initEcrobotColorSensorPortS = "ecrobot_init_nxtcolorsensor(NXT_PORT_S";
		if (portValue == "Ультразвуковой сенсор") {
			mInitCode.append(SmartLine("ecrobot_init_sonar_sensor(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
			mTerminateCode.append(SmartLine("ecrobot_term_sonar_sensor(NXT_PORT_S" + QString::number(i) + ");"
					, elementId));
		} else if (portValue == "Сенсор цвета (полные цвета)") {
				mInitCode.append(SmartLine(initEcrobotColorSensorPortS + QString::number(i)
						+ ", NXT_LIGHTSENSOR_WHITE);", elementId));
		} else if (portValue == "Сенсор цвета (красный)") {
				mInitCode.append(SmartLine(initEcrobotColorSensorPortS + QString::number(i)
						+ ",  NXT_LIGHTSENSOR_RED);", elementId));
		} else if (portValue == "Сенсор цвета (зеленый)") {
				mInitCode.append(SmartLine(initEcrobotColorSensorPortS + QString::number(i)
						+ ", NXT_LIGHTSENSOR_GREEN);", elementId));
		} else if (portValue == "Сенсор цвета (синий)") {
				mInitCode.append(SmartLine(initEcrobotColorSensorPortS + QString::number(i)
						+ ", NXT_LIGHTSENSOR_BLUE);", elementId));
		} else if (portValue == "Сенсор цвета (пассивный)") {
				mInitCode.append(SmartLine(initEcrobotColorSensorPortS + QString::number(i)
						+ ", NXT_COLORSENSOR);", elementId));
		}
	}

	return result;
}
