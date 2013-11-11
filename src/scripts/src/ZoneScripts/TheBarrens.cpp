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

class SavannahProwler : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SavannahProwler)
	SavannahProwler(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		uint8 chance = RandomUInt(3);

		if(chance == 1)
			_unit->SetStandState(STANDSTATE_SLEEP);
	}

	void OnCombatStart(Unit* pTarget)
	{
		if(_unit->GetStandState() == STANDSTATE_SLEEP)
			_unit->SetStandState(0);
	}

	static CreatureAIScript* Create(Creature* c) { return new SavannahProwler(c); }
};

void SetupZoneTheBarrens(ScriptMgr* mgr)
{
	mgr->register_creature_script(3425, &SavannahProwler::Create);	// Savannah Prowler
}