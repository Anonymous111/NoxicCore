/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

/************************************************************************/
/* Instance_UtgardePinnacle.cpp Script									*/
/************************************************************************/

#define CN_IMAGE_OF_ARTHAS		29280
#define CN_SVALA				29281
#define CN_GRAUF				26893
#define CN_SVALA_SORROWGRAVE	26668
#define CN_SKADI_THE_RUTHLESS	26693
#define CN_GORTOK_PALEHOOF		26687
#define CN_KING_YMIRON			26861

#define FRENZIED_WORGEN		26683
#define RAVENOUS_FURBOLG	26684
#define MASSIVE_JORMUNGAR	26685
#define FEROCIOUS_RHINO		26686
#define FLAME_ORB			30702

#define SPELL_CRUSH					50234
#define SPELL_WHIRLWIND				50228
#define SPELL_POISIONED_SPEAR		50255
#define SPELL_CRUSH_H				59330
#define SPELL_POISIONED_SPEAR_H		59331
#define SPELL_WHIRLWIND_H			59322
#define SPELL_CALL_FLAMES			48258
#define SPELL_RITUAL_OF_THE_SWORD	48276
#define SPELL_SINISTER_STRIKE		15667
#define SPELL_SINISTER_STRIKE_H		59409
#define SPELL_ARCING_SMASH			48260
#define SPELL_IMPALE_H				59268
#define SPELL_WITHERING_ROAR_H		59267
#define SPELL_IMPALE				48261
#define SPELL_WITHERING_ROAR		48256
#define SPELL_BANE					48294
#define SPELL_DARK_SLASH			48292
#define SPELL_FETID_ROT				48291
#define SPELL_SCREAMS_OF_THE_DEAD	51750
#define SPELL_SPIRIT_BURST			48529
#define SPELL_SPIRIT_STRIKE			48423
#define SPELL_SPIRIT_STRIKE_H		59304
#define SPELL_FETID_ROT_H			59300
#define SPELL_SPIRIT_BURST_H		59305
#define SPELL_BANE_H				59301

#define GO_SKADIDOOR 192173

#define FORCED_CELLS 4

