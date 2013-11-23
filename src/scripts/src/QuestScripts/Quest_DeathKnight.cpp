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

class IntoTheRealmOfShadows : public QuestScript
{
public:
	void OnQuestStart(Player * mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->CastSpell(mTarget, 52693, false); // i am unsure if its not the: 52275 but i think no
	}
	void OnQuestComplete(Player * mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->PlaySound(12985);
	}
};

class InServiceOfLichKing : public QuestScript
{
public:
	void OnQuestStart(Player * mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->PlaySound(14734);
		sEventMgr.AddEvent(mTarget, &Player::PlaySound, (uint32)14735, EVENT_UNK, 23000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(mTarget, &Player::PlaySound, (uint32)14736, EVENT_UNK, 49000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
};

void DeathsChallenge(Player * Winner, Player * Looser)
{
	QuestLogEntry * pQuest = Winner->GetQuestLogForEntry( 12733 );
	if(	pQuest )
	{
		if( pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0] )
		{
			pQuest->SetMobCount( 0, pQuest->GetMobCount( 0 ) + 1 );
			pQuest->SendUpdateAddKill( 0 );
			pQuest->UpdatePlayerFields();
		}
	}
	return;
}

void SetupDeathKnight(ScriptMgr* mgr)
{
	mgr->register_hook(SERVER_HOOK_EVENT_ON_DUEL_FINISHED, (void*)&DeathsChallenge);

	mgr->register_quest_script(12687, new IntoTheRealmOfShadows());
	mgr->register_quest_script(12593, new InServiceOfLichKing());
}