/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Setup.h"

class EyeOfAcherusControll : public QuestScript
{
	public:
		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
		GameObject* target1 = mTarget->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2344.52f, -5698.25f, 426.02f, 191609);
		GameObject* target2 = mTarget->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2320.20f, -5662.39f, 426.02f, 191609);

		if(target1 != NULL)
		{
		target1->SetFlags(0);
		}
		if(target2 != NULL)
		{
		target2->SetFlags(0);
		}
}

		void OnQuestComplete(Player* mTarget, QuestLogEntry* qLogEntry)
		{
		GameObject* target1 = mTarget->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2344.52f, -5698.25f, 426.02f, 191609);
		GameObject* target2 = mTarget->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2320.20f, -5662.39f, 426.02f, 191609);

		if(target1 != NULL)
		{
		target1->SetFlags(6553636);
		}
		if(target2 != NULL)
		{
		target2->SetFlags(6553636);
		}
	}	
};

void SetupTheScarletEnclave(ScriptMgr* mgr)
{
	mgr->register_quest_script(12641, new EyeOfAcherusControll);
}