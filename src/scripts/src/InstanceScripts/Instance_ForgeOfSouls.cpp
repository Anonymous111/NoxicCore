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
/* Instance_ForgeOfSouls.cpp Script										*/
/************************************************************************/

#define CN_BRONJAHM 36497
#define CN_DEVOURER_OF_SOULS 36502

#define MAGICBANE 68793
#define CORRUPTSOUL 68839
#define PHASE_1 36814
#define PHANTOMBLAST 68982
#define MIRRORED 69051
#define WELLSOULS 68863

class BronjahmAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(BronjahmAI, MoonScriptBossAI);
	BronjahmAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(MAGICBANE, Target_Current, 35, 0, 5);
		AddSpell(MAGICBANE, Target_RandomPlayer, 20, 0, 15, 5, 40, false, "I will sever your soul from your body!", Text_Yell, 16595);
		// Dont know how to set no cooldown to a spell so i put 50000 seconds.
		AddPhaseSpell(2, AddSpell(68872, Target_Self, 100, 4, 50000));
		AddPhaseSpell(2, AddSpell(70043, Target_Current, 100, 1, 0));
		AddEmote(Event_OnCombatStart, "Finally... a captive audience!", Text_Yell, 16595);
		AddEmote(Event_OnTargetDied, "Fodder for the engine!", Text_Yell, 16596);
		AddEmote(Event_OnTargetDied, "Another soul to strengthen the host!", Text_Yell, 16597);
	}

	void OnDied(Unit* mKiller)
	{
		_unit->PlaySoundToSet(16598);
		ParentClass::OnDied(mKiller);
	}

	void AIUpdate()
	{
		if(GetPhase() == 1)
		{
			if(_unit->GetHealthPct() <= 30)
			{
				Emote("The vortex of the harvested calls to you");
				_unit->Root();
				SetPhase(2);
			}
			ParentClass::AIUpdate();
		}
	}
}

class DevourerOfSoulsAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(DevourerOfSoulsAI, MoonScriptBossAI);
	DevourerOfSoulsAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(PHANTOMBLAST, Target_Current, 35, 3, 5);
		AddSpell(WELLSOULS, Target_Current, 35, 3, 20);
		AddSpell(MIRRORED, Target_RandomPlayer, 20, 0, 20, 5, 40, false, "Devourer of Souls begins to cast Mirrored Soul!", Text_Emote, 0);
		AddEmote(Event_OnCombatStart, "You dare look upon the host of souls? I shall devour you whole!", Text_Yell, 0);
	}

	void OnDied(Unit* mKiller)
	{
		_unit->PlaySoundToSet(16598);
		ParentClass::OnDied(mKiller);
	}

	void AIUpdate()
	{
		ParentClass::AIUpdate();
	}
};

void SetupForgeOfSouls(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_BRONJAHM, &BronjahmAI::Create);
	mgr->register_creature_script(CN_DEVOURER_OF_SOULS, &DevourerOfSoulsAI::Create);
}