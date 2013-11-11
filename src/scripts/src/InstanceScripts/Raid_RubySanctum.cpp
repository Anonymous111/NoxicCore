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

#include "Setup.h"

#define MAP_RS 724
#define RS_WORLD_STATE 5051
#define RS_TWILIGHT_CORPO 5050
#define RS_PHYSIC_CORPO 5049

enum rs_bosses
{
	// baltharus fight
	CN_BALTHARUS		= 39751,
	CN_BALTHARUS_CLONE	= 39899,
	CN_XERESTRASZA		= 40429,
	CN_BALTHARUS_DOORS	= 203005,
	CN_BALTHARUS_CHANNEL = 203002,

	// Zarithrian fight
	CN_ZARITHRIAN		= 39746,
	CN_ZARITHRIAN_DOORS = 203006,
	CN_FLAMECALLER		= 39814,

	// Saviana fight
	CN_SAVIANA			= 39747,

	// Halion Fight
	CN_HALION			= 39863,
	CN_HALION_TWILIGHT	= 40142,
	CN_HALION_CONTROLLER = 40146,
	CN_HALION_DOORS		= 203007,
	CN_PHYSICAL_REALM	= 203012,
};

enum rs_spells
{
	// Baltharus
	SPELL_FIRE_CHANNEL		= 76221, // this one is bad
	SPELL_BLADE_TEMPEST		= 75125,
	SPELL_REPELLING_WAVE	= 74509,
	SPELL_ENERVATING_BRAND	= 74502,
	SPELL_SIPHONED_MIGHT	= 74507,
	SPELL_SUMMON_CLONE		= 74511,

	// zarithrian
	SPELL_CLEAVE_ARMOR		= 74367,
	SPELL_INTIMIDATING_ROAR	= 74384,
	//SPELL_SUMMON_FLAMECALLER = 74398, -- not used as spell as we need different coords for each one

	// saviana
	SPELL_FLAME_BREATH		= 74403,
	SPELL_ENRAGE			= 78722,
	SPELL_CONFRAGLATION		= 74456,

	// halion
	// fire cloud is missing for now :/
	// spells which are different in 10 / 25 man are defined right above the Halion script
	SPELL_FIRE_PILLAR		= 76006, // encounter spell
	SPELL_FIERY_EXPLOSION	= 76010, // encounter spell
	//SPELL_FLAME_BREATH	= 74525, -- defined above script
	SPELL_TWILIGHT_PRECISION = 78243,
	SPELL_METEOR_STRIKE		= 75877,
	SPELL_FIERY_COMBUSTION	= 74562,
	SPELL_DUSK_SHROUD		= 75476,
	SPELL_CORPOREALITY		= 74826,
	SPELL_TWILIGHT_PHASING	= 74808,
};

enum rs_data
{
	RS_BALTHARUS,
	RS_ZARITHRIAN,
	RS_SAVIANA,
	RS_HALION,

	RS_DATA_END
};

enum halion_phases
{
	PHASE_PHYSICAL_REALM = 1,
	PHASE_TWILIGHT_REALM = 2,
	PHASE_BOTH_REALMS	 = 3
};

#define BALTHARUS_MAX_HP	Man25Int(3486000, 11156000)
#define ZARITHRIAN_MAX_HP	Man25Int(4141000, 14098000)
#define SAVIANA_MAX_HP		Man25Int(4183000, 13945000)
#define HALION_MAX_HP		Man25Int( HeroicInt(11156000,15339900), HeroicInt(43500000,58600000) )
#define FLAMECALLER_MAX_HP	Man25Int(202215, 741455)

class RubySanctumScript : public MoonInstanceScript
{
public:
	MOONSCRIPT_INSTANCE_FACTORY_FUNCTION( RubySanctumScript, MoonInstanceScript );
	RubySanctumScript( MapMgr* pMapMgr ) : MoonInstanceScript( pMapMgr )
	{
		int i;
		for(i = 0; i < RS_DATA_END; i++)
			boss_killed[i] = 0;

		for(i = 0; i < PHASE_BOTH_REALMS; i++)
			halion_corporality[i] = 50;

		halion_hp = 0;
    };

	uint32 halion_hp;

	void SetInstanceData( uint32 pType, uint32 pIndex, uint32 pData )
	{
		boss_killed[pIndex] = pData;

		// open flames around Zarithrian
		if( (boss_killed[RS_BALTHARUS] == 1) && (boss_killed[RS_SAVIANA] == 1) )
		{
			ChangeDoorState( CN_ZARITHRIAN_DOORS, State_Active );
		}

		// open flames around halion
		if( boss_killed[RS_ZARITHRIAN] == 1 )
		{
			ChangeDoorState( CN_HALION_DOORS, State_Active );
			// halion spawns after ~ 10 seconds
			RegisterScriptUpdateEvent();
			halion_spawn_timer = AddTimer(10000);
		}
	};

	void UpdateEvent()
	{
		if( IsTimerFinished(halion_spawn_timer) )
			SpawnHalion();

		if( IsTimerFinished(halion_hp_check_timer) )
			HalionHPCheck();

		ParentClass::UpdateEvent();
	};

