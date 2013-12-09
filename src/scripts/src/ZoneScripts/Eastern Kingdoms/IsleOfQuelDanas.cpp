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

class TheBattleForTheSunReachArmory : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(TheBattleForTheSunReachArmory);
		TheBattleForTheSunReachArmory(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* pKiller)
		{
			if(pKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = (TO_PLAYER(pKiller))->GetQuestLogForEntry(11537);
				if(pQuest == NULL)
				{
					pQuest = (TO_PLAYER(pKiller))->GetQuestLogForEntry(11538);
					if(pQuest == NULL)
						return;
				}

				if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[ 1 ])
				{
					uint32 newcount = pQuest->GetMobCount(1) + 1;
					pQuest->SetMobCount(1, newcount);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
		}
};

void SetupZoneUndercity(ScriptMgr* mgr)
{
	mgr->register_creature_script(24999, &TheBattleForTheSunReachArmory::Create);
	mgr->register_creature_script(25001, &TheBattleForTheSunReachArmory::Create);
	mgr->register_creature_script(25002, &TheBattleForTheSunReachArmory::Create);
}