/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (C) 2011-2012 ArcScripts2 team
 *
 * This program is free software: you can redistribute it and/or modify
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

class VilebranchKidnapper : public GameObjectAIScript
{
public:
	VilebranchKidnapper(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new VilebranchKidnapper(GO); }

	void OnActivate(Player* pPlayer)
	{
		float SSX = pPlayer->GetPositionX();
		float SSY = pPlayer->GetPositionY();
		float SSZ = pPlayer->GetPositionZ();
		float SSO = pPlayer->GetOrientation();

		Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(14748, SSX + 1, SSY, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);

		NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(14748, SSX, SSY, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);

		NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(14748, SSX - 1, SSY, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);
	}
};

void SetupTheHinterlandsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(179910, &VilebranchKidnapper::Create);
}