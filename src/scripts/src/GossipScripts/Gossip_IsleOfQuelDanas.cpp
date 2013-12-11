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

void SetupIsleOfQuelDanasGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(25059, new AyrenCloudbreaker_Gossip());
	mgr->register_gossip_script(25236, new UnrestrainedDragonhawk_Gossip());
}