/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

//MagisterTerrace Script
//Bosses

//Selin Firehart Encounter

// Creature Entry's
#define TRASH_FelCrystal 24722
#define BOSS_SelinFireheart 24723

// Normal & Heroic Spells

/*
   Mana Rage
   Caster: Fel Crystal
   Details: Empowers the caster with fel energy, restoring their mana for 10 sec.
   Triggers: Increases the target's mana by 10%.
*/
#define FC_MANARAGE 44320
#define FC_MANARAGE_TRIGGER 44321

/*
   Fel Explosion
   Caster Selin Fireheart
   Details: Area of effect damage spell, cast continually until Selin is out of mana
*/
#define SF_FELEXPLOSION 44314
/*
   Drain Life
   Caster Selin Fireheart
   Details: Randomly targeted channeled spell, deals damage and heals Selin.
*/
#define SF_DRAINLIFE 44294

// Heroic Spells
/*
   Drain Mana (Heroic Mode Only)
   Caster Selin Fireheart
   Details: Randomly targeted channeled spell on a player with mana, drain Mana to the player and give it to Selin.
*/
#define SF_DRAINMANA 46153

// Fel Crystal Spawn Locations
static LocationExtra FelCrystals[] =
{
	{225.969f, -20.0775f, -2.9731f, 0.942478f, TRASH_FelCrystal},
	{226.314f, 20.2183f, -2.98127f, 5.32325f, TRASH_FelCrystal},
	{247.888f, -14.6252f, 3.80777f, 2.33874f, TRASH_FelCrystal},
	{248.053f, 14.592f, 3.74882f, 3.94444f, TRASH_FelCrystal},
	{263.149f, 0.309245f, 1.32057f, 3.15905f, TRASH_FelCrystal}
};

class SelinFireheartAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SelinFireheartAI, MoonScriptCreatureAI);
	SelinFireheartAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(SF_DRAINLIFE, Target_RandomPlayer, 8, 0, 35);

		if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
			AddSpell(SF_DRAINMANA, Target_RandomPlayer, 8, 0, 35);

		ManaRage = dbcSpell.LookupEntry(FC_MANARAGE);
		ManaRageTrigger = AddSpell(FC_MANARAGE_TRIGGER, Target_Self, 0, 0, 0);
		FelExplosion = AddSpell(SF_FELEXPLOSION, Target_Self, 0, 0, 0);
	}

	void OnCombatStart(Unit* pTarget)
	{
		/*
			Selin Fireheart starts with 0 mana and drains it from the felcrystals in the room
			- ToDo: Set it so mana regen is off
		*/
		_unit->SetUInt32Value(UNIT_FIELD_POWER1, 0);
		ParentClass::OnCombatStart(pTarget);
	}

	/*
		During the AIUpdate() Selin will spam FelExplosion until hes out of mana
		He will then attempt to gain mana from a FelCrystal thats in the room by running to them
	*/
	void AIUpdate()
	{
		// 10% of his mana according to wowhead is 3231 which is whats needed to cast FelExplosion
		if(GetManaPercent() < 10 || FelExplosion->mEnabled == false)
			Mana();
		else if(!IsCasting())// Mana is greater than 10%
			CastFelExplosion();

		ParentClass::AIUpdate();
	}

	void Mana()
	{
		/*
			Attempt to get a Fel Crystal and move to it if not in range.
			Once in range we get the FelCrystal to cast Mana Rage on Selin
		*/
		Unit* FelCrystal = NULL;
		PreventActions(false);

		FelCrystal = FindFelCrystal();

		if(!FelCrystal || !FelCrystal->isAlive())
		{
			PreventActions(true);
			FelCrystal = NULL;
			return;
		}

		// Not in range
		if(_unit->GetDistance2dSq(FelCrystal) > 100)
		{
			MoveTo(FelCrystal->GetPositionX(), FelCrystal->GetPositionY(), FelCrystal->GetPositionZ());
			FelCrystal = NULL;
			return;
		}

		_unit->GetAIInterface()->StopMovement(0);

		if(!FelCrystal->GetCurrentSpell())
			FelCrystal->CastSpell(_unit, ManaRage, false);

		// Mana Rage giving of mana doesnt work so we give 10%(3231) / AIUpdate() Event.
		CastSpellNowNoScheduling(ManaRageTrigger);
		uint32 mana = _unit->GetPower(POWER_TYPE_MANA) + 3231;
		if(mana >= _unit->GetMaxPower(POWER_TYPE_MANA))
			mana = _unit->GetMaxPower(POWER_TYPE_MANA);

		_unit->SetUInt32Value(UNIT_FIELD_POWER1, mana);

		// Re-Enable FelExplosion
		if(GetManaPercent() >= 100)
			PreventActions(true);

		FelCrystal = NULL;
	}

	void PreventActions(bool Allow)
	{
		FelExplosion->mEnabled = Allow;
		SetAllowMelee(Allow);
		SetAllowRanged(Allow);
		SetAllowSpell(Allow);
		SetAllowTargeting(Allow);
	}

	Unit* FindFelCrystal()
	{
		/*
			Find a FelCrystal
		*/
		Unit* FC = NULL;
		for(int x = 0; x < 5; x++)
		{
			FC = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(FelCrystals[x].x, FelCrystals[x].y, FelCrystals[x].z, FelCrystals[x].addition);
			if(!FC || !FC->isAlive() || FC->GetInstanceID() != _unit->GetInstanceID())
				FC = NULL;
			else
				break;
		}
		return FC;
	}

	void CastFelExplosion()
	{
		CastSpellNowNoScheduling(FelExplosion);

		// No Idea why the mana isnt taken when the spell is cast so had to manually take it -_-
		_unit->SetUInt32Value(UNIT_FIELD_POWER1, _unit->GetPower(POWER_TYPE_MANA) - 3231);
	}

	SpellEntry* ManaRage;
	SpellDesc* ManaRageTrigger;
	SpellDesc* FelExplosion;
};

/*
	Vexallus
*/
#define BOSS_VEXALLUS 24744
#define CN_PURE_ENERGY 24745

#define VEXALLUS_CHAIN_LIGHTNING 44318
#define VEXALLUS_OVERLOAD 44353
#define VEXALLUS_ARCANE_SHOCK 44319
#define VEXALLUS_SUMMON_PURE_ENERGY 44322

class VexallusAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(VexallusAI, MoonScriptBossAI);
	VexallusAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddPhaseSpell(1, AddSpell(VEXALLUS_CHAIN_LIGHTNING, Target_Current, 19, 0, 8, 0, 0));
		AddPhaseSpell(1, AddSpell(VEXALLUS_ARCANE_SHOCK, Target_ClosestPlayer, 12, 0, 20, 0, 0, true, "Un...con...tainable.", Text_Yell, 12392));
		AddPhaseSpell(2, AddSpell(VEXALLUS_OVERLOAD, Target_Self, 85, 0, 3, 0, 0));
		mPureEnergy = AddSpell(VEXALLUS_SUMMON_PURE_ENERGY, Target_Self, 85, 0, 3);

		AddEmote(Event_OnTargetDied, "Con...sume.", Text_Yell, 12393);

		mSummon = 0;
	}

	void OnCombatStart(Unit* pTarget)
	{
		Emote("Drain... life...", Text_Yell, 12389);
		SetPhase(1);
		ParentClass::OnCombatStart(pTarget);
	}

	void AIUpdate()
	{
		if((GetHealthPercent() <= 85  && mSummon == 0) ||
				(GetHealthPercent() <= 70 && mSummon == 1) ||
				(GetHealthPercent() <= 55 && mSummon == 2) ||
				(GetHealthPercent() <= 40 && mSummon == 3) ||
				(GetHealthPercent() <= 25 && mSummon == 4))
		{
			CastSpell(mPureEnergy);
			++mSummon;
			//SpawnCreature(CN_PURE_ENERGY, 231, -207, 6, 0, true);
		}

		if(GetHealthPercent() <= 10 && GetPhase() == 1)
			SetPhase(2);

		ParentClass::AIUpdate();
	}

	SpellDesc*	mPureEnergy;
	uint8		mSummon;
};

//Priestess Delrissa
#define BOSS_Priestess_Delrissa 24560

#define PRIESTESS_DELRISSA_DISPEL_MAGIC 27609
#define PRIESTESS_DELRISSA_FLASH_HEAL 17843
#define PRIESTESS_DELRISSA_SHADOWWORD_PAIN 15654
#define PRIESTESS_DELRISSA_POWERWORD_SHIELD 44291
#define PRIESTESS_DELRISSA_RENEW 44174

class Priestess_DelrissaAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Priestess_DelrissaAI, MoonScriptBossAI);
	Priestess_DelrissaAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(PRIESTESS_DELRISSA_DISPEL_MAGIC, Target_RandomFriendly, 35, 0, 5, 0, 30);
		AddSpell(PRIESTESS_DELRISSA_FLASH_HEAL, Target_RandomFriendly, 40, 1.5, 7, 0, 40);
		AddSpell(PRIESTESS_DELRISSA_SHADOWWORD_PAIN, Target_RandomPlayer, 45, 0, 18, 0, 30);
		AddSpell(PRIESTESS_DELRISSA_POWERWORD_SHIELD, Target_RandomFriendly, 32, 0, 15, 0, 40);
		AddSpell(PRIESTESS_DELRISSA_RENEW, Target_RandomFriendly, 30, 0, 18, 0, 40);

		AddEmote(Event_OnDied, "Not what I had... planned...", Text_Yell, 12397);

		mClearHateList = AddTimer(15000);
		mKilledPlayers = 0;
	};

	void OnCombatStart(Unit* pTarget)
	{
		Emote("Annihilate them!", Text_Yell, 12395);
		//AggroRandomUnit(); // Want to aggro random unit ? Set it instead of calling premade
		// method that in this case recursively loops this procedure

		ParentClass::OnCombatStart(pTarget);
	};

	void OnTargetDied(Unit* pTarget)
	{
		if(!pTarget || !pTarget->IsPlayer())
			return;

		++mKilledPlayers;

		if(mKilledPlayers == 1)
			Emote("I call that a good start.", Text_Yell, 12405);
		else if(mKilledPlayers == 2)
			Emote("I could have sworn there were more of you.", Text_Yell, 12407);
		else if(mKilledPlayers == 3)
			Emote("Not really much of a group, anymore, is it?", Text_Yell, 12409);
		else if(mKilledPlayers == 4)
			Emote("One is such a lonely number.", Text_Yell, 12410);
		else if(mKilledPlayers == 5)
			Emote("It's been a kick, really.", Text_Yell, 12411);

		ParentClass::OnTargetDied(pTarget);
	};

	void OnCombatStop(Unit* pTarget)
	{
		Emote("It's been a kick, really.", Text_Yell, 12411);
		mKilledPlayers = 0;

		ParentClass::OnCombatStop(pTarget);
	};

	void AIUpdate()
	{
		if(IsTimerFinished(mClearHateList))
		{
			ClearHateList();
			AggroRandomUnit();
			ResetTimer(mClearHateList, 15000);
		};

		ParentClass::AIUpdate();
	};

protected:
	uint8		mKilledPlayers;
	int32		mClearHateList;
};

//Kagani Nightstrike
#define CN_KaganiNightstrike 24557

#define KAGANI_NIGHTSTRIKE_Eviscerate 46189
#define KAGANI_NIGHTSTRIKE_KidneyShot 27615
#define KAGANI_NIGHTSTRIKE_Gouge	  12540

class Kagani_NightstrikeAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Kagani_NightstrikeAI, MoonScriptBossAI);
	Kagani_NightstrikeAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(KAGANI_NIGHTSTRIKE_KidneyShot, Target_Current, 80, 0, 25, 0, 30);
		AddSpell(KAGANI_NIGHTSTRIKE_Gouge, Target_ClosestPlayer, 20, 0, 18, 0, 30);
		AddSpell(KAGANI_NIGHTSTRIKE_Eviscerate, Target_Current, 8, 0, 45, 0, 30);
	}
};

//Ellrys Duskhallow
#define CN_EllrysDuskhallow 14558

#define EllrysDuskhallow_Immolate 44267
#define EllrysDuskhallow_ShadowBolt 12471
#define EllrysDuskhallow_CurseofAgony 14875
#define EllrysDuskhallow_Fear 38595

class Ellrys_DuskhallowAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Ellrys_DuskhallowAI, MoonScriptBossAI);
	Ellrys_DuskhallowAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(EllrysDuskhallow_Immolate, Target_Current, 75, 2, 15, 0, 30);
		AddSpell(EllrysDuskhallow_ShadowBolt, Target_RandomPlayer, 75, 3, 5, 4, 40);
		AddSpell(EllrysDuskhallow_CurseofAgony, Target_RandomPlayer, 75, 0, 4, 0, 30);
		AddSpell(EllrysDuskhallow_Fear, Target_RandomPlayer, 75, 1.5, 9, 0, 20);
	}
};

