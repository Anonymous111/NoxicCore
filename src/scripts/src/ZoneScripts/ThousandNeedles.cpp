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

#include "Setup.h"

class Paoka_Swiftmountain : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Paoka_Swiftmountain);
		Paoka_Swiftmountain(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == 72)
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I appreciate the help you have shown Pao'ka. I hope this covers any misfortunes this deed has cost you.");
				_unit->Despawn(5000, 1000);
				sEAS.DeleteWaypoints(_unit);
				if(_unit->m_escorter == NULL)
					return;

				Player* pPlayer = _unit->m_escorter;
				_unit->m_escorter = NULL;
				if(pPlayer->GetQuestLogForEntry(4770))
					pPlayer->GetQuestLogForEntry(4770)->SendQuestComplete();
			}
		}
};

void SetupZoneThousandNeedles(ScriptMgr* mgr)
{
	mgr->register_creature_script(10427, &Paoka_Swiftmountain::Create);
}