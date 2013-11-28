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

class BarrelOfFilth : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(BarrelOfFilth)
	BarrelOfFilth(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(9508))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(17359, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
			pPlayer->BroadcastMessage("Missing required quest: Call of Water");
	}
};

class Razormaw : public GameObjectAIScript
{
public:
	Razormaw(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new Razormaw(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(9689);
		if(qle == NULL)
			return;

		Creature* razormaw = sEAS.SpawnCreature(pPlayer, 17592, -1203.8f, -12424.7f, 95.36f, 4.7f, 0);
		if(razormaw != NULL)
			razormaw->Despawn(6 * 60 * 1000, 0);
	}
};

class SavingPrincessStillpine : public GameObjectAIScript // TODO: Find what it does on retail
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(SavingPrincessStillpine)
	SavingPrincessStillpine(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player* pPlayer)
	{
		if(!pPlayer->HasQuest(9667))
			return;

		Creature* Princess = sEAS.GetNearestCreature(pPlayer, 17682);
		if(Princess != NULL)
			Princess->Despawn(1000, 1000);
	}
};

void SetupBloodmystIsleGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(181699, &BarrelOfFilth::Create);
	mgr->register_gameobject_script(181988, &Razormaw::Create); // Ever-burning Pyre
	mgr->register_gameobject_script(181928, &SavingPrincessStillpine::Create); // Princess Stillpine's Cage
}