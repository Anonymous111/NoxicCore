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

#include "Setup.h"

// TODO: Add the missing text!
class ProfessorPhizzlethorpe : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ProfessorPhizzlethorpe)
	ProfessorPhizzlethorpe(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 15)
		{
			_unit->GetAIInterface()->deleteWaypoints();
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Thanks, I found the fact that, it searched.");
			_unit->Despawn(1000, 0);

			if(_unit->m_escorter != NULL)
			{
				_unit->m_escorter->GetQuestLogForEntry(665)->SendQuestComplete();
				_unit->m_escorter = NULL;
			}
		}
	}
};

void SetupZoneArathiHighlands(ScriptMgr* mgr)
{
	mgr->register_creature_script(2768, &ProfessorPhizzlethorpe::Create); // Professor Phizzlethorpe
}