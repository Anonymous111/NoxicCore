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

class DashelStonefist : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DashelStonefist);
		DashelStonefist(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetFaction(12);
			_unit->SetStandState(STANDSTATE_STAND);
		}

		void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
		{
			if(_unit->GetUInt32Value(UNIT_FIELD_HEALTH) - fAmount <= _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.2f)
			{
				if(mAttacker->IsPlayer())
				{
					_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					RegisterAIUpdateEvent(1000);
					QuestLogEntry* pQuest = (TO_PLAYER(mAttacker))->GetQuestLogForEntry(1447);
					if(!pQuest)
						return;
					pQuest->SendQuestComplete();
				}
			}
		}

		void AIUpdate()
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Okay, okay! Enough fighting. No one else needs to get hurt.");
			_unit->RemoveNegativeAuras();
			_unit->SetFaction(12);
			_unit->SetHealthPct(100);
			_unit->GetAIInterface()->WipeTargetList();
			_unit->GetAIInterface()->WipeHateList();
			_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
			RemoveAIUpdateEvent();
		}
};

class Bartleby : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Bartleby);
		Bartleby(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetFaction(11);
			_unit->setEmoteState(7);
		}

		void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
		{
			if(_unit->GetUInt32Value(UNIT_FIELD_HEALTH) - fAmount <= _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 0.37f)
			{
				if(mAttacker->IsPlayer())
				{
					_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					RegisterAIUpdateEvent(1000);
					QuestLogEntry* pQuest = (TO_PLAYER(mAttacker))->GetQuestLogForEntry(1640);
					if(!pQuest)
						return;
					pQuest->SendQuestComplete();
				}
			}
		}

		void AIUpdate()
		{
			_unit->RemoveNegativeAuras();
			_unit->SetFaction(11);
			_unit->SetHealthPct(100);
			_unit->GetAIInterface()->WipeTargetList();
			_unit->GetAIInterface()->WipeHateList();
			_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetUInt32Value(UNIT_FIELD_FLAGS, 0);
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
		}

};

void SetupZoneStormwindCity(ScriptMgr* mgr)
{
	mgr->register_creature_script(4961, &DashelStonefist::Create);
	mgr->register_creature_script(6090, &Bartleby::Create);
}