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

/*static LocationExtra ProspectorAnvilwardWaypoints[] =
{
	{ 9294.834f, -6681.092f, 22.428f, 1.284f, 0 },
	{ 9297.834f, -6671.092f, 22.387f, 0.793f, 0 },
	{ 9310.375f, -6658.936f, 22.43f,  2.046f, 0 },
	{ 9306.596f, -6650.905f, 25.222f, 2.666f, 0 },
	{ 9299.666f, -6648.099f, 28.39f,  3.468f, 0 },
	{ 9292.345f, -6650.509f, 30.908f, 4.249f, 0 },
	{ 9289.426f, -6657.825f, 31.829f, 6.154f, 0 },
	{ 9294.095f, -6658.863f, 34.482f, 6.063f, 0 },
};

class ProspectorAnvilwardAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ProspectorAnvilwardAI);
		ProspectorAnvilwardAI(Creature* c) : CreatureAIScript(c)
		{
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == sizeof(ProspectorAnvilwardWaypoints) / sizeof(LocationExtra) && bForwards)
			{
				_unit->GetAIInterface()->SetWaypointMap(NULL, false);
				_unit->SetFaction(14);
				RegisterAIUpdateEvent(10000);
			}
			else if(iWaypointId == 2 && !bForwards)
			{
				_unit->GetAIInterface()->SetWaypointMap(NULL);
				_unit->m_custom_waypoint_map = NULL;
				_unit->GetAIInterface()->MoveTo(_unit->GetSpawnX(), _unit->GetSpawnY(), _unit->GetSpawnZ() + 2.05f, _unit->GetSpawnO());
				_unit->SetFaction(35);
			}
		}

		void AIUpdate()
		{
			if(!_unit->CombatStatus.IsInCombat())
			{
				RemoveAIUpdateEvent();
				_unit->GetAIInterface()->SetWaypointMap(_unit->m_custom_waypoint_map);
			}
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
			if(_unit->GetAIInterface()->GetWaypointMap() != NULL)
				_unit->GetAIInterface()->SetWaypointMap(NULL);
			else if(_unit->m_custom_waypoint_map != NULL)
			{
				for(WayPointMap::iterator itr = _unit->m_custom_waypoint_map->begin(); itr != _unit->m_custom_waypoint_map->end(); ++itr)
					delete(*itr);
				delete _unit->m_custom_waypoint_map;
			}
			_unit->m_custom_waypoint_map = NULL;

			_unit->SetFaction(35);
		}
};*/

class ApprenticeMirveda : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ApprenticeMirveda);
		ApprenticeMirveda(Creature* pCreature) : CreatureAIScript(pCreature) {}
		void OnLoad()
		{
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 1604);
			_unit->_setFaction();
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
		}
};

class WhitebarkSpirit : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WhitebarkSpirit);
		WhitebarkSpirit(Creature* pCreature) : CreatureAIScript(pCreature) {}
		void OnCombatStart(Unit* mTarget)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You've returned. Haven't you done enough?");
			RegisterAIUpdateEvent(1000);
		}
		void AIUpdate()
		{
			if(_unit->GetHealthPct() < 35)
			{
				RemoveAIUpdateEvent();
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Very well...I admit defeat");
				_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
				_unit->_setFaction();
				_unit->GetAIInterface()->disable_combat = true;
				_unit->setDeathState(CORPSE);
				_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
				_unit->Despawn(30000, 0);
			}
		}
		void OnCombatStop(Unit* mTarget)
		{
			RemoveAIUpdateEvent();
		}
		void OnTargetDied(Unit* mTarget)
		{
			RemoveAIUpdateEvent();
		}
		void OnDied(Unit *mKiller)
		{
			RemoveAIUpdateEvent();
		}
};

void SetupZoneEversongWoods(ScriptMgr* mgr)
{
	//mgr->register_creature_script(15420, &ProspectorAnvilwardAI::Create);
	mgr->register_creature_script(19456, &WhitebarkSpirit::Create);
	mgr->register_creature_script(15402, &ApprenticeMirveda::Create);
}