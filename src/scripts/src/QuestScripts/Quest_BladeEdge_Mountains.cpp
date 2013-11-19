/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

class IntotheSoulgrinder : public QuestScript
{
	public:
		void OnQuestComplete(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			Creature* qg = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(mTarget->GetPositionX(), mTarget->GetPositionY(), 0, 22941);
			if(qg == NULL)
				return;
			qg->GetMapMgr()->GetInterface()->SpawnCreature(23053, 2794.978271f, 5842.185547f, 35.911819f, 0, true, false, 0, 0);
		}
};

class powerconv : public GameObjectAIScript
{
	public:
		powerconv(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new powerconv(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10584);
			if(qle == NULL)
				return;

			Creature* magneto = sEAS.SpawnCreature(pPlayer, 21729, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ(), 0, 0);
			if(magneto != NULL)
			{
				magneto->Despawn(5 * 60 * 1000, 0);
			}

			_gameobject->Despawn(300000, 0);
		}
};

void SetupBladeEdgeMountains(ScriptMgr* mgr)
{
	mgr->register_quest_script(11000, new IntotheSoulgrinder());
}