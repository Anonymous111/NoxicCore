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

class FizzcrankGossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12435, Plr);
		if(Plr->HasQuest(11708))
			Menu->AddItem(0, "Tell me what's going on out here, Fizzcrank.", 1);

		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12455+IntId, Plr);
		if(IntId != 9)
			Menu->AddItem(0, "Go on.", ++IntId);

		Menu->SendTo(Plr);
	}
};

class SurristraszGossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 12730, Plr);
		Menu->AddItem(0, "I'd like passage to the Transitus Shield.", 1); 
		Menu->AddItem(3, "May I use a drake to fly elsewhere?", 2);

		Menu->SendTo( Plr );
	};

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		Creature* pCreature = TO_CREATURE(pObject);

		if(IntId == 1)
		{
			Plr->Gossip_Complete();
			pCreature->CastSpell(Plr, 46064, true);
		}
		else
			Plr->GetSession()->SendTaxiList(pCreature);
	}
};

void SetupBoreanTundraGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(30051, new TiareGossipScript); // Librarian Tiare
	mgr->register_gossip_script(25590, new FizzcrankGossip); // Fizzcrank Fullthrottle
	mgr->register_gossip_script(24795, new SurristraszGossip); // Surristrasz
}