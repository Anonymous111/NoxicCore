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

class TheKesselRun1 : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
			if(plr->GetQuestLogForEntry(9663))
				Menu->AddItem(0, "Warn him", 1);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						QuestLogEntry* en = plr->GetQuestLogForEntry(9663);
						if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
						{
							en->SetMobCount(0, en->GetMobCount(0) + 1);
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
							return;
						}
						break;
					}
			}
		}

};


class TheKesselRun2 : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
			if(plr->GetQuestLogForEntry(9663))
				Menu->AddItem(0, "Warn him", 1);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						QuestLogEntry* en = plr->GetQuestLogForEntry(9663);
						if(en && en->GetMobCount(1) < en->GetQuest()->required_mobcount[1])
						{
							en->SetMobCount(1, en->GetMobCount(1) + 1);
							en->SendUpdateAddKill(1);
							en->UpdatePlayerFields();
							return;
						}
						break;
					}
			}
		}

};


class TheKesselRun3 : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
			if(plr->GetQuestLogForEntry(9663))
				Menu->AddItem(0, "Warn him", 1);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* highchief = TO_CREATURE(pObject);
			if(highchief == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						QuestLogEntry* en = plr->GetQuestLogForEntry(9663);
						if(en && en->GetMobCount(2) < en->GetQuest()->required_mobcount[2])
						{
							en->SetMobCount(2, en->GetMobCount(2) + 1);
							en->SendUpdateAddKill(2);
							en->UpdatePlayerFields();
							return;
						}
						break;
					}
			}
		}

};

void SetupBloodmystIsleGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(17440, new TheKesselRun1());
	mgr->register_gossip_script(17116, new TheKesselRun2());
	mgr->register_gossip_script(17240, new TheKesselRun3());
}