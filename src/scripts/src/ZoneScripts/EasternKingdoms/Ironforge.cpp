/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

class KingMagniBronzebeard : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KingMagniBronzebeard);
	KingMagniBronzebeard(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		_unit->PlaySoundToSet(5896);
	}
};

class RoyalHistorianArchesonus : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* pPlayer, bool AutoSend)
	{
		if(pPlayer->GetQuestStatusForQuest(3702) == QMGR_QUEST_NOT_FINISHED)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2235, pPlayer);
			Menu->AddItem(2, "I am ready to listen.", 1);
			Menu->SendTo(pPlayer);
		}
	}

	void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		GossipMenu* Menu;
		switch(IntId)
		{
			case 1:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2236, pPlayer);
				Menu->AddItem(2, "That is tragic. How did this happen?", 2);
				Menu->SendTo(pPlayer);
			}break;
			case 2:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2237, pPlayer);
				Menu->AddItem(2, "Interesting, continue please.", 3);
				Menu->SendTo(pPlayer);
			}break;
			case 3:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2238, pPlayer);
				Menu->AddItem(2, "Unbelievable! How dare they??", 4);
				Menu->SendTo(pPlayer);
			}break;
			case 4:
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2239, pPlayer);
				Menu->AddItem(2, "Of course I will help!", 5);
				Menu->SendTo(pPlayer);
			}break;
			case 5:
			{
				pPlayer->Gossip_Complete();
				sQuestMgr.OnPlayerExploreArea(pPlayer, 3702);
			}break;
		}
	}
};

void SetupZoneIronforge(ScriptMgr* mgr)
{
	mgr->register_creature_script(2784, &KingMagniBronzebeard::Create);
	mgr->register_gossip_script(8879, new RoyalHistorianArchesonus());
}