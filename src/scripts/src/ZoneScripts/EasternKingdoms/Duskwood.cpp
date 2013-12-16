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

#define ELIZA_FROST_NOVA		11831
#define ELIZA_FROSTBOLT			20819
#define ELIZA_SUMMON_GUARD		3107

class ElizaAI : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(ElizaAI, MoonScriptCreatureAI);
	ElizaAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		mElizaCombatTimer = INVALIDATE_TIMER;
		SetCanEnterCombat(false);
		AddSpell(ELIZA_FROST_NOVA, Target_Current, 10, 0, 1, 0, 10, true);
		AddSpell(ELIZA_FROSTBOLT, Target_Current, 20, 3, 1);
		mSummonGuard = AddSpell(ELIZA_SUMMON_GUARD, Target_Self, 0, 0, 0);

		Emote("Wait...you are not my husband. But he must have sent you. And you...look..delicious!", Text_Say);
		mElizaCombatTimer = AddTimer(4000);

		RegisterAIUpdateEvent(1000);
	}
	void AIUpdate()
	{
		ParentClass::AIUpdate();
		if(IsTimerFinished(mElizaCombatTimer))
		{
			SetCanEnterCombat(true);
			AggroNearestUnit();
			RemoveTimer(mElizaCombatTimer);
		}
		if(GetHealthPercent() >= 10 && GetHealthPercent() <= 98 && !IsCasting())
		{
			// Correct me if I'm wrong but I saw only 1 guard spawning
			mElizaGuard = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 1871);
			if(mElizaGuard == NULL)
				CastSpellNowNoScheduling(mSummonGuard);
		}
	}

	int32 mElizaCombatTimer;
	SpellDesc* mSummonGuard;
	Creature* mElizaGuard;
};

void SetupZoneDuskwood(ScriptMgr* mgr)
{
	mgr->register_creature_script(314, &ElizaAI::Create);
}