//Eramas Brightblaze
#define CN_EramasBrightblaze 24554

#define ERAMAS_BRIGHTBLAZE_KNOCKDOWN 11428
#define ERAMAS_BRIGHTBLAZE_SNAP_KICK 46182

class Eramas_BrightblazeAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Eramas_BrightblazeAI, MoonScriptBossAI);
	Eramas_BrightblazeAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(ERAMAS_BRIGHTBLAZE_KNOCKDOWN, Target_Current, 25, 0, 5, 0, 5);
		AddSpell(ERAMAS_BRIGHTBLAZE_SNAP_KICK, Target_SecondMostHated, 40, 0, 2, 0, 5);
	}
};

//Yazzai
#define CN_YAZZAI 24561

#define YAZZAI_POLYMORPH 13323
#define YAZZAI_ICE_BLOCK 27619
#define YAZZAI_BLIZZARD 44178
#define YAZZAI_CONE_OF_COLD 38384
#define YAZZAI_FROSTBOLT 15530

class YazzaiAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(YazzaiAI, MoonScriptBossAI);
	YazzaiAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(YAZZAI_POLYMORPH, Target_RandomPlayer, 30, 1.5, 16, 0, 30);
		AddSpell(YAZZAI_ICE_BLOCK, Target_Self, 20, 0, 300, 0, 1);
		AddSpell(YAZZAI_BLIZZARD, Target_RandomPlayer, 25, 0, 20, 0, 30);
		AddSpell(YAZZAI_CONE_OF_COLD, Target_Self, 10, 0, 19, 0, 1);
		AddSpell(YAZZAI_FROSTBOLT, Target_RandomPlayer, 80, 3, 14, 0, 40);
	}
};

//Warlord Salaris
#define CN_WARLORD_SALARIS 24559

#define WARLORD_SALARIS_INTERCEPT 27577
#define WARLORD_SALARIS_DISARM 27581
#define WARLORD_SALARIS_PIERCING_HOWL 23600
#define WARLORD_SALARIS_FRIGHTENING_SHOUT 19134
#define WARLORD_SALARIS_HAMSTRING 27584
//#define WARLORD_SALARIS_BATTLE_SHOUT 27578
#define WARLORD_SALARIS_MORTAL_STRIKE 44268

class Warlord_SalarisAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Warlord_SalarisAI, MoonScriptBossAI);
	Warlord_SalarisAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		//AddSpell(uint32 pSpellId, TargetType pTargetType, float pChance, float pCastTime, int32 pCooldown, float pMinRange, float pMaxRange
		AddSpell(WARLORD_SALARIS_INTERCEPT, Target_RandomPlayer , 25, 0, 8, 8, 25);
		AddSpell(WARLORD_SALARIS_DISARM, Target_Current, 100, 0, 60, 0, 5);
		AddSpell(WARLORD_SALARIS_PIERCING_HOWL, Target_Self, 22, 0, 17, 0, 1);
		AddSpell(WARLORD_SALARIS_FRIGHTENING_SHOUT, Target_RandomPlayer, 30, 0, 9, 0, 10);
		AddSpell(WARLORD_SALARIS_HAMSTRING, Target_ClosestPlayer, 10, 0, 20, 0, 5);
		AddSpell(WARLORD_SALARIS_MORTAL_STRIKE, Target_Current, 100, 0, 6, 0, 5);
	}
};

//Geraxxas
#define CN_GARAXXAS 24555

#define GARAXXAS_AIMED_SHOT 44271
#define GARAXXAS_SHOOT 15620
#define GARAXXAS_CONCUSSIV_SHOT 27634
#define GARAXXAS_MULTI_SHOT 44285
#define GARAXXAS_WING_CLIP 44286

class GaraxxasAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(GaraxxasAI, MoonScriptBossAI);
	GaraxxasAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(GARAXXAS_AIMED_SHOT, Target_RandomPlayer, 90, 3, 6, 5, 35);
		AddSpell(GARAXXAS_SHOOT, Target_RandomPlayer, 90, 2.5, 5, 5, 30);
		AddSpell(GARAXXAS_CONCUSSIV_SHOT, Target_RandomPlayer, 40, 0, 8, 5, 35);
		AddSpell(GARAXXAS_MULTI_SHOT, Target_RandomPlayer, 25, 0, 12, 5, 30);
		AddSpell(GARAXXAS_WING_CLIP, Target_Current, 30, 0, 9, 0, 5);
	}
};

//Apoko
#define CN_APOKO 24553

#define APOKO_FROST_SHOCK 21401
#define APOKO_LESSER_HEALING_WAVE 44256
#define APOKO_PURGE 27626

class ApokoAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(ApokoAI, MoonScriptCreatureAI);
	ApokoAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(APOKO_FROST_SHOCK, Target_RandomPlayer, 40, 0, 8, 0, 20);
		AddSpell(APOKO_LESSER_HEALING_WAVE, Target_RandomFriendly, 50, 1.5, 10, 0, 40);
		AddSpell(APOKO_PURGE, Target_RandomUnit, 20, 0, 40, 0, 30);
	}
};

//Zelfan
#define CN_ZELFAN 24556

#define ZELFAN_GOBLIN_DRAGON_GUN 44272
#define ZELFAN_HIGH_EXPLOSIV_SHEEP 44276
#define ZELFAN_ROCKET_LAUNCH 44137

class ZelfanAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(ZelfanAI, MoonScriptCreatureAI);
	ZelfanAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(ZELFAN_GOBLIN_DRAGON_GUN, Target_Current, 90, 0, 15, 0, 5);
		AddSpell(ZELFAN_HIGH_EXPLOSIV_SHEEP, Target_Self, 90, 2, 80);
		AddSpell(ZELFAN_ROCKET_LAUNCH, Target_RandomPlayer, 99, 3.5, 60, 0, 45);
	}
};

//Trash mobs

// Coilskar Witch
#define CN_COILSKAR_WITCH 24696
#define COILSKAR_WITCH_FORKED_LIGHTNING 46150
#define COILSKAR_WITCH_FROST_ARROW 44639
#define COILSKAR_WITCH_MANA_SHIELD 46151
#define COILSKAR_WITCH_SHOOT 35946
/*class CoilskarWitchAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(CoilskarWitchAI, MoonScriptBossAI);
	CoilskarWitchAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(COILSKAR_WITCH_FORKED_LIGHTNING, Target_Current, 60, 2, 12, 0, 30);
		AddSpell(COILSKAR_WITCH_FROST_ARROW, Target_RandomPlayer, 15, 0, 16, 0, 40);
		AddSpell(COILSKAR_WITCH_MANA_SHIELD, Target_Self, 6, 0, 40, 0, 0);
		AddSpell(COILSKAR_WITCH_SHOOT, Target_RandomPlayer, 75, 1.5, 4, 5, 30);
	}
};*/

