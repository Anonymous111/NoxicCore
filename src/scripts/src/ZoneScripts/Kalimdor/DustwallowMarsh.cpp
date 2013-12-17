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

#define BALOS_FRIENDLY_TIMER 120
class BalosJackenQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BalosJackenQAI);
	BalosJackenQAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		friendlyTimer = BALOS_FRIENDLY_TIMER;
	}

	void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
	{
		// If Balos Jacken HP - fAmount < 20%
		if(_unit->GetUInt32Value(UNIT_FIELD_HEALTH) - fAmount <= _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.2f)
		{
			//Missing: modify fAmount to prevent Balos Jacken death.
			//force player to loose target and stop melee auto-attack:
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			//start AIUpdate
			RegisterAIUpdateEvent(1000);
		}
	}

	void AIUpdate()
	{
		if(friendlyTimer == BALOS_FRIENDLY_TIMER)
		{
			// set Balos Jacken friendly and start friendlyTimer cooldown
			_unit->RemoveNegativeAuras();
			_unit->SetFaction(35);
			_unit->SetHealthPct(100);
			_unit->GetAIInterface()->WipeTargetList();
			_unit->GetAIInterface()->WipeHateList();
			_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			//remove not_selectable flag:
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
			// decrease timer
			friendlyTimer--;
		}
		else if(friendlyTimer == 0)
		{
			// set Balos Jacken unfriendly and reset FriendlyTimer
			_unit->SetFaction(14);
			_unit->GetAIInterface()->disable_melee = false;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
			friendlyTimer = BALOS_FRIENDLY_TIMER;
			RemoveAIUpdateEvent();
		}
		else
		{
			//friendlyTimer decrease
			friendlyTimer--;
		}
	}

	void OnDied(Unit* mKiller)
	{
		RemoveAIUpdateEvent();
	}

protected:
	short friendlyTimer;
};

class OverlordMokMorokk : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(OverlordMokMorokk);
	OverlordMokMorokk(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetStandState(STANDSTATE_STAND);
	}

	void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
	{
		uint32 chance = RandomUInt(100);
		if(chance < 25)
			_unit->CastSpell(mAttacker, dbcSpell.LookupEntry(6749), true);

		if(_unit->GetUInt32Value(UNIT_FIELD_HEALTH) - fAmount <= _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.3f)
		{
			if(mAttacker->IsPlayer())
			{
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				RegisterAIUpdateEvent(1000);
				QuestLogEntry* pQuest = (TO_PLAYER(mAttacker))->GetQuestLogForEntry(1173);
				if(!pQuest)
					return;
				pQuest->SendQuestComplete();
			}
		}
	}

	void AIUpdate()
	{
		_unit->RemoveNegativeAuras();
		_unit->SetFaction(29);
		_unit->SetHealthPct(100);
		_unit->GetAIInterface()->WipeTargetList();
		_unit->GetAIInterface()->WipeHateList();
		_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
	}
};

class PrivateHendel : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PrivateHendel);
	PrivateHendel(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetFaction(12);
		_unit->SetStandState(STANDSTATE_STAND);
	}

	void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
	{
		if(_unit->GetUInt32Value(UNIT_FIELD_HEALTH) - fAmount <= _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.37f)
		{
			if(mAttacker->IsPlayer())
			{
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				RegisterAIUpdateEvent(1000);
				QuestLogEntry* pQuest = (TO_PLAYER(mAttacker))->GetQuestLogForEntry(1324);
				if(!pQuest)
					return;
				pQuest->SendQuestComplete();
			}
		}
	}

	void AIUpdate()
	{
		_unit->Emote(EMOTE_STATE_KNEEL);
		_unit->RemoveNegativeAuras();
		_unit->SetFaction(12);
		_unit->SetHealthPct(100);
		_unit->GetAIInterface()->WipeTargetList();
		_unit->GetAIInterface()->WipeHateList();
		_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
	}
};

void SetupZoneDustwallowMarsh(ScriptMgr* mgr)
{
	mgr->register_creature_script(5089, &BalosJackenQAI::Create);
	mgr->register_creature_script(4500, &OverlordMokMorokk::Create);
	mgr->register_creature_script(4966, &PrivateHendel::Create);
}