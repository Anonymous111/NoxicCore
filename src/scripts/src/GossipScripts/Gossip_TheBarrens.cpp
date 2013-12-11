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

#include "../Setup.h"

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \
    Menu->SendTo(plr);

class BeatenCorpse : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3557, plr);

			if(plr->GetQuestLogForEntry(4921) != NULL)
				Menu->AddItem(0, "I inspect the body further.", 1);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;

			switch(IntId)
			{
				case 1:
					{
						SendQuickMenu(3558);

						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(4921);
						if(pQuest == NULL)
							return;

						if(pQuest->GetMobCount(0) != 0)
							return;

						pQuest->SetMobCount(0, 1);
						pQuest->SendUpdateAddKill(0);
						pQuest->UpdatePlayerFields();
					}
					break;
			}
		}

};

void SetupTheBarrensGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(10668, new BeatenCorpse);
}