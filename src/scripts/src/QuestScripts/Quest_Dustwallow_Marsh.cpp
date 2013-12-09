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

class Cleansing_of_the_Orb_of_Orahil : public QuestScript
{
	public:

		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			float SSX = mTarget->GetPositionX();
			float SSY = mTarget->GetPositionY();
			float SSZ = mTarget->GetPositionZ();

			Creature* creat = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 6546);

			if(creat == NULL)
				return;

			creat->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Fine, if you ready to go!");

			Creature* Demon = creat->GetMapMgr()->GetInterface()->SpawnCreature(6549, creat->GetPositionX(), creat->GetPositionY(), creat->GetPositionZ(), creat->GetOrientation(), true, false, 0, 0);
			sEventMgr.AddEvent(TO_CREATURE(Demon), &Creature::AddToWorld, creat->GetMapMgr(), EVENT_UNK, 12000, 0, 1);
			sEventMgr.AddEvent(TO_CREATURE(Demon), &Creature::Despawn, (uint32)120000, (uint32)0, EVENT_CREATURE_UPDATE, 12000, 0, 1);

			creat->GetAIInterface()->setMoveType(11);
			creat->GetAIInterface()->StopMovement(3000);

			sEAS.CreateCustomWaypointMap(creat);
			sEAS.WaypointCreate(creat, -4036.163818f, -3383.940918f, 38.977619f, 2.181819f, 0, 56, 5375);
			sEAS.WaypointCreate(creat, -4037.754639f, -3376.272461f, 37.400284f, 0.002337f, 0, 56, 5375);
			sEAS.WaypointCreate(creat, -4028.081787f, -3376.667969f, 38.152534f, 5.775016f, 0, 56, 5375);
			sEAS.WaypointCreate(creat, -4018.655029f, -3382.780518f, 38.244286f, 5.688624f, 0, 56, 5375);
			sEAS.WaypointCreate(creat, -4018.655029f, -3382.780518f, 38.244286f, 5.688624f, 11000, 256, 5375);
			sEAS.WaypointCreate(creat, -4028.081787f, -3376.667969f, 38.152534f, 5.775016f, 0, 256, 5375);
			sEAS.WaypointCreate(creat, -4037.754639f, -3376.272461f, 37.400284f, 0.002337f, 0, 256, 5375);
			sEAS.WaypointCreate(creat, -4036.163818f, -3383.940918f, 38.977619f, 2.181819f, 0, 256, 5375);
			sEAS.WaypointCreate(creat, -4036.1638f, -3383.9409f, 38.9776f, -1.3662f, 0, 256, 5375);
			sEAS.WaypointCreate(creat, -4032.5759f, -3393.6271f, 38.9960f, 1.8883f, 0, 256, 5375);
			sEAS.EnableWaypoints(creat);
		}
};

class ChallengeOverlordMokMorokk : public QuestScript
{
	public:

		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			float SSX = mTarget->GetPositionX();
			float SSY = mTarget->GetPositionY();
			float SSZ = mTarget->GetPositionZ();

			Creature* Overlord = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 4500);

			if(Overlord == NULL)
				return;

			string say = "Puny ";
			say += mTarget->GetName();
			say += " wanna fight Overlord Mok'Morokk? Me beat you! Me boss here!";
			Overlord->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, say.c_str());
			Overlord->SetFaction(72);
			Overlord->GetAIInterface()->disable_melee = false;
			Overlord->GetAIInterface()->SetAllowedToEnterCombat(true);
		}
};

class TheMissingDiplomat2 : public QuestScript
{
	public:

		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			float SSX = mTarget->GetPositionX();
			float SSY = mTarget->GetPositionY();
			float SSZ = mTarget->GetPositionZ();

			Creature* Dashel = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 4966);

			if(Dashel == NULL)
				return;

			Dashel->SetFaction(72);
			Dashel->GetAIInterface()->disable_melee = false;
			Dashel->GetAIInterface()->SetAllowedToEnterCombat(true);
		}
};

void SetupDustwallowMarsh(ScriptMgr* mgr)
{
	mgr->register_quest_script(4961, new Cleansing_of_the_Orb_of_Orahil());
	mgr->register_quest_script(1955, new Cleansing_of_the_Orb_of_Orahil());
	mgr->register_quest_script(1173, new ChallengeOverlordMokMorokk());
	mgr->register_quest_script(1324, new TheMissingDiplomat2());
}