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

class APlagueUponThee : public GameObjectAIScript
{
public:
	APlagueUponThee(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new APlagueUponThee(GO); }

	void OnActivate(Player* pPlayer)
	{
		if( pPlayer->GetQuestLogForEntry(5902) || pPlayer->GetQuestLogForEntry(5904) )
		{
			GameObject * go = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(),pPlayer->GetPositionY(),pPlayer->GetPositionZ(), 177491);
			if(go == NULL)
			{
				GameObject * barel = sEAS.SpawnGameobject(pPlayer, 177491, 2449.51f, -1662.32f, 104.38f, 1.0f, 1, 0, 0, 0, 0);
				sEAS.GameobjectDelete(barel, 2*60*1000);
			}
		}
	}
};

class UlagTheCleaver : public GameObjectAIScript
{
public:
	UlagTheCleaver(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new UlagTheCleaver(GO); }

	void OnActivate(Player* pPlayer)
	{
		Creature* Ulag = NULL;
		GameObject* pDoor = NULL;
		Ulag = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2390.101807f, 336.676788f, 40.015614f, 6390);
		pDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2388.480029f, 338.3901f, 40.092899f, 176594);
		QuestLogEntry* en = pPlayer->GetQuestLogForEntry(1819);
		if(!en || pDoor == NULL || Ulag)
			return;

		Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(6390, 2390.101807f, 336.676788f, 40.015614f, 2.259590f, true, false, 0, 0);
		if(NewCreature != NULL)
		{
			NewCreature->Despawn(180000, 0);
			NewCreature->GetAIInterface()->setNextTarget(pPlayer);
			NewCreature->GetAIInterface()->AttackReaction(pPlayer, 1);
			pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 33);
			pDoor->SetByte(GAMEOBJECT_BYTES_1, 0, 0);
		};
	}
};

class AndorhalTower1 : public GameObjectAIScript
{
	public:

		AndorhalTower1(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AndorhalTower1(GO); }

		void OnActivate(Player* pPlayer)
		{

			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(5097);

			if(pQuest == NULL)
			{
				pQuest = pPlayer->GetQuestLogForEntry(5098);
				if(pQuest == NULL)
					return;
			}

			if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
		}
};

class AndorhalTower2 : public GameObjectAIScript
{
	public:

		AndorhalTower2(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AndorhalTower2(GO); }

		void OnActivate(Player* pPlayer)
		{

			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(5097);

			if(pQuest == NULL)
			{
				pQuest = pPlayer->GetQuestLogForEntry(5098);
				if(pQuest == NULL)
					return;
			}

			if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
			{
				pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
				pQuest->SendUpdateAddKill(1);
				pQuest->UpdatePlayerFields();

			}
		}
};

class AndorhalTower3 : public GameObjectAIScript
{
	public:
		AndorhalTower3(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AndorhalTower3(GO); }

		void OnActivate(Player* pPlayer)
		{

			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(5097);

			if(pQuest == NULL)
			{
				pQuest = pPlayer->GetQuestLogForEntry(5098);
				if(pQuest == NULL)
					return;
			}

			if(pQuest->GetMobCount(2) < pQuest->GetQuest()->required_mobcount[2])
			{
				pQuest->SetMobCount(2, pQuest->GetMobCount(2) + 1);
				pQuest->SendUpdateAddKill(2);
				pQuest->UpdatePlayerFields();
			}
		}
};

class AndorhalTower4 : public GameObjectAIScript
{
	public:
		AndorhalTower4(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AndorhalTower4(GO); }

		void OnActivate(Player* pPlayer)
		{

			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(5097);

			if(pQuest == NULL)
			{
				pQuest = pPlayer->GetQuestLogForEntry(5098);
				if(pQuest == NULL)
					return;
			}

			if(pQuest->GetMobCount(3) < pQuest->GetQuest()->required_mobcount[3])
			{
				pQuest->SetMobCount(3, pQuest->GetMobCount(3) + 1);
				pQuest->SendUpdateAddKill(3);
				pQuest->UpdatePlayerFields();
			}
		}
};

void SetupWesternPlaguelandsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(177490, &APlagueUponThee::Create);
	mgr->register_gameobject_script(104593, &UlagTheCleaver::Create);
	mgr->register_gameobject_script(310030, &AndorhalTower1::Create);
	mgr->register_gameobject_script(310031, &AndorhalTower2::Create);
	mgr->register_gameobject_script(310032, &AndorhalTower3::Create);
	mgr->register_gameobject_script(310033, &AndorhalTower4::Create);
}