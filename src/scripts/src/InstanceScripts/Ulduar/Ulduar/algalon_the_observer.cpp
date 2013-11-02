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

#include "StdAfx.h"
#include "Raid_Ulduar.h"
#include "../Common/Base.h" 

static Coords RoomPoints[]=
{
	{ 1646.411499f, -280.270538f, 417.321686f },
	{ 1654.442139f, -296.619995f, 417.321686f },
	{ 1649.935181f, -312.869995f, 417.321991f },
	{ 1635.889160f, -323.114960f, 417.321991f },
	{ 1626.588257f, -334.422952f, 417.321991f },
	{ 1609.273315f, -325.008759f, 417.321991f },
	{ 1613.084351f, -311.113373f, 417.321991f },
	{ 1608.645264f, -300.140015f, 417.321991f },
	{ 1611.737549f, -287.944885f, 417.321991f },
	{ 1622.536509f, -289.462799f, 417.321991f },
	{ 1634.319824f, -276.142670f, 417.321991f },
	{ 1642.059082f, -288.031097f, 417.321991f },
	{ 1654.436279f, -286.942200f, 417.321991f }
};

static Coords BlackHoleSpawns[]=
{
	{ 1640.192749f, -313.252136f, 417.321686f, 2.244802f },
	{ 1621.535767f, -311.449310f, 417.321686f, 0.723486f },
	{ 1625.286743f, -291.989807f, 417.321686f, 5.373048f },
	{ 1643.084351f, -301.061035f, 417.321686f, 3.614546f }
};

static Coords BronzebeardWaypoint[]=
{
	{ 1632.451904f, -173.976532f, 427.262726f, 4.693232f, 0 },
	{ 1631.937988f, -221.072922f, 418.409332f, 4.693232f, 0 }
};

static Coords LivingConstellationWP[]=
{
	{ 1618.260010f, -303.169342f, 420.658508f, 6.241804f },
	{ 1631.825928f, -319.399384f, 421.392365f, 1.560456f },
	{ 1642.386353f, -305.013702f, 421.466583f, 3.218021f }
};

static Coords LivingConstellationSpawn[]=
{
	{ 1678.458862f, -306.932587f, 438.095001f, 3.126851f },
	{ 1588.860718f, -312.406250f, 536.889526f, 6.256645f },
	{ 1633.562012f, -355.855469f, 434.713654f, 1.860765f }
};

static Coords AlgalonEndEvent[]=
{
	{ 1632.140381f, -302.678314f, 417.321106f, 1.604511f }, 
	{ 1632.315308f, -307.865356f, 417.321106f, 1.604511f } 
};

