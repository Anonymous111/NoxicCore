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

// Lunaclaw ghost gossip
#define GOSSIP_GHOST_MOONKIN    "You have fought well, spirit. I ask you to grand me the strenght of your body and the strenght of your heart."

class SCRIPT_DECL MoonkinGhost_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4714, plr);

			if(plr->HasQuest(6002))
			{
				Menu->AddItem(0, GOSSIP_GHOST_MOONKIN, 1);  //Horde
			}
			else if(plr->HasQuest(6001))
			{
				Menu->AddItem(0, GOSSIP_GHOST_MOONKIN, 2);  //Ally
			}

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			if(!pObject->IsCreature())
				return;
			Creature* pCreature = TO_CREATURE(pObject);

			GossipMenu* Menu;
			switch(IntId)
			{
				case 0: // Return to start
					GossipHello(pCreature, plr);
					break;

				case 1: //Horde
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4715, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(6002);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();

						pCreature->Emote(EMOTE_ONESHOT_WAVE);
						pCreature->Despawn(240000, 0);
					}
					break;

				case 2: //Ally
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4715, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(6001);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();

						pCreature->Emote(EMOTE_ONESHOT_WAVE);
						pCreature->Despawn(240000, 0);
					}
					break;

			}
		}
};

void SetupDarkshoreGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(12144, new MoonkinGhost_Gossip); // Ghost of Lunaclaw
}