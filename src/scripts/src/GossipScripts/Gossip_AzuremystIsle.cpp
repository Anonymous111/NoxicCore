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

class TheKesselRun_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		if(pObject->GetEntry() == 17440)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 8997, Plr);
		else if(pObject->GetEntry() == 17240)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9040, Plr);
		else if(pObject->GetEntry() == 17240)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9038, Plr);

		if(Plr->HasQuest(9663))
			Menu->AddItem(0, "Warn him", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(pObject->GetEntry() == 17440)
			sEAS.KillMobForQuest(Plr, 9663, 0);
		else if(pObject->GetEntry() == 17116)
			sEAS.KillMobForQuest(Plr, 9663, 1);
		else if(pObject->GetEntry() == 17240)
			sEAS.KillMobForQuest(Plr, 9663, 2);
	}
};

void SetupAzuremystIsleGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(17440, new TheKesselRun_Gossip()); // High Chief Stillpine
	mgr->register_gossip_script(17116, new TheKesselRun_Gossip()); // Exarch Menelaous
	mgr->register_gossip_script(17240, new TheKesselRun_Gossip()); // Admiral Odesyus
}