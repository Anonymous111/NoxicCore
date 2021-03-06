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

#define HEMET 27986
#define HADRIUS 28047
#define TAMARA 28568
#define GOSSIP_TASTETEST "Care to try Grimbooze Thunderbrew's Jungle punch?"

class SCRIPT_DECL HemetTasteTest : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(12645))
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
				Menu->AddItem(0, GOSSIP_TASTETEST, 1);

				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			switch(IntId)
			{
				case 1:
					{
						string msg = "Aye, I'll try it.";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg.c_str());
						string msg2 = "That's exactly what I needed!";
						string msg3 = "It's got my vote! That'll put hair on your chest like nothing else will.";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg2.c_str(), 2000);
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg3.c_str(), 4000);
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(12645);
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

class SCRIPT_DECL HadriusTasteTest : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(12645))
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
				Menu->AddItem(0, GOSSIP_TASTETEST, 1);

				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			switch(IntId)
			{
				case 1:
					{
						string msg = "I'm always up for something of Grimbooze's.";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg.c_str());
						string msg2 = "Well, so far, it tastes like something my wife would drink...";
						string msg3 = "Now, there's the kick I've come to expect from Grimbooze's drinks! I like it!";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg2.c_str(), 2000);
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg3.c_str(), 4000);
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(12645);
						if(pQuest == NULL)
							return;

						if(pQuest->GetMobCount(0) != 0)
							return;
						pQuest->SetMobCount(1, 1);
						pQuest->SendUpdateAddKill(1);
						pQuest->UpdatePlayerFields();
					}
					break;
			}
		}

};

class SCRIPT_DECL TamaraTasteTest : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(12645))
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 40002, plr);
				Menu->AddItem(0, GOSSIP_TASTETEST, 1);

				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			switch(IntId)
			{
				case 1:
					{
						string msg = " Sure!";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg.c_str());
						string msg2 = "Oh my...";
						string msg3 = "Tastes like I'm drinking... engine degreaser!";
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg2.c_str(), 2000);
						pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, msg3.c_str(), 4000);
						QuestLogEntry* pQuest = plr->GetQuestLogForEntry(12645);
						if(pQuest == NULL)
							return;

						if(pQuest->GetMobCount(0) != 0)
							return;
						pQuest->SetMobCount(2, 1);
						pQuest->SendUpdateAddKill(2);
						pQuest->UpdatePlayerFields();
					}
					break;
			}
		}
};

void SetupSholazarBasinGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(HEMET, new HemetTasteTest());
	mgr->register_gossip_script(HADRIUS, new HadriusTasteTest());
	mgr->register_gossip_script(TAMARA, new TamaraTasteTest());
}