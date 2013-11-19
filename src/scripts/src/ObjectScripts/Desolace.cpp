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

class SerpentStatue : public GameObjectAIScript
{
public:
	SerpentStatue(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new SerpentStatue(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(6027);
		if(qle == NULL)
			return;

		Creature* naga = sEAS.SpawnCreature(pPlayer, 12369, 246.741f, 2953.3f, 5.8631f, 1.078f, 0);
		if(naga != NULL)
			naga->Despawn(6 * 60 * 1000, 0);
	}
};

class HandofIruxos : public GameObjectAIScript
{
public:
	HandofIruxos(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new HandofIruxos(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(5381);
		if(qle == NULL)
			return;

		Creature* demon = sEAS.SpawnCreature(pPlayer, 11876, -348.231f, 1763.85f, 138.371f, 4.42728f, 0);
		if(demon != NULL)
			demon->Despawn(6 * 60 * 1000, 0);
	}
};

class LegionPortals : public GameObjectAIScript
{
	public:
		LegionPortals(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new LegionPortals(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(5581);
			if(qle == NULL)
				return;

			if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
			{
				qle->SetMobCount(0, qle->GetMobCount(0) + 1);
				qle->SendUpdateAddKill(0);
				qle->UpdatePlayerFields();
			}
			return;
		}
};

void SetupDesolaceGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(177673, &SerpentStatue::Create);
	mgr->register_gameobject_script(176581, &HandofIruxos::Create);
	mgr->register_gameobject_script(177400, &LegionPortals::Create);
}