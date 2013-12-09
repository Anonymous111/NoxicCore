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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \
	Menu->SendTo(plr);

class Prisoner12 : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr)
	{
		if(!plr)
			return;

		GossipMenu* Menu;
		Creature* Prisoner12 = TO_CREATURE(pObject);
		if(Prisoner12 == NULL)
			return;

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
		if(plr->GetQuestLogForEntry(9164))
			Menu->AddItem(0, "Release Him.", 1);

		Menu->SendTo(plr);
	}

	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(!plr)
			return;

		Creature* Prisoner12 = TO_CREATURE(pObject);
		if(Prisoner12 == NULL)
			return;

		switch(IntId)
		{
			case 0:
				GossipHello(pObject, plr);
				break;
			case 1:
			{
				QuestLogEntry* pQuest = plr->GetQuestLogForEntry(9164);
				if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();

					if(!Prisoner12)
						return;

					Prisoner12->Despawn(5000, 6 * 60 * 1000);
					Prisoner12->SetStandState(STANDSTATE_STAND);
					Prisoner12->SetEmoteState(7);
					return;
				}
				break;
			}
		}
	}
};

class Prisoner22 : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr)
	{
		if(!plr)
			return;

		GossipMenu* Menu;
		Creature* Prisoner22 = TO_CREATURE(pObject);
		if(Prisoner22 == NULL)
			return;

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
		if(plr->GetQuestLogForEntry(9164))
			Menu->AddItem(0, "Release Him.", 1);

		Menu->SendTo(plr);
	}

	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(!plr)
			return;

		Creature* Prisoner22 = TO_CREATURE(pObject);
		if(Prisoner22 == NULL)
			return;

		switch(IntId)
		{
			case 0:
				GossipHello(pObject, plr);
				break;
			case 1:
			{
				QuestLogEntry* pQuest = plr->GetQuestLogForEntry(9164);
				if(pQuest && pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
				{
					pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();

					if(!Prisoner22)
						return;

					Prisoner22->Despawn(5000, 6 * 60 * 1000);
					Prisoner22->SetStandState(STANDSTATE_STAND);
					Prisoner22->SetEmoteState(7);
					return;
				}
				break;
			}
		}
	}
};


class Prisoner32 : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr)
	{
		if(!plr)
			return;

		GossipMenu* Menu;
		Creature* Prisoner32 = TO_CREATURE(pObject);
		if(Prisoner32 == NULL)
			return;

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
		if(plr->GetQuestLogForEntry(9164))
			Menu->AddItem(0, "Release Him.", 1);

		Menu->SendTo(plr);
	}

	void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(!plr)
			return;

		Creature* Prisoner32 = TO_CREATURE(pObject);
		if(Prisoner32 == NULL)
			return;

		switch(IntId)
		{
			case 0:
				GossipHello(pObject, plr);
				break;
			case 1:
			{
				QuestLogEntry* pQuest = plr->GetQuestLogForEntry(9164);
				if(pQuest && pQuest->GetMobCount(2) < pQuest->GetQuest()->required_mobcount[2])
				{
					pQuest->SetMobCount(2, pQuest->GetMobCount(2) + 1);
					pQuest->SendUpdateAddKill(2);
					pQuest->UpdatePlayerFields();

					if(!Prisoner32)
						return;

					Prisoner32->Despawn(5000, 6 * 60 * 1000);
					Prisoner32->SetStandState(STANDSTATE_STAND);
					Prisoner32->SetEmoteState(7);
					return;
				}
				break;
			}
		}
	}
};

void SetupGhostlandsGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(16208, new Prisoner12());
	mgr->register_gossip_script(16206, new Prisoner22());
	mgr->register_gossip_script(16209, new Prisoner32());
}