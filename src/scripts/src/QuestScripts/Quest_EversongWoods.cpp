/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

class SCRIPT_DECL UnexpectedResults : public QuestScript
{
	public:
		void OnQuestStart(Player* pPlayer, QuestLogEntry *qLogEntry)
		{
			if( pPlayer == NULL || pPlayer->GetMapMgr() == NULL)
				return;

			Creature *Mirveda = pPlayer->GetMapMgr()->GetSqlIdCreature(40436);
			if(Mirveda == NULL)
				return;

			Creature * RotlimbA=  sEAS.SpawnCreature(pPlayer, 15658, 8732.59, -7144.96, 35.22, 3.56, 48000);
			Creature * RotlimbB=  sEAS.SpawnCreature(pPlayer, 15658, 8726.72, -7137.34, 35.22, 3.98, 48000);
			Creature * RotlimbC=  sEAS.SpawnCreature(pPlayer, 15658, 8718.37, -7132.00, 35.22, 4.30, 48000);
			RotlimbA->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbA->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbA->m_noRespawn=true;
			RotlimbB->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbB->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbB->m_noRespawn=true;
			RotlimbC->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbC->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbC->m_noRespawn=true;
			Mirveda->SetUInt32Value(UNIT_NPC_FLAGS, 0);
			Mirveda->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, pPlayer->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
			Mirveda->_setFaction();
			TimedEvent *te1 = TimedEvent::Allocate(this, new CallbackP1<UnexpectedResults, Player*>(this, &UnexpectedResults::QuestComplete, pPlayer), 0, 60000, 1);  
			pPlayer->event_AddEvent(te1);
			TimedEvent *te2 = TimedEvent::Allocate(this, new CallbackP1<UnexpectedResults, Creature*>(this, &UnexpectedResults::MirvedaReset, Mirveda), 0, 63000, 1);  
			Mirveda->event_AddEvent(te2);
		}
  
		void QuestComplete(Player * pPlayer)
		{
			Creature *Mirveda = pPlayer->GetMapMgr()->GetSqlIdCreature(40436);
			QuestLogEntry *en = pPlayer->GetQuestLogForEntry(8488);
			if(en && Mirveda->isAlive())
			{
				Mirveda->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "We made it!...thanks for protecting me");
				Mirveda->Emote(EMOTE_ONESHOT_LAUGH);
				en->SetMobCount(0, 1);
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
				en->SendQuestComplete();
				return;
			}
		}

		void MirvedaReset(Creature * AMirveda)
        {
			AMirveda->GetAIInterface()->SetAIState(STATE_IDLE);
			AMirveda->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 1604);
			AMirveda->_setFaction();
			AMirveda->SetUInt32Value(UNIT_NPC_FLAGS, 2);
		}
};

class ThirstUnending : public QuestScript
{
public:
	Player* pPlayer;
	Creature* pCreature = _unit->GetEntry(15274);
	if(pCreature->GetSpellEntry(28730 || 25046 || 50613))
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(8346);
		//pCreature->KillMob() // Should kill the mob, what is that damn command?!
		pQuest->SendQuestComplete();
	}
};

void SetupEversongWoods(ScriptMgr* mgr)
{
	mgr->register_quest_script(8488, new UnexpectedResults());
	mgr->register_quest_script(8346, new ThirstUnending());
}