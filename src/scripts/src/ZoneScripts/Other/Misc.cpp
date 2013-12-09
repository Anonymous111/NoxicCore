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

class Kaliri : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Kaliri);
	Kaliri(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetFaction(35);
	}
};

#define QUEST_CLUCK 3861
#define ITEM_CHICKEN_FEED 11109

class Chicken : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Chicken);
	Chicken(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetFaction(12);
		_unit->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
		RegisterAIUpdateEvent(120000);
	}

	void AIUpdate()
	{
		if(_unit->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
			OnLoad();
	}
};

/*class ArmyofDeadGhoul : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ArmyofDeadGhoul)
	ArmyofDeadGhoul(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->GetAIInterface()->m_canMove = false;
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(200);
	}

	void AIUpdate()
	{
		_unit->CastSpell(_unit, 20480, false);
		_unit->GetAIInterface()->m_canMove = true;
		RemoveAIUpdateEvent();
	}
};

class EranikusTheChained : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(EranikusTheChained)
	EranikusTheChained(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		Player* pPlayer = sEAS.GetNearestPlayer(_unit);
		switch(rand()%8)
		{
			case 0:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Will the nightmare ever end?! I cannot force myself awake!", pPlayer);
			break;
			case 1:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My soul is not a trinket! Mortal, you must release me from these chains!", pPlayer);
			break;
			case 2:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My eyes! It burns... it burns...", pPlayer);
			break;
			case 3:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Torture me no more! Release me, mortal! The Swamp of Sorrows... mortal... please...", pPlayer);
			break;
			case 4:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Foolish mortal, I will rend your soul in two once I am released!", pPlayer);
			break;
			case 5:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Foolish mortals you do not yet see the potential of that Artifact.", pPlayer);
			break;
			case 6:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You are an agent of their wicked god, fool. I will see you destroyed!", pPlayer);
			break;
			case 7:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "It hurts so much... Itharius, my old friend... Please help me...", pPlayer);
			break;
			case 8:
				_unit->SendChatMessageToPlayer(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My charge to watch the temple has failed... my corrupted soul knows no peace...", pPlayer);
			break;
		}
	}
};*/

/*************************************** Zeppelins *******************************************/

// Thundercaller (Og to Uc) zepplin definitions
#define THUNDERCALLER 164871
#define ZAPETTA 9566
#define FREZZA 9564
#define KRAXX 23713
#define KRIXX 23635
#define CLOUDKICKER 25077
#define COPPERNUT 25070
#define RUSTHAMMER 25071
#define SPARKFLY 25074
#define QUICKFIX 25072
#define FAIRWEATHER 25076

// The Iron Eagle (Og to grom'gol) zeppelin definitions
#define IRONEAGLE 175080
#define SNURK 12136
#define NEZRAZ 3149
#define FASTWRENCH 24931
#define GAZZLEGEAR 24930
#define CROSSWIRE 24929

// The Purple Princess (Undercity to Grom'Gol) zeppelin definitions
#define PURPLEPRINCESS 176495
#define HINDENBURG 3150
#define OVERSPECK 12137
#define HATCH 25104
#define HAMMERFLANGE 25100
#define DUUNA 25106
#define BOLTSHINE 25103
#define CUTPIPE 25101

