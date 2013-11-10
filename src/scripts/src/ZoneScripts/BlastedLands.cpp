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
#include "../Common/EasyFunctions.h"

class KirithAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KirithAI)
	KirithAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			_unit->CastSpell(_unit, 10853, true);
			Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(7729, _unit->GetPositionX() + 2, _unit->GetPositionY() + 2, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(3 * 6 * 1000, 0);
		}
	}
};

void SetupZoneBlastedLands(ScriptMgr* mgr)
{
	mgr->register_creature_script(7728,  &KirithAI::Create); // Kirith the Damned
}