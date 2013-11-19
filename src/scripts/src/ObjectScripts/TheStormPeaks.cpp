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

class LokensFury : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(LokensFury);
		LokensFury(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 12965))
				sEAS.KillMobForQuest(pPlayer, 12965, 0);
		};

};

class LokensPower : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(LokensPower);
		LokensPower(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 12965))
				sEAS.KillMobForQuest(pPlayer, 12965, 1);
		};

};

class LokensFavor : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(LokensFavor);
		LokensFavor(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 12965))
				sEAS.KillMobForQuest(pPlayer, 12965, 2);
		};

};

void SetupStormPeaksGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(192120, &LokensFury::Create);
	mgr->register_gameobject_script(192121, &LokensPower::Create);
	mgr->register_gameobject_script(192122, &LokensFavor::Create);
}