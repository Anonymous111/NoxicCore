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

class BrazierOfEverfount : public GameObjectAIScript
{
public:
	BrazierOfEverfount(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new BrazierOfEverfount(GO); }

	void OnActivate(Player* pPlayer)
	{
		if(pPlayer->GetQuestLogForEntry(63))
		{
			float SSX = pPlayer->GetPositionX();
			float SSY = pPlayer->GetPositionY();
			float SSZ = pPlayer->GetPositionZ();
			float SSO = pPlayer->GetOrientation();

			Creature* NewCreature = pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(5894, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(600000, 0);
		}
		else
			pPlayer->BroadcastMessage("Missing required quest : Call of Water");
	}
};

class DustySpellbooks : public GameObjectAIScript
{
public:
	DustySpellbooks(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new DustySpellbooks(GO); }

	void OnLootTaken(Player* pLooter, ItemPrototype* pItemInfo)
	{
		QuestLogEntry* en = pLooter->GetQuestLogForEntry(422);
		if(!en)
			return;

		float SSX = pLooter->GetPositionX();
		float SSY = pLooter->GetPositionY();
		float SSZ = pLooter->GetPositionZ();
		float SSO = pLooter->GetOrientation();

		Creature* NewCreature = pLooter->GetMapMgr()->GetInterface()->SpawnCreature(1770, SSX, SSY, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "The Sons of Arugal will rise against all who challenge the power of the Moonrage!");
	}
};

void SetupSilverpineForestGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(113791, &BrazierOfEverfount::Create); // Brazier of Everfount
	mgr->register_gameobject_script(1571, &DustySpellbooks::Create); // Dusty Spellbooks
}