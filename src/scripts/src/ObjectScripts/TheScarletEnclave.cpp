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

#define CN_INITIATE_1				29519
#define CN_INITIATE_2				29565
#define CN_INITIATE_3				29567
#define CN_INITIATE_4				29520

class AcherusSoulPrison : GameObjectAIScript
{
public:
    AcherusSoulPrison(GameObject * goinstance) : GameObjectAIScript(goinstance) {}
    static GameObjectAIScript * Create(GameObject* GO) 
	{ 
	return new AcherusSoulPrison(GO); 
	}

    void OnActivate(Player* pPlayer)
    {
        QuestLogEntry * en = pPlayer->GetQuestLogForEntry(12848);
        if(!en)
			return;
            
		if(en->GetMobCount(0) != 0)
			return;

		float SSX = pPlayer->GetPositionX();
		float SSY = pPlayer->GetPositionY();
		float SSZ = pPlayer->GetPositionZ();
            
		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ);
		     
		if(!pCreature || !pCreature->isAlive())
			return;

		if (pCreature->GetEntry() == CN_INITIATE_1 || pCreature->GetEntry() == CN_INITIATE_2 || pCreature->GetEntry() == CN_INITIATE_3 || pCreature->GetEntry() == CN_INITIATE_4)
		{
			pPlayer->SendChatMessage(CHAT_MSG_SAY, LANG_UNIVERSAL, "I give you the key to your salvation");
            pCreature->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
            pCreature->GetAIInterface()->SetNextTarget(pPlayer);
            pCreature->GetAIInterface()->AttackReaction(pPlayer, 1, 0);
            pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You have committed a big mistake, demon");
		}
    }
};

class EyeofAcherusControl : public GameObjectAIScript
{
	public:
		EyeofAcherusControl(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new EyeofAcherusControl(GO); }

		void OnActivate(Player* pPlayer)
		{
			if(!pPlayer->GetQuestLogForEntry(12641))
				return;
			//pPlayer->CastSpell(pPlayer, 51888, true);// origonal
			pPlayer->CastSpell(pPlayer, 51852, true);
		}
};

void SetupTheScarletEnclaveGameObject(ScriptMgr* mgr)
{
	uint32 SoulPrisonIds[] = { 191577, 191580, 191581, 191582, 191583, 191584, 191585, 191586, 191587, 191588, 191589, 191590, 0};
	mgr->register_gameobject_script(SoulPrisonIds, &AcherusSoulPrison::Create);
	mgr->register_gameobject_script(191609, &EyeofAcherusControl::Create);
}