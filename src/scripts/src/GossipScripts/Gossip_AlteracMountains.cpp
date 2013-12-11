/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2009 FrozenThrone Shard <http://www.dowlee.it/ft>
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

class Summoning : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* pPlayer, bool AutoSend)
	{
		if(!pPlayer)
			return;

		GossipMenu* Menu;
		Creature* windwatcher = TO_CREATURE(pObject);
		if(windwatcher == NULL)
			return;

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, pPlayer);
		if(pPlayer->GetQuestLogForEntry(1713))
			Menu->AddItem( 0, "I'm ready, Summon Him!", 1);

		if(AutoSend)
			Menu->SendTo(pPlayer);
	}

	void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(!pPlayer)
			return;

		Creature* windwatcher = TO_CREATURE(pObject);
		if(windwatcher == NULL)
			return;

		switch(IntId)
		{
			case 0:
				GossipHello(pObject, pPlayer, true);
				break;
			case 1:
			{
				if(pPlayer == NULL || pPlayer->GetMapMgr() == NULL || pPlayer->GetMapMgr()->GetInterface() == NULL)
					return;

				Creature* whirlwind = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 6239);
				if(whirlwind != NULL)
				{
					if(!whirlwind->isAlive())
						whirlwind->Delete();
					else
						return;
				}

				whirlwind = sEAS.SpawnCreature(pPlayer, 6239, pPlayer->GetPositionX()+7, pPlayer->GetPositionY()+7, pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 0);
				whirlwind->Despawn(5*60*1000, 0);
			}break;
		}
	}

	void Destroy()
	{
		delete this;
	}
};

void SetupAlteracMountainsGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(6176, new Summoning());
}