// Sister of Torment
#define CN_SISTER_OF_TORMENT 24697
#define SISTER_OF_TORMENT_DEADLY_EMBRACE 44547
#define SISTER_OF_TORMENT_LASH_OF_PAIN 44640
/*class SisterOfTormentAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SisterOfTormentAI, MoonScriptBossAI);
	SisterOfTormentAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(SISTER_OF_TORMENT_LASH_OF_PAIN, Target_Current, 60, 0, 8, 0, 5);
		AddSpell(SISTER_OF_TORMENT_DEADLY_EMBRACE, Target_RandomPlayer, 20, 1.5, 16, 0, 20);
	}
};*/

// Sunblade Blood Knight
#define CN_SB_BLOOD_KNIGHT 24684
#define SUNBLADE_BLOOD_KNIGHT_HOLY_LIGHT 46029
#define SUNBLADE_BLOOD_KNIGHT_JUDGEMENT_OF_WRATH 44482
#define SUNBLADE_BLOOD_KNIGHT_SEAL_OF_WRATH 46030
/*class SunbladeBloodKnightAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeBloodKnightAI, MoonScriptBossAI);
	SunbladeBloodKnightAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(SUNBLADE_BLOOD_KNIGHT_JUDGEMENT_OF_WRATH, Target_Current, 20, 0, 30, 0, 5);
		AddSpell(SUNBLADE_BLOOD_KNIGHT_SEAL_OF_WRATH, Target_Self, 99, 0, 30, 0, 0);
		AddSpell(SUNBLADE_BLOOD_KNIGHT_HOLY_LIGHT, Target_Self, 10, 2, 30, 0, 40);
	}
};*/

// Sunblade Imp
#define CN_SB_IMP 24815
#define SUNBLADE_IMP_FIREBOLT 44577
/*class SunbladeImpAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeImpAI, MoonScriptBossAI);
	SunbladeImpAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(SUNBLADE_IMP_FIREBOLT, Target_Current, 100, 2, (int32)2.5, 0, 30);
	}
};*/

// Sunblade Keeper
#define SUNBLADE_KEEPER 24762
#define SUNBLADE_KEEPER_BANISH 44765
#define SUNBLADE_KEEPER_SHADOW_BOLT 15232
#define SUNBLADE_KEEPER_SHADOW_BOLT_VOLLEY 20741
/*class SunbladeKeeperAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeKeeperAI, MoonScriptCreatureAI);
	SunbladeKeeperAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(SUNBLADE_KEEPER_BANISH, Target_RandomPlayer, 20, 2, 9, 0, 30);
		AddSpell(SUNBLADE_KEEPER_SHADOW_BOLT, Target_RandomPlayer, 35, 3, 4, 0, 40);
		AddSpell(SUNBLADE_KEEPER_SHADOW_BOLT_VOLLEY, Target_Self, 30, 0, 10);
	}
};*/

// Sunblade Mage Guard
#define CN_SB_MAGE_GUARD 24683
#define SUNBLADE_MAGE_GUARD_GLAVE_THROW 46028
#define SUNBLADE_MAGE_GUARD_MAGIC_DAMPENING_FIELD 44475
/*class SunbladeMageGuardAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeMageGuardAI, MoonScriptBossAI);
	SunbladeMageGuardAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(SUNBLADE_MAGE_GUARD_GLAVE_THROW, Target_Current, 60, 0, 25, 0, 5);
		AddSpell(SUNBLADE_MAGE_GUARD_MAGIC_DAMPENING_FIELD, Target_RandomPlayer, 20, 1, 35, 0, 20);
	}
};*/

// Sunblade Magister
#define CN_SB_MAGISTER 24685
#define SUNBLADE_MAGISTER_ARCANE_NOVA 46036
#define SUNBLADE_MAGISTER_FROSTBOLT 46035
/*class SunbladeMagisterAI : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeMagisterAI, MoonScriptBossAI);
	SunbladeMagisterAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(SUNBLADE_MAGISTER_FROSTBOLT, Target_Current, 65, 2, 4, 0, 30);
		AddSpell(SUNBLADE_MAGISTER_ARCANE_NOVA, Target_Self, 12, 1.5, 40, 0, 0);
	}
};*/

// Brightscale Wyrm
#define BRIGHTSCALE_WYRM 24761
#define BRIGHTSCALE_WYRM_ENERGY_INFUSION 44406
/*class BrightscaleWyrmAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(BrightscaleWyemAI, MoonScriptCreatureAI);
	BrightscaleWyrmAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{

	}

	void OnDied(Unit* mKiller)
	{
		Aura* pAura = Aura*(new Aura(dbcSpell.LookupEntry(BRIGHTSCALE_WYRM_ENERGY_INFUSION), 20000, mKiller, mKiller));
		if(pAura != NULL)
			mKiller->AddAura(pAura, NULLAURA);
	}
};*/

// Ethereum Smuggler
#define ETHEREUM_SMUGGLER 24698
#define ETHEREUM_SMUGGLER_ARCANE_EXPLOSION 44538
/*class EthereumSmugglerAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(EtereumSmugglerAI, MoonScriptCreatureAI);
	EthereumSmugglerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(ETHEREUM_SMUGGLER_ARCANE_EXPLOSION, Target_Self, 35, 1, 10);
	}
};*/

// Fizzle
#define FIZZLE 24656
#define FIZZLE_FIREBOLT 44164
/*class FizzleAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(FizzleAI, MoonScriptCreatureAI);
	FizzleAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(FIZZLE_FIREBOLT, Target_RandomPlayer, 35, 1, 1, 0, 30);
		_unit->GetAIInterface()->disable_melee = true;
	}
};*/

// Sunblade Physician
#define SUNBLADE_PHYSICIAN 24687
#define SUNBLADE_PHYSICIAN_INJECT_POISON 46046
#define SUNBLADE_PHYSICIAN_PRAYER_OF_MENDING 46045
/*class SunbladePhysicianAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladePhysicianAI, MoonScriptCreatureAI);
	SunbladePhysicianAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(SUNBLADE_PHYSICIAN_INJECT_POISON, Target_Self, 35, 1, 8);
		AddSpell(SUNBLADE_PHYSICIAN_PRAYER_OF_MENDING, Target_RandomFriendly, 25, 0, 10);
	}
};*/

