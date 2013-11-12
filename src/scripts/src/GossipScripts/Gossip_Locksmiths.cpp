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

class LockSmith : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13572, Plr);

		if(Plr->HasFinishedQuest(3201) && !Plr->GetItemInterface()->GetItemCount(5396, true))
			Menu->AddItem(0, "I've lost my Key to Searing Gorge.", 1);
		if(Plr->HasFinishedQuest(10704) && !Plr->GetItemInterface()->GetItemCount(31084, true))
			Menu->AddItem(0, "I've lost my Key to the Arcatraz.", 2);
		if(Plr->HasFinishedQuest(3802) && !Plr->GetItemInterface()->GetItemCount(11000, true))
			Menu->AddItem(0, "I've lost my Shadowforge Key.", 3);
		if((Plr->HasFinishedQuest(5505) || Plr->HasFinishedQuest(5511)) && !Plr->GetItemInterface()->GetItemCount(13704, true))
			Menu->AddItem(0, "I've lost my Skeleton Key.", 4);
		if((Plr->HasFinishedQuest(10758) || Plr->HasFinishedQuest(10764)) && !Plr->GetItemInterface()->GetItemCount(28395, true))
			Menu->AddItem(0, "I've lost my Shattered Halls Key.", 5);
		if(Plr->HasFinishedQuest(9837) && !Plr->GetItemInterface()->GetItemCount(24490, true))
			Menu->AddItem(0, "I've lost my Master's Key.", 6);
		if(Plr->HasFinishedQuest(10109) && !Plr->GetItemInterface()->GetItemCount(27808, true))
			Menu->AddItem(0, "I've lost my Jump-a-tron 4000 Key.", 7);
		if(Plr->HasQuest(13159) && !Plr->GetItemInterface()->GetItemCount(42482, true))
			Menu->AddItem(0, "I've lost my Violet Hold Key.", 8);

		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		Creature* pCreature = TO_CREATURE(pObject);

		switch(IntId)
		{
			case 1:
				pCreature->CastSpell(Plr, 54880, true); // Create Key to Searing Gorge
				break;
			case 2:
				pCreature->CastSpell(Plr, 54881, true); // Create Key to the Arcatraz
				break;
			case 3:
				pCreature->CastSpell(Plr, 54882, true); // Create Shadowforge Key
				break;
			case 4:
				pCreature->CastSpell(Plr, 54883, true); // Create Skeleton Key
				break;
			case 5:
				pCreature->CastSpell(Plr, 54884, true); // Create Shattered Halls Key
				break;
			case 6:
				pCreature->CastSpell(Plr, 54885, true); // Create The Master's Key
				break;
			case 7:
				pCreature->CastSpell(Plr, 54886, true); // Create Jump-a-tron 4000 Key
				break;
			case 8:
				pCreature->CastSpell(Plr, 67253, true); // Create The Violet Hold Key
				break;
		}
		Plr->Gossip_Complete();
   }
};

void SetupLocksmiths(ScriptMgr* mgr)
{
	mgr->register_gossip_script(29725, new LockSmith()); // Benik Boltshear - Stormwind
	mgr->register_gossip_script(29728, new LockSmith()); // Walter Soref - Undercity
	mgr->register_gossip_script(29665, new LockSmith()); // Pazik "The Pick" Prylock - Dalaran
}