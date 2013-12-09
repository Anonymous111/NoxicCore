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

#include "../Setup.h"

class EthereumTransponderZeta : public GameObjectAIScript
{
public:
	EthereumTransponderZeta(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new EthereumTransponderZeta(GO); }

	void OnActivate(Player* pPlayer)
	{
		Creature* commander = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 20482);
		if(commander)
			return;

		if(pPlayer->GetQuestLogForEntry(10339))
		{
			float SSX = 4017.96f;
			float SSY = 2315.91f;
			float SSZ = 116.418f;
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(20482, SSX, SSY, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(1 * 60 * 1000, 0);
		}
	}
};

class TyraliusPrison : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(TyraliusPrison)
	TyraliusPrison(GameObject* goinstance) : GameObjectAIScript(goinstance){}

	void OnActivate(Player* pPlayer)
	{
		// Spawning Captain Tyralius
		sEAS.SpawnCreature(pPlayer, 20787, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 2*60*1000);
	}
};

void SetupNetherstormGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(184383, &EthereumTransponderZeta::Create);
	mgr->register_gameobject_script(184588, &TyraliusPrison::Create);
}