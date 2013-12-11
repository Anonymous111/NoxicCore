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

class DarkTidingsAlliance : public QuestScript
{
public:
	void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
	{
		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17479);
		if(pCreature == NULL)
			return;

		char msg[100];
		sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg); // Changed Player to Creature. I wonder if it was blizzlike
	}
};

class DarkTidingsHorde : public QuestScript
{
public:
	void OnQuestComplete(Player* pPlayer, QuestLogEntry* qLogEntry)
	{
		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17558);
		if(pCreature == NULL)
			return;

		char msg[100];
		sprintf(msg, "Psst, %s, get over here.", pPlayer->GetName());
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, msg);
	}
};


void SetupHellfirePeninsula(ScriptMgr* mgr)
{
	mgr->register_quest_script(9587, new DarkTidingsAlliance());
	mgr->register_quest_script(9588, new DarkTidingsHorde());
}
