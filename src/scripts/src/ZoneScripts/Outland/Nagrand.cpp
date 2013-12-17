/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

class GiseldaTheCroneQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GiseldaTheCroneQAI);
	GiseldaTheCroneQAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			if((TO_PLAYER(mKiller))->GetTeam() == 0)
			{
				QuestLogEntry* pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(9936);
				if(pQuest && pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
				{
					pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
			else
			{
				QuestLogEntry *pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(9935);
				if(pQuest && pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
				{
					pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
					pQuest->SendUpdateAddKill(1);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
		}
	}
};

class mogorQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(mogorQAI);
	mogorQAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
	}
};

class NotOnMyWatch : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(NotOnMyWatch);
	NotOnMyWatch(Creature* pCreature) : CreatureAIScript(pCreature) {};

	void OnCombatStart(Unit* mTarget)
	{
		RegisterAIUpdateEvent(1000);
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "In Nagrand, food hunt ogre!");
	}

	void OnCombatStop()
	{
		RemoveAIUpdateEvent();
	}

	void OnDied(Unit* mTarget)
	{
		RemoveAIUpdateEvent();
	}

	void OnLoad()
	{
		_unit->SetFaction(14);
		RemoveAIUpdateEvent();
	}

	void AIUpdate()
	{
		if(_unit->GetHealthPct() < 30)
		{
			Unit* pUnit = _unit->GetAIInterface()->GetMostHated();
			if(pUnit != NULL && pUnit->IsPlayer())
				TO_PLAYER(pUnit)->EventAttackStop();
			_unit->SetFaction(35);
			_unit->GetAIInterface()->WipeHateList();
			_unit->GetAIInterface()->WipeTargetList();
			_unit->SetStandState(STANDSTATE_SIT);
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
			_unit->Despawn(180000, 0);

			RemoveAIUpdateEvent();
		}
	}
};

void SetupZoneNagrand(ScriptMgr* mgr)
{
	mgr->register_creature_script(18351, &NotOnMyWatch::Create);
	mgr->register_creature_script(18069, &mogorQAI::Create);
	mgr->register_creature_script(17147, &GiseldaTheCroneQAI::Create);
	mgr->register_creature_script(17148, &GiseldaTheCroneQAI::Create);
	mgr->register_creature_script(18397, &GiseldaTheCroneQAI::Create);
	mgr->register_creature_script(18658, &GiseldaTheCroneQAI::Create);
	mgr->register_creature_script(17146, &GiseldaTheCroneQAI::Create);
}