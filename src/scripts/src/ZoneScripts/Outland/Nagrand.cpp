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

class SunspringVillager : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SunspringVillager);
	SunspringVillager(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		//SetCanEnterCombat(false);
		_unit->GetAIInterface()->m_canMove = false;
	}
};

void SetupZoneNagrand(ScriptMgr* mgr)
{
	mgr->register_creature_script(18240, &SunspringVillager::Create);
}