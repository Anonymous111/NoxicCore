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

/*--------------------------------------------------------------------------------------------------------*/
// Crisis at the Sunwell

class ScryingOrb : public GameObjectAIScript
{
	public:
		ScryingOrb(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new ScryingOrb(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(11490);
			if(pQuest)
			{
				float SSX = pPlayer->GetPositionX();
				float SSY = pPlayer->GetPositionY();
				float SSZ = pPlayer->GetPositionZ();

				GameObject* pOrb = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(SSX, SSY, SSZ, 187578);
				if(pOrb)
				{
					pOrb->SetState(0);
					pQuest->SetMobCount(0, 1);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
				}
				return;
			}
			else
			{
				pPlayer->BroadcastMessage("Missing required quest : The Scryer's Scryer");
			}
		}
};









#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, pPlayer); \
    Menu->SendTo(pPlayer);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Ayren Cloudbreaker Gossip

class SCRIPT_DECL AyrenCloudbreaker_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12252, pPlayer);

			if(pPlayer->GetQuestLogForEntry(11532) || pPlayer->GetQuestLogForEntry(11533))
				Menu->AddItem(0, "Speaking of action, I've been ordered to undertake an air strike.", 1);

			if(pPlayer->GetQuestLogForEntry(11543) || pPlayer->GetQuestLogForEntry(11542))
				Menu->AddItem(0, "I need to intercept the Dawnblade reinforcements.", 2);

			Menu->SendTo(pPlayer);
		}

		void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* Code)
		{
			switch(IntId)
			{
				case 1:
					{
						TaxiPath* pPath = sTaxiMgr.GetTaxiPath(779);
						pPlayer->TaxiStart(pPath, 22840, 0);
						pPlayer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
					}
					break;
				case 2:
					{
						TaxiPath* pPath = sTaxiMgr.GetTaxiPath(784);
						pPlayer->TaxiStart(pPath, 22840, 0);
						pPlayer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
					}
					break;
			}
		}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Unrestrained Dragonhawk Gossip

class SCRIPT_DECL UnrestrainedDragonhawk_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12371, pPlayer);
			if(pPlayer->GetQuestLogForEntry(11543) || pPlayer->GetQuestLogForEntry(11542))
				Menu->AddItem(0, "<Ride the dragonhawk to Sun's Reach>", 1);

			Menu->SendTo(pPlayer);
		}

		void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* Code)
		{
			switch(IntId)
			{
				case 1:
					{
						TaxiPath* pPath = sTaxiMgr.GetTaxiPath(788);
						pPlayer->TaxiStart(pPath, 22840, 0);
						pPlayer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
					}
					break;
			}
		}

};

// The Battle for the Sun's Reach Armory
class TheBattleForTheSunReachArmory : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(TheBattleForTheSunReachArmory);
		TheBattleForTheSunReachArmory(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* pKiller)
		{
			if(pKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = (TO_PLAYER(pKiller))->GetQuestLogForEntry(11537);
				if(pQuest == NULL)
				{
					pQuest = (TO_PLAYER(pKiller))->GetQuestLogForEntry(11538);
					if(pQuest == NULL)
						return;
				}

				if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[ 1 ])
				{
					uint32 newcount = pQuest->GetMobCount(1) + 1;
					pQuest->SetMobCount(1, newcount);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
		}
};



void SetupIsleOfQuelDanas(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(187578, &ScryingOrb::Create);

	mgr->register_creature_script(24999, &TheBattleForTheSunReachArmory::Create);
	mgr->register_creature_script(25001, &TheBattleForTheSunReachArmory::Create);
	mgr->register_creature_script(25002, &TheBattleForTheSunReachArmory::Create);

	mgr->register_gossip_script(25059, new AyrenCloudbreaker_Gossip());
	mgr->register_gossip_script(25236, new UnrestrainedDragonhawk_Gossip());
}