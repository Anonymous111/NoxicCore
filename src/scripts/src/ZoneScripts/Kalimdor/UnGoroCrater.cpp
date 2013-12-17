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

class A_Me01  : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(A_Me01);
	A_Me01(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 28)
		{
			//_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Tr.........."); // Where the fuck did this come from????
			/* From wowpedia:
			    A-Me says: A-Me good. Good, A-Me. Follow... follow A-me. Home. A-me go home.
			    A-Me says: Bad, Un'Goro Gorilla. Un'Goro Gorilla, bad!
			    A-Me says: Good...good, A-Me. A-Me good. Home. Find home.
			    A-Me says: Danger, Danger! <mob name> try hurt A-Me.
			    A-Me says: A-me home! A-Me, good! Good A-Me. Home Home. Home. 
			*/
			_unit->Despawn(5000, 1000);
			sEAS.DeleteWaypoints(_unit);
			if(_unit->m_escorter == NULL)
				return;

			Player* pPlayer = _unit->m_escorter;
			_unit->m_escorter = NULL;
			pPlayer->GetQuestLogForEntry(4245)->SendQuestComplete();
		}
	}
};

class RingoDeadNPC : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(RingoDeadNPC);
	RingoDeadNPC(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetStandState(7);
		_unit->setDeathState(CORPSE);
		_unit->GetAIInterface()->m_canMove = false;
	}
};

void SetupZoneUnGoroCrater(ScriptMgr* mgr)
{
	mgr->register_creature_script(9623, &A_Me01::Create);
	mgr->register_creature_script(9999, &RingoDeadNPC::Create);
}