	uint32 GetInstanceData( uint32 pType, uint32 pIndex )
	{
		return boss_killed[pIndex];
	};

	void OnCreatureDeath( Creature * pVictim, Unit * pKiller )
	{
		switch( pVictim->GetEntry() )
		{
			case CN_BALTHARUS:
			{
				SetInstanceData(0, RS_BALTHARUS, 1);

				// there may be up to 3 clones
				for( int i = 0; i < 3; i++ )
				{
					Creature * cr = FindClosestCreatureOnMap(CN_BALTHARUS_CLONE, pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ());
					if( cr )
						cr->Die(pVictim, 0, 0);
				}
			};
			break;
			case CN_ZARITHRIAN:
			{
				SetInstanceData(0, RS_ZARITHRIAN, 1);
			};
			break;
			case CN_SAVIANA:
			{
				SetInstanceData(0, RS_SAVIANA, 1);
			};
			break;
			case CN_HALION:
			case CN_HALION_TWILIGHT:
			{
				Player * pPlayer;
				for( PlayerStorageMap::iterator itr = mInstance->m_PlayerStorage.begin(); itr !=  mInstance->m_PlayerStorage.end(); ++itr )
				{
					pPlayer = itr->second;
					pPlayer->RemoveAura(74807);
				}

				if( pVictim->GetEntry() == CN_HALION )
					FindClosestCreatureOnMap(CN_HALION_TWILIGHT, pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ())->Die( pVictim, 0, 0 );
				else
					FindClosestCreatureOnMap(CN_HALION, pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ())->Die( pVictim, 0, 0 );
			};
			break;
			case CN_FLAMECALLER:
			{
				//pVictim->Despawn(500, 0);
			};
			break;
		}
	};

	// update HP due to differences between 10 / 25 man (just bosses)
	void OnCreaturePushToWorld( Creature * pCreature )
	{
		switch( pCreature->GetEntry() )
		{
			case CN_BALTHARUS:
			{
				pCreature->SetMaxHealth( BALTHARUS_MAX_HP );
				pCreature->SetHealth( BALTHARUS_MAX_HP );
			} break;
			case CN_BALTHARUS_CLONE:
			{
				pCreature->SetMaxHealth( BALTHARUS_MAX_HP );
			} break;
			case CN_ZARITHRIAN:
			{
				pCreature->SetMaxHealth( ZARITHRIAN_MAX_HP );
				pCreature->SetHealth( ZARITHRIAN_MAX_HP );
			} break;
			case CN_SAVIANA:
			{
				pCreature->SetMaxHealth( SAVIANA_MAX_HP );
				pCreature->SetHealth( SAVIANA_MAX_HP );
			} break;
			case CN_HALION:
			{
				pCreature->SetMaxHealth( HALION_MAX_HP );
				pCreature->SetHealth( HALION_MAX_HP );
			} break;
			case CN_HALION_TWILIGHT:
			{
				pCreature->SetMaxHealth( HALION_MAX_HP );
				pCreature->SetHealth( halion_hp );
			} break;
			case CN_FLAMECALLER:
			{
				pCreature->SetMaxHealth( FLAMECALLER_MAX_HP );
				pCreature->SetHealth( FLAMECALLER_MAX_HP );
			} break;

		}
	};

	void ChangeDoorState(uint32 entry, GameObjectState pState)
	{
		AddGameObjectStateByEntry(entry, pState, true);
	};

	void SpawnHalion()
	{
		RemoveTimer(halion_spawn_timer);

		// halion controller
		SpawnCreature(CN_HALION_CONTROLLER, 3156.83f, 535.477f, 72.88f, 0.0f);
	};

	void InitHalionHPCheck()
	{
		halion_hp_check_timer = AddTimer(10000);

		AddWorldState(RS_WORLD_STATE, 50);
		AddWorldState(RS_TWILIGHT_CORPO, 50);
		AddWorldState(RS_PHYSIC_CORPO, 50);

		Player * pPlayer;
		for( PlayerStorageMap::iterator itr = mInstance->m_PlayerStorage.begin(); itr !=  mInstance->m_PlayerStorage.end(); ++itr )
		{
			pPlayer = itr->second;

			if( pPlayer->GetSession() )
				SendWorldStates(pPlayer);
		}
	};

	void HalionHPCheck()
	{
		ResetTimer(halion_hp_check_timer, 10000);

		Creature * halion_phys = FindClosestCreatureOnMap(CN_HALION, 3156.83f, 535.477f, 72.88f);
		Creature * halion_twil = FindClosestCreatureOnMap(CN_HALION_TWILIGHT, 3156.83f, 535.477f, 72.88f);

		if( halion_phys && halion_twil )
		{
			uint32 phys_hp = halion_phys->GetHealth();
			uint32 twil_hp = halion_twil->GetHealth();

			if( phys_hp > twil_hp )
			{
				uint32 diff = phys_hp - twil_hp;

				UpdateCorporality(PHASE_TWILIGHT_REALM, false, diff);
				UpdateCorporality(PHASE_PHYSICAL_REALM, true, diff);
			}
			else if( phys_hp < twil_hp )
			{
				uint32 diff = twil_hp - phys_hp;

				UpdateCorporality(PHASE_TWILIGHT_REALM, true, diff);
				UpdateCorporality(PHASE_PHYSICAL_REALM, false, diff);
			}
		}
	};

