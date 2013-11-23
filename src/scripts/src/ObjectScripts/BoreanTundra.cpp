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

// Call to Arms!
class BellRope : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(BellRope);
		BellRope(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 11965))
				sEAS.KillMobForQuest(pPlayer, 11965, 0);
		};

};

// Reading the Meters
class ColdarraGeoMonitorNexus : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ColdarraGeoMonitorNexus);
		ColdarraGeoMonitorNexus(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 11900))
				sEAS.KillMobForQuest(pPlayer, 11900, 0);
		};

};

class ColdarraGeoMonitorSouth : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ColdarraGeoMonitorSouth);
		ColdarraGeoMonitorSouth(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 11900))
				sEAS.KillMobForQuest(pPlayer, 11900, 1);
		};

};

class ColdarraGeoMonitorNorth : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ColdarraGeoMonitorNorth);
		ColdarraGeoMonitorNorth(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 11900))
				sEAS.KillMobForQuest(pPlayer, 11900, 2);
		};

};

class ColdarraGeoMonitorWest : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ColdarraGeoMonitorWest);
		ColdarraGeoMonitorWest(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(sEAS.GetQuest(pPlayer, 11900))
				sEAS.KillMobForQuest(pPlayer, 11900, 3);
		};

};

class NerubarEggSac : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(NerubarEggSac)
	NerubarEggSac(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(sEAS.GetQuest(pPlayer, 11602))
			return;

		sEAS.KillMobForQuest(pPlayer, 11602, 0);
		_gameobject->SetState(1);
		_gameobject->SetState(0);
		_gameobject->Despawn(500, 60000);
	};
};

// Hatching a Plan
class BlueDragonEgg : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(BlueDragonEgg);
		BlueDragonEgg(GameObject* goinstance) : GameObjectAIScript(goinstance) {};

		void OnActivate(Player* pPlayer)
		{
			if(!sEAS.GetQuest(pPlayer, 11936))
				return;

			sEAS.KillMobForQuest(pPlayer, 11936, 0);
			_gameobject->SetState(1);
			_gameobject->SetState(0);
			_gameobject->Despawn(500, 60000);
		}
};

void SetupBoreanTundraGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(188163, &BellRope::Create);
	mgr->register_gameobject_script(188100, &ColdarraGeoMonitorNexus::Create);
	mgr->register_gameobject_script(188101, &ColdarraGeoMonitorSouth::Create);
	mgr->register_gameobject_script(188102, &ColdarraGeoMonitorNorth::Create);
	mgr->register_gameobject_script(188103, &ColdarraGeoMonitorWest::Create);
	mgr->register_gameobject_script(187655, &NerubarEggSac::Create);
	mgr->register_gameobject_script(188133, &BlueDragonEgg::Create);
}