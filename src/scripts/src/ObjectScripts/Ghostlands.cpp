/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
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

class AlterofTidalMastery : public GameObjectAIScript
{
	public:
		AlterofTidalMastery(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new AlterofTidalMastery(GO); }

		void OnActivate(Player* pPlayer)
		{
			pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(16292, 7934.343750f, -7637.020996f, 112.694130f, 3.098388f, true, false, 0, 0);
		}
};

void SetupGhostlandsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181157, &AlterofTidalMastery::Create);
}