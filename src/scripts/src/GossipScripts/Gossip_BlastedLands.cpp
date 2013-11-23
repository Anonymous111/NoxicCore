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

class FallenHero : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1391, Plr);
		if(Plr->HasQuest(2702))
			Menu->AddItem(0, "I need to speak with Corporal.", 1);

		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(sEAS.GetNearestCreature(Plr, 7750) == NULL)
			sEAS.SpawnCreature(Plr, 7750, -10630, -2986.98f, 28.9815f, 4.73538f, 600000);

		/*if(sEAS.GetNearestGameObject(Plr, 141980) == NULL) // TODO: SpawnGameObject does not take 13 arguments
			sEAS.SpawnGameobject(Plr, 141980, -10633.4f, -2985.83f, 28.986f, 4.74371f, 600000, 1, 0, 0, 0, 0.695946f, -0.718095f);*/
	}
};

void SetupBlastedLandsGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(7572, new FallenHero()); // Fallen Hero of the Horde
}