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

class PathoftheAdept : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			if(!pPlayer)
				return;

			GossipMenu* Menu;
			Creature* lord = TO_CREATURE(pObject);
			if(lord == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);
			if(pPlayer->GetQuestLogForEntry(9692))
				Menu->AddItem(0, "Take Insignia", 1);

			Menu->SendTo(pPlayer);
		}

		void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!pPlayer)
				return;

			Creature* lord = TO_CREATURE(pObject);
			if(lord == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, pPlayer);
				break;
				case 1:
				{
					sEAS.AddItem(24226, pPlayer);
					return;
				}
				break;
			}
		}

};

void SetupSilvermoonCityGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(17832, new PathoftheAdept());
}