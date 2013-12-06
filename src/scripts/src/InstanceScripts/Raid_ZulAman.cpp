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

#define CN_NALORAKK					23576
#define CN_CLTOTEM					24224
#define CN_AKILZON					23574
#define CN_SOARING_EAGLE		    24858 //SUMMONS  Akil'zon <Eagle Avatar>
#define CN_FEATHER_VORTEX			24136
#define CN_HALAZZI					23577
#define CN_LYNX_SPIRIT				24143
#define CN_TOTEM					24224
#define CN_GAZAKROTH				24244
#define CN_THURG					24241 
#define CN_LORD_RAADAN				24243 
#define CN_DARKHEART				24246 
#define CN_ALYSON_ANTILLE			24240
#define CN_SLITHER					24242 
#define CN_FENSTALKER				24245 
#define CN_KORAGG					24247 

//Phase 1
#define HALAZZI_SABER_LASH				 43267 //43267 //43268 ///40810 //40816
//Phase 2
#define HALAZZI_FLAME_SHOCK				 43303
#define HALAZZI_EARTH_SHOCK				 43305 //INSTANT , VARIOUS
//Phase 3
//Halazzi now drops his totems more frequently as well as doing more damage.

#define S_POISON_BOLT	43579 
#define TH_CLEAVE					43273
#define	TH_BLOODLUST				43578
#define DH_FEAR						43590
#define FEN_VOLATILE_INFECTION		43586
#define ALYS_HEAL					43575
#define	ALYS_DISPEL					43577
#define KOR_COLD_STARE				43593
#define KOR_MIGHTY_BLOW				43592
#define FEATHER_VORTEX_VISUAL		43119
#define AKILZON_STATIC_DISRUPTION	44008 //INSTANT
#define AKILZON_CALL_LIGHTING		43661 //INSTANT 
#define AKILZON_GUST_OF_WIND		43621 //INSTANT
#define AKILZON_ELECTRICAL_STORM	43648
#define LR_FLAME_BREATH				43582 
#define LR_THUNDER_CLAP				43583
#define GAZAKROTH_FIREBOLT			43584
#define CLT_LIGHTNING				43301
#define EAGLE_SWOOP					44732 //INSTANT//Halazzi <Lynx Avatar>
#define HALAZZI_ENRAGE				44779
#define NALORAKK_MANGLE				44955
#define NALORAKK_SURGE				25787	// 42402 - correct spell hits creature casting spell
#define NALORAKK_LACERATING_SLASH	42395
#define NALORAKK_REND_FLESH			42397
#define NALORAKK_DEAFENING_ROAR		42398
#define NALORAKK_BRUTAL_SWIPE		42384
#define NALORAKK_BERSERK			41924

class NalorakkAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(NalorakkAI, MoonScriptBossAI);
	NalorakkAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddPhaseSpell(1, AddSpell(NALORAKK_BRUTAL_SWIPE, Target_Current, 2, 0, 35));
		AddPhaseSpell(1, AddSpell(NALORAKK_MANGLE, Target_Current, 12, 0, 20));
		AddPhaseSpell(1, AddSpell(NALORAKK_SURGE, Target_RandomPlayer, 8, 0, 20, 0.0f, 45.0f, true, "I bring da pain!", Text_Yell, 12071));

		AddPhaseSpell(2, AddSpell(NALORAKK_LACERATING_SLASH, Target_Current, 12, 0, 20));
		AddPhaseSpell(2, AddSpell(NALORAKK_REND_FLESH, Target_Current, 12, 0, 12));
		AddPhaseSpell(2, AddSpell(NALORAKK_DEAFENING_ROAR, Target_RandomPlayer, 11, 0, 12));

		SetEnrageInfo(AddSpell(NALORAKK_BERSERK, Target_Self, 0, 0, 600, 0, 0, false, "You had your chance, now it be too late!", Text_Yell, 12074), 600000);

		AddEmote(Event_OnCombatStart, "You be dead soon enough!", Text_Yell, 12070);
		AddEmote(Event_OnTargetDied, "Da Amani gonna rule again!", Text_Yell, 12076);
		AddEmote(Event_OnTargetDied, "Now whatchoo got to say?", Text_Yell, 12075);
		AddEmote(Event_OnDied, "I... be waitin' on da udda side....", Text_Yell, 12077);

		// Bear Form
		Morph = AddSpell(42377, Target_Self, 0, 0, 0, 0, 0, false, "You call on da beast, you gonna get more dan you bargain for!", Text_Yell, 12072);
	}

	void OnCombatStart(Unit* pTarget)
	{
		// 45 Seconds until switch to Bear Form
		MorphTimer = AddTimer(45000);

		ParentClass::OnCombatStart(pTarget);
	}

	void OnCombatStop(Unit* pTarget)
	{
		// On leaving combat he changes back to a troll
		SetDisplayId(21631);

		ParentClass::OnCombatStop(pTarget);
	}

	void OnDied(Unit* pKiller)
	{
		// On death he changes back to a troll
		SetDisplayId(21631);

		ParentClass::OnDied(pKiller);
	}

	void AIUpdate()
	{
		ParentClass::AIUpdate();

		// Bear Form
		if(IsTimerFinished(MorphTimer) && GetPhase() == 1)
		{
			SetPhase(2, Morph);
			// Morph into a bear since the spell doesnt work
			SetDisplayId(21635);
			// 20 Seconds until switch to Troll Form
			ResetTimer(MorphTimer, 20000);
		}
		// Troll Form
		else if(IsTimerFinished(MorphTimer) && GetPhase() == 2)
		{
			// Remove Bear Form
			RemoveAura(42377);
			// Transform back into a Troll
			SetDisplayId(21631);
			SetPhase(1);
			// 45 Seconds until switch to Bear Form
			ResetTimer(MorphTimer, 45000);

			Emote("Make way for Nalorakk!", Text_Yell, 12073);
		}
	}

	SpellDesc* Morph;
	int32 MorphTimer;
};

class AkilzonAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(AkilzonAI, MoonScriptBossAI);
	AkilzonAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(AKILZON_STATIC_DISRUPTION, Target_Self, 2, 0, 60);
		AddSpell(AKILZON_CALL_LIGHTING, Target_Current, 2, 0, 0);
		AddSpell(AKILZON_GUST_OF_WIND, Target_Current, 0, 0, 0);
		AddSpell(AKILZON_ELECTRICAL_STORM, Target_Self, 1, 0, 0);

		AddEmote(Event_OnCombatStart, "I be da predator! You da prey!", Text_Yell, 12013);
		AddEmote(Event_OnTargetDied, "Stop your cryin'!", Text_Yell, 12018);
		AddEmote(Event_OnTargetDied, "Ya got nothin'!", Text_Yell, 12017);
		AddEmote(Event_OnDied, "You can't... kill... me spirit!", Text_Yell, 12019);
	}
	void OnCombatStart(Unit* pTarget)
	{
		// 2 Minute timer till Soaring Eagles are spawned
		mSummonTime = AddTimer(120000);

		ParentClass::OnCombatStart(pTarget);
	}
	void AIUpdate()
	{
		ParentClass::AIUpdate();

		if(IsTimerFinished(mSummonTime))
		{
			CreatureAIScript* Eagle = NULL;
			// Spawn 3 Soaring Eagles
			for(int x = 0; x < 3; x++)
			{
				Eagle = SpawnCreature(CN_SOARING_EAGLE, (_unit->GetPositionX() + RandomFloat(12) - 10), (_unit->GetPositionY() + RandomFloat(12) - 15),
					_unit->GetPositionZ(), _unit->GetOrientation(), true);
				if(Eagle)
				{
					Eagle->AggroNearestUnit();
					Eagle->SetDespawnWhenInactive(true);
				}
			}
			Eagle = NULL;
			Emote("Feed, me bruddahs!", Text_Yell, 12019);
			// Restart the timer
			ResetTimer(mSummonTime, 120000);
		}
	}

	int32 mSummonTime;
};

class SoaringEagleAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SoaringEagleAI);
	SoaringEagleAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(EAGLE_SWOOP, Target_Destination, 5, 0, 0);
		GetUnit()->m_noRespawn = true;
	}
};

class HalazziAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(HalazziAI, MoonScriptBossAI);
	HalazziAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddPhaseSpell(1, AddSpell(HALAZZI_SABER_LASH, Target_Destination, 0.5, 0, 0, 0, 0, false, "Me gonna carve ya now!", Text_Yell, 12023));

		AddPhaseSpell(2, AddSpell(HALAZZI_FLAME_SHOCK, Target_Current, 12, 0, 0));
		AddPhaseSpell(2, AddSpell(HALAZZI_EARTH_SHOCK, Target_Current, 12, 0, 0));

		AddPhaseSpell(3, AddSpell(HALAZZI_SABER_LASH, Target_Destination, 0.5, 0, 0, 0, 0, false, "You gonna leave in pieces!", Text_Yell, 12024));
		AddPhaseSpell(3, AddSpell(HALAZZI_FLAME_SHOCK, Target_Current, 18, 0, 0));
		AddPhaseSpell(3, AddSpell(HALAZZI_EARTH_SHOCK, Target_Current, 18, 0, 0));
		AddPhaseSpell(3, AddSpell(HALAZZI_ENRAGE, Target_Self, 100, 0, 60));

		// Transfigure: 4k aoe damage
		Transfigure = AddSpell(44054, Target_Self, 0, 0, 0, 0, 0, false, "I fight wit' untamed spirit...", Text_Yell, 12021);

		AddEmote(Event_OnCombatStart, "Get on your knees and bow to da fang and claw!", Text_Yell, 12020);
		AddEmote(Event_OnTargetDied, "You cant fight da power...", Text_Yell, 12026);
		AddEmote(Event_OnTargetDied, "You all gonna fail...", Text_Yell, 12027);
		AddEmote(Event_OnDied, "Chaga... choka'jinn.", Text_Yell, 12028);
		mLynx = NULL;
	}

	void OnCombatStart(Unit* pTarget)
	{
		mTotemTimer = AddTimer(5000); // Just to make the Timer ID
		SplitCount = 1;
		MaxHealth = _unit->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
		mLynx = NULL;
	}

	void OnCombatStop(Unit* pTarget)
	{
		Merge();
	}

	void AIUpdate()
	{
		// Every 25% Halazzi calls on the lynx
		if(!mLynx && GetHealthPercent() <= (100 - SplitCount * 25))
			Split();

		// Lynx OR Halazzi is at 20% HP Merge them together again
		if(mLynx && (mLynx->GetHealthPct() <= 20 || GetHealthPercent() <= 20))
			Merge();

		// At <25% Phase 3 begins
		if(GetHealthPercent() < 25 && GetPhase() == 1)
		{
			ResetTimer(mTotemTimer, 30000);
			SetPhase(3);
		}

		if(GetPhase() == 2 || GetPhase() == 3)
		{
			if(IsTimerFinished(mTotemTimer))
			{
				CreatureAIScript* Totem = NULL;
				Totem = SpawnCreature(CN_TOTEM, (_unit->GetPositionX() + RandomFloat(3) - 3), (_unit->GetPositionY() + RandomFloat(3) - 3), _unit->GetPositionZ(), 0, true);
				if(Totem)
				{
					Totem->Despawn(60000); // Despawn in 60 seconds
					Totem->AggroNearestPlayer();
					Totem = NULL;
				}
				switch(GetPhase())
				{
					case 2:
						ResetTimer(mTotemTimer, 60000);
					break;
					case 3:
						ResetTimer(mTotemTimer, 30000);
					break; // Spawn them faster then phase 2
				}
			}
		}
	}

	void Split()
	{
		CurrentHealth = GetUnit()->GetUInt32Value(UNIT_FIELD_HEALTH);
		SetDisplayId(24144);
		_unit->SetHealth(240000);
		_unit->SetUInt32Value(UNIT_FIELD_MAXHEALTH, 240000);

		mLynx = GetUnit()->GetMapMgr()->GetInterface()->SpawnCreature(CN_LYNX_SPIRIT, GetUnit()->GetPositionX(), GetUnit()->GetPositionY(), GetUnit()->GetPositionZ(), GetUnit()->GetOrientation(), true, false, 0, 0);
		if(mLynx)
		{
			mLynx->GetAIInterface()->AttackReaction(GetUnit()->GetAIInterface()->getNextTarget(), 1);
			mLynx->m_noRespawn = true;
		}

		SetPhase(2, Transfigure);
	}

	void Merge()
	{
		if(mLynx)
		{
			mLynx->Despawn(0, 0);
			mLynx = NULL;
			Emote("Spirit, come back to me!", Text_Yell, 12022);
		}

		if(CurrentHealth)
			_unit->SetHealth(CurrentHealth);
		if(MaxHealth)
			_unit->SetUInt32Value(UNIT_FIELD_MAXHEALTH, MaxHealth);
		SetDisplayId(21632);

		SplitCount++;
		SetPhase(1);
	}

	Creature* mLynx;
	SpellDesc* Transfigure;
	int32 mTotemTimer;
	int32 CurrentHealth;
	int32 MaxHealth;
	int SplitCount;
};

class LynxSpiritAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(LynxSpiritAI);
	LynxSpiritAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		// Lynx Flurry
		AddSpell(43290, Target_Self, 15, 0, 8);
		// Shred Armor
		AddSpell(43243, Target_Current, 20, 0, 0);
	}
};

class CLTOTEMAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CLTOTEMAI);
	CLTOTEMAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		SetDespawnWhenInactive(true);
		AddSpell(CLT_LIGHTNING, Target_RandomPlayer, 100, 0.5f, 2);
	}
};

class GAZAKROTHAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GAZAKROTHAI);
	GAZAKROTHAI(Creature* pCreature) : CreatureAIScript(pCreature) {}
	void OnCombatStart(Unit* pTarget)
	{
		RegisterAIUpdateEvent(500);
	}
	void AIUpdate()
	{
		if(!IsCasting())
			GetUnit()->CastSpell(GetUnit()->GetAIInterface()->GetMostHated(), GAZAKROTH_FIREBOLT, false);
	}
};

class LORDRAADANAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(LORDRAADANAI);
	LORDRAADANAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		FlameBreathTimer = ThunderClapTimer = INVALIDATE_TIMER;
	}
	void OnCombatStart(Unit* pTarget)
	{
		FlameBreathTimer = AddTimer(10000);
		ThunderClapTimer = AddTimer(3000);
	}
	void AIUpdate()
	{
		if(IsTimerFinished(FlameBreathTimer))
		{
			GetUnit()->CastSpell(GetUnit()->GetAIInterface()->GetMostHated(), LR_FLAME_BREATH, false);
			ResetTimer(FlameBreathTimer, 10000);
		}
		if(IsTimerFinished(ThunderClapTimer))
		{
			GetUnit()->CastSpellAoF(GetUnit()->GetPositionX(), GetUnit()->GetPositionY(), GetUnit()->GetPositionZ(), dbcSpell.LookupEntryForced(LR_THUNDER_CLAP), false);
			ResetTimer(ThunderClapTimer, 10000);
		}
	}
	
protected:
	int32 FlameBreathTimer, ThunderClapTimer;
};

class SLITHERAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SLITHERAI);
	SLITHERAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(S_POISON_BOLT, Target_RandomPlayer, 100, 2, 2);
	}
};

class THURGAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(THURGAI);
	THURGAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(TH_CLEAVE, Target_Current, 100, 0, 6);
		AddSpell(TH_BLOODLUST, Target_Self, 100, 0, 30);
	}
};

class DARKHEARTAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(DARKHEARTAI);
	DARKHEARTAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(DH_FEAR, Target_Destination, 100, 0, 20);
	}
};

class FENSTALKERAI : public ArcSciptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FENSTALKERAI);
	FENSTALKERAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(FEN_VOLATILE_INFECTION, Target_RandomPlayer, 100, 0, 20);
	}
};

class ALYSONANTILLEAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ALYSONANTILLEAI);
	ALYSONANTILLEAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		AddSpell(ALYS_HEAL, Target_WoundedFriendly, 100, 2, 10);
		DispelTimer = INVALIDATE_TIMER;
	}
	void OnCombatStart(Unit* pTarget)
	{
		DispelTimer = AddTimer(15000);
		ParentClass::OnCombatStart(pTarget);
	}
	void AIUpdate()
	{
		if(!IsCasting() && IsTimerFinished(DispelTimer))
		{
			std::vector<Unit*> DispelTargets;
			OBJECT_ITERATOR(GetUnit())
			{
				if(pObj->IsUnit() && !isHostile(pObj, GetUnit()))
				{
					Unit* pUnit = TO_UNIT(pObj);
					if(pUnit->isAlive())
					{
						if(pUnit->HasAurasWithNameHash(SPELL_HASH_POLYMORPH) || pUnit->HasAurasWithNameHash(SPELL_HASH_HIBERNATE) || pUnit->HasAurasWithNameHash(SPELL_HASH_FEAR))
							DispelTargets.push_back(pUnit);
					}
				}
			}
			END_OBJECT_ITERATOR(GetUnit());
			Unit* pTarget;
			if(!DispelTargets.size())
				pTarget = GetUnit()->GetAIInterface()->GetMostHated();
			else
				pTarget = DispelTargets[rand() % DispelTargets.size()];

			if(pTarget)
				GetUnit()->CastSpell(pTarget, ALYS_DISPEL, false);
			ResetTimer(DispelTimer, 15000);
		}
	}

protected:
	int32 DispelTimer;
};

class KORAGGAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KORAGGAI);
	KORAGGAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		AddSpell(KOR_MIGHTY_BLOW, Target_Current, 100, 0, 10);
		AddSpell(KOR_COLD_STARE, Target_RandomPlayer, 100, 0, 20);
	}
};

class FEATHERVORTEXAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FEATHERVORTEXAI, CreatureAIScript);
	FEATHERVORTEXAI(Creature* pCreature) : CreatureAIScript(pCreature), mTarget(0)
	{
		GetUnit()->CastSpell(GetUnit(), FEATHER_VORTEX_VISUAL, true);
		SetAllowMelee(false);
		GetUnit()->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		//target first victim
		AggroNearestPlayer();
		Unit* uTarget = GetRandomTargetMoon(MTT_Player, true);
		if(uTarget)
		{
			mTarget = uTarget->GetGUID();
			GetUnit()->GetAIInterface()->taunt(uTarget);
		}
		SetDespawnWhenInactive(true);
	}
	void OnCombatStart(Unit * pTarget)
	{
		ChangeTimer = AddTimer(10000);	
	}
	void ChangeTarget()
	{
		//erase old target
		GetUnit()->GetAIInterface()->taunt(NULL, false);
		//generate new target to follow
		Unit* uTarget = GetRandomTargetMoon(MTT_Player);
		if(!uTarget)
			uTarget = GetRandomTargetMoon(MTT_Unit, true);
		if(uTarget)
		{
			//set him as MT
			GetUnit()->GetAIInterface()->taunt(uTarget);
			mTarget = uTarget->GetGUID();
			ResetTimer(ChangeTimer, (5 + RandomUInt(5)) * 1000);
		}
	}

	void AIUpdate()
	{
		Unit* uTarget = GetUnit()->GetMapMgrUnit(mTarget);
		if(uTarget)
		{
			if(!uTarget->isAlive())
				ChangeTarget();
			if(GetUnit()->CalcDistance(uTarget) <= 4 || IsTimerFinished(ChangeTimer))
				ChangeTarget();
			MoveTo(uTarget);
		}
		else
			ChangeTarget();
	}
	uint64 mTarget;
	uint32 ChangeTimer;
};

bool ColdStare(uint32 i, SPELLPOINTER pSpell)
{
	Unit* pCaster = pSpell->u_caster;
	if(pCaster)
	{
		float mindist = 20.0f;
		Unit* pTarget = NULL;
		PLAYER_ITERATOR(pCaster)
		{
			if(pPlr->CalcDistance(pCaster) < mindist)
			{
				mindist = pPlr->CalcDistance(pCaster);
				pTarget = TO_UNIT(pPlr);
			}
		}
		END_PLAYER_ITERATOR(pCaster)
		//damage part
		pCaster->CastSpell(pCaster, 43594, true);
		//jump the debuff
		AURAPOINTER StareAura = pCaster->FindAura(43593);
		if(!StareAura)
			return true;
		if(pTarget)
		{
			SPELLPOINTER StareSpell = SpellPool.PooledNew();
			StareSpell->Init(pCaster, dbcSpell.LookupEntryForced(43593), true, NULLAUR);
			StareSpell->forced_basepoints[0] = StareAura->GetModAmount(0) - 1;
			SpellCastTargets targets(pTarget->GetGUID());
			StareSpell->prepare(&targets);
		}
		//remove the debuff from original owner
		pCaster->RemoveAura(StareAura);
	}
	return true;
}

class PillarOfFire : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SOARINGEAGLEAI);
	PillarOfFire(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		SetDespawnWhenInactive(true);
		GetUnit()->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
	}
};

void SetupZulAman(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_NALORAKK, &NalorakkAI::Create);

	mgr->register_creature_script(CN_AKILZON, &AkilzonAI::Create);
	mgr->register_creature_script(CN_SOARING_EAGLE, &SoaringEagleAI::Create);

	mgr->register_creature_script(CN_HALAZZI, &HalazziAI::Create);
	mgr->register_creature_script(CN_LYNX_SPIRIT, &LynxSpiritAI::Create);

	mgr->register_creature_script(CN_CLTOTEM, &CLTOTEMAI::Create);
	mgr->register_creature_script(CN_GAZAKROTH, &GAZAKROTHAI::Create);
	mgr->register_creature_script(CN_LORD_RAADAN, &LORDRAADANAI::Create);
	mgr->register_creature_script(CN_SLITHER, &SLITHERAI::Create);
	mgr->register_creature_script(CN_THURG, &THURGAI::Create);
	mgr->register_creature_script(CN_DARKHEART, &DARKHEARTAI::Create);
	mgr->register_creature_script(CN_FENSTALKER, &FENSTALKERAI::Create);
	mgr->register_creature_script(CN_ALYSON_ANTILLE, &ALYSONANTILLEAI::Create);
	mgr->register_creature_script(CN_KORAGG, &KORAGGAI::Create);
	mgr->register_creature_script(CN_FEATHER_VORTEX, &FEATHERVORTEXAI::Create);
	mgr->register_creature_script(24187, &PillarOfFire::Create);

	mgr->register_dummy_spell(43613, &ColdStare);
}
