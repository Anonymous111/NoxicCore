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

class TheFallenExarch : public GameObjectAIScript
{
public:
	TheFallenExarch(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new TheFallenExarch(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10915);
		if(qle == NULL)
			return;

		Creature* exarch = sEAS.SpawnCreature(pPlayer, 22452, -3365.9f, 5143.19f, -9.00132f, 3.05f, 0);
		if(exarch != NULL)
			exarch->Despawn(6 * 60 * 1000, 0);
	}
};

class TerokksDownfall : public GameObjectAIScript
{
public:
	TerokksDownfall(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new TerokksDownfall(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(11073) && pPlayer->GetItemInterface()->GetItemCount(32720, 1))
		{
			pPlayer->CastSpell(pPlayer, 41004, false);
			/*float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(21838, SSX, SSY, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);*/
		}
		else
			pPlayer->BroadcastMessage("You need to have item: Time-Lost Offering and to have quest: Terokk's Downfall");
	}
};

class TheFinalCode : public GameObjectAIScript
{
	public:
		TheFinalCode(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new TheFinalCode(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10447);
			if(qle == NULL)
				return;

			if(qle->GetMobCount(1) < qle->GetQuest()->required_mobcount[1])
			{
				qle->SetMobCount(1, qle->GetMobCount(1) + 1);
				qle->SendUpdateAddKill(1);
				qle->UpdatePlayerFields();
			}
		}
};

class FirewingPointUpper : public GameObjectAIScript
{
public:
	FirewingPointUpper(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FirewingPointUpper(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -2260, 3223.16f, 5.534f, 1.60f);
	}
};

class FirewingPointLower : public GameObjectAIScript
{
public:
	FirewingPointLower(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FirewingPointLower(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -2263, 3111.45f, 136.35f, 3.65f);
	}
};

class FirewingPointOrb1 : public GameObjectAIScript
{
public:
	FirewingPointOrb1(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FirewingPointOrb1(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -2260.6f, 3186.5f, 23.6f, 4.724170f);
	}
};

class FirewingPointOrb2 : public GameObjectAIScript
{
public:
	FirewingPointOrb2(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new FirewingPointOrb2(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, -2250.4f, 3120.7f, 27.3f, 4.724170f);
	}
};

void SetupTerokkarForestGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(184999, &TheFallenExarch::Create);
	mgr->register_gameobject_script(185928, &TerokksDownfall::Create);
	mgr->register_gameobject_script(184725, &TheFinalCode::Create);
	mgr->register_gameobject_script(182546, &FirewingPointUpper::Create);
	mgr->register_gameobject_script(182547, &FirewingPointLower::Create);
	mgr->register_gameobject_script(182543, &FirewingPointOrb1::Create);
	mgr->register_gameobject_script(182548, &FirewingPointOrb2::Create);
}