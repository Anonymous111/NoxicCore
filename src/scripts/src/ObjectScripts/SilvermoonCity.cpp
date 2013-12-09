/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
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

class ThePathoftheAdept : public GameObjectAIScript
{
public:
	ThePathoftheAdept(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new ThePathoftheAdept(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(!pPlayer)
			return;

		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(9692);
		if(pQuest == NULL)
			return;

		Creature* zelemar = sEAS.SpawnCreature(pPlayer, 17830, pPlayer->GetPositionX()+5, pPlayer->GetPositionY()+5, pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		zelemar->Despawn(6*60*1000, 0);
	}
};

void SetupSilvermoonCityGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(182024, &ThePathoftheAdept::Create);
}