/*class Cloudkicker : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Cloudkicker)
	Cloudkicker(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		state = -1; // base state, means do nothing
	}

	void AIUpdate()
	{
		// random events
		// random script when starting #1
		if(state == 0)
		{
			Emote("Mister Copperpot, you may take us out.", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #2
		if(state == 1)
		{
			Emote("Full spead ahead Mister Copperbolt!", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if(state == 2)
		{
			Emote("Take us out nice and fast mister Copperpants.", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if(state == 3)
			state = 1;

		// we just arrived to kalimdor, landing
		if(state == 4)
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));

			if(Rand(50))
				Emote("I can't believe how lucky we got on that trip! I really am the greatest sky-captain in all realms!", Text_Say);
			else
				Emote("Another successful trip! Come on boys let's buzz the tower!", Text_Say);

			timer = AddTimer(8000);
			state = 5;
		}
		if(state == 5 && IsTimerFinished(timer))
		{
			RemoveTimer(timer);
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			state = -1;
			RemoveAIUpdateEvent();
		}
	}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		// we just changed our map, we should shout that we are docking :)
		if(pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId())
		{
			if(Rand(50))
			{
				// start dialog with state 4
				state = 4;
				RegisterAIUpdateEvent(1000);
			}
		}
		// we are starting our way
		else if(pTransporter->mLastWaypoint->second.delayed)
		{
			// start dialog with random state 0 - 3
			state = pTransporter->start_event;
			RegisterAIUpdateEvent(1000);
		}
	}

private:
	int8 state;
	int32 timer;
};

class Coppernut : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Coppernut)
	Coppernut(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		state = 0;
	}

	void AIUpdate()
	{
		// random script when starting #1
		if(state == 0)
		{
			timer = AddTimer(4000);
			state = 7;
		}
		if(state == 7 && IsTimerFinished(timer))
		{
			Emote("Sir, if you could at least get my gender correct...", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #2
		if(state == 1)
		{
			timer = AddTimer(4000);
			state = 8;
		}
		if(state == 8 && IsTimerFinished(timer))
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			Emote("Mister Fairweather, slow ahead if you please!", Text_Say);
			RemoveTimer(timer);
			timer = AddTimer(5000);
			state = 9;
		}
		if(state == 9 && IsTimerFinished(timer))
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			Emote("Close sir...", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if(state == 2)
		{
			timer = AddTimer(4000);
			state = 10;
		}
		if(state == 10 && IsTimerFinished(timer))
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			Emote("Mister Fairweather, slow ahead if you please!", Text_Say);
			RemoveTimer(timer);
			timer = AddTimer(5000);
			state = 11;
		}
		if(state == 11 && IsTimerFinished(timer))
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			Emote("You almost got my name right that time, sir.", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		if(state == 3)
			state = 1;
		
		// we just arrived to kalimdor, landing script
		if(state == 4)
		{
			timer = AddTimer(4000);
			state = 5;
		}
		if(state == 5 && IsTimerFinished(timer))
		{
			RemoveTimer(timer);
			turn_timer = AddTimer(4000);
			state = 6;
				
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			Emote("Prepare to dock!", Text_Say);
			_unit->Emote(EMOTE_ONESHOT_SHOUT);
		}
		if(state == 6 && IsTimerFinished(turn_timer))
		{
			RemoveTimer(turn_timer);
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			state = -1;
			RemoveAIUpdateEvent();
		}
	}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		// we just changed our map, we should shout that we are docking :)
		if(pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId())
		{
			// start dialog with state 1
			state = 4;
			RegisterAIUpdateEvent(1000);
		}
		// we are starting our way
		else if(pTransporter->mLastWaypoint->second.delayed)
		{
			// start dialog with random state 0 - 3
			state = pTransporter->start_event;
			RegisterAIUpdateEvent(1000);
		}
	}

private:
	uint8 state;
	int32 timer;
	int32 turn_timer;
};

class Fairweather : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Fairweather)
	Fairweather(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		if(pTransporter->state == TRANSPORTER_STATE_JUST_CHANGED_MAP || pTransporter->state == TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING)
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			_unit->SetEmoteState(EMOTE_STATE_USESTANDING);
		}
		else
		{
			_unit->SetFacing(_unit->GetOrientation()+float(M_PI));
			_unit->SetEmoteState(0);
		}
	}
};

class Hatch : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Hatch)
	Hatch(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		state = 0;
	}

	void AIUpdate()
	{
		if(state == 1)
		{
			timer = AddTimer(5000);
			state = 2;
		}
		if(state == 2 && IsTimerFinished(timer))
		{
			RemoveTimer(timer);
			state = 0;
			Emote("It's go time!", Text_Say);
			_unit->SetStandState(0);
			RemoveAIUpdateEvent();
		}
	}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		// we are docking
		if(pTransporter->mCurrentWaypoint->second.delayed)
		{
			Emote("I'm going to take short nap. Do you think you can handle the ship while she's not moving?", Text_Say);
			_unit->SetStandState(3);
		}
		// we are starting our way
		else if(pTransporter->mLastWaypoint->second.delayed)
		{
			state = 1;
			RegisterAIUpdateEvent(1000);
		}
	}

private:
	uint8 state;
	int32 timer;
};

class Hammerflange : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Hammerflange)
	Hammerflange(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		// we are starting our way
		if(pTransporter->mLastWaypoint->second.delayed)
		{
			Emote("NAP'S OVER!! WE ARE HEADING OUT!", Text_Say);
		}
	}
};

class Duuna : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Duuna)
	Duuna(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnTransporterUpdate(Transporter* pTransporter)
	{
		// we are starting our way
		if(pTransporter->mLastWaypoint->second.delayed || pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId())
		{
			// sit
			_unit->SetStandState(1);
		}
		// next waypoint will be docking
		else if(pTransporter->mNextWaypoint->second.delayed)
		{
			// stand up
			_unit->SetStandState(0);
		}
	}
};

// this is simple worker AI
class Zepp_Worker : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Zepp_Worker)
	Zepp_Worker(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		state = 0;
		initiliaze_state = RandomUInt(1); // begin at random state
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		//these are used for initializing
		if(initiliaze_state == 0 || (IsTimerFinished(timer) && state == 0))
		{
			_unit->SetEmoteState(EMOTE_STATE_WORK);
			timer = AddTimer((RandomUInt(3)+6)*1000);
			state = 2;
			initiliaze_state = 2;
		}
		else if(initiliaze_state == 1 || (IsTimerFinished(timer) && state == 1))
		{
			RemoveTimer(timer);
			_unit->SetEmoteState(EMOTE_STATE_USESTANDING);
			timer = AddTimer((RandomUInt(3)+6)*1000);
			state = 2;
			initiliaze_state = 2;
		}
		else if(IsTimerFinished(timer) && state == 2)
		{
			RemoveTimer(timer);
			_unit->SetEmoteState(0);
			timer = AddTimer(2000);
			state = RandomUInt(1);
		}
	}

private:
	uint8 state;
	uint8 initiliaze_state;
	int32 timer;
};

void ZeppelinThundercaller(Transporter* pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{
		// undercity
		if(pTransporter->GetMapId() == 0)
		{
			Creature* cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, ZAPETTA);
			if(!cr)
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!");

			if(Rand(35))
			cr->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_ORCISH, "There goes the zeppelin to Orgrimmar. I hope there's no explosions this time.", 61500);

		}
		else
		// orgrimmar
		{
			Creature* cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, FREZZA);
			if(!cr)
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!");
		}
	}
}

void ZeppelinIronEagle(Transporter* pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{*/
		// grom'gol - this one is not announcing it!
		/*if(pTransporter->GetMapId() == 0)
		{
			Creature* cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, NEZRAZ);
			if(!cr)
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!");
		}
		else*/
		// orgrimmar
		/*{
			Creature* cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, SNURK);
			if(!cr)
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Grom'gol has just arrived! All aboard for Stranglethorn!");
		}
	}
}

void ZeppelinPurplePrincess(Transporter* pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{
		*/// this one is not announcing on retail!
		/*Creature* cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, OVERSPECK);
		if(cr)
			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!");*/

		/*Creature* cr2 = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, HINDENBURG);
		if(cr2)
			cr2->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Grom'gol has just arrived! All aboard for Stranglethorn!");
	}
}

void OnTransporterUpdate(Transporter* pTransporter, bool delayed)
{
	switch(pTransporter->GetEntry())
	{
		// Thundercaller (Undercity <-> Orgrimmar)
		case THUNDERCALLER:
			ZeppelinThundercaller(pTransporter, delayed);
		break;
		// Iron Eagle (Orgrimmar <-> Grom'Gol)
		case IRONEAGLE:
			ZeppelinIronEagle(pTransporter, delayed);
		break;
		// Purple Princess (Undercity <-> Grom'Gol)
		case PURPLEPRINCESS:
			ZeppelinPurplePrincess(pTransporter, delayed);
		break;
	}
}*/