	uint32 GetCorporealitySpell(uint32 realm)
	{
		uint32 corp_level = halion_corporality[realm];
		uint32 spellid;

		if( corp_level == 0 )
			spellid = 74836;
		else if( corp_level == 10 )
			spellid = 74835;
		else if( corp_level == 20 )
			spellid = 74834;
		else if( corp_level == 30 )
			spellid = 74833;
		else if( corp_level == 40 )
			spellid = 74832;
		else if( corp_level == 50 )
			spellid = SPELL_CORPOREALITY;
		else if( corp_level == 60 )
			spellid = 74827;
		else if( corp_level == 70 )
			spellid = 74828;
		else if( corp_level == 80 )
			spellid = 74829;
		else if( corp_level == 90 )
			spellid = 74830;
		else if( corp_level == 100 )
			spellid = 74831;

		return spellid;
	};

	void UpdateCorporality(uint32 realm, bool increase, uint32 hp_diff)
	{
		uint32 corp_level;

		if( hp_diff < 50000 )
			corp_level = 50;
		else if( hp_diff < 100000 )
			corp_level = (increase ? 60 : 40);
		else if( hp_diff < 200000 )
			corp_level = (increase ? 70 : 30);
		else if( hp_diff < 300000 )
			corp_level = (increase ? 80 : 20);
		else if( hp_diff < 400000 )
			corp_level = (increase ? 90 : 10);
		else
			corp_level = (increase ? 100 : 0);

		uint32 orig = halion_corporality[realm];

		if( orig == corp_level )
			return;

		// add new corporality
		int32 corpo = corp_level;

		if( !increase && corpo < 50 )
		{
			Creature * cr1 = FindClosestCreatureOnMap(CN_HALION, 3156.83f, 535.477f, 72.88f);
			Creature * cr2 = FindClosestCreatureOnMap(CN_HALION_TWILIGHT, 3156.83f, 535.477f, 72.88f);

			if( realm == PHASE_PHYSICAL_REALM )
			{
				cr1->SendChatMessage( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Your efforts force Halion further out of the twilight realm!" );
				//cr2->SendChatMessage( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Your efforts force Halion further out of the twilight realm!" );
			}
			else
			{
				//cr1->SendChatMessage( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Your efforts force Halion further out of the physical realm!" );
				cr2->SendChatMessage( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, "Your efforts force Halion further out of the physical realm!" );
			}
		}

		if( realm == PHASE_PHYSICAL_REALM )
		{
			SetWorldState(RS_PHYSIC_CORPO, corpo);
		}
		else
		{
			SetWorldState(RS_TWILIGHT_CORPO, corpo);
		}

		halion_corporality[realm] = corpo;
	};

	void SetSelection(Creature * cr)
	{
		Player * pPlayer;
		for( PlayerStorageMap::iterator itr = mInstance->m_PlayerStorage.begin(); itr !=  mInstance->m_PlayerStorage.end(); ++itr )
		{
			pPlayer = itr->second;
			pPlayer->smsg_AttackStop( cr->GetGUID() );
			if( pPlayer->GetCurrentSpell()->m_targets.m_unitTarget == cr->GetGUID() )
				pPlayer->GetCurrentSpell()->cancel();

			pPlayer->SetSelection( 0 );
			pPlayer->SetTargetGUID( 0 );
		}
	};

private:
	uint32 boss_killed[RS_DATA_END];
	int32 halion_spawn_timer;
	int32 halion_hp_check_timer;
	uint32 halion_corporality[3];
};

class BaltharusAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(BaltharusAI, MoonScriptBossAI);
	BaltharusAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell( SPELL_BLADE_TEMPEST, Target_Self, 50, 0, 12 );
		AddSpell( SPELL_ENERVATING_BRAND, Target_Self, 40, 0, 14);
		AddSpell( SPELL_SIPHONED_MIGHT, Target_Self, 40, 0, 20);

		AddEmote(Event_OnTargetDied, "Baltharus leaves no survivors!", Text_Yell, 17521);
		AddEmote(Event_OnTargetDied, "This world has enough heroes.", Text_Yell, 17522);
		AddEmote(Event_OnCombatStart, "Ah, the entertainment has arrived.", Text_Yell, 17520);