enum ALGALON_DEFINES
{
	// Game Objects
	Doodad_UL_SigilDoor_01						= 194767,
	Doodad_UL_UniverseGlobe_01					= 194148,
	Doodad_UL_UniverseFloor_01					= 194715,
	Doodad_UL_UniverseFloor_02					= 194716,
	Doodad_UL_TrapDoor_03						= 194253,
	Doodad_UL_SigilDoor_03						= 194910,
	UL_GIFT_OF_THE_OBSERVER						= 194821,
	// Creatures
	CN_ALGALON									= 32871,
	CN_BRANN									= 33235,  // used at intro scene
	CN_AZEROTH									= 34246,
	CN_COLLAPSING_STAR							= 32955,
	CN_BLACK_HOLE								= 32953,
	CN_LIVING_CONSTELLATION						= 33052,
	CN_DARK_MATTER								= 33089,
	CN_UNLEASEHED_DARK_MATTER					= 34097,
	// Algalon Spells 
	ALGALON_QUANTUM_STRIKE_10					= 64395,
	ALGALON_QUANTUM_STRIKE_25					= 64592,
	ALGALON_BIG_BANG_10							= 64443, 
	ALGALON_BIG_BANG_25							= 64584,
	ALGALON_BERSEK								= 47008,
	ALGALON_PHASE_PUNCH							= 64412,
	ALGALON_ASCEND_TO_HEAVENS					= 64487,
	// Stars spells
	STAR_EXPLODE								= 64122, // used on stars death
	STAR_SUMMON_BLACK_HOLE						= 62189,
	// phase related spells
	BLACK_HOLE_DAMAGE_AURA						= 62169,
	BLACK_HOLE_PHASE_AURA						= 64417,
	BLACK_HOLE_VISUAL_VOID_ZONE					= 64017,
	// Living Constellation spells
	ARCANE_BARRAGE								= 64599,
	// thanks to Compboy for this 2 ids, start event spells
	ALGALON_CHANNEL								= 64996,
	ALGALON_ARRIVAL								= 64997,
	// achievement killcredit spell
	ALGALON_KILLCREDIT							= 65184,
	// Algalon Sound ids
	UR_ALGALON_SUMMON01							= 15405,      //UR_Algalon_Summon01.wav
	UR_ALGALON_SUMMON02							= 15406,      //UR_Algalon_Summon02.wav
	UR_ALGALON_SUMMON03							= 15407,     //UR_Algalon_Summon03.wav
	UR_ALGALON_AGGRO01							= 15386,      //UR_Algalon_Aggro01.wav
	UR_ALGALON_ADDS01							= 15392,      //UR_Algalon_Adds01.wav
	UR_ALGALON_BHOLE01							= 15391,      //UR_Algalon_BHole01.wav
	UR_ALGALON_SPECIAL01						= 15396,      //UR_Algalon_Special01.wav
	UR_ALGALON_SPACE01							= 15390,      //UR_Algalon_Space01.wav
	UR_ALGALON_BERSERK01                        = 15394,      //UR_Algalon_Berzerk01.wav
	// Branns sound ids
	UR_BRANN_ALGALONSUMMONED01					= 15824,      //UR_Brann_AlgalonSummoned01.wav
	UR_BRANN_ALGALONSUMMONED02					= 15825,      //UR_Brann_AlgalonSummoned02.wav
	// timer macros
	TIMER_STAR_01								= 15000, 
	TIMER_STAR_02								= 40000,
	TIMER_START_DELAY							= 12000,
	TIMER_BIG_BANG								= 90000,
	TIMER_BIG_BANG_CAST							= 8000,
	TIMER_ENRAGE								= 360000,
	TIMER_SUMMON_DARK_MATTER					= 30000,
	TIMER_LIVING_CONSTELLATION_JOIN				= 38000,
};

typedef std::vector<Creature*> EncounterArray;

class AlgalonAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(AlgalonAI, MoonScriptBossAI);
	AlgalonAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddPhaseSpell( 2, AddSpell( ALGALON_QUANTUM_STRIKE_10, Target_Current, 50, 0, 6 ) );
		AddPhaseSpell( 2, AddSpell( ALGALON_PHASE_PUNCH, Target_Current, 99, 0, 12 ) );
		AddPhaseSpell( 3, AddSpell( ALGALON_QUANTUM_STRIKE_10, Target_Current, 50, 0, 6 ) );
		AddPhaseSpell( 3, AddSpell( ALGALON_PHASE_PUNCH, Target_Current, 99, 0, 12 ) );
		mEnrage = AddSpell( ALGALON_BERSEK, Target_Self, 0, 0, 0 ); // 6 minutes enrage

		AddEmote( Event_OnCombatStart, "Your actions are illogical. All possible results for this encounter have been calculated. The pantheon will receive the observer's message regardless outcome.", Text_Yell, UR_ALGALON_AGGRO01 );
	
		SetCanEnterCombat( false );
		SetFlyMode( true );

		mIntro = true;
		mFirstEncounter = true;
		mEndScene = false;
		mScene = 0;
		mTimer = 0;
		pAzeroth = NULL;
		
		_bigBang = false;
		mEnrageTimer = INVALIDATE_TIMER;
		mAddTimer = INVALIDATE_TIMER;
		mTimeoutTimer = INVALIDATE_TIMER;
		mBigBangTimer = INVALIDATE_TIMER;

		RegisterAIUpdateEvent( 1000 );
	};

	void OnCombatStart(Unit* pTarget)
	{
		// additional spell timers
		mAddTimer = AddTimer( TIMER_STAR_01 + TIMER_START_DELAY ); // star timer
		mBigBangTimer = AddTimer( TIMER_BIG_BANG + TIMER_START_DELAY ); //90 seconds + 12 seconds
		mEnrageTimer = AddTimer( TIMER_ENRAGE ); // 6 minutes
		_bigBang = false;

		// add timers and stop him from doing anything
		mTimeoutTimer = AddTimer( TIMER_START_DELAY );
		DelayNextAttack( TIMER_START_DELAY );
		_unit->SetUInt64Value( UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9 );
		
		SetAllowMelee( false );
		SetAllowSpell( false );
		SetAllowTargeting( false );
		SetCanMove( false );
		TriggerCooldownOnAllSpells(); 
	
		ParentClass::OnCombatStart( pTarget );
	};

	

	void AIUpdate()
	{
		if( mIntro )
		{
			++mTimer;
			switch( mTimer )
			{
			case 1:
			case 5:
			case 9:
			case 12:
			case 19:
			case 29:
			case 34:
				IntroScene();
			break;
			};	
		}

		

		if( GetHealthPercent() <= 3 && GetPhase() == 3 )
		{
			// lets set him out of combat
			mEndScene = true;
			SetCanEnterCombat(false);
			_unit->GetAIInterface()->HandleEvent( EVENT_LEAVECOMBAT, _unit, 0 );
			
			AddWaypoint(CreateWaypoint( 1, 0, Flag_Run, AlgalonEndEvent[1] ));
			ForceWaypointMove( 1 );
		};

		if( GetHealthPercent() <= 20 && GetPhase() == 2 )
			PhaseThree();

		if( IsTimerFinished( mEnrageTimer ) )
		{
			CastSpellNowNoScheduling( mEnrage );
			Emote( "You are... out of time.", Text_Yell, UR_ALGALON_BERSERK01 );
			RemoveTimer( mEnrageTimer );
		};

		if( IsTimerFinished( mTimeoutTimer ) )
			StartHandler();

		if( IsTimerFinished( mAddTimer ) )
			SummonStars();
		
		if( IsTimerFinished( mBigBangTimer ) )
			BigBang();

		ParentClass::AIUpdate();
	};

	void OnCombatStop(Unit* pTarget)
	{
		DespawnAllEncounterCreatures();

		if( pPlanet != NULL && pPlanet->GetState() == 0)
			pPlanet->SetState(1);

		if( pFloor1 != NULL && pFloor1->GetState() == 1)
			pFloor1->SetState(0);
		
		if( pFloor2 != NULL && pFloor2->GetState() == 0) 
			pFloor2->SetState(1);

		if( pTrapDoor != NULL && pTrapDoor->GetState() == 0 )
			pTrapDoor->SetState(1);

		if( pLimitDoor != NULL && pFloor2->GetState() == 1 )		
			pLimitDoor->SetState(0);

		ParentClass::OnCombatStop( pTarget );

		if( !mEndScene )
		{
			/* to prevent possible bugs */
			mFirstEncounter = false;
			RemoveAIUpdateEvent();
			_unit->SetUInt64Value( UNIT_FIELD_FLAGS, 0 );
		}
	};

	void OnReachWP(uint32 iWaypointId, bool bForwards )
	{
		if ( iWaypointId == 1 )
		{
			/*for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{
				(*PlayerIter)->CastSpell( (*PlayerIter), ALGALON_KILLCREDIT, true );
			}*/
			_unit->GetMapMgr()->GetInterface()->SpawnGameObject( UL_GIFT_OF_THE_OBSERVER, AlgalonEndEvent[0].mX, AlgalonEndEvent[0].mY, AlgalonEndEvent[0].mZ, AlgalonEndEvent[0].mO, false, 0, 0, 1 ); 
			//RegisterAIUpdate( 1000 );
			//_unit->CombatStatus.TryToClearAttackTargets();
		};
	};

	void IntroScene()
	{
		if( mScene != 7 )
		{
			switch( mScene )
			{
			case 0:
				_unit->CastSpell( _unit, ALGALON_ARRIVAL, true );
				break;
			case 1:
				Emote( "Translocation complete. Commencing planetary analysis of Azeroth.", Text_Say, UR_ALGALON_SUMMON01 );
				break;
			case 2:
				_unit->Emote( EMOTE_ONESHOT_SPELLCAST_OMNI );
				SpawnCreature( CN_AZEROTH, 1631.762817f, -293.814301f, 417.321106f, 1.573153f );
				break;
			case 3:
				Emote( "Stand back mortals. I am not here to fight you.", Text_Say, UR_ALGALON_SUMMON02 );
				SetFlyMode( false );
				pAzeroth = static_cast<Creature*>( ForceCreatureFind(CN_AZEROTH, 1631.762817f, -293.814301f, 417.321106f ) );
				if( pAzeroth != NULL )
					SetTargetToChannel( pAzeroth, ALGALON_CHANNEL );
				break;
			case 4:
				Emote( "It is in the universe's best interest to re-originate this planet, should my analysis find systemic corruption. Do not interfere.", Text_Say, UR_ALGALON_SUMMON03 );
				break;
			case 5:
				SetTargetToChannel( NULL, 0 );
				pAzeroth->Despawn(0, 0);
				break;
			case 6:
				SetCanEnterCombat( true );
				mIntro = false;
				RemoveAIUpdateEvent();
				break;
			}
			++mScene;
		}
	};

	void StartHandler()
	{
		if( mFirstEncounter )
		{
			Emote( "See your world through my eyes: A universe so vast as to be immeasurable - incomprehensible even to your greatest minds.", Text_Yell, UR_ALGALON_SPACE01 );
			mFirstEncounter = false;
		};

		_unit->SetUInt64Value( UNIT_FIELD_FLAGS, 0 );

		SetAllowMelee( true );
		SetAllowSpell( true );
		SetAllowTargeting( true );
		SetCanMove( true );
		TriggerCooldownOnAllSpells();

		pPlanet = GetNearestGameObject( Doodad_UL_UniverseGlobe_01 );
		if( pPlanet != NULL && pPlanet->GetState() == 1 )
			pPlanet->SetState( 0 );

		pFloor1 = GetNearestGameObject( Doodad_UL_UniverseFloor_01 );
		if( pFloor1 != NULL && pFloor1->GetState() == 0 )
			pFloor1->SetState( 1 );

		pFloor2 = GetNearestGameObject( Doodad_UL_UniverseFloor_02 );
		if( pFloor2 != NULL && pFloor2->GetState() == 1 )
			pFloor2->SetState( 0 );

		pTrapDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords( 1632.324585f, -246.840393f, 417.323151f, Doodad_UL_TrapDoor_03 );
		if( pTrapDoor != NULL && pFloor2->GetState() == 1 )		
			pTrapDoor->SetState( 0 );

		pLimitDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords( 1632.324585f, -246.840393f, 417.323151f, Doodad_UL_SigilDoor_03 );
		if( pLimitDoor != NULL && pFloor2->GetState() == 0 )		
			pLimitDoor->SetState( 1 );

		for( int i=0; i < 3; i++ )
		{
			SpawnCreature( CN_LIVING_CONSTELLATION, LivingConstellationSpawn[i].mX, LivingConstellationSpawn[i].mY, LivingConstellationSpawn[i].mZ, LivingConstellationSpawn[i].mO, 1 );
		};
		
		SetPhase( 2 );
		RemoveTimer( mTimeoutTimer );
	};

	void SummonStars()
	{
		_unit->SendChatMessage(CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Algalon the Observer begins to Summon Collapsing Stars!" );
		Emote( "The stars come to my aid.", Text_Yell, UR_ALGALON_ADDS01 );

		uint32 mRandom = 0;
		for( int i = 0; i < 4; i++ )
		{
			mRandom = RandomUInt( 11 );
			SpawnCreature( CN_COLLAPSING_STAR, RoomPoints[mRandom].mX, RoomPoints[mRandom].mY, RoomPoints[mRandom].mZ, 0, true, 1 );
		};			
		ResetTimer( mAddTimer, TIMER_STAR_02 );
	};

	void BigBang()
	{
		if( !_bigBang )
		{
			_unit->CastSpell( _unit, dbcSpell.LookupEntryForced(ALGALON_BIG_BANG_10), false );
			_unit->SendChatMessage(CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Algalon the Observer begins to cast Big Bang!" );
			Emote( "Witness the fury of cosmos!", Text_Yell, UR_ALGALON_SPECIAL01 );
			_bigBang = true;
			ResetTimer( mBigBangTimer, TIMER_BIG_BANG_CAST ); //8 seconds cast time
		}
		else
		{
			bool mPhasedPlayer = false;

			for( set<Player*>::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter ) 
			{
				if( (*PlayerIter)->GetPhase() == 1 )
					mPhasedPlayer = true;
				else
					(*PlayerIter)->RemoveAura( BLACK_HOLE_PHASE_AURA );
			}

			if( mPhasedPlayer == false )
			_unit->CastSpell( _unit, ALGALON_ASCEND_TO_HEAVENS, false ); // wipe raid
			_bigBang = false;
			ResetTimer( mBigBangTimer, TIMER_BIG_BANG );
		};
	};

	void PhaseThree()
	{
		DespawnAllEncounterCreatures();
		for( int i = 0; i < 4; ++i )
		{
			SpawnCreature( CN_BLACK_HOLE, BlackHoleSpawns[i].mX,  BlackHoleSpawns[i].mY,  BlackHoleSpawns[i].mZ,  BlackHoleSpawns[i].mO, false );
		};
		Emote("Beware!", Text_Yell, UR_ALGALON_BHOLE01);
		RemoveTimer( mAddTimer );
		RemoveTimer( mBigBangTimer );
		SetPhase( 3 );
	};

	void AddEncounterCreature( Creature* pCreature )
	{
		mEncounterArray.push_back( pCreature );
	};

	void DespawnAllEncounterCreatures()
	{
		for( vector<Creature*>::iterator CreatureIter = mEncounterArray.begin(); CreatureIter != mEncounterArray.end(); ++CreatureIter )
		{
			if( (*CreatureIter) != NULL )
				(*CreatureIter)->Despawn( 0, 0);
		};
		mEncounterArray.clear();
	};

	void Destroy()
	{
		delete this;
	};

	// Vars:
	// Game Objects
	GameObject*		pPlanet; 
	GameObject*		pFloor1;
	GameObject*		pFloor2;
	GameObject*		pTrapDoor;
	GameObject*		pLimitDoor;

	// Spell Desc
	SpellDesc*		mEnrage;

	// Creature pointer
	Creature*		pAzeroth;

	// boolean
	bool			mIntro;
	bool			mFirstEncounter;
	bool			mEndScene;
	bool			_bigBang;

	// counters
	uint32			mScene;
	uint32			mTimer;

	// timers
	int32			mEnrageTimer;
	int32			mAddTimer;
	int32			mTimeoutTimer;
	int32			mBigBangTimer;

private:
	EncounterArray	mEncounterArray;
};

class AlgalonDoorGO : public GameObjectAIScript
{
public:
	AlgalonDoorGO(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject* GO) { return new AlgalonDoorGO(GO); }

	void OnActivate(Player* pPlayer)
	{
		RegisterAIUpdateEvent( 45000 ); 
		_gameobject->GetMapMgr()->GetInterface()->SpawnCreature( CN_BRANN, BronzebeardWaypoint[0].mX, BronzebeardWaypoint[0].mY, BronzebeardWaypoint[0].mZ, BronzebeardWaypoint[0].mO, true, true, NULL, NULL, 1);
	};
	
	void AIUpdate()
	{
		_gameobject->GetMapMgr()->GetInterface()->SpawnCreature( CN_ALGALON, 1631.954712f, -303.857910f, 417.321167f, 1.482785f, true, true, NULL, NULL, 1);
		_gameobject->Despawn( 1000, 0 );
	};

	void Destroy()
	{
		delete this;
	};
};

class AzerothAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AzerothAI);
	AzerothAI(Creature* pCreature) : CreatureAIScript(pCreature) {};

	void OnLoad()
	{
		_unit->SetUInt64Value( UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE );
		_unit->GetAIInterface()->SetAllowedToEnterCombat( false );
	};

	void Destroy()
	{
		delete this;
	};
};

class CollapsingStarAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(CollapsingStarAI, MoonScriptCreatureAI);
	CollapsingStarAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature){}

	void OnLoad()
	{
		RegisterAIUpdateEvent( 1000 );
		_unit->GetAIInterface()->SetAllowedToEnterCombat( false );
		SetAllowTargeting( false );
		uint32 mRandom = RandomUInt(  11 );
		MoveTo(RoomPoints[mRandom].mX, RoomPoints[mRandom].mY, RoomPoints[mRandom].mZ, false);
		mMoveCounter = 0;

		AlgalonAI* mAlgalon = NULL;
		Creature* pAlgalon = static_cast<Creature*>(ForceCreatureFind( CN_ALGALON, 1632.250000f, -307.548004f, 416.264008f));
		if ( pAlgalon != NULL && pAlgalon->GetScript() != NULL )
		{
				mAlgalon = (AlgalonAI*)(pAlgalon->GetScript());
				mAlgalon->AddEncounterCreature( _unit );
		}
		pAlgalon = NULL;
		mAlgalon = NULL;
	};

	void AIUpdate()
	{
		++mMoveCounter;
		uint32 mHealth = _unit->GetUInt32Value(UNIT_FIELD_HEALTH);
		_unit->SetUInt32Value( UNIT_FIELD_HEALTH, mHealth - ( mHealth / 100 ) ); // loose 1 pct every sec
		if(mMoveCounter == 5)
		{
			uint32 mRandom = RandomUInt( 11 );
			MoveTo(RoomPoints[mRandom].mX, RoomPoints[mRandom].mY, RoomPoints[mRandom].mZ, false);
			mMoveCounter = 0;
		};

		ParentClass::AIUpdate();
	};

	void OnDied(Unit* pUnit)
	{
		_unit->CastSpell(_unit, STAR_EXPLODE, true );
		_unit->CastSpell(_unit, STAR_SUMMON_BLACK_HOLE, true );

		CancelAllSpells();
		CancelAllTimers();
		RemoveAllAuras();

		Despawn( 1000, 0 );
	};

	void Destroy()
	{
		delete this;
	};

