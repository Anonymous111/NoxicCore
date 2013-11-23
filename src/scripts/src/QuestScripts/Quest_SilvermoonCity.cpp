/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

class ThePathoftheAdept : public GameObjectAIScript
{
public:
	ThePathoftheAdept(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new ThePathoftheAdept(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(!pPlayer)
			return;

		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(9692);
		if(pQuest == NULL)
			return;

		Creature* zelemar = sEAS.SpawnCreature(pPlayer, 17830, pPlayer->GetPositionX()+5, pPlayer->GetPositionY()+5, pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
		zelemar->Despawn(6*60*1000, 0);
	}
};

class PathoftheAdept : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			if(!pPlayer)
				return;

			GossipMenu* Menu;
			Creature* lord = TO_CREATURE(pObject);
			if(lord == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);
			if(pPlayer->GetQuestLogForEntry(9692))
				Menu->AddItem(0, "Take Insignia", 1);

			Menu->SendTo(pPlayer);
		}

		void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!pPlayer)
				return;

			Creature* lord = TO_CREATURE(pObject);
			if(lord == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, pPlayer);
				break;
				case 1:
				{
					sEAS.AddItem(24226, pPlayer);
					return;
				}
				break;
			}
		}

};

class LordDawnstar : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(LordDawnstar);
		LordDawnstar(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
			_unit->SetStandState(7);
			_unit->setDeathState(CORPSE);
			_unit->GetAIInterface()->m_canMove = false;
		}
};

void SetupSilvermoonCity(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(182024, &ThePathoftheAdept::Create);

	mgr->register_gossip_script(17832, new PathoftheAdept());

	mgr->register_creature_script(17832, &LordDawnstar::Create);
}