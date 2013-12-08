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

class CorruptMinorManifestationWater : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CorruptMinorManifestationWater);
	CorruptMinorManifestationWater(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		float SSX = _unit->GetPositionX();
		float SSY = _unit->GetPositionY();
		float SSZ = _unit->GetPositionZ();
		float SSO = _unit->GetOrientation();

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(5895, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);
	}
};

void SetupZoneSilverpineForest(ScriptMgr* mgr)
{
	mgr->register_creature_script(5894, &CorruptMinorManifestationWater::Create);
}