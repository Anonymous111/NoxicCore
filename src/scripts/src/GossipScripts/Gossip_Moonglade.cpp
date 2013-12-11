/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

class SilvaFilnaveth_Gossip : public Arcpro::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcpro::Gossip::Menu menu(pObject->GetGUID(), 0);
			if(plr->getClass() == DRUID && plr->getRace() == RACE_NIGHTELF)
			{
				menu.setTextID(4914);
				menu.AddItem(Arcpro::Gossip::ICON_CHAT, "I'd like to fly to Rut'theran Village.", 1);
			}
			else if(plr->getClass() == DRUID && plr->getRace() == RACE_TAUREN)
				menu.setTextID(4915);
			else
				menu.setTextID(4913);

			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;
			plr->TaxiStart(sTaxiMgr.GetTaxiPath(315), 479, 0); // Hippogryph
		}

		void Destroy() { delete this; }

};

class BunthenPlainswind_Gossip : public Arcpro::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcpro::Gossip::Menu menu(pObject->GetGUID(), 0);
			if(plr->getClass() == DRUID && plr->getRace() == RACE_TAUREN)
			{
				menu.setTextID(4918);
				menu.AddItem(Arcpro::Gossip::ICON_CHAT, "I'd like to fly to Thunder Bluff.", 1);
			}
			else if(plr->getClass() == DRUID && plr->getRace() == RACE_NIGHTELF)
				menu.setTextID(4917);
			else
				menu.setTextID(4916);

			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;
			plr->TaxiStart(sTaxiMgr.GetTaxiPath(316), 295, 0); // Wyvern
		}

		void Destroy() { delete this; }
};

// bear ghost gossip
#define GOSSIP_GHOST_BEAR_A    "What do you represent, spirit?"
#define GOSSIP_GHOST_BEAR_B    "I seek to understand the importance of strength of the body."
#define GOSSIP_GHOST_BEAR_C    "I seek to understand the importance of strength of the heart."
#define GOSSIP_GHOST_BEAR_D    "I have heard your words, Great Bear Spirit, and I understand. I now seek your blessings to fully learn the way of the Claw."

class SCRIPT_DECL BearGhost_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4719, plr);

			if(plr->HasQuest(5930)) // horde
			{
				Menu->AddItem(0, GOSSIP_GHOST_BEAR_A, 1);
			}
			else if(plr->HasQuest(5929)) // ally
			{
				Menu->AddItem(0, GOSSIP_GHOST_BEAR_A, 5);
			}

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature*  pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(!pObject->IsCreature())
				return;

			GossipMenu* Menu;
			switch(IntId)
			{
				case 0: // Return to start
					GossipHello(pCreature, plr);
					break;
				case 1:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4721, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_B, 2);
						Menu->SendTo(plr);
						break;
					}
				case 2:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4733, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_C, 3);
						Menu->SendTo(plr);
						break;
					}
				case 3:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4734, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_D, 4);
						Menu->SendTo(plr);
						break;
					}
				case 4:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4735, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(5930);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();
						break;
					}
				case 5:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4721, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_B, 6);
						Menu->SendTo(plr);
						break;
					}
				case 6:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4733, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_C, 7);
						Menu->SendTo(plr);
						break;
					}
				case 7:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4734, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_D, 8);
						Menu->SendTo(plr);
						break;
					}
				case 8:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4735, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(5929);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();
						break;
					}
			}
		}
};

void SetupMoongladeGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(11800, new SilvaFilnaveth_Gossip); // Silva Fil'naveth
	mgr->register_creature_gossip(11798, new BunthenPlainswind_Gossip); // Bunthen Plainswind
	mgr->register_gossip_script(11956, new BearGhost_Gossip); // Great Bear Spirit
}