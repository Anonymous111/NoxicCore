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

class EclipsionSpawn : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(EclipsionSpawn)
	EclipsionSpawn(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		_unit->CastSpell(_unit, 38311, true); // Cast spell: "Summon Eclipsion Hawkstrider"
	}
};

// Infiltrating Dragonmaw Fortress Quest
class InfiltratingDragonmawFortressQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(InfiltratingDragonmawFortressQAI);
	InfiltratingDragonmawFortressQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			QuestLogEntry* pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(10836);
			if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
				return;
			}
		}
	}
};

class KneepadsQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KneepadsQAI);
	KneepadsQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}
		void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			QuestLogEntry* pQuest = NULL;
			pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(10703);
			if(pQuest == NULL)
			{
				pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(10702);
				if(pQuest == NULL)
					return;
			}

			if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
		}
		return;
	}
};

#define CN_DEATHBRINGER_JOVAAN	21633

struct WPWaitTimes
{
	LocationExtra mCoords;
	uint32 WaitTime;
};

const WPWaitTimes DeathbringerJovaanWP[] =
{
	{ { }, 0},
	{ { -3310.743896f, 2951.929199f, 171.132538f, 5.054039f, Flag_Walk }, 0 },
	{ { -3308.501221f, 2940.098389f, 171.025772f, 5.061895f, Flag_Walk }, 0 },
	{ { -3306.261203f, 2933.843210f, 170.934145f, 5.474234f, Flag_Walk }, 44000 },
	{ { -3310.743896f, 2951.929199f, 171.132538f, 1.743588f, Flag_Walk }, 0 }
};

class DeathbringerJovaanAI : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(DeathbringerJovaanAI, MoonScriptCreatureAI);
	DeathbringerJovaanAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		mJovaanTimer = INVALIDATE_TIMER;
		mJovaanPhase = -1;

		for(int i = 1; i < 5; ++i)
			AddWaypoint(CreateWaypoint(i, DeathbringerJovaanWP[i].WaitTime, DeathbringerJovaanWP[i].mCoords.addition, DeathbringerJovaanWP[i].mCoords));
	}

	void AIUpdate()
	{
		if(IsTimerFinished(mJovaanTimer))
		{
			switch(mJovaanPhase)
			{
				case 0:
				{
					MoonScriptCreatureAI* pRazuunAI = SpawnCreature(21502, -3300.47f, 2927.22f, 173.870f, 2.42924f, false);	// Spawn Razuun
					if(pRazuunAI != NULL)
					{
						pRazuunAI->GetUnit()->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_2);
						pRazuunAI->SetCanEnterCombat(false);
						pRazuunAI->SetMoveType(Move_DontMoveWP);
						pRazuunAI->SetCanMove(false);
					}
					_unit->SetStandState(STANDSTATE_KNEEL);
					_unit->Emote(EMOTE_ONESHOT_TALK);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Everything is in readiness, warbringer.");
					mJovaanPhase = 1;
					ResetTimer(mJovaanTimer, 6000);
				}break;
				case 1:
				{
					_unit->Emote(EMOTE_ONESHOT_TALK);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Warbringer, that will require the use of all the hold's infernals. It may leave us vulnerable to a counterattack.");
					mJovaanPhase = 2;
					ResetTimer(mJovaanTimer, 11000);
				}break;
				case 2:
				{
					_unit->SetStandState(STANDSTATE_STAND);
					mJovaanPhase = 3;
					ResetTimer(mJovaanTimer, 1000);
				}break;
				case 3:
				{
					_unit->Emote(EMOTE_ONESHOT_SALUTE);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "It shall be as you say, warbringer. One last question, if I may...");
					mJovaanPhase = 4;
					ResetTimer(mJovaanTimer, 10000);
				}break;
				case 4:
				{
					_unit->Emote(EMOTE_ONESHOT_QUESTION);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "What's in the crate?");
					mJovaanPhase = 5;
					ResetTimer(mJovaanTimer, 10000);
				}break;
				case 5:
				{
					_unit->Emote(EMOTE_ONESHOT_SALUTE);
					mJovaanPhase = -1;
					RemoveTimer(mJovaanTimer);
				}break;
			}
		}
		ParentClass::AIUpdate();
	}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		switch(iWaypointId)
		{
			case 3:
			{
				RegisterAIUpdateEvent(1000);
				_unit->Emote(EMOTE_ONESHOT_POINT);
				mJovaanPhase = 0;
				mJovaanTimer = AddTimer(1500);
			}break;
			case 4:
				Despawn(1, 0);
			break;
			}
		}

	int32 mJovaanTimer;
	int32 mJovaanPhase;
};

