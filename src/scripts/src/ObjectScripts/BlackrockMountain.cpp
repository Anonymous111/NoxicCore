/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (C) 2011-2012 ArcScripts2 team
 *
 * This program is free software: you can redistribute it and/or modify
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

class OrbOfCommand : public GameObjectAIScript
{
public:
	OrbOfCommand(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new OrbOfCommand(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->HasFinishedQuest(7761) && pPlayer->getLevel() >= 58 && pPlayer->InGroup() == true)
		{
			pPlayer->SafeTeleport(469, 0, -7672.939941f, -1107.307617f, 396.649994f, 0.616532f);
		}
		else if(pPlayer->getLevel() <= 57 || pPlayer->HasFinishedQuest(7761) == false)
		{
			pPlayer->BroadcastMessage("You need to be level 58 and have completed the quest: Blackhand's Command");
		}
		else if(pPlayer->HasFinishedQuest(7761) == true && pPlayer->getLevel() >= 58 && pPlayer->InGroup() == false)
		{
			pPlayer->BroadcastMessage("You need to be in a raid group to be able to enter this instance.");
		}
	}
};

void SetupBlackrockMountainGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(179879, &OrbOfCommand::Create);
}