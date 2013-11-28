/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
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

class DreadmaulRock : public GameObjectAIScript
{
public:
	DreadmaulRock(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new DreadmaulRock(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(3821);
		if(pQuest == NULL)
			return;

		Creature* shaghost = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 9136);
		if(shaghost)
				return;

		Creature* shaghostspawn = sEAS.SpawnCreature(pPlayer, 9136, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(shaghostspawn != NULL)
			shaghostspawn->Despawn(2 * 60 * 1000, 0);
	}
};

class TabletoftheSeven : public GameObjectAIScript
{
public:
	TabletoftheSeven(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new TabletoftheSeven(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(4296);
		if(pQuest == NULL)
			return;

		pPlayer->CastSpell(pPlayer, 15065, true); // Cast spell: "Create Tablet Transcript".
		/*if(pPlayer->GetItemInterface()->GetItemCount(11470, 0) < 1)
			sEAS.AddItem(11470, pPlayer);*/
	}
};

void SetupBurningSteppesGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(160445, &DreadmaulRock::Create); // Sha'ni Proudtusk's Remains
	mgr->register_gameobject_script(169294, &TabletoftheSeven::Create); // Tablet of the Seven
}