#define SAY_DOC1 "I'm saved! Thank you, doctor!"
#define SAY_DOC2 "HOORAY! I AM SAVED!"
#define SAY_DOC3 "Sweet, sweet embrace... take me..."

#define A_RUNTOX -3742.96
#define A_RUNTOY -4531.52
#define A_RUNTOZ 11.91

#define H_RUNTOX -1016.44
#define H_RUNTOY -3508.48
#define H_RUNTOZ 62.96

const uint32 allianceSoldierId[3] =
{
	12938, // 12938 Injured Alliance Soldier
	12936, // 12936 Badly injured Alliance Soldier
	12937  // 12937 Critically injured Alliance Soldier
};

const uint32 hordeSoldierId[3] =
{
	12923, //12923 Injured Soldier
	12924, //12924 Badly injured Soldier
	12925  //12925 Critically injured Soldier
};

class InjuredSoldier : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(InjuredSoldier);
	InjuredSoldier(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetUInt32Value(UNIT_FIELD_BYTES_0, 16777472);
		_unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		_unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
		_unit->SetUInt32Value(UNIT_FIELD_BYTES_1, 7);

		uint32 sid = _unit->GetEntry();

		switch(sid)
		{
			case 12923:
			case 12938:
				_unit->SetHealthPct(75);
				break;
			case 12924:
			case 12936:
				_unit->SetHealthPct(50);
				break;
			case 12925:
			case 12937:
				_unit->SetHealthPct(25);
				break;
		}
	}
};