/*void SummonSvalaSorrowGrave(Player* plr)
{
	Creature* Svala = plr->GetCreatureNearestCoords(296.6319f, -346.0750f, 90.6306f, CN_SVALA);
	if(Svala == NULL)
		return;

	Creature* ImageOfArthas = ForceCreatureAIFind(CN_IMAGE_OF_ARTHAS, 296.3020f, -366.5547f, 93.4234f);
	if(ImageOfArthas == NULL)
		plr->SpawnCreature(CN_IMAGE_OF_ARTHAS, 296.3020f, -366.5547f, 93.4234f, 1.6336f, 30*1000); // Spawn Image of Arthas

	Svala->SetAttackable(false);
}

// TODO: Its supposed that Skadi mounts Grauf and starts attacking in the air.
void SkadiMount(Player* plr)
{
	Creature* Grauf = plr->GetCreatureNearestCoords(341.7409f, -516.9550f, 104.6689f, CN_GRAUF);
	if(Grauf == NULL)
		return;

	sEAS.WaypointCreateCustom(Grauf);
	sEAS.WaypointCreate(Grauf, 407.3898f, -512.5412f, 105.2506f, 3.0615f, 0, 256, 27043);	// 1
	Grauf->MoveToWaypoint(1);

	Creature* Skadi = plr->GetCreatureNearestCoords(343.0199f, -507.3250f, 104.5670f, 26693);
	if(Skadi == NULL)
		return;

	sEAS.WaypointCreateCustom(Skadi);
	sEAS.WaypointCreate(Skadi, 407.3898f, -512.5412f, 105.2506f, 3.0615f, 0, 256, 27418);	// 1
	sEAS.WaypointCreate(Skadi, 479.7927f, -512.8654f, 104.7229f, 3.0615f, 0, 256, 27418);	// 2
	Skadi->MoveToWaypoint(2);
}

class Svala : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Svala, MoonScriptCreatureAI);
	Svala(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}
	uint32 i;

	void OnSpawn() 
	{
		i = 0;
		RegisterAIUpdateEvent(3000);
	}

	void AIUpdate()
	{
		Player* plr = _unit->GetNearestAlivePlayer();
		if(plr == NULL)
			return;

		Creature* ImageOfArthas = ForceCreatureAIFind(29280, 296.3020f, -366.5547f, 93.4234f);
		if(ImageOfArthas == NULL)
			return;

		ImageOfArthas->SetSelectable(false);
		switch(i)
		{
			case 0:
				Yell("My liege! I have done as you asked, and now beseech you for your blessing!");
			break;
			case 1:
			ImageOfArthas->Yell("Your sacrifice is a testament to your obedience. Indeed you are worthy of this charge. Arise, and forever be known as Svala Sorrowgrave!");
			break;
			case 2:
				ImageOfArthas->Emote(EMOTE_ONESHOT_POINT);
				ImageOfArthas->CastSpell(_unit, 54142, false);
				CastSpell(_unit, 54140, false);
				SetFlyMode(true);
			break;
			case 5:
				CastSpell(_unit, 54205, false);
				SpawnCreature(26668, _unit->GetPositionX(), _unit->GetPositionY(), 90.6303f, 1.6336f, 0);
				Despawn(0, 0);
				ImageOfArthas->InterruptSpell();
				ImageOfArthas->RemoveNegativeAura(54140);
			break;
		}
		++i;
		ParentClass::AIUpdate();
	}
};

class SvalaSorrowgrave : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SvalaSorrowgrave, MoonScriptBossAI);
	uint32 chatCount;
	SvalaSorrowgrave(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		if(IsNormalInstance())
			AddSpell2(SPELL_SINISTER_STRIKE, Target_Current, 5*1000, 2*1000);
		else
			AddSpell2(SPELL_SINISTER_STRIKE_H, Target_Current, 5*1000, 2*1000);

		AddSpell2(SPELL_CALL_FLAMES, Target_RandomPlayer, 10*1000, 5*1000);
		AddSpell2(SPELL_RITUAL_OF_THE_SWORD, Target_RandomPlayer, 50*1000, 10*1000);
		AddEmote(Event_OnCombatStart, "I will vanquish your soul!", Text_Yell, 8825);
		AddEmote(Event_OnTargetDied, "You were a fool to challenge the power of the Lich King!", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "Your will is done, my king.", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "Another soul for my master.", Text_Yell, 8829);
		AddEmote(Event_OnDied, "Nooo! I did not come this far... to...", Text_Yell, 8828);
		AddEmote(Event_OnTaunt, "Your death approaches.", Text_Yell, 8831);
		AddEmote(Event_OnTaunt, "Go now to my master.", Text_Yell, 8832);
		AddEmote(Event_OnTaunt, "Your end is inevitable.", Text_Yell, 8833);
		AddEmote(Event_OnTaunt, "Any last words?", Text_Yell, 8833);
		chatCount = 0;
		RegisterAIUpdateEvent(3000);
		SetCanEnterCombat(false);
	}

	void OnCombatStart(Unit* pTarget)
	{
		SetWieldWeapon(true);
		CancelAllCooldowns();
		ParentClass::OnCombatStart(pTarget);
	}

	void AIUpdate()
	{
		Player* plr = _unit->GetNearestAlivePlayer();
		if(plr == NULL)
			return;

		Creature* ImageOfArthas = ForceCreatureAIFind(29280, 296.3020f, -366.5547f, 93.4234f);
		if(ImageOfArthas == NULL)
			return;

		switch(chatCount)
		{
			case 0:
				Yell("The sensation is... beyond my imagining. I am yours to command, my king.");
				SetFlyMode(true);
			break;
			case 1:
				ImageOfArthas->Yell("Your first test awaits you. Destroy our uninvited guests.");
			break;
			case 2:
				Yell("I will be happy to slaughter them in your name! Come, enemies of the Scourge! I will show you the might of the Lich King!");
				SetCanEnterCombat(true);
				Attack(_unit->GetNearestAlivePlayer());
			break;
		}
		++chatCount;
		ParentClass::AIUpdate();
	}
};

class SkaditheRuthless : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(SkaditheRuthless, MoonScriptBossAI);

	SkaditheRuthless(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		if(IsNormalInstance())
		{
			AddSpell2(SPELL_CRUSH, Target_Current, 10*1000, 2*1000);
			AddSpell2(SPELL_WHIRLWIND, Target_Current, 10*1000, 2*1000);
			AddSpell2(SPELL_POISIONED_SPEAR, Target_RandomPlayer, 10*1000, 2*1000);
		}
		else
		{
			AddSpell2(SPELL_CRUSH_H, Target_Current, 10*1000, 2*1000);
			AddSpell2(SPELL_WHIRLWIND_H, Target_Current, 10*1000, 2*1000);
			AddSpell2(SPELL_POISIONED_SPEAR_H, Target_RandomPlayer, 10*1000, 2*1000);
		}

		AddEmote(Event_OnCombatStart, "What mongrels dare intrude here? Look alive, my brothers! A feast for the one that brings me their heads!", Text_Yell, 8825);
		AddEmote(Event_OnTargetDied, "Not so brash now, are you?", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "I'll mount your skull from the highest tower!", Text_Yell, 8829);
		AddEmote(Event_OnDied, "ARGH! You call that... an attack? I'll... show... aghhhh...", Text_Yell, 8828);
	}

	void OnDied(Unit* mKiller)
	{
		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		GameObject* Door = _unit->GetGameObjectNearestCoords(477.496f, -477.183f, 103.064f, GO_SKADIDOOR);
		if(Door == NULL)
			return;

		Door->SetState(0);
		ParentClass::OnDied(mKiller);
	}

	void OnGraufDied()
	{
		Yell("You motherless knaves! Your corpses will make fine morsels for my new drake!");
		SetSelectable(true);
		SetCanEnterCombat(true);		
		Attack(_unit->GetNearestAlivePlayer());
	}
};

class GortokPalehoof : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(GortokPalehoof, MoonScriptBossAI);
	GortokPalehoof(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		if(IsNormalInstance())
		{
			AddSpell2(SPELL_IMPALE, Target_RandomPlayer, 15000);
			AddSpell2(SPELL_WITHERING_ROAR, Target_RandomPlayer, 20*1000, 5*1000);
		}
		else
		{
			AddSpell2(SPELL_IMPALE_H, Target_RandomPlayer, 15000);
			AddSpell2(SPELL_WITHERING_ROAR_H, Target_RandomPlayer, 20*1000, 5*1000);
		}

		AddSpell2(SPELL_ARCING_SMASH, Target_Current, 7*1000, 3*1000);
		AddEmote(Event_OnCombatStart, "What this place? I will destroy you!", Text_Yell, 8825);
		AddEmote(Event_OnTargetDied, "You die! That what master wants!", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "An easy task!", Text_Yell, 8829);
	}
};

class KingYmiron : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(KingYmiron, MoonScriptBossAI);
	KingYmiron(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		if(IsNormalInstance())
		{
			AddSpell2(SPELL_BANE, Target_Self, 10*1000, 5*1000);
			AddSpell2(SPELL_FETID_ROT, Target_RandomPlayer, 15*1000, 5*1000);
			AddSpell2(SPELL_SPIRIT_BURST, Target_Self, 12*1000, 3*1000);
			AddSpell2(SPELL_SPIRIT_STRIKE, Target_Current, 10*1000, 5*1000);
		}
		else
		{
			AddSpell2(SPELL_BANE_H, Target_Self, 10*1000, 5*1000);
			AddSpell2(SPELL_FETID_ROT_H, Target_RandomPlayer, 15*1000, 5*1000);
			AddSpell2(SPELL_SPIRIT_BURST_H, Target_Self, 12*1000, 3*1000);
			AddSpell2(SPELL_SPIRIT_STRIKE_H, Target_Current, 10*1000, 5*1000);
		}

		AddSpell2(SPELL_DARK_SLASH, Target_RandomPlayer, 15*1000, 5*1000);
		AddSpell2(SPELL_SCREAMS_OF_THE_DEAD, Target_RandomPlayer, 20*1000, 5*1000);
		AddEmote(Event_OnCombatStart, "You invade my home and then dare to challenge me? I will tear the hearts from your chests and offer them as gifts to the death god! Rualg nja gaborr!", Text_Yell, 8825);
		AddEmote(Event_OnTargetDied, "Your death is only the beginning!", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "You have failed your people!", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "There is a reason I am king!", Text_Yell, 8829);
		AddEmote(Event_OnTargetDied, "Bleed no more!", Text_Yell, 8829);
		AddEmote(Event_OnDied, "What... awaits me... now?", Text_Yell, 8828);
	}

	void OnDied(Unit* mKiller)
	{
		GameObject* Door = _unit->GetGameObjectNearestCoords(445.062f, -325.52f, 100.953f, 192174);
		if(Door != NULL)
			Door->SetState(0);

		ParentClass::OnDied(mKiller);
	}
};

class DarkSlash : public SpellScript
{
	void CalculateEffect(Spell* spell, uint32 i, Unit* target, SchoolDmgResult* result)
	{
		if(target == NULL || spell->u_caster == NULL)
			return;

		result->dmg = (uint32)target->GetHealth() / 2;
		result->static_damage = true;
	}
};

const uint32 CreaturesStasis[] = { FRENZIED_WORGEN, RAVENOUS_FURBOLG, MASSIVE_JORMUNGAR, FEROCIOUS_RHINO, 0 };
class StasisGenerator : public GameObjectAIScript
{
public:
	GAMEOBJECT_INIT_SCRIPT_DC(StasisGenerator);

	void OnActivate(Player* plr)
	{
		Creature* FlameOrb = plr->GetCreatureNearestObject(plr, FLAME_ORB);

		if(FlameOrb != NULL)
			return;

		plr->CastSpell(plr, 48048, false);
		FlameOrb = plr->SpawnCreature(FLAME_ORB, 282.4500f, -451.6841f, 111.9154f, 6.2745f, 0);

		//Supposed to make the Red orb effect, cant cast the spell on the FlameOrb
		FlameOrb->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_ATTACKABLE);
		FlameOrb->GetAIInterface()->m_moveFly = true;
		FlameOrb->SetSelectable(false);
		FlameOrb->CastSpell(FlameOrb, 48044, false);

		Creature *Statue = plr->GetRandomCreatureByEntrys(100.f, CreaturesStasis);

		if(Statue == NULL || Statue->isDead() == true)
			return;

		FlameOrb->CastSpell(Statue, 45465, false); //Similar spell to retail, couldnt find the same.
		Statue->SetSelectable(true);
		Statue->SetAttackable(true);
		Statue->EnableCombat(true);
		Statue->RemovePositiveAura(16245);
		Statue->Attack(Statue->GetNearestAlivePlayer());
		_gameobject->SetUInt32Value(GAMEOBJECT_FLAGS , GO_FLAG_INTERACT_COND);
		_gameobject->SetState(0);
	}
};

// MageHunterChannel Spell Change it if you find the correct visual pl0x
class MageHunterChannel : public SpellScript
{
public:
	bool OnAura(Aura* aura, uint32 i, bool apply) 
	{
		if(apply == true) // On Finish Effect.
			return true;

		Unit* caster = aura->GetUnitCaster();
		Unit* target = aura->GetTarget();

		if(caster == NULL || target == NULL || target->IsCreature() == false)
			return false;

		Creature* Statue = TO_CREATURE(target);

		return false;
	}
};

const uint32 CreaturesRhino[] = { FRENZIED_WORGEN, RAVENOUS_FURBOLG, MASSIVE_JORMUNGAR, 0 };
class FerociousRhino : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(FerociousRhino, MoonScriptCreatureAI);
	FerociousRhino(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller == NULL)
			return;

		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		Creature* FlameOrb = plr->GetCreatureNearestObject(plr, FLAME_ORB);

		if(FlameOrb == NULL)
			return;

		FlameOrb->CastSpell(FlameOrb, 48044, false);

		bool Boss = false;

		Creature* Gortok = FlameOrb->GetCreatureNearestObject(plr, CN_GORTOK_PALEHOOF);
		if(Gortok == NULL || Gortok->isDead() == true)
			return;

		Creature* MassiveJormungar = plr->GetCreatureNearestObject(plr, MASSIVE_JORMUNGAR);
		Creature* FrenziedWorgen = plr->GetCreatureNearestObject(plr, FRENZIED_WORGEN);
		Creature* RavenousFurbolg = plr->GetCreatureNearestObject(plr, RAVENOUS_FURBOLG);
		if(IsHeroicInstance() == false)
		{
			if(MassiveJormungar == NULL || FrenziedWorgen == NULL || RavenousFurbolg == NULL ||
				MassiveJormungar->isDead() == true || FrenziedWorgen->isDead() == true || RavenousFurbolg->isDead() == true)
			{
				Boss = true;
			}
		}
		else
		{
			if((MassiveJormungar == NULL || FrenziedWorgen == NULL || RavenousFurbolg == NULL) ||
				(MassiveJormungar->isDead() == true && FrenziedWorgen->isDead() == true && RavenousFurbolg->isDead() == true))
			{
				Boss = true;
			}
		}

		Creature* Statue = plr->GetRandomCreatureByEntrys(100.f, CreaturesRhino);

		if(Statue == NULL && Boss == false)
			return;

		Creature* Chosen = (Boss == true) ? Gortok : Statue;

		FlameOrb->CastSpell(Chosen, 45465, false); // Similar spell to retail, couldnt find the same.
		Chosen->SetSelectable(true);
		Chosen->SetAttackable(true);
		Chosen->EnableCombat(true);
		Chosen->RemovePositiveAura(16245);
		Chosen->Attack(Chosen->GetNearestAlivePlayer());
		ParentClass::OnDied(mKiller);
	}
};

const uint32 CreaturesWorgen[] = { FEROCIOUS_RHINO, RAVENOUS_FURBOLG, MASSIVE_JORMUNGAR, 0 };
class FrenziedWorgen : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(FrenziedWorgen, MoonScriptCreatureAI);
	FrenziedWorgen(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller == NULL)
			return;

		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		Creature* FlameOrb = plr->GetCreatureNearestObject(plr, FLAME_ORB);

		if(FlameOrb == NULL)
			return;

		FlameOrb->CastSpell(FlameOrb, 48044, false);

		bool Boss = false;
		Creature* Gortok = FlameOrb->GetCreatureNearestObject(plr, CN_GORTOK_PALEHOOF);
		if(Gortok == NULL || Gortok->isDead() == true)
			return;

		Creature* MassiveJormungar = plr->GetCreatureNearestObject(plr, MASSIVE_JORMUNGAR);
		Creature* FerociousRhino = plr->GetCreatureNearestObject(plr, FEROCIOUS_RHINO);
		Creature* RavenousFurbolg = plr->GetCreatureNearestObject(plr, RAVENOUS_FURBOLG);
		if(IsHeroicInstance() == false)
		{
			if(MassiveJormungar == NULL || FerociousRhino == NULL || RavenousFurbolg == NULL ||
				MassiveJormungar->isDead() == true || FerociousRhino->isDead() == true || RavenousFurbolg->isDead() == true)
			{
				Boss = true;
			}
		}
		else
		{
			if((MassiveJormungar == NULL || FerociousRhino == NULL || RavenousFurbolg == NULL) ||
				(MassiveJormungar->isDead() == true && FerociousRhino->isDead() == true && RavenousFurbolg->isDead() == true))
			{
				Boss = true;
			}
		}

		Creature* Statue = plr->GetRandomCreatureByEntrys(100.f, CreaturesWorgen);

		if(Statue == NULL && Boss == false)
			return;

		Creature* Chosen = (Boss == true) ? Gortok : Statue;

		FlameOrb->CastSpell(Chosen, 45465, false);//Similar spell to retail, couldnt find the same.
		Chosen->SetSelectable(true);
		Chosen->SetAttackable(true);
		Chosen->EnableCombat(true);
		Chosen->RemovePositiveAura(16245);
		Chosen->Attack(Chosen->GetNearestAlivePlayer());
		ParentClass::OnDied(mKiller);
	}
};

const uint32 CreaturesFurbolg[] = { FEROCIOUS_RHINO, FRENZIED_WORGEN, MASSIVE_JORMUNGAR, 0 };
class RavenousFurbolg : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(RavenousFurbolg, MoonScriptCreatureAI);
	RavenousFurbolg(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller == NULL)
			return;

		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		Creature* FlameOrb = plr->GetCreatureNearestObject(plr, FLAME_ORB);

		if(FlameOrb == NULL)
			return;

		FlameOrb->CastSpell(FlameOrb, 48044, false);

		bool Boss = false;
		Creature* Gortok = FlameOrb->GetCreatureNearestObject(plr, CN_GORTOK_PALEHOOF);
		if(Gortok == NULL || Gortok->isDead() == true)
			return;

		Creature* MassiveJormungar = plr->GetCreatureNearestObject(plr, MASSIVE_JORMUNGAR);
		Creature* FerociousRhino = plr->GetCreatureNearestObject(plr, FEROCIOUS_RHINO);
		Creature* FrenziedWorgen = plr->GetCreatureNearestObject(plr, FRENZIED_WORGEN);

		if(IsHeroicInstance() == false)
		{
			if(MassiveJormungar == NULL || FerociousRhino == NULL || FrenziedWorgen == NULL ||
				MassiveJormungar->isDead() == true || FerociousRhino->isDead() == true || FrenziedWorgen->isDead() == true)
			{
				Boss = true;
			}
		}

		else
		{
			if((MassiveJormungar == NULL || FerociousRhino == NULL || FrenziedWorgen == NULL) ||
				(MassiveJormungar->isDead() == true && FerociousRhino->isDead() == true && FrenziedWorgen->isDead() == true))
			{
				Boss = true;
			}
		}

		Creature* Statue = plr->GetRandomCreatureByEntrys(100.f, CreaturesFurbolg);

		if(Statue == NULL && Boss == false)
			return;

		Creature* Chosen = (Boss == true) ? Gortok : Statue;

		FlameOrb->CastSpell(Chosen, 45465, false);//Similar spell to retail, couldnt find the same.
		Chosen->SetSelectable(true);
		Chosen->SetAttackable(true);
		Chosen->EnableCombat(true);
		Chosen->RemovePositiveAura(16245);
		Chosen->Attack(Chosen->GetNearestAlivePlayer());
		ParentClass::OnDied(mKiller);
	}
};

const uint32 CreaturesJormungar[] = { FEROCIOUS_RHINO, FRENZIED_WORGEN, RAVENOUS_FURBOLG, 0 };
class MassiveJormungar : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(MassiveJormungar, MoonScriptCreatureAI);
	MassiveJormungar(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller == NULL)
			return;

		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		Creature* FlameOrb = plr->GetCreatureNearestObject(plr, FLAME_ORB);

		if(FlameOrb == NULL)
			return;

		FlameOrb->CastSpell(FlameOrb, 48044, false);

		bool Boss = false;
		Creature* Gortok = FlameOrb->GetCreatureNearestObject(plr, CN_GORTOK_PALEHOOF);
		if(Gortok == NULL || Gortok->isDead() == true)
			return;

		Creature* RavenousFurbolg = plr->GetCreatureNearestObject(plr, RAVENOUS_FURBOLG);
		Creature* FerociousRhino = plr->GetCreatureNearestObject(plr, FEROCIOUS_RHINO);
		Creature* FrenziedWorgen = plr->GetCreatureNearestObject(plr, FRENZIED_WORGEN);
		if(IsHeroicInstance() == false)
		{
			if(RavenousFurbolg == NULL || FerociousRhino == NULL || FrenziedWorgen == NULL ||
				RavenousFurbolg->isDead() == true || FerociousRhino->isDead() == true || FrenziedWorgen->isDead() == true)
			{
				Boss = true;
			}
		}

		else
		{
			if((RavenousFurbolg == NULL || FerociousRhino == NULL || FrenziedWorgen == NULL) ||
				(RavenousFurbolg->isDead() == true && FerociousRhino->isDead() == true && FrenziedWorgen->isDead() == true))
			{
				Boss = true;
			}
		}

		Creature* Statue = plr->GetRandomCreatureByEntrys(100.f, CreaturesJormungar);

		if(Statue == NULL && Boss == false)
			return;

		Creature* Chosen = (Boss == true) ? Gortok : Statue;

		FlameOrb->CastSpell(Chosen, 45465, false);//Similar spell to retail, couldnt find the same.
		Chosen->SetSelectable(true);
		Chosen->SetAttackable(true);
		Chosen->EnableCombat(true);
		Chosen->RemovePositiveAura(16245);
		Chosen->Attack(Chosen->GetNearestAlivePlayer());
		ParentClass::OnDied(mKiller);
	}
};

class Grauf : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Grauf, MoonScriptCreatureAI);
	Grauf(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

	void OnReachWP(uint32 iWaypointId, bool bForwards)
	{
		if(iWaypointId != 1)
			return;

		_unit->SetSelectable(true);
		_unit->SetAttackable(true);
		_unit->EnableCombat(true);
		_unit->Attack(_unit->GetNearestAlivePlayer());
	}

	void OnDied(Unit* mKiller)
	{
		if(mKiller == NULL)
			return;

		Player* plr = mKiller->GetPlayer();
		if(plr == NULL)
			return;

		Creature* Skadi = _unit->GetCreatureNearestObject(plr, CN_SKADI_THE_RUTHLESS);

		if(Skadi != NULL && Skadi->GetScript() != NULL)
			((SkaditheRuthless*)Skadi->GetScript())->OnGraufDied();

		ParentClass::OnDied(mKiller);
	}
};

static entryPos forcedList[FORCED_CELLS] =
{
	{ GO_SKADIDOOR,				477.496f,	-477.183f,	103.064f },
	{ CN_SKADI_THE_RUTHLESS,	343.02f,	-507.325f,	104.567f },
	{ CN_GRAUF,					341.741f,	-516.955f,	104.669f },
	{ 29281,					296.6319f,	-346.0750f,	90.6306f },
};

class UtgardePinnacle : public InstanceScript
{
public:
	INSTANCE_INIT_SCRIPT(UtgardePinnacle);
	UtgardePinnacle() {}

	//On AreaTrigger
	void OnAreaTrigger(Player* plr, uint32 AreaTrigger)
	{
		switch (AreaTrigger)
		{
			case 5140: SummonSvalaSorrowGrave(plr); break;
			case 4991: SkadiMount(plr); break;
		}
	}

	void OnLoad(MapMgr* mapMgr)
	{
		int i;

		for(i = 0; i < FORCED_CELLS; i++)
			mapMgr->LoadForcedCell(forcedList[i].x, forcedList[i].y);
	}
};*/

