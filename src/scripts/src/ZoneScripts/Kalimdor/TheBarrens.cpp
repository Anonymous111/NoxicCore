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

class SavannahProwler : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SavannahProwler);
	SavannahProwler(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		uint8 chance = RandomUInt(3);

		if(chance == 1)
			_unit->SetStandState(STANDSTATE_SLEEP); 
	}

	void OnCombatStart(Unit* pTarget)
	{
		if(_unit->GetStandState() == STANDSTATE_SLEEP)
			_unit->SetStandState(0);
	}

	void Destroy()
	{
		delete this;
	}
};

class Gilthares_Firebough : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Gilthares_Firebough);
	Gilthares_Firebough(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 100)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Finally, I am rescued");
			_unit->Despawn(5000,1000);
			sEAS.DeleteWaypoints(_unit);
			if(_unit->m_escorter == NULL)
				return;

			Player* pPlayer = _unit->m_escorter;
			_unit->m_escorter = NULL;
			pPlayer->GetQuestLogForEntry(898)->SendQuestComplete();
		}
	}
};

class Wizzlecranks_Shredder : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Wizzlecranks_Shredder);
	Wizzlecranks_Shredder(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 195)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Thank you Young warior!");
			_unit->Despawn(5000, 1000);
			sEAS.DeleteWaypoints(_unit);
			if(_unit->m_escorter == NULL)
				return;

			Player* pPlayer = _unit->m_escorter;
			_unit->m_escorter = NULL;
			pPlayer->GetQuestLogForEntry(863)->SendQuestComplete();
		}
	}
};

int kolkarskilled = 0;
class VerogtheDervish : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(VerogtheDervish);
	VerogtheDervish(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		kolkarskilled++;
		if(mKiller->IsPlayer())
		{
			Player* mPlayer = TO_PLAYER(mKiller);

			if(kolkarskilled > 8 && mPlayer->GetQuestLogForEntry(851))
			{
				_unit->GetMapMgr()->GetInterface()->SpawnCreature(3395, -1209.8f, -2729.84f, 106.33f, 4.8f, true, false, 0, 0)->Despawn(600000, 0);
				kolkarskilled = 0;
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "I am slain! Summon Verog!");
			}
		}
	}
};

void SetupZoneTheBarrens(ScriptMgr* mgr)
{
	mgr->register_creature_script(3425, &SavannahProwler::Create);
	mgr->register_creature_script(3465, &Gilthares_Firebough::Create);
	mgr->register_creature_script(3275, &VerogtheDervish::Create);
	mgr->register_creature_script(3274, &VerogtheDervish::Create);
	mgr->register_creature_script(3397, &VerogtheDervish::Create);
	mgr->register_creature_script(4316, &VerogtheDervish::Create);
	mgr->register_creature_script(3439, &Wizzlecranks_Shredder::Create);
}