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

class PeonSleepingAI : CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PeonSleepingAI)
	PeonSleepingAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		RegisterAIUpdateEvent(3000 + RandomUInt(180000));
	}

	void AIUpdate()
	{
		_unit->CastSpell(_unit, 18795, true); // Or? 17743
		RemoveAIUpdateEvent();
	}
};

class LieutenantBenedict : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(LieutenantBenedict);
	LieutenantBenedict(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller)
			return;

		if(mKiller->IsPlayer())
		{
			Player* pPlayer = TO_PLAYER(mKiller);
			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(784);
			if(pQuest == NULL)
				return;

			pQuest->SetMobCount(2, 1);
			pQuest->SendUpdateAddKill(2);
			pQuest->UpdatedPlayerFields();
		}
	}
};

void SetupZoneDurotar(ScriptMgr* mgr)
{
	mgr->register_creature_script(10556, &PeonSleepingAI::Create);
	mgr->register_creature_script(3192, &LieutenantBenedict::Create);
}