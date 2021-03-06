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

#include "../Setup.h"

class RottingCadaver : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(RottingCadaver)
	RottingCadaver(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		_unit->CastSpell(_unit, 17064, true); // Cast spell: "Summon Rotting Worms".
	}
};

class SummonOozeling : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SummonOozeling)
	SummonOozeling(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		_unit->CastSpell(_unit, 12018, true); // Cast spell: "Summon Oozeling".
	}
};

void SetupZoneWesternPlaguelands(ScriptMgr* mgr)
{
	mgr->register_creature_script(4474, &RottingCadaver::Create);
	mgr->register_creature_script(1806, &SummonOozeling::Create);
	mgr->register_creature_script(1808, &SummonOozeling::Create);
}