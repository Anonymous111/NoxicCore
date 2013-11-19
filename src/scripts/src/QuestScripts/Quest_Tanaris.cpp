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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \ Menu->SendTo(plr);



class SpiritScreeches : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* spirit = TO_CREATURE(pObject);
			if(spirit == NULL)
				return;

			if(plr->GetQuestLogForEntry(3520))
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2039, plr);
				Menu->AddItem(0, "Goodbye", 1);

				Menu->SendTo(plr);
			}



		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* spirit = TO_CREATURE(pObject);
			if(spirit == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(3520);
						if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
						{
							pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
							pQuest->SendUpdateAddKill(0);
							pQuest->UpdatePlayerFields();
						}
						if(!spirit)
							return;

						spirit->Despawn(1, 0);
						return;

					}
			}
		}

};

class StewardOfTime : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			if(plr->GetQuestLogForEntry(10279) || plr->HasFinishedQuest(10279))
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9978, plr);
				Menu->AddItem(0, "Please take me to the master's lair", 1);
				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* creat = TO_CREATURE(pObject);
			switch(IntId)
			{
				case 1:
					creat->CastSpell(plr, dbcSpell.LookupEntry(34891), true);
					break;
			}
		}

};

void SetupTanaris(ScriptMgr* mgr)
{
	mgr->register_gossip_script(8612, new SpiritScreeches());
	mgr->register_gossip_script(20142, new StewardOfTime());
}