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

class Obsidias_Egg : public GameObjectAIScript
{
public:
	Obsidias_Egg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new Obsidias_Egg(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(11078))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(23282, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
				pPlayer->BroadcastMessage("Missing required quest : To Rule The Skies");
	}
};

class Rivendarks_Egg : public GameObjectAIScript
{
public:
	Rivendarks_Egg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new Rivendarks_Egg(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(11078))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(23061, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
			pPlayer->BroadcastMessage("Missing required quest : To Rule The Skies");
	}
};

class Furywings_Egg : public GameObjectAIScript
{
public:
	Furywings_Egg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new Furywings_Egg(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(11078))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(23261, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
			pPlayer->BroadcastMessage("Missing required quest : To Rule The Skies");
	}
};

class Insidions_Egg : public GameObjectAIScript
{
public:
	Insidions_Egg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new Insidions_Egg(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(11078))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(23281, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
			pPlayer->BroadcastMessage("Missing required quest: To Rule The Skies");
	}
};

class TheThunderspike : public GameObjectAIScript
{
	public:
		TheThunderspike(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new TheThunderspike(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(!pPlayer->GetQuestLogForEntry(10526))
				return;

			// Wth is that ? To remove ?
			GameObject* gobj = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 184729);
			if(!gobj)
				return;

			gobj->Despawn(6 * 60 * 1000, 0);

			Creature* spike = sEAS.SpawnCreature(pPlayer, 21319, 1315.54f, 6688.33f, -18, 0.001f, 0);
			spike->Despawn(5 * 60 * 1000, 0);
		}
};

class PowerConverter : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(PowerConverter)
	PowerConverter(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->HasQuest(10584))
		{
			Creature* Elec = sEAS.SpawnCreature(pPlayer, 21729, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ(), _gameobject->GetOrientation(), 1000);
			Elec->GetAIInterface()->AttackReaction(pPlayer, 1);
		}
		_gameobject->Despawn(0, 1000);
	}
};

class NetherEgg : public GameObjectAIScript
{
public:
	NetherEgg(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new NetherEgg(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10609);
		if(pQuest == NULL)
			return;

		Creature* whelp = sEAS.SpawnCreature(pPlayer, 20021, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ(), 0, 0);
		if(whelp != NULL)
			whelp->Despawn(5 * 60 * 1000, 0);

		_gameobject->Despawn(300000, 0);
	}
};

class LegionObelisk : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(LegionObelisk)
	LegionObelisk(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(!pPlayer->HasQuest(10821))
			return;

		GameObject* obelisk1 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2898.92f, 4759.29f, 277.408f, 185198);
		GameObject* obelisk2 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2942.30f, 4752.28f, 285.553f, 185197);
		GameObject* obelisk3 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2834.39f, 4856.67f, 277.632f, 185196);
		GameObject* obelisk4 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2923.37f, 4840.36f, 278.450f, 185195);
		GameObject* obelisk5 = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2965.75f, 4835.25f, 277.949f, 185193);
		if(!obelisk1 || !obelisk2 || !obelisk3 || !obelisk4 || !obelisk5)
			return;

		_gameobject->SetState( 0 );
		if(obelisk1->GetState() == 0 && obelisk2->GetState() == 0 && obelisk3->GetState() == 0 && obelisk4->GetState() == 0 && obelisk5->GetState() == 0)
			sEAS.SpawnCreature(pPlayer, 19963, 2943.59f, 4779.05f, 284.49f, 1.89f, 1000);

		sEventMgr.AddEvent(obelisk1, &GameObject::SetState, (uint8)1, EVENT_UNK, 600000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(obelisk2, &GameObject::SetState, (uint8)1, EVENT_UNK, 600000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(obelisk3, &GameObject::SetState, (uint8)1, EVENT_UNK, 600000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(obelisk4, &GameObject::SetState, (uint8)1, EVENT_UNK, 600000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(obelisk5, &GameObject::SetState, (uint8)1, EVENT_UNK, 600000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
};

class StasisChamberAlpha : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(StasisChamberAlpha)
	StasisChamberAlpha(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(!pPlayer->HasQuest(10974))
			return;

		Creature *pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(3989.094482f, 6071.562500f, 266.416656f, 22920);
		if(pCreature != NULL)
		{
			pCreature->SetFaction(14);
			pCreature->SetScale(1.0f);
			pCreature->GetAIInterface()->setNextTarget(pPlayer);
			pCreature->GetAIInterface()->AttackReaction(pPlayer, 1);
		}
	}
};

class powerconv : public GameObjectAIScript
{
	public:
		powerconv(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new powerconv(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(10584);
			if(qle == NULL)
				return;

			Creature* magneto = sEAS.SpawnCreature(pPlayer, 21729, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionZ(), 0, 0);
			if(magneto != NULL)
			{
				magneto->Despawn(5 * 60 * 1000, 0);
			}

			_gameobject->Despawn(300000, 0);
		}
};

void SetupBladeEdgeMountainsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(185932, &Obsidias_Egg::Create);
	mgr->register_gameobject_script(185936, &Rivendarks_Egg::Create);
	mgr->register_gameobject_script(185937, &Furywings_Egg::Create);
	mgr->register_gameobject_script(185938, &Insidions_Egg::Create);
	mgr->register_gameobject_script(184729, &TheThunderspike::Create);
	mgr->register_gameobject_script(184906, &PowerConverter::Create); // Power Converter
	mgr->register_gameobject_script(184867, &NetherEgg::Create); // Nether Drake Egg
	uint32 LegionObliskIds[] = { 185193, 185195, 185196, 185197, 185198, 0 };
	mgr->register_gameobject_script(LegionObliskIds, &LegionObelisk::Create); // Legion Obelisk
	mgr->register_gameobject_script(185512, &StasisChamberAlpha::Create); // Stasis Chamber Alpha
	mgr->register_gameobject_script(184906, &powerconv::Create);
}