void SetupZoneMisc(ScriptMgr* mgr)
{
	// Main script used for Zeppelin Masters
	//mgr->register_hook(SERVER_HOOK_EVENT_ON_TRANSPORTER_UPDATE, (void*)&OnTransporterUpdate);

	mgr->register_creature_script(21468, &Kaliri::Create);
	mgr->register_creature_script(620, &Chicken::Create);
	/*mgr->register_creature_script(24207, &ArmyofDeadGhoul::Create);
	mgr->register_creature_script(8506, &EranikusTheChained::Create);

	// Zeppelin Thundercaller
	mgr->register_creature_script(CLOUDKICKER, &Cloudkicker::Create);
	mgr->register_creature_script(COPPERNUT, &Coppernut::Create);
	mgr->register_creature_script(FAIRWEATHER, &Fairweather::Create);
	mgr->register_creature_script(RUSTHAMMER, &Zepp_Worker::Create);
	mgr->register_creature_script(SPARKFLY, &Zepp_Worker::Create);
	mgr->register_creature_script(QUICKFIX, &Zepp_Worker::Create);

	// Zeppelin the Purple Princess
	mgr->register_creature_script(HATCH, &Hatch::Create);
	mgr->register_creature_script(HAMMERFLANGE, &Hammerflange::Create);
	mgr->register_creature_script(DUUNA, &Duuna::Create);
	mgr->register_creature_script(BOLTSHINE, &Zepp_Worker::Create);
	mgr->register_creature_script(CUTPIPE, &Zepp_Worker::Create);

	// Zeppelin the Iron Eagle
	mgr->register_creature_script(FASTWRENCH, &Zepp_Worker::Create);
	mgr->register_creature_script(GAZZLEGEAR, &Zepp_Worker::Create);
	mgr->register_creature_script(CROSSWIRE, &Zepp_Worker::Create);*/
	mgr->register_creature_script(12923, &InjuredSoldier::Create);
	mgr->register_creature_script(12924, &InjuredSoldier::Create);
	mgr->register_creature_script(12925, &InjuredSoldier::Create);
	mgr->register_creature_script(12936, &InjuredSoldier::Create);
	mgr->register_creature_script(12937, &InjuredSoldier::Create);
	mgr->register_creature_script(12938, &InjuredSoldier::Create);
}