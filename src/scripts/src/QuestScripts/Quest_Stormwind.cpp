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

class TheMissingDiplomat : public QuestScript
{
	public:

		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			float SSX = mTarget->GetPositionX();
			float SSY = mTarget->GetPositionY();
			float SSZ = mTarget->GetPositionZ();

			Creature* Dashel = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 4961);

			if(Dashel == NULL)
				return;

			Dashel->SetFaction(72);
			Dashel->GetAIInterface()->disable_melee = false;
			Dashel->GetAIInterface()->SetAllowedToEnterCombat(true);

			uint32 chance = RandomUInt(100);
			if(chance < 15)
			{
				string say = "Now you're gonna get it good, ";
				say += (TO_PLAYER(mTarget))->GetName();
				say += "!";
				Dashel->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, say.c_str());
			}
			sEAS.SpawnCreature(mTarget, 4969, -8686.803711f, 445.267792f, 99.789223f, 5.461184f, 300000);
			sEAS.SpawnCreature(mTarget, 4969, -8675.571289f, 444.162262f, 99.644737f, 3.834103f, 300000);
		}
};

void SetupStormwind(ScriptMgr* mgr)
{
	mgr->register_quest_script(1447, new TheMissingDiplomat());
}
