/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 *
 * This program is free software: you can redistribute it and/or modify
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

class ChieftainOomoorooQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ChieftainOomoorooQAI);
	ChieftainOomoorooQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(9573);
			if(pQuest != NULL && pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
			{
				pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
				pQuest->SendUpdateAddKill(1);
				pQuest->UpdatePlayerFields();
			}
		}
	}
};

void SetupZoneAzuremystIsle(ScriptMgr* mgr)
{
	mgr->register_creature_script(17189, &ChieftainOomoorooQAI::Create);
}