private:
	uint32	mMoveCounter;
};

class BlackHoleAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(BlackHoleAI, MoonScriptCreatureAI);
	BlackHoleAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature){}
	
	void OnLoad()
	{
		_unit->SetUInt64Value( UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE );
		_unit->GetAIInterface()->SetAllowedToEnterCombat( false );
		mVoidZone = false;

		Creature* pAlgalon = static_cast<Creature*>(ForceCreatureFind( CN_ALGALON, 1632.250000f, -307.548004f, 416.264008f));
		AlgalonAI* mAlgalon = NULL;
		if ( pAlgalon != NULL && pAlgalon->GetScript() != NULL )
		{
				mAlgalon = (AlgalonAI*)(pAlgalon->GetScript());
				mAlgalon->AddEncounterCreature( _unit );
				if( mAlgalon->GetPhase() == 3 )
					mPhaseTwo = true;
		}
		pAlgalon = NULL;
		mAlgalon = NULL;

		RegisterAIUpdateEvent( 100 );
	};

	void AIUpdate()
	{
		Unit* pPlayer = GetNearestPlayer();
		if( pPlayer != NULL && pPlayer->isAlive() == true && pPlayer->GetDistance2dSq(static_cast<Object*>(_unit)) <= 3.5f )
		{
			if( !pPlayer->HasAura( BLACK_HOLE_PHASE_AURA ) )
			{
				_unit->CastSpell( pPlayer, BLACK_HOLE_DAMAGE_AURA, true);
				pPlayer->CastSpell( pPlayer, BLACK_HOLE_PHASE_AURA, true);
			}
		};
		
		Creature* pLivingConstellation = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), CN_LIVING_CONSTELLATION);
		if( pLivingConstellation != NULL && pLivingConstellation->GetDistance2dSq(static_cast<Object*>(_unit)) <= 3.5f )
		{
			pLivingConstellation->Despawn( 0, 0 );
			Despawn();
		};

		if( mPhaseTwo )
			mSummonTimer = AddTimer( TIMER_SUMMON_DARK_MATTER );
		
		if( IsTimerFinished( mSummonTimer ) )
		{
			SpawnCreature( CN_UNLEASEHED_DARK_MATTER );
			ResetTimer( mSummonTimer, TIMER_SUMMON_DARK_MATTER );
		}

		if( !mVoidZone )
			ApplyAura( BLACK_HOLE_VISUAL_VOID_ZONE );
	};

	void Destroy()
	{
		delete this;
	};