// Sunblade Warlock
#define SUNBLADE_WARLOCK 24686
#define SUNBLADE_WARLOCK_FEL_ARMOR 44520
#define SUNBLADE_WARLOCK_IMMOLATE 46042
#define SUNBLADE_WARLOCK_INCINERATE 46043
#define SUNBLADE_WARLOCK_SUMMON_SUNBLADE_IMP 48320
/*class SunbladeWarlockAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SunbladeWarlockAI, MoonScriptCreatureAI);
	SunbladeWarlockAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(SUNBLADE_WARLOCK_FEL_ARMOR, Target_Self, 10, 0, 30);
		AddSpell(SUNBLADE_WARLOCK_IMMOLATE, Target_RandomPlayer, 35, 2, 5);
		AddSpell(SUNBLADE_WARLOCK_INCINERATE, Target_RandomPlayer, 30, 2, 5);
		AddSpell(SUNBLADE_WARLOCK_SUMMON_SUNBLADE_IMP, Target_Self, 25, 0, 15);
	}
};*/

// Wretched Bruiser
#define WRETCHED_BRUISER 24689
#define WRETCHED_BRUISER_WRETCHED_STRIKE 44534
#define WRETCHED_BRUISER_DRINK_FEL_INFUSION 44505
/*class WretchedBruiserAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(WretchedBruiserAI, MoonScriptCreatureAI);
	WretchedBruiserAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(WRETCHED_BRUISER_DRINK_FEL_INFUSION, Target_Self, 2, 0, 30);
		AddSpell(WRETCHED_BRUISER_WRETCHED_STRIKE, Target_Current, 35, 0, 5);
	}
};*/

// Wretched HUSK
#define WRETCHED_HUSK 24690
#define WRETCHED_HUSK_WRETCHED_FROSTBOLT 44504
#define WRETCHED_HUSK_WRETCHED_FIREBALL 44503
/*class WretchedHuskAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(WretchedHuskAI, MoonScriptCreatureAI);
	WretchedHuskAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(WRETCHED_BRUISER_DRINK_FEL_INFUSION, Target_Self, 2, 0, 30);
		AddSpell(WRETCHED_HUSK_WRETCHED_FROSTBOLT, Target_RandomPlayer, 35, 3, 5);
		AddSpell(WRETCHED_HUSK_WRETCHED_FIREBALL, Target_RandomPlayer, 35, 3, 5);
	}
};*/

// Wretched Skulker
#define WRETCHED_SKULKER 24688
#define WRETCHED_SKULKER_WRETCHED_STAB 44533
/*class WretchedSkulkerAI : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(WretchedSkulkerAI, MoonScriptCreatureAI);
	WretchedSkulkerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(WRETCHED_BRUISER_DRINK_FEL_INFUSION, Target_Self, 2, 0, 30);
		AddSpell(WRETCHED_SKULKER_WRETCHED_STAB, Target_Current, 35, 0, 5);
	}
};*/

// Fel Crystal
#define FEL_CRYSTAL 24722
/*class FelCrystalAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(FelCrystalAI);
	FelCrystalAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->m_canMove = false;
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
	}

	void OnDied(Unit* mKiller)
	{
		Creature* selinfh = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), SELIN_FIREHEART);
		if(selinfh)
		{
			if(selinfh->GetCurrentSpell())
			{
				selinfh->GetCurrentSpell()->cancel();
			}
		}
	}
};*/

// Pure Energy
#define PURE_ENERGY 24745
#define PURE_ENERGY_ENERGY_BOLT 44342
/*class PureEnergyAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PureEnergyAI);
	PureEnergyAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		_unit->CastSpell(_unit, dbcSpell.LookupEntry(PURE_ENERGY_ENERGY_BOLT), true);
	}
    
	void OnDied(Unit* mKiller)
	{

		Aura* pAura = Aura*(new Aura(dbcSpell.LookupEntry(44335), 30000, mKiller, mKiller));
		if(pAura != NULL)
			mKiller->AddAura(pAura, NULLAURA);

		RemoveAIUpdateEvent();
	}

	void OnCombatStop(Unit* mTarget)
	{
		RemoveAIUpdateEvent();
		_unit->Despawn(0, 0);
	}
};*/

// Kael'thas Sunstrider
#define KAELTHAS 24664
#define PHOENIX 24674
#define PHOENIX_FIREBALL 44202
#define PHOENIX_EMBER_BLAST 44199
#define PHOENIX_REBIRTH_DMG 44196
#define PHOENIX_HELLFIRE 39132
#define PHOENIX_EGG 24675

// Phoenix
/*class KaelPhoenixAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KaelPhoenixAI);
	KaelPhoenixAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
		Creature* kaelthas = NULLCREATURE;
		kaelthas = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), KAELTHAS);
		if(!kaelthas)
		{
			_unit->Despawn(0, 0);
		}
		else
		{
			_unit->GetAIInterface()->SetNextTarget(kaelthas->GetAIInterface()->GetNextTarget());
		}
	}

	void AIUpdate()
	{
		Creature* kaelthas = NULLCREATURE;
		kaelthas = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), KAELTHAS);
		if(!kaelthas)
		{
			RemoveAIUpdateEvent();
			_unit->Despawn(0, 0);
		}
		else
		{
			if(kaelthas->GetHealthPct() < 50)
			{
				_unit->GetAIInterface()->m_canMove = false;
				CastSpellOnRandomTarget();
			}

			_unit->CastSpell(_unit, dbcSpell.LookupEntry(PHOENIX_HELLFIRE), true);

			if(_unit->GetHealthPct() > 5)
			{
				_unit->SetHealthPct(_unit->GetHealthPct() - 5);
			}
			else
			{
				_unit->GetMapMgr()->GetInterface()->SpawnCreature(PHOENIX_EGG, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, true, false, 0, 0);
				RemoveAIUpdateEvent();
				_unit->Despawn(0, 0);
			}
		}
	}

	void OnCombatStop(Unit* mTarget)
	{
		RemoveAIUpdateEvent();
	}

	void OnDied(Unit* mKiller)
	{
		_unit->GetMapMgr()->GetInterface()->SpawnCreature(PHOENIX_EGG, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, true, false, 0, 0);
		RemoveAIUpdateEvent();
		_unit->Despawn(0, 0);
	}

	void CastSpellOnRandomTarget()
	{
		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
		{
			std::vector<UnitPointer > TargetTable;

			if(!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit* RTarget = TargetTable[RandTarget];

			if(!RTarget)
				return;

			_unit->CastSpell(RTarget, dbcSpell.LookupEntry(PHOENIX_FIREBALL), false);

			TargetTable.clear();
		}
	}
};

// Phoenix Egg
class PhoenixEggAI : public MoonScriptCreatureAI
{
public:
	int p;
    
	ADD_CREATURE_FACTORY_FUNCTION(PhoenixEggAI);
	PhoenixEggAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->m_canMove = false;
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
		p = 0;
	}

	void AIUpdate()
	{
		p++;
		if(p >= 12)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(PHOENIX_REBIRTH_DMG), true);
			_unit->GetMapMgr()->GetInterface()->SpawnCreature(PHOENIX, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, true, false, 0, 0);
			RemoveAIUpdateEvent();
			_unit->Despawn(0, 0);
		}
	}
};*/

