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

static Coords SunkenTreauseWP[SunkenTreauseWPCount] =
{
        { -2078.054443f, -2091.207764f, 9.526212f, 0 },
        { -2076.626465f, -2109.960449f, 14.320494f, 0 },
        { -2072.851074f, -2123.574219f, 18.482662f, 0 },
        { -2063.878906f, -2132.617920f, 21.430487f, 0 },
        { -2051.495117f, -2145.205811f, 20.500065f, 0 },
        { -2044.748291f, -2152.411377f, 20.158432f, 0 },
        { -2044.748291f, -2152.411377f, 20.158432f, 0 },
        { -2044.748291f, -2152.411377f, 20.158432f, 0 },
        { -2044.748291f, -2152.411377f, 20.158432f, 0 },
        { -2044.748291f, -2152.411377f, 20.158432f, 0 },
        { -2051.495117f, -2145.205811f, 20.500065f, 0 },
        { -2063.878906f, -2132.617920f, 21.430487f, 0 },
        { -2072.851074f, -2123.574219f, 18.482662f, 0 },
        { -2076.626465f, -2109.960449f, 14.320494f, 0 },
        { -2078.054443f, -2091.207764f, 9.526212f, 0 }
};

class SunkenTreasure : public QuestScript
{
public:
	void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
	{
		float SSX = mTarget->GetPositionX();
		float SSY = mTarget->GetPositionY();
		float SSZ = mTarget->GetPositionZ();

		Creature* creat = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 2768);
		if(creat == NULL)
			return;
		creat->m_escorter = mTarget;
		creat->GetAIInterface()->setMoveType(11);
		creat->GetAIInterface()->StopMovement(3000);
		creat->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Defens Me!");
		creat->SetUInt32Value(UNIT_NPC_FLAGS, 0);

		CreateCustomWaypointMap(creat);
		for(uint32 i = 0; i < SunkenTreauseWPCount; i++)
			WaypointCreate(creat, SunkenTreauseWP[i].mX, SunkenTreauseWP[i].mY, SunkenTreauseWP[i].mZ, 0.0f, 0, 256, 4049);

		EnableWaypoints(creat);
	}
};

void SetupArathiHighlands(ScriptMgr* mgr)
{
	mgr->register_quest_script(665, new SunkenTreasure());
}