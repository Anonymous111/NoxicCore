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

class ZethGorMustBurnAlliance : public GameObjectAIScript
{
public:
	ZethGorMustBurnAlliance(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new ZethGorMustBurnAlliance(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10895);
		if(pQuest != NULL)
		{
			GameObject* pBeacon = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 184661);
			if(pBeacon != NULL && pBeacon->GetUInt32Value(GAMEOBJECT_FLAGS) > 0)
				pBeacon->SetUInt32Value(GAMEOBJECT_FLAGS, (pBeacon->GetUInt32Value(GAMEOBJECT_FLAGS) - 1));

			// Northern Zeth'Gor Tower
			if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				GameObject* pNorthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-820.0f, 2029.0f, 55.0f, 300150);
				if(pNorthern != NULL && pPlayer->CalcDistance(pPlayer, pNorthern) < 40) // if reduced the server will crash when out of range
				{
					pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();

					GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -819.77f, 2029.09f, 55.6082f, 0, 4, 0, 0, 0, 0);
					if(pGameobject != NULL)
						sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

					return;
				}
			}

			// Southern Zeth'Gor Tower
			if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
			{
				GameObject* pSouthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-1150.0f, 2110.0f, 84.0f, 300150);
				if(pSouthern != NULL && pPlayer->CalcDistance(pPlayer, pSouthern) < 40)
				{
					pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();

					GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -1150.53f, 2109.92f, 84.4204f, 0, 4, 0, 0, 0, 0);
					if(pGameobject != NULL)
						sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

					return;
				}
			}

			// Forge Zeth'Gor Tower
			if(pQuest->GetMobCount(2) < pQuest->GetQuest()->required_mobcount[2])
			{
				GameObject* pForge = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-893.0f, 1919.0f, 82.0f, 300150);
				if(pForge != NULL && pPlayer->CalcDistance(pPlayer, pForge) < 40)
				{
					pQuest->SetMobCount(2, pQuest->GetMobCount(2) + 1);
					pQuest->SendUpdateAddKill(2);
					pQuest->UpdatePlayerFields();

					GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -893.499f, 1919.27f, 81.6449f, 0, 4, 0, 0, 0, 0);
					if(pGameobject != NULL)
						sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

					return;
				}
			}

			// Foothill Zeth'Gor Tower
			if(pQuest->GetMobCount(3) < pQuest->GetQuest()->required_mobcount[3])
			{
				GameObject* pFoothill = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-978.0f, 1879.0f, 111.0f, 300150);
				if(pFoothill != NULL && pPlayer->CalcDistance(pPlayer, pFoothill) < 40)
				{
					pQuest->SetMobCount(3, pQuest->GetMobCount(3) + 1);
					pQuest->SendUpdateAddKill(3);
					pQuest->UpdatePlayerFields();

					GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -977.713f, 1879.500f, 110.892f, 0, 4, 0, 0, 0, 0);
					if(pGameobject != NULL)
						sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);

					return;
				}
			}
			else
				pPlayer->BroadcastMessage("You are too far away!");
		}
		else
			pPlayer->BroadcastMessage("Missing required quest: Zeth'Gor Must Burn");
	}
};

void SetupHellfirePeninsulaGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181582, &KaliriNest::Create);
	mgr->register_gameobject_script(181606, &HaaleshiAltar::Create);
	mgr->register_gameobject_script(184500, &FalconTowerUpper::Create);
	mgr->register_gameobject_script(184501, &FalconTowerLower::Create);
	mgr->register_gameobject_script(184661, &ZethGorMustBurnAlliance::Create);
}