// Gravity Lapse Bubble
#define BUBBLE_DMG 29765
#define GL_BUBBLE 100922
/*class GLBubbleAI : public MoonScriptCreatureAI
{
public:
	int t;
	ADD_CREATURE_FACTORY_FUNCTION(GLBubbleAI);
	GLBubbleAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		_unit->GetAIInterface()->m_moveFly = true;
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(500);
		t = 0;
		AddRandomWPs(_unit);
		_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
		_unit->GetAIInterface()->setWaypointToMove(1);
	}

	void AIUpdate()
	{
		Unit* pUnit;
		float dist;

		for(unordered_set<Object*>::iterator itr = _unit->GetInRangeOppFactsSetBegin(); itr != _unit->GetInRangeOppFactsSetEnd(); itr++)
		{
			if((*itr)->GetTypeId() != TYPEID_UNIT && (*itr)->GetTypeId() != TYPEID_PLAYER)
				continue;

			pUnit = TO_UNIT((*itr));

			if(!pUnit->isAlive() || _unit == pUnit)
				continue;

			dist = _unit->GetDistance2dSq(pUnit);
			if(dist < 10)
			{
				_unit->CastSpell(pUnit, dbcSpell.LookupEntry(BUBBLE_DMG), true);
			}
		}

		t++;
		if(t > 60)
		{
			_unit->Despawn(0, 0);
			RemoveAIUpdateEvent();
		}

		if((t % 8) == 0)
		{
			_unit->GetAIInterface()->setWaypointToMove(RandomUInt(4));
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
		}
	}

	void AddRandomWPs(Unit* pUnit)
	{
		int n = 5;
		int r = 30;

		for(int i = 0; i < n; i++)
		{
			float ang = rand()/100.0f;
			float ran = (rand()%(r*10))/10.0f;
			while(ran < 1)
			{
				ran = (rand()%(r*10))/10.0f;
			}

			float x = pUnit->GetPositionX()+ran*sin(ang);
			float y = pUnit->GetPositionY()+ran*cos(ang);
			float z = pUnit->GetPositionZ() + (float)RandomFloat(5.0f);
         
			WayPoint* wp = new WayPoint;
			wp->id = (uint32)mUnit->GetAIInterface()->GetWayPointsCount()+1;
			wp->x = x;
			wp->y = y;
			wp->z = z;
			wp->waittime = 0;
			wp->flags = 0;
			wp->forwardemoteoneshot = 0;
			wp->forwardemoteid = 0;
			wp->backwardemoteoneshot = 0;
			wp->backwardemoteid = 0;
			wp->forwardskinid = 0;
			wp->backwardskinid = 0;
				
			pUnit->GetAIInterface()->addWayPoint(wp);
		}
	}
};*/

// Flamestrike AI
#define KAEL_FLAMESTRIKE 24666
#define FLAMESTRIKE_SPELL 44190
#define FLAME_STRIKE_TRIGGER_FLAME_STRIKE_EFFECT    36730
/*class KaelFlamestrikeAI : public MoonScriptCreatureAI
{
public:
	int g;
	ADD_CREATURE_FACTORY_FUNCTION(KaelFlamestrikeAI);
	KaelFlamestrikeAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		_unit->GetAIInterface()->disable_melee = true;
		_unit->CastSpell(_unit, dbcSpell.LookupEntry(FLAME_STRIKE_TRIGGER_FLAME_STRIKE_EFFECT), true);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
		_unit->m_canMove = false;
		_unit->m_noRespawn = true;
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
		g = 0;
	}

	void AIUpdate()
    {
		if(g > 5)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(FLAMESTRIKE_SPELL), true);
			RemoveAIUpdateEvent();
			_unit->Despawn(0, 0);
		}
	}
};*/

