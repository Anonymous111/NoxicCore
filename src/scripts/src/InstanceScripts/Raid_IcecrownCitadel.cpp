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

/************************************************************************/
/* Raid_IcecrownCitadel.cpp Script										*/
/************************************************************************/


class ICCTeleporter : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* pPlayer, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 0, pPlayer);
		Menu->AddItem(0, "Teleport to Light's Hammer", 0);
		Menu->AddItem(0, "Teleport to Oratory of The Damned", 1);
		Menu->AddItem(0, "Teleport to Rampart of Skulls", 2);
		Menu->AddItem(0, "Teleport to Deathbringer's Rise", 3);
		Menu->AddItem(0, "Teleport to The Plagueworks", 4);
		Menu->AddItem(0, "Teleport to The Crimson Halls", 5);
		Menu->AddItem(0, "Teleport to The Frostwing Halls", 6);
		Menu->AddItem(0, "Teleport to The Frost Queen's Lair", 7);
		Menu->AddItem(0, "Teleport to The Frozen Throne", 8);
		if(AutoSend)
			Menu->SendTo(pPlayer);
	};

	void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char * Code)
	{
		switch(IntId)
		{
			case 0:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), -17.856115f, 2211.640137f, 30.115812f, 0.0f);
		    break;
			case 1:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), -503.632599f, 2211.219971f, 62.823246f, 0.0f);
		    break;
			case 2:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), -615.098267f, 2211.509766f, 199.973083f, 0.0f);
		    break;
			case 3:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), -549.151001f, 2211.463967f, 539.290222f, 0.0f);
			break;
			case 4:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), 4356.780273f, 2863.636230f, 349.337982f, 0.0f);
            break;
			case 5:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), 4453.248535f, 2769.325684f, 349.347473f, 0.0f);
            break;
			case 6:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), 4356.853516f, 2674.143311f, 349.340118f, 0.0f);
            break;
			case 7:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), 4356.527344f, 2402.710205f, 220.462723f, 0.0f);
            break;
			case 8:
				pPlayer->SafeTeleport(631, pPlayer->GetInstanceID(), -782.4f, 2604.1f, 1784.6f, 0.0f);
			break;
		}
	};

	void GossipEnd(Object* pObject, Player* pPlayer)
	{
		GossipScript::GossipEnd(pObject, pPlayer);
	};

	void Destroy()
	{
		delete this;
	};
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
    mgr->register_go_gossip_script(201907, new ICCTeleporter());
    mgr->register_go_gossip_script(201908, new ICCTeleporter());
    mgr->register_go_gossip_script(201909, new ICCTeleporter());
    mgr->register_go_gossip_script(201917, new ICCTeleporter());
    mgr->register_go_gossip_script(201918, new ICCTeleporter());
    mgr->register_go_gossip_script(201923, new ICCTeleporter());
    mgr->register_go_gossip_script(202223, new ICCTeleporter());
    mgr->register_go_gossip_script(202235, new ICCTeleporter());
    mgr->register_go_gossip_script(202242, new ICCTeleporter());
    mgr->register_go_gossip_script(202243, new ICCTeleporter());
	mgr->register_go_gossip_script(202244, new ICCTeleporter());
	mgr->register_go_gossip_script(202245, new ICCTeleporter());
	mgr->register_go_gossip_script(202246, new ICCTeleporter());
}