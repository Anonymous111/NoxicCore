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

class Dalinda_Malem  : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Dalinda_Malem);
		Dalinda_Malem(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == 13)
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Thanks, these orcs wanted me to weld in the boiler");
				_unit->Despawn(5000, 1000);
				sEAS.DeleteWaypoints(_unit);
				if(_unit->m_escorter == NULL)
					return;
				Player* plr = _unit->m_escorter;
				_unit->m_escorter = NULL;
				plr->GetQuestLogForEntry(1440)->SendQuestComplete();
			}
		}
};

void SetupZoneDesolace(ScriptMgr* mgr)
{
	mgr->register_creature_script(5644, &Dalinda_Malem::Create);
}