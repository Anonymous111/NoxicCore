/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2009 FrozenThrone Shard <http://www.dowlee.it/ft>
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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \
	Menu->SendTo(plr);

class TheMomentofTruth : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* doctor = TO_CREATURE(pObject);
			if(doctor == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
			if(plr->GetQuestLogForEntry(10201) && plr->GetItemInterface()->GetItemCount(28500, 0))
				Menu->AddItem(0, "Try this", 1);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* doctor = TO_CREATURE(pObject);
			if(doctor == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						plr->GetItemInterface()->RemoveItemAmt(2799, 1);
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(10201);
						if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
						{
							pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
							pQuest->SendUpdateAddKill(0);
							pQuest->UpdatePlayerFields();
						}
					}
					break;
			}
		}

};

void SetupTerrokarForestGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(19606, new TheMomentofTruth());
}