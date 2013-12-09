/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

class SummonElizaQuest : public QuestScript
{
	public:
		void OnQuestComplete(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			Creature* Eliza = sEAS.SpawnCreature(mTarget, 314, -10271.127f, 53.784f, 42.711f, 1.72f);
			if(Eliza != NULL)
				Eliza->Despawn(300000, 0);	// Should it be that much ?
		};
};

void SetupDuskwood(ScriptMgr* mgr)
{
	mgr->register_quest_script(254, new SummonElizaQuest());
}