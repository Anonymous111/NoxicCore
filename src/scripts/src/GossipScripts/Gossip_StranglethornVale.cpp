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

class StrFever : public GossipScript
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
			if(plr->GetQuestLogForEntry(348) && plr->GetItemInterface()->GetItemCount(2799, 0) && !plr->GetItemInterface()->GetItemCount(2797, 0))
				Menu->AddItem(0, "I'm ready, Summon Him!", 1);

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
						doctor->CastSpell(doctor, dbcSpell.LookupEntry(12380), true);
						if(!plr || !plr->GetMapMgr() || !plr->GetMapMgr()->GetInterface())
							return;
						Creature* firstenemy = sEAS.SpawnCreature(plr, 1511, -13770.5f, -6.79f, 42.8f, 5.7f , 0);
						firstenemy->GetAIInterface()->MoveTo(-13727.8f, -26.2f, 46.15f, 4.07f);
						firstenemy->Despawn(10 * 60 * 1000, 0);
					}
					break;
			}
		}

};

void SetupStranglethornValeGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(1449, new StrFever());
}