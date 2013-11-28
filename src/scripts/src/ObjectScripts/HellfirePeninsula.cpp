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

//quest #9397
class KaliriNest : public GameObjectAIScript
{
	public:
		KaliriNest(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new KaliriNest(GO); }

		void OnActivate(Player* plr)
		{
			// mostly they are males
			if(Rand(20))
				sEAS.SpawnCreature(plr, 17034, plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), 2*60*1000);
			else
				sEAS.SpawnCreature(plr, 17039, plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), 2*60*1000);
		}
};

class HaaleshiAltar : public GameObjectAIScript
{
public:
	HaaleshiAltar(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new HaaleshiAltar(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->HasQuest(9418))
			sEAS.SpawnCreature(pPlayer, 17085, -1323.14f, 4042.12f, 117.0f, pPlayer->GetOrientation()+float(M_PI), 360000);
	}
};

class FalconTowerUpper : public GameObjectAIScript
{
public:
	FalconTowerUpper(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FalconTowerUpper(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -588.9f, 4070.8f, 93.8f, 4.724170f);
	}
};

class FalconTowerLower : public GameObjectAIScript
{
public:
	FalconTowerLower(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FalconTowerLower(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -592.2f, 4070.2f, 143.3f, 4.724170f);
	}
};

void SetupHellfirePeninsulaGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181582, &KaliriNest::Create);
	mgr->register_gameobject_script(181606, &HaaleshiAltar::Create);
	mgr->register_gameobject_script(184500, &FalconTowerUpper::Create);
	mgr->register_gameobject_script(184501, &FalconTowerLower::Create);
}