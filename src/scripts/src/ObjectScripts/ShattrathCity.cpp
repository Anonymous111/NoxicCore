/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

class PortalEffectSunwellIsle : public GameObjectAIScript
{
public:
	PortalEffectSunwellIsle(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->getLevel() >= 70) 
		{
			//pPlayer->SafeTeleport(530, 4080, 12803.374023f, -6907.089844f, 41.114765f, 2.251736f);
			pPlayer->CastSpell(pPlayer, dbcSpell.LookupEntry(44870), true);
		}
		else if(pPlayer->getLevel() <= 69)
		{
			pPlayer->BroadcastMessage("You must be at least level 70 to use this!");
		}
	}
	static GameObjectAIScript* Create(GameObject* GO) { return new PortalEffectSunwellIsle(GO); }
};
GameObjectAIScript* create_go(GameObject* GO) { return new PortalEffectSunwellIsle(GO); }

void SetupShattrathCityGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(187056, &PortalEffectSunwellIsle::Create);
}