// Kael'thas
#define KAEL_FLAME_STRIKE 46162
#define KAEL_PYROBLAST 36819
#define KAEL_SHOCK_BARRIER 46165
#define KAEL_GRAVITY_LAPSE 44224
#define KAEL_FIREBALL 46164
#define KAEL_GL_DMG_KBACK 44226
#define KAEL_GL_VISUAL 44251
#define KAEL_GL_SUMMON 35989
#define KAEL_KNOCKBACK 28405
/*class KaelThasMTAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KaelThasMTAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];
	int gl;
	int tired;
	int sc;
	int p1;
	float Phase;

	KaelThasMTAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		nrspells = 4;
		for(int i=0;i<nrspells;i++)
		{
			m_spellcheck[i] = false;
		}

		spells[0].info = dbcSpell.LookupEntry(KAEL_FLAME_STRIKE);
		spells[0].targettype = TARGET_RANDOM_DESTINATION;
		spells[0].instant = true;
		spells[0].perctrigger = 23.0f;
		spells[0].cooldown = 6;

		spells[1].info = dbcSpell.LookupEntry(KAEL_PYROBLAST);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].perctrigger = 15.0f;
		spells[1].cooldown = 10;

		spells[2].info = dbcSpell.LookupEntry(KAEL_FIREBALL);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = false;
		spells[2].perctrigger = 30.0f;
		spells[2].cooldown = 6;

		spells[3].info = dbcSpell.LookupEntry(KAEL_SHOCK_BARRIER);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].perctrigger = 23.0f;
		spells[3].cooldown = 10;
	}


	void OnCombatStart(Unit* mTarget)
	{
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Don't look so smug! I know what you're thinking, but Tempest Keep was merely a set back. Did you honestly believe I would trust the future to some blind, half-night elf mongrel?");
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Oh no, no, no, he was merely an instrument, a stepping stone to a much larger plan! It has all led to this...and this time, you will not interfere!");
		_unit->PlaySoundToSet(12413);

		gl = tired = p1 = 0;
		Phase = 1;

		RegisterAIUpdateEvent(1000);
	}

	void OnCombatStop(Unit* mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		_unit->GetAIInterface()->SetAIState(STATE_IDLE);

		if(!_unit->GetAIInterface()->GetNextTarget())
		{
			RemoveAIUpdateEvent();
		}
	}

	void OnDied(Unit* mKiller)
	{
		RemoveAIUpdateEvent();
		_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "My demise accomplishes nothing! The Master will have you! You will drown in your own blood! The world shall burn! Aaaghh!");
		_unit->PlaySoundToSet(12421);

		Unit* pUnit;
		for(unordered_set<Object*>::iterator itr = _unit->GetInRangeOppFactsSetBegin(); itr != _unit->GetInRangeOppFactsSetEnd(); itr++)
		{
			if((*itr)->GetTypeId() != TYPEID_UNIT && (*itr)->GetTypeId() != TYPEID_PLAYER)
				continue;

			pUnit = TO_UNIT((*itr));
			if(pUnit == _unit)
				continue;

			if(!pUnit->isAlive())
				continue;

			pUnit->DisableFlight();
		}

		Creature* ball = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), GL_BUBBLE);
		while(ball)
		{    
			ball->Despawn(0, 0);
			ball = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), GL_BUBBLE);
		}
	}

	void AIUpdate()
	{
		if (Phase == 1)
		{
			p1++;
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
			if(p1 == 20 || p1 == 40)
			{
				_unit->GetMapMgr()->GetInterface()->SpawnCreature(PHOENIX, _unit->GetPositionX() + RandomUInt(3), _unit->GetPositionY() + RandomUInt(2), _unit->GetPositionZ() + RandomUInt(2), 0, true, false, 0, 0);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Vengeance burns!");
				_unit->PlaySoundToSet(12415);
			}
		}

		if(_unit->GetHealthPct() <= 50)
		{
			if(Phase == 1)
			{
				Phase = 1.5;
				_unit->CastSpell(_unit, dbcSpell.LookupEntry(KAEL_GRAVITY_LAPSE), false);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "I'll turn your world...upside...down.");
				_unit->PlaySoundToSet(12418);
				sc = 0;
				_unit->GetAIInterface()->m_canMove = false;
			}
			else if(Phase == 1.5)
			{
				sc++;
				if(sc > 2)
				{
					Phase = 1.75;
					_unit->CastSpell(_unit, dbcSpell.LookupEntry(KAEL_GL_VISUAL), false);
				}
			}
			else if(Phase == 1.75)
			{
				// Gravity Lapse
				Unit* pUnit;
				for(unordered_set<Object*>::iterator itr = _unit->GetInRangeOppFactsSetBegin(); itr != _unit->GetInRangeOppFactsSetEnd(); itr++)
				{
					if((*itr)->GetTypeId() != TYPEID_PLAYER)
						continue;

					pUnit = TO_UNIT((*itr));
					if(pUnit == _unit)
						continue;

					if(!pUnit->isAlive())
						continue;

					pUnit->EnableFlight();
				}

				Phase = 2;
				// Summon ball things
				Unit* ball1;
				Unit* ball2;
				Unit* ball3;

				ball1 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(GL_BUBBLE, _unit->GetPositionX() + RandomUInt(3), _unit->GetPositionY() + RandomUInt(2), _unit->GetPositionZ() + RandomUInt(2), 0, true, false, 0, 0);
				ball2 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(GL_BUBBLE, _unit->GetPositionX() - RandomUInt(3), _unit->GetPositionY() - RandomUInt(2), _unit->GetPositionZ() + RandomUInt(2), 0, true, false, 0, 0);
				ball3 = _unit->GetMapMgr()->GetInterface()->SpawnCreature(GL_BUBBLE, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, true, false, 0, 0);
			}
			else if(Phase == 2)
			{
				gl++;
				_unit->GetAIInterface()->m_canMove = false;
				if(gl > 30)
				{
					// Undo Gravity Lapse
					Unit* pUnit;
					for(unordered_set<Object*>::iterator itr = _unit->GetInRangeOppFactsSetBegin(); itr != _unit->GetInRangeOppFactsSetEnd(); itr++)
					{
						if((*itr)->GetTypeId() != TYPEID_PLAYER)
							continue;
    
						pUnit = TO_UNIT((*itr));
						if(pUnit == _unit)
							continue;
    
						if(!pUnit->isAlive())
							continue;

						pUnit->DisableFlight();
						gl = 0;
					}

					Phase = 2.5;

					Creature* ball = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), GL_BUBBLE);
					while(ball)
					{
						ball->Despawn(0, 0);
						ball = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords( _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), GL_BUBBLE);
					}
				}
				else
				{
					float z_diff;
					Unit* pUnit;
					for(unordered_set<Object*>::iterator itr = _unit->GetInRangeOppFactsSetBegin(); itr != _unit->GetInRangeOppFactsSetEnd(); itr++)
					{
						if((*itr)->GetTypeId() != TYPEID_UNIT && (*itr)->GetTypeId() != TYPEID_PLAYER)
							continue;

						pUnit = TO_UNIT((*itr));
						if(pUnit == _unit)
							continue;

						if(!pUnit->isAlive())
							continue;

						pUnit->EnableFlight();
						z_diff = fabs(_unit->GetPositionZ() - pUnit->GetPositionZ());
						if(z_diff < 1)
						{
							_unit->CastSpell(pUnit, dbcSpell.LookupEntry(KAEL_KNOCKBACK), true);
						}
					}
				}
			}
			else if(Phase == 2.5)
			{
				gl++;
				_unit->GetAIInterface()->m_canMove = false;
				if(gl > 10 && RandomUInt(100) < 20)
				{
					// Gravity Lapse
					Phase = 1.5;

					_unit->CastSpell(_unit, dbcSpell.LookupEntry(KAEL_GRAVITY_LAPSE), false);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Do not get...too comfortable.");
					_unit->PlaySoundToSet(12420);
					gl = sc = 0;
				}
			}

			if(_unit->GetHealthPct() < 20 && tired == 0)
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Master, grant me strength.");
				_unit->PlaySoundToSet(12419);
				tired = 1;
			}
		}
	}

	void SpellCast(float val)
	{
		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
		{
			float comulativeperc = 0;
			Unit* target = NULLUNIT;
			for(int i=0;i<nrspells;i++)
			{
				if(!spells[i].perctrigger)
					continue;

				if(m_spellcheck[i])
				{
					target = _unit->GetAIInterface()->GetNextTarget();
					switch(spells[i].targettype)
					{
						case TARGET_SELF:
						case TARGET_VARIOUS:
							_unit->CastSpell(_unit, spells[i].info, spells[i].instant);
							break;
						case TARGET_ATTACKING:
							_unit->CastSpell(target, spells[i].info, spells[i].instant);
							break;
						case TARGET_DESTINATION:
							_unit->CastSpellAoF(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(), spells[i].info, spells[i].instant);
							break;
						case TARGET_RANDOM_FRIEND:
						case TARGET_RANDOM_SINGLE:
						case TARGET_RANDOM_DESTINATION:
							CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast);
							break;
					}

					m_spellcheck[i] = false;
					return;
				}

				uint32 t = (uint32)time(NULL);
				if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					spells[i].casttime = t + spells[i].cooldown;
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
    }

	void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
	{
		if(!maxdist2cast)
			maxdist2cast = 100.0f;

		if(!maxhp2cast)
			maxhp2cast = 100;

		if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
		{
			std::vector<Unit*> TargetTable;
			for(unordered_set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr) 
			{ 
				if(((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && ((*itr)->GetTypeId()== TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->GetInstanceID() == _unit->GetInstanceID()) // isAttackable(_unit, (*itr)) && 
				{
					Unit* RandomTarget = NULLUNIT;
					RandomTarget = TO_UNIT(*itr);
					if(RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast*mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast*maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || (_unit->GetAIInterface()->getThreatByPtr(RandomTarget) > 0 && isHostile(_unit, RandomTarget))))
					{
						TargetTable.push_back(RandomTarget);
					} 
				} 
			}

			if(_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
				TargetTable.push_back(_unit);

			if(!TargetTable.size())
				return;

			size_t RandTarget = rand()%TargetTable.size();

			Unit* RTarget = TargetTable[RandTarget];
			if(!RTarget)
				return;

			switch(spells[i].targettype)
			{
				case TARGET_RANDOM_FRIEND:
				case TARGET_RANDOM_SINGLE:
					_unit->CastSpell(RTarget, spells[i].info, spells[i].instant);
					break;
				case TARGET_RANDOM_DESTINATION:
				{
					_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Felomin ashal!");
					_unit->PlaySoundToSet(12417);
				}break;
			}

			TargetTable.clear();
		}
	}

protected:
	int nrspells;
};*/

