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

#include "Setup.h"

/************************************************************************/
/* Raid_VaultOfArchavon.cpp Script										*/
/************************************************************************/

#define CN_ARCHAVON 31125

#define Berserk			47008
#define CrushingLeap	58963
#define RockShards		58678
#define Stomp			58663
#define Impale_DMG		58666
#define Impale			50839

class Archavon : public MoonScriptBossAI
{
    MOONSCRIPT_FACTORY_FUNCTION(Archavon, MoonScriptBossAI);
	Archavon(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(RockShards, Target_RandomPlayer, 100, 0, 15);
		AddSpell(CrushingLeap, Target_RandomPlayer, 100, 0, 30);

		sStomp = dbcSpell.LookupEntryForced( Stomp );
		sImpaleDmg = dbcSpell.LookupEntryForced( Impale_DMG );
		sImpale = dbcSpell.LookupEntryForced( Impale );
		sBerserk = dbcSpell.LookupEntryForced( Berserk );
	}

	void OnCombatStart(Unit* mTarget)
    {
		mStompTimer = AddTimer(45000);
		mRageTimer = AddTimer(300000);
	}

	void OnCombatStop(Unit* mTarget)
	{
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		_unit->GetAIInterface()->SetAIState(STATE_IDLE);
		RemoveAIUpdateEvent();
	}

	void AIUpdate(Player *pPlayer)
	{
		if(IsTimerFinished(mStompTimer))
		{
			CastSpellOnTarget( pPlayer, Target_Self, sStomp, true );
			CastSpellOnTarget( pPlayer, Target_Self, sImpaleDmg, true );
			CastSpellOnTarget( pPlayer, Target_Current, sImpale, true );
			ResetTimer( mStompTimer, 45000 );
		}

		if(IsTimerFinished(mRageTimer))
		{
			CastSpellOnTarget( pPlayer, Target_RandomPlayer, sBerserk, true );
		}
		ParentClass::AIUpdate();
	}

	void Destroy()
	{
		delete this;
	}

private:
	int32 mRageTimer;
	int32 mStompTimer;
	SpellEntry* sStomp;
	SpellEntry* sImpaleDmg;
	SpellEntry* sImpale;
	SpellEntry* sBerserk;
};

void SetupVaultOfArchavon(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_ARCHAVON, &Archavon::Create);
}