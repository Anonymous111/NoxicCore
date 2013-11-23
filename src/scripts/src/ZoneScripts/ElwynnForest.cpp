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

class DefiasBandit: public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(DefiasBandit, MoonScriptCreatureAI);
    DefiasBandit(Creature* pCreature) : MoonScriptCreatureAI(pCreature) 
	{
		AddSpell(8646, Target_Current, 20, 0, 4);
	}
	/*Bandit says: Give me all your gold!
    Bandit says: No one here gets out alive!
    Bandit says: You're in the wrong place at the wrong time, missy!
    Bandit says: You're in the wrong place at the wrong time, pal!*/
	void OnCombatStop(Unit* pTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
		ParentClass::OnCombatStop(pTarget);
    }
};

void SetupZoneElwynnForest(ScriptMgr* mgr)
{
	mgr->register_creature_script(116, &DefiasBandit::Create);
}