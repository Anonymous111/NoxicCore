/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
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

class TiareGossipScript : public GossipScript
{
	public:
		void OnHello(Object* pObject, Player* Plr, bool AutoSend)
		{
			Arcpro::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 1, Plr, 1, 0, "Teleport me to Amber Ledge!");
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* EnteredCode)
		{
			Arcpro::Gossip::Menu::Complete(plr);
			TO_CREATURE(pObject)->CastSpell(plr, dbcSpell.LookupEntry(50135), true);
		}
		void Destroy() { delete this; }
};

enum eFizzcrank
{
    NPC_FIZZCRANK               = 25590,

    GOSSIP_TEXTID_FIZZCRANK1    = 12456,
    GOSSIP_TEXTID_FIZZCRANK2    = 12457,
    GOSSIP_TEXTID_FIZZCRANK3    = 12458,
    GOSSIP_TEXTID_FIZZCRANK4    = 12459,
    GOSSIP_TEXTID_FIZZCRANK5    = 12460,
    GOSSIP_TEXTID_FIZZCRANK6    = 12461,
    GOSSIP_TEXTID_FIZZCRANK7    = 12462,
    GOSSIP_TEXTID_FIZZCRANK8    = 12463,
    GOSSIP_TEXTID_FIZZCRANK9    = 12464,

    QUEST_THE_MECHAGNOMES       = 11708
};

#define GOSSIP_ITEM_GO_ON   "Go on."
#define GOSSIP_ITEM_TELL_ME "Tell me what's going on out here, Fizzcrank."

class FizzcrankGossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			GossipMenu* Menu;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);

			if(sEAS.GetQuest(pPlayer, QUEST_THE_MECHAGNOMES))
				Menu->AddItem(0, GOSSIP_ITEM_TELL_ME, 1);

			Menu->SendTo(pPlayer);
		}

		void GossipSelectOption(Object* pObject, Player*  pPlayer, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 1:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK1, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 2);
					Menu->SendTo(pPlayer);
					break;
				case 2:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK2, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 3);
					Menu->SendTo(pPlayer);
					break;
				case 3:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK3, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 4);
					Menu->SendTo(pPlayer);
					break;
				case 4:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK4, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 5);
					Menu->SendTo(pPlayer);
					break;
				case 5:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK5, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 6);
					Menu->SendTo(pPlayer);
					break;
				case 6:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK6, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 7);
					Menu->SendTo(pPlayer);
					break;
				case 7:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK7, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 8);
					Menu->SendTo(pPlayer);
					break;
				case 8:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK8, pPlayer);
					Menu->AddItem(0, GOSSIP_ITEM_GO_ON, 9);
					Menu->SendTo(pPlayer);
					break;
				case 9:
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), GOSSIP_TEXTID_FIZZCRANK9, pPlayer);
					Menu->SendTo(pPlayer);
					break;
			}
		}

};

#define GOSSIP_ITEM_FREE_FLIGHT "I'd like passage to the Transitus Shield."
#define GOSSIP_ITEM_FLIGHT      "May I use a drake to fly elsewhere?"

enum eSurristrasz
{
    NPC_SURRISTRASZ             = 24795,

    SPELL_ABMER_TO_COLDARRA     = 46064
};

class SurristraszGossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			GossipMenu* Menu;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);

			Menu->AddItem(0, GOSSIP_ITEM_FREE_FLIGHT, 1);
			Menu->AddItem(3, GOSSIP_ITEM_FLIGHT, 2);

			Menu->SendTo(pPlayer);
		};

		void GossipSelectOption(Object* pObject, Player*  pPlayer, uint32 Id, uint32 IntId, const char* Code)
		{
			if(!pObject->IsCreature())
				return;

			switch(IntId)
			{
				case 1:
					pPlayer->Gossip_Complete();
					pPlayer->CastSpell(pPlayer, SPELL_ABMER_TO_COLDARRA, true);
					break;
				case 2:
					pPlayer->GetSession()->SendTaxiList(TO_CREATURE(pObject));
					break;
			};
		};
};

void SetupBoreanTundraGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(30051, new TiareGossipScript);
	mgr->register_gossip_script(NPC_FIZZCRANK, new FizzcrankGossip());
	mgr->register_gossip_script(NPC_SURRISTRASZ, new SurristraszGossip());
}