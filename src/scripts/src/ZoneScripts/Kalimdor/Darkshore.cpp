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

class Lunaclaw : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Lunaclaw);
	Lunaclaw(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		Player* pPlayer = TO_PLAYER(mKiller);
		sEAS.SpawnCreature(pPlayer, 12144, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, 1 * 60 * 1000);
	}
};

void SetupZoneDarkshore(ScriptMgr* mgr)
{
	mgr->register_creature_script(12138, &Lunaclaw::Create);
}