private:
	bool		mVoidZone;
	bool		mPhaseTwo;

	int32		mSummonTimer;
};

class LivingConstellationAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(LivingConstellationAI, MoonScriptBossAI);
	LivingConstellationAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddPhaseSpell( 2, AddSpell( ARCANE_BARRAGE, Target_RandomPlayer, 100, 2, 5, 0, 60 ) );

		SetFlyMode( true );
		SetCanEnterCombat( false );
		SetAllowMelee( false );
		SetAllowSpell( false );
		SetAllowTargeting( false);
		SetCanMove( false );
	};

	void OnLoad()
	{
		Creature* pAlgalon = static_cast<Creature*>(ForceCreatureFind( CN_ALGALON, 1632.250000f, -307.548004f, 416.264008f));
		AlgalonAI* mAlgalon = NULL;
		if ( pAlgalon != NULL && pAlgalon->GetScript() != NULL )
		{
				mAlgalon = (AlgalonAI*)(pAlgalon->GetScript());
				mAlgalon->AddEncounterCreature( _unit );
		}
		pAlgalon = NULL;
		mAlgalon = NULL;

		SetPhase( 1 );
		mJoinTimer = AddTimer( TIMER_LIVING_CONSTELLATION_JOIN );
		RegisterAIUpdateEvent( 1000 );
	};

	void AIUpdate()
	{
		if( GetPhase() == 1 )
		{
			if( IsTimerFinished( mJoinTimer ) )
			{
				SpawnCreature( CN_LIVING_CONSTELLATION );
				RemoveTimer( mJoinTimer );

				SetCanEnterCombat( true );
				SetAllowSpell( true );
				SetAllowTargeting( true );
				SetCanMove( true );
				SetPhase( 2 );
				
				uint32 mRandom = RandomUInt( 2 );
				AddWaypoint( CreateWaypoint( 1, 0, Flag_Fly, LivingConstellationWP[mRandom] ) );
				ForceWaypointMove( 1 );		
			}
		};

		ParentClass::AIUpdate();
	};

	void OnDied(Unit* pKiller)
	{
		Despawn( 1000, 0 );
	};

	void OnReachWP(uint32 iWaypoinyId, bool bForwards)
	{
		if( !IsInCombat() )
			AggroNearestPlayer(1);
	};

	void Destroy()
	{
		delete this;
	};

	int32		mJoinTimer;
};

class BrannBronzebeardAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(BrannBronzebeardAI, MoonScriptCreatureAI);
	BrannBronzebeardAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature){}
	
	void OnLoad()
	{
		mScene = 0;
		RegisterAIUpdateEvent( 8000 );
	};

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId == 1)
		{
			Emote( "We did it lads! We got here before Algalon's arrival! Maybe we can rig the systems to interfere with his analysis.", Text_Yell, UR_BRANN_ALGALONSUMMONED01);
			_unit->Emote(EMOTE_ONESHOT_TALK);
			RegisterAIUpdateEvent(8000);
		}
	};

	void AIUpdate()
	{
		if(mScene == 0)
		{
			for( int i=0; i < 2; i++ )
			{
				AddWaypoint(CreateWaypoint( i, 0, Flag_Walk, BronzebeardWaypoint[i]));
			}
			++mScene;
			ForceWaypointMove(1);
			RemoveAIUpdateEvent();
		}
		else if( mScene == 1)
		{
			Emote( "I'll head back to the Archivum and see if I can jam his signal. I might be able to buy us some time while you take care of him.", Text_Yell, UR_BRANN_ALGALONSUMMONED02);
			_unit->Emote(EMOTE_ONESHOT_TALK);
			RemoveAIUpdateEvent();
			Despawn();
		}
	};

	void Destroy()
	{
		delete this;
	};

