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
class NeltharakusTale_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(plr->GetQuestLogForEntry(10814))
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10613, plr);
				Menu->AddItem(0, "I am listening, dragon", 1);
				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			if(!pObject->IsCreature())
				return;

			switch(IntId)
			{
				case 1:
					{
						GossipMenu* Menu;
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10614, plr);
						Menu->AddItem(0, "But you are dragons! How could orcs do this to you?", 2);
						Menu->SendTo(plr);
					}
					break;
				case 2:
					{
						GossipMenu* Menu;
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10615, plr);
						Menu->AddItem(0, "Your mate?", 3);
						Menu->SendTo(plr);
					}
					break;
				case 3:
					{
						GossipMenu* Menu;
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10616, plr);
						Menu->AddItem(0, "I have battled many beasts, dragon. I will help you.", 4);
						Menu->SendTo(plr);
					}
					break;
				case 4:
					{
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(10814);
						if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
						{
							pQuest->SetMobCount(0, 1);
							pQuest->SendUpdateAddKill(0);
							pQuest->UpdatePlayerFields();
						}
					}
					break;
			}
		}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Flanis Swiftwing
class FlanisSwiftwing_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* Plr);
		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code);
		void GossipEnd(Object* pObject, Player* Plr, Creature* pCreature);

};

void FlanisSwiftwing_Gossip::GossipHello(Object* pObject, Player* plr)
{
	GossipMenu* Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
	if(plr->GetQuestLogForEntry(10583) != NULL)
		Menu->AddItem(0, "Examine the corpse", 1);

	Menu->SendTo(plr);
};

void FlanisSwiftwing_Gossip::GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
{
	Creature* pCreature = (pObject->IsCreature()) ? TO_CREATURE(pObject) : NULL;
	if(pCreature == NULL)
		return;
	if(IntId == 1)
	{
		Item* item;
		item = objmgr.CreateItem(30658 , plr);
		item->SetStackCount(1);
		if(!plr->GetItemInterface()->AddItemToFreeSlot(item))
		{
			plr->GetSession()->SendNotification("No free slots were found in your inventory!");
			item->DeleteMe();
		}
		else
		{
			plr->SendItemPushResult(false, true, false, true, plr->GetItemInterface()->LastSearchResult()->ContainerSlot,
			                        plr->GetItemInterface()->LastSearchResult()->Slot, 1, item->GetEntry(), item->GetItemRandomSuffixFactor(),
			                        item->GetItemRandomPropertyId(), item->GetStackCount());
		}
	}
};
void FlanisSwiftwing_Gossip::GossipEnd(Object* pObject, Player* Plr, Creature* pCreature)
{
	GossipScript::GossipEnd(pObject, Plr);
}

void SetupShadowmoon(ScriptMgr* mgr)
{
	mgr->register_gossip_script(21657, new NeltharakusTale_Gossip());
	mgr->register_gossip_script(21727, new FlanisSwiftwing_Gossip()); //Add Flanis' Pack
}