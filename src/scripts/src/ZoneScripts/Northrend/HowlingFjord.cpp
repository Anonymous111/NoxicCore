/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

#include "../Setup.h"

class NorthFleet : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(NorthFleet);
		NorthFleet(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(11230);
				if(pQuest != NULL)
				{
					if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = pQuest->GetMobCount(0) + 1;
						pQuest->SetMobCount(0, newcount);
						pQuest->SendUpdateAddKill(0);
						pQuest->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

class ChillmereScourge : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ChillmereScourge);
		ChillmereScourge(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(11397);
				if(pQuest != NULL)
				{
					if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = pQuest->GetMobCount(0) + 1;
						pQuest->SetMobCount(0, newcount);
						pQuest->SendUpdateAddKill(0);
						pQuest->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

class Baleheim : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Baleheim);
		Baleheim(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(11283);
				if(pQuest != NULL)
				{
					if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = pQuest->GetMobCount(0) + 1;
						pQuest->SetMobCount(0, newcount);
						pQuest->SendUpdateAddKill(0);
						pQuest->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

void SetupZoneHowlingFjord(ScriptMgr* mgr)
{
	mgr->register_creature_script(23643, &ChillmereScourge::Create);
	mgr->register_creature_script(23645, &ChillmereScourge::Create);
	mgr->register_creature_script(23644, &ChillmereScourge::Create);
	mgr->register_creature_script(24540, &ChillmereScourge::Create);
	mgr->register_creature_script(24485, &ChillmereScourge::Create);
	mgr->register_creature_script(23653, &Baleheim::Create);
	mgr->register_creature_script(23655, &Baleheim::Create);
	mgr->register_creature_script(24015, &Baleheim::Create);
	mgr->register_creature_script(23866, &NorthFleet::Create);
	mgr->register_creature_script(23934, &NorthFleet::Create);
	mgr->register_creature_script(23946, &NorthFleet::Create);
	mgr->register_creature_script(23794, &NorthFleet::Create);
	mgr->register_creature_script(23793, &NorthFleet::Create);
}