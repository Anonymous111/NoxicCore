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

class AlterofTidalMastery : public GameObjectAIScript
{
	public:
		AlterofTidalMastery(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AlterofTidalMastery(GO); }

		void OnActivate(Player* pPlayer)
		{
			pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(16292, 7934.343750f, -7637.020996f, 112.694130f, 3.098388f, true, false, 0, 0);
		}
};

class VanquishingAquantion : public GameObjectAIScript
{
public:
	VanquishingAquantion(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new VanquishingAquantion(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(9174);
		if(pQuest == NULL)
			return;

		Creature* naga = sEAS.SpawnCreature(pPlayer, 16292, 7938, -7632, 114, 3.05f, 0);
		naga->Despawn(6 * 60 * 1000, 0);
	}
};

/*--------------------------------------------------------------------------------------------------------*/

class GildedBrazier : public GameObjectAIScript
{
	public:
		GildedBrazier(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new GildedBrazier(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(pPlayer->GetQuestLogForEntry(9678))
			{
				float SSX = pPlayer->GetPositionX();
				float SSY = pPlayer->GetPositionY();
				float SSZ = pPlayer->GetPositionZ();
				float SSO = pPlayer->GetOrientation();

				GameObject* Brazier = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(SSX, SSY, SSZ, 181956);
				if(Brazier)
				{
					Brazier->SetState(0);
					pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(17716, SSX, SSY, SSZ, SSO, true, false, 0, 0)->Despawn(600000, 0);
				}
			}
			else
			{
				pPlayer->BroadcastMessage("Missing required quest: The First Trial");
			}
		}
};

void SetupGhostlandsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181157, &AlterofTidalMastery::Create);
	mgr->register_gameobject_script(181157, &VanquishingAquantion::Create);
	mgr->register_gameobject_script(181956, &GildedBrazier::Create);
}