		cloned = 0;
    };

	void OnLoad()
	{
		RegisterAIUpdateEvent(mAIUpdateFrequency);
		speech_timer = AddTimer(11000);
	};

	void OnCombatStart(Unit* pTarget)
	{
		// stop channeling
		GameObject * flamedoors = GetNearestGameObject( CN_BALTHARUS_DOORS );
		if(flamedoors != NULL)
			flamedoors->SetState( State_Active );

		SetTargetToChannel( NULL, 0 );

		ParentClass::OnCombatStart(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		// start channeling
		GameObject * flamedoors = GetNearestGameObject( CN_BALTHARUS_DOORS );
		if(flamedoors != NULL)
			flamedoors->SetState( State_Inactive );

		SetTargetToChannel( GetNearestGameObject( CN_BALTHARUS_CHANNEL ), SPELL_FIRE_CHANNEL );

		ParentClass::OnCombatStop(pTarget);
	};

	void AIUpdate()
	{
		if( IsInCombat() )
		{
			// cloning
			uint32 hp = GetHealthPercent();
			// at 75% do only on heroic
			if( hp <= 75 && cloned == 0 && IsHeroic() )
			{
				MakeClone(GetHealth());
			}
			// at 50% both version
			else if( hp <= 50 && ( ( cloned == 0 ) || ( IsHeroic() && cloned == 1 ) )  )
			{
				MakeClone(GetHealth());
			}
			// at 25% only on heroic
			else if( GetHealthPercent() <= 25 && cloned == 2 && IsHeroic() )
			{
				MakeClone(GetHealth());
			}
		}
		else
		{
			if( GetTargetToChannel() == NULL )
				SetTargetToChannel(GetNearestGameObject( CN_BALTHARUS_CHANNEL ), SPELL_FIRE_CHANNEL);
		}

		if( IsTimerFinished(speech_timer) )
			EncounterTalk();

		ParentClass::AIUpdate();
	};

	void OnDied(Unit* pKiller)
	{
		Emote("I... Didn't see that coming...", Text_Yell, 17523);

		ParentClass::OnDied(pKiller);
	};

	void MakeClone(uint32 val)
	{
		SpellDesc * ds = AddSpell(SPELL_REPELLING_WAVE, Target_Self, 100, 0, 0, 0.0f, 0.0f, false, "Twice the pain and half the fun.", Text_Yell, 17524, NULL, 1);
		CastSpellNowNoScheduling(ds);

		SpellDesc * ds2 = AddSpell(SPELL_SUMMON_CLONE, Target_Self, 100, 0, 0, 0.0f, 0.0f, false, "", TextType(0), 0, NULL, 1);
		CastSpellNowNoScheduling(ds2);

		MoonScriptCreatureAI * cr = GetNearestCreature( CN_BALTHARUS_CLONE );
		if( cr != NULL )
		{
			// sets clone's hp to same as orig has
			cr->GetUnit()->SetHealth(val);
		}
		cloned++;
	};

	void EncounterTalk()
	{
		RemoveTimer(speech_timer);
		Emote("Your power wanes, ancient one.... Soon you will join your friends.", Text_Yell, 17525);
	};

private:
	uint8 cloned;
	int32 speech_timer;
};

class Baltharus_CloneAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Baltharus_CloneAI, MoonScriptBossAI);
	Baltharus_CloneAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell( SPELL_BLADE_TEMPEST, Target_Self, 50, 0, 12 );
		AddSpell( SPELL_ENERVATING_BRAND, Target_Self, 40, 0, 14);
		AddSpell( SPELL_SIPHONED_MIGHT, Target_Self, 40, 0, 20);
    };

	void OnCombatStart(Unit* pTarget)
	{
		ParentClass::OnCombatStart(pTarget);
	};

	void AIUpdate()
	{
		ParentClass::AIUpdate();		
	};

	void OnDied(Unit* pKiller)
	{
		ParentClass::OnDied(pKiller);
	};
};

class XerestraszaAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(XerestraszaAI, MoonScriptBossAI);
	XerestraszaAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = dynamic_cast<RubySanctumScript*>( GetInstanceScript() );
	};

	void OnLoad()
	{
		// he has not been killed
		if( mInstance->GetInstanceData( 0, RS_BALTHARUS ) == 0 )
		{
			// she should has npc flags 0 from start
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 0);

			char * text = "Help! I am trapped within this tree! I require aid!";
			sEAS.EventYell(_unit, text, 5000);
			sEAS.EventPlaySound(_unit, 17490, 5000);

			// reg ai update for every sec
			RegisterAIUpdateEvent(1000);
		}
	};

	void AIUpdate()
	{
		// he is killed
		if( mInstance->GetInstanceData( 0, RS_BALTHARUS ) == 1 )
		{
			// move to destination
			SetCanMove(true);
			SetBehavior(Behavior_Default);
			SetAllowMelee(false);
			SetAllowSpell(false);
			MoveTo(3155.54f, 342.39f, 84.59f, 1.79f, false);

			// set her as q starter and finisher
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

			// add all speaking events
			char * text1 = "Thank you! I could not have held out for much longer.... A terrible thing has happened here.";
			sEAS.EventSay(_unit, text1, 11000);
			sEAS.EventPlaySound(_unit, 17491, 11000);

			char * text2 = "We believed the Sanctum was well-fortified, but we were not prepared for the nature of this assault.";
			sEAS.EventSay(_unit, text2, 20000);
			sEAS.EventPlaySound(_unit, 17492, 20000);

			char * text3 = "The Black dragonkin materialized from thin air, and set upon us before we could react.";
			sEAS.EventSay(_unit, text3, 27000);
			sEAS.EventPlaySound(_unit, 17493, 27000);

			char * text4 = "We did not stand a chance. As my brethren perished around me, I managed to retreat here and bar the entrance.";
			sEAS.EventSay(_unit, text4, 34000);
			sEAS.EventPlaySound(_unit, 17494, 34000);

			char * text5 = "They slaughtered us with cold efficiency, but the true focus of their interest seemed to be the eggs kept here in the Sanctum.";
			sEAS.EventSay(_unit, text5, 45000);
			sEAS.EventPlaySound(_unit, 17495, 45000);

			char * text6 = "The commander of the forces on the ground here is a cruel brute named Zarithrian, but I fear there are greater powers at work.";
			sEAS.EventSay(_unit, text6, 55500);
			sEAS.EventPlaySound(_unit, 17496, 55500);

			char * text7 = "In their initial assault, I caught a glimpse of their true leader, a fearsome full-grown twilight dragon.";
			sEAS.EventSay(_unit, text7, 65000);
			sEAS.EventPlaySound(_unit, 17497, 65000);

			char * text8 = "I know not the extent of their plans, heroes, but I know this: They cannot be allowed to succeed!";
			sEAS.EventSay(_unit, text8, 74000);
			sEAS.EventPlaySound(_unit, 17498, 74000);

			RemoveAIUpdateEvent();
		}
	};

