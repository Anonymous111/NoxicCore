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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \
    Menu->SendTo(plr);

class TheKesselRun : public QuestScript
{
	public:
		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			if(!mTarget)
				return;
			if(!mTarget->HasSpell(30829))
				mTarget->CastSpell(mTarget, 30829, true);
		}
};

int fulborgskilled = 0;
class SavingPrincessStillpine : public GameObjectAIScript
{
	public:
		SavingPrincessStillpine(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new SavingPrincessStillpine(GO); }

		void OnActivate(Player* pPlayer)
		{
			QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(9667);
			if(qle == NULL)
				return;

			if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
			{
				qle->SetMobCount(0, qle->GetMobCount(0) + 1);
				qle->SendUpdateAddKill(0);
				qle->UpdatePlayerFields();
			}

			Creature* princess = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 17682);
			if(!princess)
				return;

			princess->Despawn(1000, 6 * 60 * 1000);
			return;
		}
};

void SetupBloodmystIsle(ScriptMgr* mgr)
{
	mgr->register_quest_script(9663, new TheKesselRun());

	mgr->register_gameobject_script(181928, &SavingPrincessStillpine::Create);
}