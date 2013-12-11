/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 *
 * This program is free software: you can redistribute it and/or modify
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

class JeanPierrePoulain : public GossipScript
{
		public:
			void GossipHello(Object* pObject, Player* plr)
			{
			GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 14500, plr);
			if(plr->HasFinishedQuest(13668) || plr->GetQuestLogForEntry(13668) || plr->HasFinishedQuest(13667) || plr->GetQuestLogForEntry(13667))
			{
				Menu->SendTo(plr);
			}
			else
			{
				Menu->AddItem(0, "I'll take the flight."	,1);
				Menu->SendTo(plr);
			}
}			

void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
{
			switch(IntId)
			{
			case 0:
				GossipHello(pObject, Plr);
				break;
			case 1:
				Plr->CastSpell(Plr, 64795, true);
				break;
			}
				Plr->Gossip_Complete();
		}
};

void SetupCrystalsongForestGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(34244, new JeanPierrePoulain);
}