class OrbSunwell : public GameObjectAIScript
{
public:
	OrbSunwell(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new OrbSunwell(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 4080, 12558.393555f, -6774.535645f, 15.027822f, 0.035100f);		 // Sunwell quit portal
	}
};

void SetupMagistersTerrace(ScriptMgr* mgr)
{
	//Bosses
	mgr->register_creature_script(BOSS_SelinFireheart, &SelinFireheartAI::Create);
	mgr->register_creature_script(BOSS_VEXALLUS, &VexallusAI::Create);
	mgr->register_creature_script(BOSS_Priestess_Delrissa, &Priestess_DelrissaAI::Create);
	//mgr->register_creature_script(KAELTHAS, &KaelThasMTAI::Create);
	//Priestess Delrissa Encounter Creature AI
	mgr->register_creature_script(CN_KaganiNightstrike, &Kagani_NightstrikeAI::Create);
	mgr->register_creature_script(CN_EllrysDuskhallow, &Ellrys_DuskhallowAI::Create);
	mgr->register_creature_script(CN_EramasBrightblaze, &Eramas_BrightblazeAI::Create);
	mgr->register_creature_script(CN_YAZZAI, &YazzaiAI::Create);
	mgr->register_creature_script(CN_WARLORD_SALARIS, &Warlord_SalarisAI::Create);
	mgr->register_creature_script(CN_GARAXXAS, &GaraxxasAI::Create);
	mgr->register_creature_script(CN_APOKO, &ApokoAI::Create);
	mgr->register_creature_script(CN_ZELFAN, &ZelfanAI::Create);

	//Trash Mobs
	//mgr->register_creature_script(CN_COILSKAR_WITCH, &CoilskarWitchAI::Create);
	//mgr->register_creature_script(CN_SISTER_OF_TORMENT, &SisterOfTormentAI::Create);
	//mgr->register_creature_script(CN_SB_IMP, &SunbladeImpAI::Create);
	//mgr->register_creature_script(CN_SB_MAGE_GUARD, &SunbladeMageGuardAI::Create);
	//mgr->register_creature_script(CN_SB_MAGISTER, &SunbladeMagisterAI::Create);
	//mgr->register_creature_script(PURE_ENERGY, &PureEnergyAI::Create);
	//mgr->register_creature_script(GL_BUBBLE, &GLBubbleAI::Create);
	//mgr->register_creature_script(PHOENIX_EGG, &PhoenixEggAI::Create);
	//mgr->register_creature_script(PHOENIX, &KaelPhoenixAI::Create);
	//mgr->register_creature_script(KAEL_FLAMESTRIKE, &KaelFlamestrikeAI::Create);
	//mgr->register_creature_script(WRETCHED_HUSK, &WretchedHuskAI::Create);
	//mgr->register_creature_script(WRETCHED_SKULKER, &WretchedSkulkerAI::Create);
	//mgr->register_creature_script(WRETCHED_BRUISER, &WretchedBruiserAI::Create);
	//mgr->register_creature_script(SUNBLADE_WARLOCK, &SunbladeWarlockAI::Create);
	//mgr->register_creature_script(SUNBLADE_PHYSICIAN, &SunbladePhysicianAI::Create);
	//mgr->register_creature_script(SUNBLADE_KEEPER, &SunbladeKeeperAI::Create);
	//mgr->register_creature_script(SUNBLADE_IMP, &SunbladeImpAI::Create);
	//mgr->register_creature_script(SISTER_OF_TORMENT, &TormentSisterAI::Create);
	//mgr->register_creature_script(FIZZLE, &FizzleAI::Create);
	//mgr->register_creature_script(ETHEREUM_SMUGGLER, &EthereumSmugglerAI::Create);
	//mgr->register_creature_script(COILSKAR_WITCH, &CoilskarWitchAI::Create);
	//mgr->register_creature_script(SUNBLADE_BLOOD_KNIGHT, &SunbladeBloodKnightAI::Create);
	//mgr->register_creature_script(BRIGHTSCALE_WYRM, &BrightscaleWyrmAI::Create);
	//mgr->register_creature_script(FEL_CRYSTAL, &FelCrystalAI::Create);

	mgr->register_gameobject_script(188173, &OrbSunwell::Create);
}