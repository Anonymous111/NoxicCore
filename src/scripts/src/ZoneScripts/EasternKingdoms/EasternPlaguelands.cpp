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

class Flayer : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Flayer);
	Flayer(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		Creature* pCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(11064, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(pCreature)
			pCreature->Despawn(60000, 0);
	}
};

class ArajTheSummoner : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ArajTheSummoner);
	ArajTheSummoner(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		GameObject* pGameObject = sEAS.SpawnGameobject(TO_PLAYER(mKiller), 177241, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), 1, 0, 0, 0, 0);
		sEAS.GameobjectDelete(pGameObject, 60000);
	}
};

void SetupZoneEasternPlaguelands(ScriptMgr* mgr)
{
	mgr->register_creature_script(8532, &Flayer::Create);
	mgr->register_creature_script(8531, &Flayer::Create);
	mgr->register_creature_script(8530, &Flayer::Create);
	mgr->register_creature_script(1852, &ArajTheSummoner::Create);
}