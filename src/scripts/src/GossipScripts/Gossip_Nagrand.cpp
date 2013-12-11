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

class LumpGossipScript : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
			Menu->AddItem(0, "Why are Boulderfist out this far? You know this is Kurenai territory!", 1);
			Menu->SendTo(plr);
		};

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			Creature* Lump = TO_CREATURE(pObject);
			if(Lump == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;
				case 1:
					if(plr->GetQuestLogForEntry(9918))
					{
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(9918);
						if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
						{
							uint32 newcount = pQuest->GetMobCount(0) + 1;
							pQuest->SetMobCount(0, newcount);
							pQuest->SendUpdateAddKill(0);
							pQuest->UpdatePlayerFields();
						}
					}
					break;
			}
		};

};

void SetupNagrandGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(18351, new LumpGossipScript());
}