#define CN_WARBRINGER_RAZUUN	21502

class WarbringerRazuunAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(WarbringerRazuunAI, MoonScriptCreatureAI);
		WarbringerRazuunAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			RegisterAIUpdateEvent(1000);
			mRazuunTimer = AddTimer(800);
			mRazuunPhase = 0;
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mRazuunTimer))
			{
				switch(mRazuunPhase)
				{
					case 0:
						{
							_unit->Emote(EMOTE_ONESHOT_TALK);
							_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Doom Lord Kazzak will be pleased. You are to increase the pace of your attacks. Destroy the orcish and dwarven strongholds with all haste.");
							mRazuunPhase = 1;
							ResetTimer(mRazuunTimer, 9000);
						}
						break;
					case 1:
						{
							_unit->Emote(EMOTE_ONESHOT_TALK);
							_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Don't worry about that. I've increased production at the Deathforge. You'll have all the infernals you need to carry out your orders. Don't fail, Jovaan.");
							mRazuunPhase = 2;
							ResetTimer(mRazuunTimer, 15000);
						}
						break;
					case 2:
						{
							_unit->Emote(EMOTE_ONESHOT_QUESTION);
							_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Yes?");
							mRazuunPhase = 3;
							ResetTimer(mRazuunTimer, 8000);
						}
						break;
					case 3:
						{
							_unit->Emote(EMOTE_ONESHOT_QUESTION);
							_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Crate? I didn't send you a crate, Jovaan. Don't you have more important things to worry about? Go see to them!");
							mRazuunPhase = 4;
							ResetTimer(mRazuunTimer, 5000);
						}
						break;
					case 4:
						{
							mRazuunPhase = -1;
							RemoveTimer(mRazuunTimer);
							Despawn(0, 0);
							return;
						}
						break;
				}
			}
			ParentClass::AIUpdate();
		}

		int32	mRazuunTimer;
		int32	mRazuunPhase;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Warbringer Razuun
#define CN_ENSLAVED_NETHERWING_DRAKE	21722

class EnslavedNetherwingDrakeAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(EnslavedNetherwingDrakeAI, MoonScriptCreatureAI);
		EnslavedNetherwingDrakeAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			LocationExtra WayPoint = { _unit->GetPositionX(), _unit->GetPositionY() + 30, _unit->GetPositionZ() + 100, _unit->GetOrientation(), Flag_Fly };
			SetCanMove(false);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_FEIGN_DEATH | UNIT_FLAG_NOT_ATTACKABLE_2);
			AddWaypoint(CreateWaypoint(1, 0, Flag_Fly, WayPoint));
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == 1)
			{
				Despawn(0, 3 * 60 * 1000);
			}
		}
};

void SetupZoneShadowmoonValley(ScriptMgr* mgr)
{
	mgr->register_creature_script(11980, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(21718, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(21719, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(21720, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(22253, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(22274, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(22331, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(23188, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(21717, &InfiltratingDragonmawFortressQAI::Create);
	mgr->register_creature_script(21878, &KneepadsQAI::Create);
	mgr->register_creature_script(21879, &KneepadsQAI::Create);
	mgr->register_creature_script(21864, &KneepadsQAI::Create);
	mgr->register_creature_script(CN_DEATHBRINGER_JOVAAN, &DeathbringerJovaanAI::Create);
	mgr->register_creature_script(CN_WARBRINGER_RAZUUN, &WarbringerRazuunAI::Create);
	mgr->register_creature_script(CN_ENSLAVED_NETHERWING_DRAKE, &EnslavedNetherwingDrakeAI::Create);
	mgr->register_creature_script(19806, &EclipsionSpawn::Create);
	mgr->register_creature_script(22018, &EclipsionSpawn::Create);
}