private:
	RubySanctumScript * mInstance;
};

// minion spawn locations
float spawn_x[] = { 3012.70f, 3033.47f, 3023.72f, 0 };
float spawn_y[] = { 490.114f, 535.377f, 585.291f, 0 };
float spawn_z[] = { 89.125f, 89.643f, 88.832f, 0 };
float spawn_o[] = { 1.64f, 3.1374f, 4.3508f, 0 };

class ZarithrianAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(ZarithrianAI, MoonScriptBossAI);
	ZarithrianAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = dynamic_cast<RubySanctumScript*>( GetInstanceScript() );

		AddSpell( SPELL_CLEAVE_ARMOR, Target_Current, 60, 0, 6 );
		AddSpell( SPELL_INTIMIDATING_ROAR, Target_ClosestPlayer, 40, 0, 20);

		AddEmote(Event_OnTargetDied, "You thought you stood a chance?", Text_Yell, 17513);
		AddEmote(Event_OnTargetDied, "It's for the best.", Text_Yell, 17514);
		AddEmote(Event_OnCombatStart, "Alexstrasza has chosen capable allies... A pity that I must END YOU!", Text_Yell, 17512);
    };

	void OnCombatStart(Unit* pTarget)
	{
		// every 30 seconds?
		summon_timer = AddTimer(30*1000);
		// fire stand up again, you cannot leave that area
		mInstance->ChangeDoorState( CN_ZARITHRIAN_DOORS, State_Inactive);

		ParentClass::OnCombatStart(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		// fire doors down
		mInstance->ChangeDoorState( CN_ZARITHRIAN_DOORS, State_Active);

		ParentClass::OnCombatStop(pTarget);
	};

	void OnDied(Unit* pKiller)
	{
		Emote("HALION! I...", Text_Yell, 17515);

		ParentClass::OnDied(pKiller);
	};

	void AIUpdate()
	{
		if( IsTimerFinished(summon_timer) )
			SpawnMinions();

		ParentClass::AIUpdate();
	};

	void SpawnMinions()
	{
		ResetTimer(summon_timer, 30*1000);

		// yell text
		Emote("Turn them to ash, minions!", Text_Yell, 17516);

		// spawn 3 minions in different locations
		for(int i = 0; i < 3; i++)
		{
			SpawnCreature(CN_FLAMECALLER, spawn_x[i], spawn_y[i], spawn_z[i], spawn_o[i], true);
		}
	};

private:
	RubySanctumScript * mInstance;
	int32 summon_timer;
};

#define CON_RAN_PLR				Man25Int(2,5)
#define	SPELL_FIRE_NOVA			Man25Int(78723, 78724)

class SavianaAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SavianaAI, MoonScriptBossAI);
	SavianaAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = dynamic_cast<RubySanctumScript*>( GetInstanceScript() );

		AddSpell( SPELL_FLAME_BREATH, Target_Current, 60, 0, 8 );

		AddEmote(Event_OnTargetDied, "Halion will be pleased.", Text_Yell, 17529);
		AddEmote(Event_OnTargetDied, "As it should be...", Text_Yell, 17530);
		AddEmote(Event_OnCombatStart, "You will sssuffer for this intrusion!", Text_Yell, 17528);
    };

	void OnCombatStart(Unit* pTarget)
	{
		// every 60 seconds cca from video
		fly_timer = AddTimer(60*1000);
		enrage_timer = AddTimer(45*1000);

		ParentClass::OnCombatStart(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		ParentClass::OnCombatStop(pTarget);
	};

	void OnDied(Unit* pKiller)
	{
		// find real message :)
		Emote("<screaming>", Text_Yell, 17531);

		ParentClass::OnDied(pKiller);
	};

	void AIUpdate()
	{
		// stop casting, disable melee, fly up
		if( IsTimerFinished(fly_timer) )
			Fly();

		// fly above the water
		if( IsTimerFinished(fly_next) )
			FlyNext();

		// cast confraglate
		if( IsTimerFinished(confraglate_timer) )
			Confraglate();

		// return back to target
		if( IsTimerFinished(return_back_timer) )
			ReturnBack();

		// enrage every 45 second
		if( IsTimerFinished(enrage_timer) )
			Enrage();

		// fire nova casting
		if( IsTimerFinished(fire_nova_timer) )
		{
			// if she is in Enrage, spam fire nova every 2 sec
			if( HasAura(SPELL_ENRAGE) )
			{
				CastSpellOnTarget(GetUnit()->GetAIInterface()->GetMostHated(), TargetGen_Current, dbcSpell.LookupEntry(SPELL_FIRE_NOVA), true);
				ResetTimer(fire_nova_timer, 2000);
			}
			// else remove spaming of fire nova
			else
				RemoveTimer(fire_nova_timer);
		}

		ParentClass::AIUpdate();
	};

	void Enrage()
	{
		ResetTimer(enrage_timer, 45*1000);

		// cast spell on self
		CastSpellOnTarget(_unit, Target_Self, dbcSpell.LookupEntry(SPELL_ENRAGE), true);

		// fire nova every 2 sec
		fire_nova_timer = AddTimer(2000);
	};

	void Fly()
	{
		ResetTimer(fly_timer, 60*1000);
		SetFlyMode(true);
		SetAllowMelee(false);
		SetAllowTargeting(false);

		MoveTo( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ()+4.0f, _unit->GetOrientation(), false);
		fly_next = AddTimer(2000);
		confraglate_timer = AddTimer(6000);
	};

	void FlyNext()
	{
		RemoveTimer( fly_next );
		MoveTo( 3153.07f, 679.457f, 95.0f, 4.74f, false );
	};

	void Confraglate()
	{
		// remove timer first
		RemoveTimer( confraglate_timer );

		// pick up 2 or 5 random players (depends on 10 / 25 man ) and cast confraglate on them
		for( int i = 0; i < CON_RAN_PLR; i++)
		{
			CastSpellOnTarget(GetBestPlayerTarget(), TargetGen_RandomPlayerDestination, dbcSpell.LookupEntry(SPELL_CONFRAGLATION), true);
		}

		// yell text
		Emote("Burn in the master's flame!", Text_Yell, 17532);

		// return back to target
		GetUnit()->GetAIInterface()->_CalcDestinationAndMove(GetUnit()->GetAIInterface()->GetMostHated(), 20.0f );

		return_back_timer = AddTimer(4000);
	};

	void ReturnBack()
	{
		RemoveTimer(return_back_timer);

		SetFlyMode(false);
		SetBehavior(Behavior_Melee);
		SetAllowMelee(true);
		SetAllowTargeting(true);
	};

private:
	RubySanctumScript * mInstance;
	int32 fly_timer;
	int32 confraglate_timer;
	int32 return_back_timer;
	int32 enrage_timer;
	int32 fire_nova_timer;
	int32 fly_next;
};

// some spells which are different in different modes
#define SPELL_HALION_FLAME_BREATH	Man25Int(74525, 74527)
#define SPELL_HALION_DARK_BREATH	Man25Int(74806, 75954)

