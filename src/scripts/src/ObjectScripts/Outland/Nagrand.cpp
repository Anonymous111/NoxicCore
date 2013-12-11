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

#include "../Setup.h"

class BringMetheEgg : public GameObjectAIScript
{
public:
	BringMetheEgg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new BringMetheEgg(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10111);
		if(qle == NULL)
			return;

		if(!pPlayer->HasAura(33382))
			pPlayer->CastSpell(pPlayer, 33382, true);
	}
};

class MysteriousEgg : public GameObjectAIScript
{
public:
	MysteriousEgg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new MysteriousEgg(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10111);
		if(qle == NULL)
			return;

		if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
		{
			qle->SetMobCount(0, qle->GetMobCount(0) + 1);
			qle->SendUpdateAddKill(0);
			qle->UpdatePlayerFields();
		}

		Creature* bird = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 19055);
		if(bird)
			return;

		bird = sEAS.SpawnCreature(pPlayer, 19055, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(bird != NULL)
			bird->Despawn(5*60*1000, 0);
	}
};

void SetupNagrandGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(183146, &BringMetheEgg::Create);
	mgr->register_gameobject_script(183147, &MysteriousEgg::Create);
}