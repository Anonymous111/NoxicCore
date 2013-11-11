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

class EclipsionSpawn : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(EclipsionSpawn)
	EclipsionSpawn(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		_unit->CastSpell(_unit, 38311, true); // Cast spell: "Summon Eclipsion Hawkstrider"
	}
};

void SetupZoneShadowmoonValley(ScriptMgr* mgr)
{
	mgr->register_creature_script(19806, &EclipsionSpawn::Create);	// Eclipsion Bloodwarder
	mgr->register_creature_script(22018, &EclipsionSpawn::Create);	// Eclipsion Cavalier
}