// this is script for NPC in PHASE_PHYSICAL_REALM
class HalionAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(HalionAI, MoonScriptBossAI);
	HalionAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = dynamic_cast<RubySanctumScript*>( GetInstanceScript() );
		phase = PHASE_PHYSICAL_REALM;

		// Phase 1 Physical realm
		AddSpell( SPELL_HALION_FLAME_BREATH, Target_Current, 60, 2, 10 );
		AddSpell( SPELL_METEOR_STRIKE, Target_RandomPlayerDestination, 50, 0, 20);
		AddSpell( SPELL_FIERY_COMBUSTION, Target_RandomPlayerNotCurrent, 50, 0, 40);

		AddEmote(Event_OnTargetDied, "Another hero falls!", Text_Yell, 17501);
		AddEmote(Event_OnTargetDied, "Hahaha!", Text_Yell, 17502);
		AddEmote(Event_OnCombatStart, "Your world teeters on the brink of annihilation. You will ALL bear witness to the coming of a new age of DESTRUCTION!", Text_Yell, 17500);
    };

	void OnLoad()
	{
		Emote("Meddlesome insects, you're too late! The Ruby Sanctum is lost.", Text_Yell, 17499);
	};

	void OnCombatStart(Unit* pTarget)
	{
		// popup fire around halion
		mInstance->ChangeDoorState(CN_HALION_DOORS, State_Inactive);
		// cast twilight precision on self
		SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_TWILIGHT_PRECISION);
		CastSpellOnTarget( _unit, Target_Self, sp, false );

		if( phase == PHASE_PHYSICAL_REALM )
			ParentClass::OnCombatStart(pTarget);
		else
			GetUnit()->SetHealth( mInstance->halion_hp );
	};

	void OnCombatStop(Unit* pTarget)
	{
		ParentClass::OnCombatStop(pTarget);
	};

	void OnDied(Unit* pKiller)
	{
		// find real message :)
		Emote("Relish this victory, mortals, for it will be your last! This world will burn with the master's return!", Text_Yell, 17503);

		// stop fire around halion
		mInstance->ChangeDoorState(CN_HALION_DOORS, State_Active);

		ParentClass::OnDied(pKiller);
	};

	void AIUpdate()
	{
		if( IsTimerFinished(spawn_portal_timer) )
			SpawnPortal();

		if( GetHealthPercent() <= 75 && phase == PHASE_PHYSICAL_REALM )
			ChangePhase( PHASE_TWILIGHT_REALM );
		else if( GetHealthPercent() <= 50 && phase == PHASE_TWILIGHT_REALM )
			ChangePhase( PHASE_BOTH_REALMS );
		else if( phase == PHASE_BOTH_REALMS )
		{
			uint32 spellid = mInstance->GetCorporealitySpell(PHASE_PHYSICAL_REALM);
			GetUnit()->RemoveAllAuraByNameHash( SPELL_HASH_CORPOREALITY );
			SpellEntry * sp = dbcSpell.LookupEntryForced(spellid);
			CastSpellOnTarget( GetUnit(), Target_Self, sp, true);
		}

		ParentClass::AIUpdate();
	};

	void ChangePhase(uint32 val)
	{
		if( val == PHASE_TWILIGHT_REALM )
		{
			Emote("You will find only suffering within the realm of twilight! Enter if you dare!", Text_Yell, 17507);
			spawn_portal_timer = AddTimer(2500);

			// make this one not attacking and invisible by sending him into another phase
			SetAllowMelee(false);
			SetAllowSpell(false);
			SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_TWILIGHT_PHASING);
			CastSpellOnTarget( _unit, Target_Self, sp, false );
			phase = PHASE_TWILIGHT_REALM;
		}
		else if( val == PHASE_BOTH_REALMS )
		{
			// make him back attacking and visible
			SetAllowMelee(true);
			SetAllowSpell(true);
			SetCanMove(true);
			RemoveAura(SPELL_TWILIGHT_PHASING);
			phase = PHASE_BOTH_REALMS;
			SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_CORPOREALITY);
			CastSpellOnTarget( _unit, Target_Self, sp, false );
		}
	};

	void SpawnPortal()
	{
		// remove selections for all players
		mInstance->SetSelection(GetUnit());
		mInstance->halion_hp = GetUnit()->GetHealth();
		// remove timer
		RemoveTimer(spawn_portal_timer);
		// remove ai update event
		RemoveAIUpdateEvent();
		// spawn portal to second realm for 30 secs
		sEAS.SpawnGameobject(_unit, 203011, 3156.83f, 535.477f, 72.88f, 0.0f, 30*1000, 1, 1.5f);
		MoonScriptCreatureAI * ai = SpawnCreature(CN_HALION_TWILIGHT, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), true, 32);
		if( ai )
		{
			// copy original halion's threat list
			CopyThreatList( ai->GetUnit() );
		}
	};

private:
	RubySanctumScript * mInstance;
	uint8 phase;
	int32 spawn_portal_timer;
};

// this is script for NPC in PHASE_TWILIGHT_REALM
class HalionTwilightAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(HalionTwilightAI, MoonScriptBossAI);
	HalionTwilightAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = dynamic_cast<RubySanctumScript*>( GetInstanceScript() );
		phase = PHASE_TWILIGHT_REALM;
		
		// we need to change spells in hacky way if it is 25 man mode :(
		if( mInstance->Is25Man() )
		{
			SpellEntry * sp = dbcSpell.LookupEntry( SPELL_DUSK_SHROUD );
			if( sp != NULL )
				sp->EffectTriggerSpell[0] = 75485;
		}

		// Phase 2 Twilight realm
		AddSpell( SPELL_HALION_DARK_BREATH, Target_Current, 60, 2, 10 );
		AddSpell( SPELL_DUSK_SHROUD, Target_Self, 50, 0, 10 );

		AddEmote(Event_OnTargetDied, "Another hero falls!", Text_Yell, 17501);
		AddEmote(Event_OnTargetDied, "Hahaha!", Text_Yell, 17502);
    };

	void OnLoad()
	{
		//GetUnit()->SetHealth( mInstance->halion_hp );
	};

	void OnCombatStart(Unit* pTarget)
	{
		// cast twilight precision on self
		SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_TWILIGHT_PRECISION);
		CastSpellOnTarget( _unit, Target_Self, sp, false );

		GetUnit()->SetHealth( mInstance->halion_hp );

		ParentClass::OnCombatStart(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		ParentClass::OnCombatStop(pTarget);
	};

	void OnDied(Unit* pKiller)
	{
		ParentClass::OnDied(pKiller);
	};

	void AIUpdate()
	{
		if( GetHealthPercent() <= 50 && phase == PHASE_TWILIGHT_REALM )
			ChangePhase( PHASE_BOTH_REALMS );
		else if( phase == PHASE_BOTH_REALMS )
		{
			uint32 spellid = mInstance->GetCorporealitySpell(PHASE_TWILIGHT_REALM);
			GetUnit()->RemoveAllAuraByNameHash( SPELL_HASH_CORPOREALITY );
			SpellEntry * sp = dbcSpell.LookupEntryForced(spellid);
			CastSpellOnTarget( GetUnit(), Target_Self, sp, true);
		}

		ParentClass::AIUpdate();
	};

	void ChangePhase(uint32 val)
	{
		if( val == PHASE_BOTH_REALMS )
		{
			phase = PHASE_BOTH_REALMS;
			SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_CORPOREALITY);
			CastSpellOnTarget( _unit, Target_Self, sp, false );

			// save his HP
			mInstance->halion_hp = GetUnit()->GetHealth();

			// now spawns 4 portals, 2 in both realm
			sEAS.SpawnGameobject(_unit, 203012, 3184.75f, 553.12f, 72.92f, 0.0f, 1200*1000, 32, 1);
			sEAS.SpawnGameobject(_unit, 203011, 3184.75f, 553.12f, 72.92f, 0.0f, 1200*1000, 1, 1);

			sEAS.SpawnGameobject(_unit, 203012, 3140.52f, 516.45f, 72.88f, 0.0f, 1200*1000, 32, 1);
			sEAS.SpawnGameobject(_unit, 203011, 3140.52f, 516.45f, 72.88f, 0.0f, 1200*1000, 1, 1);

			MoonScriptCreatureAI * ai = GetNearestCreature(CN_HALION);
			if( ai )
			{
				ai->GetUnit()->SetHealth(GetUnit()->GetHealth());
				ai->RegisterAIUpdateEvent(1000);
			}

			// send world state
			mInstance->InitHalionHPCheck();
		}
	};

