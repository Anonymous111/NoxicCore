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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, pPlayer); \
    Menu->SendTo(pPlayer);

class PrisonerGossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* pPlayer)
	{
		if(pPlayer == NULL) // useless, but who knows
			return;

		if(!pObject->IsCreature()) // can't imagine to get this null lol
			return;

		int32 i = -1;
		Creature* pPrisoner = TO_CREATURE(pObject);
		switch(pPrisoner->GetEntry())
		{
			case 20677:
				i = 0;
				break;
			case 20678:
				i = 1;
				break;
			case 20679:
				i = 2;
				break;
		}

		if(i == -1)
			return;

		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10368);
		if(pQuest != NULL && pQuest->GetMobCount(i) < pQuest->GetQuest()->required_mobcount[i])
		{
			if(pPlayer->GetItemInterface()->GetItemCount(29501) > 0)
			{
				GossipMenu* Menu;
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10104, pPlayer);
				Menu->AddItem(0, "Walk free, Elder. Bring the spirits back to your tribe.", 1);
				Menu->SendTo(pPlayer);
			}
		}
	}

	void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(pPlayer == NULL)
			return;

		if(!pObject->IsCreature())
			return;

		switch(IntId)
		{
			case 0:
				GossipHello(pObject, pPlayer);
				break;
			case 1:
				{
					int32 i = -1;
					Creature* pPrisoner = TO_CREATURE(pObject);
					switch(pPrisoner->GetEntry())
					{
						case 20677:
							i = 0;
							break;
						case 20678:
							i = 1;
							break;
						case 20679:
							i = 2;
							break;
					}

					if(i == -1)
						return;

					QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10368);
					if(pQuest != NULL && pQuest->GetMobCount(i) < pQuest->GetQuest()->required_mobcount[i])
					{
						pQuest->SetMobCount(i, pQuest->GetMobCount(i) + 1);
						pQuest->SendUpdateAddKill(i);
						pQuest->UpdatePlayerFields();

						switch(pPrisoner->GetEntry())
						{
							case 20677:
								pPrisoner->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You've freed me! The winds speak to my people once again and grant us their strength. I thank you, stranger.");
							break;
                                                        case 20678:
								pPrisoner->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I am free! I will ask the spirit of fire to return to us so that my people may have the courage to fight their masters! I thank you, $r.");
							break;
							case 20679:
								pPrisoner->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I'm free! The spirit of water returns to my people. It will bring us the wisdom we need to survive in this harsh land. I am in your debt, $N.");
							break;
						}
						pPrisoner->Despawn(5000, 6 * 60 * 1000);
						pPrisoner->SetStandState(STANDSTATE_STAND);
					}
				}
				break;
		}
	}
};

void SetupHellfirePeninsulaGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(20677, new PrisonerGossip());
	mgr->register_gossip_script(20678, new PrisonerGossip());
	mgr->register_gossip_script(20679, new PrisonerGossip());
}