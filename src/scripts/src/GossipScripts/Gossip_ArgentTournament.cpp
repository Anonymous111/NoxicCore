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

class GetKraken_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 14692, Plr);
		Menu->AddItem(0, "Mount the Hippogryph and prepare for the battle!", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		TaxiPath* path = sTaxiMgr.GetTaxiPath(1268);
		Plr->TaxiStart(path, 22471, 0);
	}
};

void SetupArgentTournamentGossip(Scriptmgr* mgr)
{
	mgr->register_gossip_script(44685, new GetKraken_Gossip());
}