private:
	RubySanctumScript * mInstance;
	uint8 phase;
};

class HalionControllerAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(HalionControllerAI, MoonScriptCreatureAI);
	HalionControllerAI(Creature * pCreature) : MoonScriptCreatureAI(pCreature){};

	void OnLoad()
	{
		this->SetCanEnterCombat(false);
		spawn_halion = AddTimer(12000);
		cast_spell = AddTimer(1000);
		RegisterAIUpdateEvent(1000);
	};

	void AIUpdate()
	{
		if( IsTimerFinished(spawn_halion) )
			SpawnHalion();

		if( IsTimerFinished(cast_spell) )
			CastSpell();

		ParentClass::AIUpdate();
	};

	void SpawnHalion()
	{
		RemoveTimer(spawn_halion);
		SpawnCreature(CN_HALION, 3156.83f, 535.477f, 72.88f, 3.20f, false, 1);
		SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_FIERY_EXPLOSION);
		CastSpellOnTarget( _unit, Target_Self, sp, false );
		RemoveAIUpdateEvent();
	};

	void CastSpell()
	{
		RemoveTimer(cast_spell);
		SpellEntry * sp = dbcSpell.LookupEntryForced(SPELL_FIRE_PILLAR);
		CastSpellOnTarget( _unit, Target_Self, sp, false );
	};

private:
	int32 spawn_halion;
	int32 cast_spell;
};

#define SPELL_LAVA_GOUT Man25Int(74394, 74395)
#define SPELL_BLAST_NOVA Man25Int(74392, 74393)

class OnyxFlamecallerAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(OnyxFlamecallerAI, MoonScriptCreatureAI);
	OnyxFlamecallerAI(Creature * pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell( SPELL_LAVA_GOUT, Target_Current, 75, 2, 10);
		AddSpell( SPELL_BLAST_NOVA, Target_Self, 60, 2.5f, 15);
	};

	void OnLoad()
	{
		SetBehavior(Behavior_Melee);
		SetAllowMelee(true);
		SetAllowTargeting(true);
		AggroRandomPlayer();
		// this means they will first aggro and run to target and then they will start casting and attacking
		TriggerCooldownOnAllSpells();
	};

	void OnCombatStart(Unit* pTarget)
	{
		ParentClass::OnCombatStart(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		ParentClass::OnCombatStop(pTarget);
	};

	void OnDied(Unit* pKiller)
	{
		ParentClass::OnDied(pKiller);
	};

	void AIUpdate()
	{
		ParentClass::AIUpdate();
	};
};

class PhysicalRealmPort : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(PhysicalRealmPort);
	PhysicalRealmPort(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		pPlayer->RemoveAura(74807);
	}
};

void SetupTheRubySanctum(ScriptMgr* mgr)
{
	// Bosses
	mgr->register_creature_script(CN_BALTHARUS, &BaltharusAI::Create);
	mgr->register_creature_script(CN_BALTHARUS_CLONE, &Baltharus_CloneAI::Create);
	mgr->register_creature_script(CN_XERESTRASZA, &XerestraszaAI::Create);
	mgr->register_creature_script(CN_ZARITHRIAN, &ZarithrianAI::Create);
	mgr->register_creature_script(CN_SAVIANA, &SavianaAI::Create);
	mgr->register_creature_script(CN_HALION, &HalionAI::Create);
	mgr->register_creature_script(CN_HALION_TWILIGHT, &HalionTwilightAI::Create);
	mgr->register_creature_script(CN_HALION_CONTROLLER, &HalionControllerAI::Create);
	mgr->register_creature_script(CN_FLAMECALLER, &OnyxFlamecallerAI::Create);
	mgr->register_gameobject_script(CN_PHYSICAL_REALM, &PhysicalRealmPort::Create);

    // Instance
	mgr->register_instance_script(MAP_RS, &RubySanctumScript::Create);
};