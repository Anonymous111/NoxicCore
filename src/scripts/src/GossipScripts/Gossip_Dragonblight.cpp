/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

class WoodlandWalkerGossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			Creature*  pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			uint32 chance = RandomUInt(1);
			if(chance == 0)
			{
				pCreature->SetFaction(14);
				pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "The Woodlands Walker is angered by your request and attacks!");
			}
			else
			{
				sEAS.AddItem(36786, plr);
				pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Breaking off a piece of its bark, the Woodlands Walker hands it to you before departing.");
			}

		}
};

void SetupDragonblightGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(26421, new WoodlandWalkerGossip());
}