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

class CuregosGold : public GameObjectAIScript
{
public:
	CuregosGold(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new CuregosGold(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(2882);
		if(qle == NULL)
			return;

		pPlayer->CastSpell(pPlayer, 11462, true); // Cast spell: "Summon Pirate Treasure and Trigger Mob".
		/*Creature* pirate = sEAS.SpawnCreature(pPlayer, 7899, pPlayer->GetPositionX() + RandomFloat(5.0f), pPlayer->GetPositionY() + RandomFloat(5.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(pirate != NULL)
			pirate->Despawn(6 * 60 * 1000, 0);

		pirate = sEAS.SpawnCreature(pPlayer, 7899, pPlayer->GetPositionX() - RandomFloat(5.0f), pPlayer->GetPositionY() + RandomFloat(5.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(pirate != NULL)
			pirate->Despawn(6 * 60 * 1000, 0);

		pirate = sEAS.SpawnCreature(pPlayer, 7901, pPlayer->GetPositionX() + RandomFloat(5.0f), pPlayer->GetPositionY() - RandomFloat(5.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(pirate != NULL)
			pirate->Despawn(6 * 60 * 1000, 0);

		pirate = sEAS.SpawnCreature(pPlayer, 7901, pPlayer->GetPositionX() + RandomFloat(5.0f), pPlayer->GetPositionY() + RandomFloat(5.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(pirate != NULL)
			pirate->Despawn(6 * 60 * 1000, 0);

		pirate = sEAS.SpawnCreature(pPlayer, 7902, pPlayer->GetPositionX() - RandomFloat(5.0f), pPlayer->GetPositionY() - RandomFloat(5.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		if(pirate != NULL)
			pirate->Despawn(6 * 60 * 1000, 0);

		GameObject* gobj = sEAS.SpawnGameobject(pPlayer, 142194, pPlayer->GetPositionX() + 5, pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 1, 0, 0, 0, 0);
		sEAS.GameobjectDelete(gobj, 10 * 60 * 1000);*/
	}
};

void SetupTanarisGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(142189, &CuregosGold::Create);
}