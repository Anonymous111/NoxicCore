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

class PurifyingTotem : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PurifyingTotem)
	PurifyingTotem(Creature* pCreature ) : CreatureAIScript(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
		_unit->Root();
		_unit->Despawn(8000, 0);
	}
};

class SeaforiumDepthCharge : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SeaforiumDepthCharge)
	SeaforiumDepthCharge(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
		_unit->Root();
		sEAS.EventCastSpell(_unit, _unit, 45502, 3000);
		_unit->Despawn(3500, 0);
	}
};

void SetupZoneBoreanTundra(ScriptMgr* mgr)
{
	mgr->register_creature_script(25494, &PurifyingTotem::Create); // Purifying Totem
	mgr->register_creature_script(25401, &SeaforiumDepthCharge::Create); // Seaforium Depth Charge
}