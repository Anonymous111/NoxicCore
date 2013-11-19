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

#include "Setup.h"

class ArximagTeleportDown : public GossipScript
{
/*public:
	void Destroy()
	{
		delete this;
	}

	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1994, plr);

		Menu->AddItem(0, "[I am ready.]", 1);

		if(AutoSend)
			Menu->SendTo(plr);
	}
	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
	{
		Creature* pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULLCREATURE;
		if(pCreature == NULL)
		{
			return;
		}

		GossipMenu* Menu;
		switch(IntId)
		{
		case 0:
			GossipHello(pObject, plr, true);
			break;
		case 1:
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1994, plr);
			 plr->EventTeleport(1, 3649.567627, -4705.155762, 120.966309);
			break;
		}
	}*/
};

class ArximagTeleportUp : public GossipScript
{
/*public:
	void Destroy()
	{
		delete this;
	}

	void GossipHello(Object* pObject, Player* plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);

		Menu->AddItem(0, "[I am ready.]", 1);

		if(AutoSend)
			Menu->SendTo(plr);
	}

	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
	{
		Creature* pCreature = (pObject->GetTypeId()==TYPEID_UNIT)?(TO_CREATURE(pObject)):NULLCREATURE;
		if(pCreature == NULL)
		{
			return;
		}

		GossipMenu* Menu;
		switch(IntId)
		{
			case 0:
				GossipHello(pObject, plr, true);
				break;
			case 1:
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);
				plr->EventTeleport(1, 3778.438721, -4612.299805, 227.253922);
				break;
		}
	}*/
};

void SetupAzsharaGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(8399, new ArximagTeleportDown()); 
	mgr->register_gossip_script(8395, new ArximagTeleportUp()); 
}