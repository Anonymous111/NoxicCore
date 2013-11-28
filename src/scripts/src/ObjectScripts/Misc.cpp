/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 * Copyright (C) 2011-2013 ArcScripts2 Team
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

class Blacksmithing_Plans_Use : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(Blacksmithing_Plans_Use)
	Blacksmithing_Plans_Use(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnLootTaken(Player* pLooter, ItemPrototype* pItemInfo)
	{
		float SSX = pLooter->GetPositionX();
		float SSY = pLooter->GetPositionY();
		float SSZ = pLooter->GetPositionZ();
		float SSO = pLooter->GetOrientation();

		Creature* NewCreature = pLooter->GetMapMgr()->GetInterface()->SpawnCreature(11120, SSX, SSY, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);
	}
};

class DeathGate1 : public GameObjectAIScript
{
public:
	DeathGate1(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new DeathGate1(GO); }

	void OnSpawn()
	{
		RegisterAIUpdateEvent(500);
	}

	void AIUpdate()
	{
		Player* pPlayer = _gameobject->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ());
		if(!pPlayer)
			return;

		if(_gameobject->CalcDistance(_gameobject, pPlayer) <= 1.5f && pPlayer->GetMapId() == 609)
			pPlayer->SafeTeleport(609, 4298, 2390.18f, -5640.28f, 420.84f, 0.57f);
		else if(_gameobject->CalcDistance(_gameobject, pPlayer) <= 1.5f && pPlayer->GetMapId() == 0)
			pPlayer->SafeTeleport(0, pPlayer->GetInstanceID(), 2387.468994f, -5642.544922f, 420.809937f, 0.620461f);
	}
};

class DeathGate2 : public GameObjectAIScript
{
public:
	DeathGate2(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new DeathGate2(GO); }

	void OnSpawn()
	{
		RegisterAIUpdateEvent(500);
	}

	void AIUpdate()
	{
		Player* pPlayer = _gameobject->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ());
		if(!pPlayer)
			return;

		if(_gameobject->CalcDistance(_gameobject, pPlayer) <= 1.5f && pPlayer->GetMapId() == 609)
			pPlayer->SafeTeleport(609, 4298, 2397.57f, -5636.03f, 377.05f, 0.57f);
		else if(_gameobject->CalcDistance(_gameobject, pPlayer) <= 1.5f && pPlayer->GetMapId() == 0)
			pPlayer->SafeTeleport(0, pPlayer->GetInstanceID(), 2395.233154f, -5637.875488f, 377.086884f, 0.520721f);
	}
};

class DeathGate3 : public GameObjectAIScript
{
public:
	DeathGate3(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new DeathGate3(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->getClass() == 6)
		{
			if(pPlayer->GetMapId() == 609)
				pPlayer->SafeTeleport(609, pPlayer->GetInstanceID(), 2354.496826f, -5661.948730f, 389.454865f, 0.365210f);
			else
				pPlayer->SafeTeleport(0, pPlayer->GetInstanceID(), 2354.496826f, -5661.948730f, 389.454865f, 0.365210f);
		}
	}
};

class ManaThistle : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(ManaThistle)
	ManaThistle(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnLootTaken(Player* pLooter, ItemPrototype* pItemInfo) 
	{
		Spell* pSpell = new Spell(_gameobject, dbcSpell.LookupEntryForced(28718), true, NULL);
		SpellCastTargets targets(pLooter->GetGUID());
		pSpell->prepare(&targets); // Cast spell: "Mana Thistle".
	}
};

class TheRootofAllEvil : public GameObjectAIScript
{
	public:
		TheRootofAllEvil(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new TheRootofAllEvil(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(8481);
			if(qle == NULL)
				return;

			Creature* xandivious = sEAS.SpawnCreature(pPlayer, 15623, pPlayer->GetPositionX() + 5, pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
			if(xandivious != NULL)
				xandivious->Despawn(6 * 60 * 1000, 0);
		}
};

class TitanRelic : public GameObjectAIScript
{
public:
	TitanRelic(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript * Create(GameObject* GO) { return new TitanRelic(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->m_bg && pPlayer->m_bg->GetType() == BATTLEGROUND_STRAND_OF_THE_ANCIENTS)
		{
			GameObject* sota = (GameObject*)pPlayer->m_bg;
			sota->Rebuild();
		}
	}
};

void SetupMiscGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(173232, &Blacksmithing_Plans_Use::Create);
	mgr->register_gameobject_script(191538, &DeathGate1::Create);
	mgr->register_gameobject_script(191539, &DeathGate2::Create);
	mgr->register_gameobject_script(190942, &DeathGate3::Create);
	mgr->register_gameobject_script(181281, &ManaThistle::Create);
	mgr->register_gameobject_script(180672, &TheRootofAllEvil::Create);
	mgr->register_gameobject_script(192829, &TitanRelic::Create);
}