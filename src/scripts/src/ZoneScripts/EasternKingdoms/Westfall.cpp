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

class The_Defias_Traitor : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(The_Defias_Traitor);
	The_Defias_Traitor(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 19)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Tell your master that this is where Van Cleef is hiding. I'm outta here!");
			_unit->Despawn(5000, 1000);
			sEAS.DeleteWaypoints(_unit);
			if(_unit->m_escorter == NULL)
				return;

			Player* pPlayer = _unit->m_escorter;
			_unit->m_escorter = NULL;
			pPlayer->GetQuestLogForEntry(155)->SendQuestComplete();
		}
	}
};

void SetupZoneWestfall(ScriptMgr* mgr)
{
	mgr->register_creature_script(467, &The_Defias_Traitor::Create);
}