void SetupUtgardePinnacle(ScriptMgr* mgr)
{
	/*mgr->register_instance_script(575, &UtgardePinnacle::Create);

	mgr->register_creature_script(CN_KING_YMIRON, &KingYmiron::Create);
	mgr->register_creature_script(29281, &Svala::Create);
	mgr->register_creature_script(CN_SVALA_SORROWGRAVE , &SvalaSorrowgrave::Create);
	mgr->register_creature_script(CN_SKADI_THE_RUTHLESS, &SkaditheRuthless::Create);
	mgr->register_creature_script(CN_GORTOK_PALEHOOF, &GortokPalehoof::Create);
	mgr->register_creature_script(FEROCIOUS_RHINO, &FerociousRhino::Create);
	mgr->register_creature_script(FRENZIED_WORGEN, &FrenziedWorgen::Create);
	mgr->register_creature_script(RAVENOUS_FURBOLG, &RavenousFurbolg::Create);
	mgr->register_creature_script(MASSIVE_JORMUNGAR, &MassiveJormungar::Create);
	mgr->register_creature_script(CN_GRAUF, &Grauf::Create);

	mgr->register_spell_script(45465, new MageHunterChannel);
	mgr->register_spell_script(SPELL_DARK_SLASH, new DarkSlash);
	
	mgr->register_gameobject_script(188593, &StasisGenerator::Create);*/
}