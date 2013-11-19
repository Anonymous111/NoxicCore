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

class OrbOfTransLocQuelTop : public GameObjectAIScript
{
public:
	OrbOfTransLocQuelTop(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new OrbOfTransLocQuelTop(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 4080, 12782.415039f, -6879.196289f, 23.106073f, 2.222675f);		 // teleports to the lower level
	}
};

class OrbOfTransLocQuelLower : public GameObjectAIScript
{
public:
	OrbOfTransLocQuelLower(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new OrbOfTransLocQuelLower(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 4080, 12791.350586f, -6891.479004f, 31.322657f, 5.336779f);		 // teleports to the upper level
	}
};

void SetupIsleofQuelDanasGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(187431, &OrbOfTransLocQuelTop::Create);
	mgr->register_gameobject_script(187428, &OrbOfTransLocQuelLower::Create);
}