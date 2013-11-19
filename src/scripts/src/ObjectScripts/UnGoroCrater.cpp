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

class NorthernPylon : public GameObjectAIScript
{
	public:
		NorthernPylon(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new NorthernPylon(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(pPlayer->HasFinishedQuest(4284))
			{
				QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(4285);
				if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = pQuest->GetMobCount(0) + 1;
					pQuest->SetMobCount(0, newcount);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
			else if(pPlayer->HasFinishedQuest(4284) == false)
			{
				pPlayer->BroadcastMessage("You need to have completed the quest : Crystals of Power");
			}
		}
};

class EasternPylon : public GameObjectAIScript
{
	public:
		EasternPylon(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new EasternPylon(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(pPlayer->HasFinishedQuest(4284))
			{
				QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(4287);
				if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = pQuest->GetMobCount(0) + 1;
					pQuest->SetMobCount(0, newcount);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
			else if(pPlayer->HasFinishedQuest(4284) == false)
			{
				pPlayer->BroadcastMessage("You need to have completed the quest : Crystals of Power");
			}
		}
};

class WesternPylon : public GameObjectAIScript
{
	public:
		WesternPylon(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new WesternPylon(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(pPlayer->HasFinishedQuest(4284))
			{
				QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(4288);
				if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = pQuest->GetMobCount(0) + 1;
					pQuest->SetMobCount(0, newcount);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
			else if(pPlayer->HasFinishedQuest(4284) == false)
			{
				pPlayer->BroadcastMessage("You need to have completed the quest : Crystals of Power");
			}
		}
};

void SetupUnGoroCraterGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(164955, &NorthernPylon::Create);
	mgr->register_gameobject_script(164957, &EasternPylon::Create);
	mgr->register_gameobject_script(164956, &WesternPylon::Create);
}