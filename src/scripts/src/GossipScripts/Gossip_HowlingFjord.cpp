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

class Plaguethis_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
			Menu->AddItem(0, "Where would you like to fly too?", 2);
			if(plr->GetQuestLogForEntry(11332) != NULL)
				Menu->AddItem(0, "Greer, I need a gryphon to ride and some bombs to drop on New Agamand!", 1);


			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? TO_CREATURE(pObject) : NULL;
			if(pCreature == NULL)
				return;

			switch(IntId)
			{
				case 1:
					{
						Item* item;
						item = objmgr.CreateItem(33634 , plr);
						item->SetStackCount(10);

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

						if(pCreature->GetEntry() == 23859)
						{
							TaxiPath* path = sTaxiMgr.GetTaxiPath(745);
							plr->TaxiStart(path, 17759, 0);
						}
						break;
					}
				case 2:
					{
						plr->GetSession()->SendTaxiList(pCreature);
						break;
					}
			}
		}

};

void SetupNetherstormGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(23859, new Plaguethis_Gossip()); // Thanks Dzjhenghiz
}