private:
	int32 mScene;
};

class UnleashedDarkMatterAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(UnleashedDarkMatterAI, MoonScriptCreatureAI);
	UnleashedDarkMatterAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature){}

	void OnLoad()
	{
		Creature* pAlgalon = static_cast<Creature*>(ForceCreatureFind( CN_ALGALON, 1632.250000f, -307.548004f, 416.264008f));
		AlgalonAI* mAlgalon = NULL;
		if ( pAlgalon != NULL && pAlgalon->GetScript() != NULL )
		{
				mAlgalon = (AlgalonAI*)(pAlgalon->GetScript());
				mAlgalon->AddEncounterCreature( _unit );
		}
		pAlgalon = NULL;
		mAlgalon = NULL;
	};
};

class PhasePunchAI  : public SpellScript
{
public:
	ADD_SPELL_FACTORY_FUNCTION(PhasePunchAI);
	PhasePunchAI(Spell* spellinstance) : SpellScript(spellinstance) {};

	void OnCast() 
	{
		if( _spell->GetUnitTarget() && _spell->GetUnitTarget()->IsPlayer())
		{
			Player* pVictim = static_cast<Player*>(_spell->GetUnitTarget());
			if ( pVictim->GetAuraStackCount( ALGALON_PHASE_PUNCH ) == 5 )
			{
					pVictim->RemoveAllAuraById( ALGALON_PHASE_PUNCH );
					Aura* pAura = new Aura( dbcSpell.LookupEntryForced(BLACK_HOLE_PHASE_AURA), 10000, pVictim, pVictim, true);
					if( pAura != NULL )	
						pVictim->AddAura(pAura, NULL);
			};
		}
	};
};

void SetupAlgalon(ScriptMgr * mgr)
{
	mgr->register_creature_script( CN_ALGALON, &AlgalonAI::Create);
	mgr->register_creature_script( CN_AZEROTH, &AzerothAI::Create);
	mgr->register_creature_script( CN_COLLAPSING_STAR, &CollapsingStarAI::Create);
	mgr->register_creature_script( CN_BLACK_HOLE, &BlackHoleAI::Create);
	mgr->register_creature_script( CN_BRANN, &BrannBronzebeardAI::Create);
	mgr->register_creature_script( CN_LIVING_CONSTELLATION, &LivingConstellationAI::Create);
	mgr->register_creature_script( CN_UNLEASEHED_DARK_MATTER, &UnleashedDarkMatterAI::Create );

	mgr->register_gameobject_script( Doodad_UL_SigilDoor_01, &AlgalonDoorGO::Create);

	//mgr->register_spell_script( ALGALON_PHASE_PUNCH, &PhasePunchAI::Create);
};