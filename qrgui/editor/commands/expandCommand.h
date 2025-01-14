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

#include "editor/commands/nodeElementCommand.h"
#include "editor/commands/resizeCommand.h"

namespace qReal {
namespace gui {
namespace editor {
namespace commands {

class ExpandCommand : public NodeElementCommand
{
	Q_OBJECT
public:
	ExpandCommand(const NodeElement *node);
	virtual ~ExpandCommand();

protected:
	bool execute();
	bool restoreState();

private:
	void changeExpanded();

	QMap<Id, QPointF> mShifting;
	ResizeCommand *mResizeCommand;
};

}
}
}
}
