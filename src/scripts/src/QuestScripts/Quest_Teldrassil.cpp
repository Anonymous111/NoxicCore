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

class Zenn_Foulhoof : public QuestScript
{
public:
	void OnQuestComplete(Player* mTarget, QuestLogEntry* qLogEntry)
	{
		Creature* pCreature = mTarget->GetMapMgr()->GetSqlIdCreature(43727);
		if(pCreature == NULL)
			return;

		pCreature->SetDisplayId(901);
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Ribbit! No!! This cannot...ribbit...be! You have duped me with...ribbit...your foul trickery! Ribbit!");

		sEventMgr.AddEvent(TO_OBJECT(pCreature), &Object::EventSetUInt32Value, (uint32)UNIT_FIELD_DISPLAYID, (uint32)10035, EVENT_UNK, 50000, 0, 1);
	}
};

void SetupTeldrassil(ScriptMgr* mgr)
{
	mgr->register_quest_script(489, new Zenn_Foulhoof());
}