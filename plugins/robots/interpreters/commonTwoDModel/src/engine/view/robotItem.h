#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPainter>

#include <qrutils/graphicsUtils/abstractItem.h>
#include <qrutils/graphicsUtils/rectangleImpl.h>
#include <qrutils/graphicsUtils/rotateItem.h>

#include "sensorItem.h"
#include "rotater.h"

#include "src/engine/model/robotModel.h"

namespace twoDModel {
namespace view {

/** @brief Class that represents a robot in 2D model */
class RobotItem : public QObject, public graphicsUtils::RotateItem
{
	Q_OBJECT

public:
	RobotItem(QString const &robotImageFileName, model::RobotModel &robotModel);

	QRectF rect() const override;
	void setSelected(bool isSelected) override;
	void checkSelection() override;

	void setRotater(Rotater *rotater);

	QRectF boundingRect() const override;
	QRectF calcNecessaryBoundingRect() const override;
	void drawItem(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget = 0) override;
	void drawExtractionForItem(QPainter *painter) override;
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void resizeItem(QGraphicsSceneMouseEvent *event) override;

	/// Same as QGraphicsItem::setPos(). Needed as slot for connection.
	void setPos(QPointF const &newPos);
	/// Same as QGraphicsItem::setRotation(). Needed as slot for connection.
	void setRotation(qreal rotation) override;

	void addSensor(SensorItem *sensor);
	void removeSensor(SensorItem *sensor);

	void clearSensors();

	/// Returns false if we're dragging robot item somewhere
	bool isOnTheGround() const;

	void setNeededBeep(bool isNeededBeep);

	void recoverDragStartPosition();

protected:
	QVariant itemChange(GraphicsItemChange change, QVariant const &value);

signals:
	void mousePressed();
	void changedPosition();

private:
	class BeepItem : public QGraphicsItem
	{
	protected:
		void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);
		QRectF boundingRect() const;

	private:
		void drawBeep(QPainter *painter);
		void drawBeepArcs(QPainter *painter, QPointF const &center, qreal radius);
	};

	void onLanded();

	/** @brief Image of a robot drawn on scene */
	QImage mImage;
	// Takes ownership
	BeepItem *mBeepItem;

	/** @brief List of sensors added to robot */
	QList<SensorItem *> mSensors;  // Does not have ownership

	bool mIsOnTheGround;
	QPointF mDragStart;
	Rotater *mRotater;
	graphicsUtils::RectangleImpl mRectangleImpl;

	model::RobotModel &mRobotModel;
};

}
}
