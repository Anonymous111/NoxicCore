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

class PirateTreasureTrigger : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PirateTreasureTrigger)
	PirateTreasureTrigger(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->CastSpell(_unit, 11485, true); // Cast spell: "Summon Treasure Hunting Bucanneer".
		_unit->CastSpell(_unit, 11487, true); // Cast spell: "Summon Treasure Hunting Swashbuckler".
		_unit->CastSpell(_unit, 11487, true); // Cast spell: "Summon Treasure Hunting Swashbuckler".
		_unit->CastSpell(_unit, 11463, true); // Cast spell: "Summon Treasure Hunting Pirate".
		_unit->CastSpell(_unit, 11463, true); // Cast spell: "Summon Treasure Hunting Pirate".
	}
};

class ScreecherSpirit : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ScreecherSpirit);
	ScreecherSpirit(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		if(!_unit)
			return;

		Creature* cialo = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 5307);
		if(!cialo)
			return;

		if(!cialo->isAlive())
			cialo->Despawn(1, 6 * 60 * 1000);

		_unit->Despawn(60 * 1000, 0);
	}
};

void SetupZoneTanaris(ScriptMgr* mgr)
{
	mgr->register_creature_script(8612, &ScreecherSpirit::Create);
	mgr->register_creature_script(7898, &PirateTreasureTrigger::Create);
}