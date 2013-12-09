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

class Darrowshire_Spirit : public GossipScript
{
	public:

		void GossipHello(Object* pObject, Player* plr)
		{
			QuestLogEntry* en = plr->GetQuestLogForEntry(5211);

			if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
			{
				uint32 newcount = en->GetMobCount(0) + 1;

				en->SetMobCount(0, newcount);
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}

			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3873, plr);

			Menu->SendTo(plr);

			if(!pObject || !pObject->IsCreature())
				return;

			Creature* Spirit = TO_CREATURE(pObject);

			Spirit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			Spirit->Despawn(4000, 0);
		}

};

void SetupEasternPlaguelandsGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(11064, new Darrowshire_Spirit());
}