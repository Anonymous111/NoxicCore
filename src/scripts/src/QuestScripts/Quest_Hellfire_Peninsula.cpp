/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

class FelOrcScavengersQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FelOrcScavengersQAI);
	FelOrcScavengersQAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(10482);
			if(pQuest != NULL && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
		}
	}
};

class BurdenOfSoulsQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BurdenOfSoulsQAI);
	BurdenOfSoulsQAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(10864);
		if(pQuest != NULL && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
		{
			pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
			pQuest->SendUpdateAddKill(0);
			pQuest->UpdatePlayerFields();
		}
	}
};

class Dreadtusk : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Dreadtusk);
	Dreadtusk(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		QuestLogEntry* pQuest = TO_PLAYER(mKiller)->GetQuestLogForEntry(10255);
		if(pQuest != NULL && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
		{
			pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
			pQuest->SendUpdateAddKill(0);
			pQuest->UpdatePlayerFields();
		}
	}
};

class PrisonersDreghoodElders : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PrisonersDreghoodElders);
	PrisonersDreghoodElders(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetStandState(STANDSTATE_SIT);
		_unit->setDeathState(CORPSE);
		_unit->GetAIInterface()->m_canMove = false;
	}
};

class AncestralSpiritWolf : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AncestralSpiritWolf);
	AncestralSpiritWolf(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->CastSpell(_unit, 29938, false);
	}
};

class HellfireDeadNPC : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(HellfireDeadNPC);
	HellfireDeadNPC(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetStandState(7);
		_unit->setDeathState(CORPSE);
		_unit->GetAIInterface()->m_canMove = false;
	}
};

class DarkTidingsAlliance : public QuestScript
{
public:
	void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
	{
		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17479);
		if(pCreature == NULL)
			return;

		char msg[100];
		sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg); // Changed Player to Creature. I wonder if it was blizzlike
	}
};

class DarkTidingsHorde : public QuestScript
{
public:
	void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
	{
		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17558);
		if(pCreature == NULL)
			return;

		char msg[100];
		sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg);
	}
};


void SetupHellfirePeninsula(ScriptMgr* mgr)
{
	// Finished
	mgr->register_creature_script(16772, &FelOrcScavengersQAI::Create);
	mgr->register_creature_script(19701, &FelOrcScavengersQAI::Create);
	mgr->register_creature_script(16876, &FelOrcScavengersQAI::Create);
	mgr->register_creature_script(16925, &FelOrcScavengersQAI::Create);
	mgr->register_creature_script(18952, &FelOrcScavengersQAI::Create);
	mgr->register_creature_script(19411, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(19410, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(16867, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(16870, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(19413, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(19414, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(16878, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(19415, &BurdenOfSoulsQAI::Create);
	mgr->register_creature_script(16992, &Dreadtusk::Create);

	/*-------------------------------------------------------------------*/
	// TODO
	//mgr->register_dummy_spell(35460, &FuryOfTheDreghoodElders);


	/*-------------------------------------------------------------------*/
	// NPC States
	mgr->register_creature_script(20677, &PrisonersDreghoodElders::Create);
	mgr->register_creature_script(20678, &PrisonersDreghoodElders::Create);
	mgr->register_creature_script(20679, &PrisonersDreghoodElders::Create);
	mgr->register_creature_script(17405, &HellfireDeadNPC::Create);
	mgr->register_creature_script(16852, &HellfireDeadNPC::Create);
	mgr->register_creature_script(20158, &HellfireDeadNPC::Create);

	mgr->register_quest_script(9587, new DarkTidingsAlliance());
	mgr->register_quest_script(9588, new DarkTidingsHorde());

	mgr->register_creature_script(17077, &AncestralSpiritWolf::Create);
}
