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

class Zealot : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Zealot);
		Zealot(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(!_unit->HasAura(3287))
				return;

			if(iWaypointId == 2)
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My mind. . .me flesh. . .I'm. . .rotting. . . .!");

			if(iWaypointId == 7)
				_unit->CastSpell(_unit, dbcSpell.LookupEntry(5), true);
		}
};

class CalvinMontague : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(CalvinMontague);
		CalvinMontague(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetFaction(68);
			_unit->SetStandState(STANDSTATE_STAND);
		}

		void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
		{
			if(_unit->GetHealthPct() < 10)
			{
				if(mAttacker->IsPlayer())
				{
					_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					RegisterAIUpdateEvent(1000);
					QuestLogEntry* pQuest = (TO_PLAYER(mAttacker))->GetQuestLogForEntry(590);
					if(!pQuest)
						return;

					pQuest->SendQuestComplete();
				}
			}
		}

		void AIUpdate()
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Okay, okay! Enough fighting.");
			_unit->RemoveNegativeAuras();
			_unit->SetFaction(68);
			_unit->SetStandState(STANDSTATE_SIT);
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(433), true);
			sEventMgr.AddEvent(TO_UNIT(_unit), &Unit::SetStandState, (uint8)STANDSTATE_STAND, EVENT_CREATURE_UPDATE, 18000, 0, 1);
			_unit->GetAIInterface()->WipeTargetList();
			_unit->GetAIInterface()->WipeHateList();
			_unit->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, _unit, 0);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
		}
};

void SetupZoneTirisfalGlades(ScriptMgr* mgr)
{
	mgr->register_creature_script(1931, &Zealot::Create);
	mgr->register_creature_script(6784, &CalvinMontague::Create);
}