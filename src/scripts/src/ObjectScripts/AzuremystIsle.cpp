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

class ProphecyofAkida : public GameObjectAIScript
{
public:
	ProphecyofAkida(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new ProphecyofAkida(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(9544);
		if(qle == NULL)
			return;

		if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
		{
			qle->SetMobCount(0, qle->GetMobCount(0) + 1);
			qle->SendUpdateAddKill(0);
			qle->UpdatePlayerFields();
		}

		Creature* prisoner = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17375);
		if(!prisoner)
			return;

		prisoner->Despawn(1, 6 * 60 * 1000);
	}
};

class StrengthofOne : public GameObjectAIScript
{
	public:
		StrengthofOne(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new StrengthofOne(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(9582);
			if(qle == NULL)
				return;

			// What is this ? :O To remove ?
			Creature* reaver = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17556);
			if(reaver)
			{
				Creature* reaver2 = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(17556, reaver->GetPositionX(), reaver->GetPositionY(), reaver->GetPositionZ(), reaver->GetOrientation(), true, false, 0, 0);
				reaver2->Despawn(5 * 60 * 1000, 0);
				reaver->Despawn(1, 5 * 60 * 1000);
			}

		}
};

class HealingTheLake : public GameObjectAIScript
{
	public:
		HealingTheLake(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new HealingTheLake(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(181433);
			if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
		}
};

void SetupAzuremystIsleGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181730, &ProphecyofAkida::Create);
	mgr->register_gameobject_script(181849, &StrengthofOne::Create);
	mgr->register_gameobject_script(181433, &HealingTheLake::Create);
}