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

#include "styledButton.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QStyle>

#include "brandManager/brandManager.h"
#include "circleWidget.h"

#include <QSizePolicy>

using namespace qReal;

StyledButton::StyledButton(const QString &text, const QString &icon, QWidget *parent)
	: QPushButton(parent)
{
	setMouseTracking(true);
	setFlat(true);
	auto direction = icon.isEmpty() ? QBoxLayout::LeftToRight : QBoxLayout::TopToBottom;
	auto layout = new QBoxLayout(direction, this);
	layout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);

	if (!icon.isEmpty()) {
		layout->addStretch();
		setObjectName("withIcon");
		QWidget * const circleWidget = new CircleWidget(QSize(100, 100), icon, this);
		layout->addWidget(circleWidget, 0, Qt::AlignCenter);
		bindHighlightedOnHover(circleWidget);
		setMinimumSize(QSize(200,200));
		setSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
	}

	QLabel * const textLabel = new QLabel(text, this);
	textLabel->setWordWrap(true);
	textLabel->setAttribute(Qt::WA_Hover);
	auto textAlignment = icon.isEmpty() ?  Qt::AlignLeft : Qt::AlignHCenter;
	textLabel->setAlignment(textAlignment);
	if (!icon.isEmpty()) {
		textLabel->setObjectName("withoutIcon");
	}

	// Beginning from some version of Qt >= 5.5 QLabel does not take into account word wrap when calculating size hint,
	// so second line becomes clipped off. We use two lines for some buttons, so we manually set minimum height of a
	// label to fit two lines with our default font. Somebody who has internet connection shall provide more adequate
	// solution.
	//textLabel->setMinimumHeight(55);

	layout->addWidget(textLabel, 0, textAlignment);
	bindHighlightedOnHover(textLabel);
	layout->addStretch();
	setStyleSheet(BrandManager::styles()->startTabButtonStyle());
}

void StyledButton::bindHighlightedOnHover(QWidget * const widget)
{
	widget->setProperty("enabled", false);
	mChildren << widget;
}

void StyledButton::enterEvent(QEvent *event)
{
	QPushButton::enterEvent(event);
	highlight(true);
}

void StyledButton::leaveEvent(QEvent *event)
{
	QPushButton::leaveEvent(event);
	highlight(false);
}

QSize StyledButton::sizeHint() const
{
	auto size = QPushButton::sizeHint();
	qDebug() << size;
	return QSize(size.width(), size.width());
}

void StyledButton::highlight(bool on)
{
	for (QWidget * const child : mChildren) {
		child->setProperty("enabled", on);
		child->style()->unpolish(child);
		child->style()->polish(child);
	}
}
