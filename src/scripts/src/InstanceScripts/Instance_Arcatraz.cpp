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

/************************************************************************/
/* Instance_Arcatraz.cpp Script											*/
/************************************************************************/

// Arcatraz DefenderAI
#define CN_ARCATRAZ_DEFENDER 20857
#define PROTEAN_SUBDUAL 36288
#define FLAMING_WEAPON 36601
#define IMMOLATE 36638
/*class ArcatrazDefenderAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ArcatrazDefenderAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    ArcatrazDefenderAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(PROTEAN_SUBDUAL);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(FLAMING_WEAPON);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 15.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(IMMOLATE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 8.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Arcatraz SentinelAI
#define CN_ARCATRAZ_SENTINEL 20869
#define ENERGY_DISCHARGE 36717
#define EXPLODE 36719 // DBC: 36722, 36719
//Permanent Feign Death (Root) 31261 ?
/*class ArcatrazSentinelAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ArcatrazSentinelAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    ArcatrazSentinelAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(ENERGY_DISCHARGE);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 8.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(EXPLODE);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(_unit->GetHealthPct() <= 5)
			_unit->CastSpell(_unit, spells[1].info, spells[1].instant);

		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Arcatraz WarderAI
// SPELL CASTING TO REWRITE (spell ids are correct)
#define CN_ARCATRAZ_WARDER 20859
#define ARCANE_SHOT 36609
#define SHOT 15620
#define IMPROVED_WING_CLIP 35963
#define CHARGED_ARCANE_SHOT 36608
//Shoot Arcane Explosion Arrow 36327 ?
/*class ArcatrazWarderAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ArcatrazWarderAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    ArcatrazWarderAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(ARCANE_SHOT);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(SHOT);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(IMPROVED_WING_CLIP);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 8.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(CHARGED_ARCANE_SHOT);
		spells[3].targettype = TARGET_ATTACKING;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(_unit->GetAIInterface()->GetNextTarget())
		{
			Unit *target = NULL;
			target = _unit->GetAIInterface()->GetNextTarget();
			if(_unit->GetDistance2dSq(target) >= 100.0f && _unit->GetDistanceSq(target) <= 900.0f)
			{
				_unit->GetAIInterface()->m_canMove = false;
				int RangedSpell;
				RandomUInt(1000);
				RangedSpell=rand()%100;
				if(RangedSpell >= 0 && RangedSpell <= 20)
				{
					_unit->CastSpell(target, spells[3].info, spells[3].instant);
					_unit->setAttackTimer(spells[3].attackstoptimer, false);
				}
				if(RangedSpell > 20 && RangedSpell <= 40)
				{
					_unit->CastSpell(target, spells[0].info, spells[0].instant);
					_unit->setAttackTimer(spells[0].attackstoptimer, false);
				}
				else
				{
					_unit->CastSpell(target, spells[1].info, spells[1].instant);
					_unit->setAttackTimer(spells[1].attackstoptimer, false);
				}
			}

			else
			{
				_unit->GetAIInterface()->m_canMove = true;
				if(_unit->GetDistance2dSq(target) < 100.0f)
				{
					float val = (float)RandomFloat(100.0f);
					SpellCast(val);
				}
			}
		}
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())	// I was too lazy to rewrite it =S
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Blackwing DrakonaarAI
// SIMPLE_TELEPORT should be used when creature is summoned during Skyriss encounter
#define CN_BLACKWING_DRAKONAAR 20911
#define SIMPLE_TELEPORT 12980
#define BROOD_POWER_BLACK 39033
#define MORTAL_STRIKE 13737
#define BLAST_WAVE 39038
/*class BlackwingDrakonaarAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(BlackwingDrakonaarAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    BlackwingDrakonaarAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(SIMPLE_TELEPORT);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(BROOD_POWER_BLACK);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 7.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(MORTAL_STRIKE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 10.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(BLAST_WAVE);
		spells[3].targettype = TARGET_VARIOUS;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 6.0f;
		spells[3].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		_unit->GetAIInterface()->SetAIState(STATE_IDLE);
		RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Blazing TricksterAI
#define CN_BLACKWING_TRICKSTER 20905
#define FIREBOLT 36906
#define FIRE_SHIELD 36907
/*class BlackwingTricksterAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(BlackwingTricksterAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    BlackwingTricksterAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(FIREBOLT);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(FIRE_SHIELD);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 7.0f;
		spells[1].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {		
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Death WatcherAI
#define CN_DEATH_WATCHER 20867
#define TENTACLE_CLEAVE 36664
#define DRAIN_LIFE 36655
#define DEATH_COUNT 36657	// DBC: 36657, 36660
/*class DeathWatcherAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(DeathWatcherAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    DeathWatcherAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(TENTACLE_CLEAVE);
		spells[0].targettype = TARGET_ATTACKING;	// to prevent crashes changed from VARIOUS
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(DRAIN_LIFE);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 8.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(DEATH_COUNT);
		spells[2].targettype = TARGET_VARIOUS;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;

		MarkApplied = 0;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		MarkApplied = 0;
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		MarkApplied = 0;
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		MarkApplied = 0;
		CastTime();
    }

    void AIUpdate()
	{
		if(_unit->GetHealthPct() <= 50 && !MarkApplied)
		{
			_unit->CastSpell(_unit, spells[2].info, spells[2].instant);
			MarkApplied = 1;
		}
		else
		{
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
		}
	}

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:

	uint32 MarkApplied;
	int nrspells;
};*/

// Defender CorpseAI
// Seems to be ok, but not sure if I won't mess with this script a bit
#define CN_DEFENDER_CORPSE 21303
#define CORPSE_BURST 36593
#define BLOODY_EXPLOSION 36599
//#define PERMANENT_FEIGN_DEATH_ROOT 31261	// I don't have much infos and I am not sure about how it should work
											// I presume this is just corpse which should cast spell when player is close or attack it
/*class DefenderCorpseAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(DefenderCorpseAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    DefenderCorpseAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(CORPSE_BURST);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(BLOODY_EXPLOSION);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
		_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Protean SpawnAI
#define CN_PROTEAN_SPAWN 21395	// it's sth that spawns from Defender Corpse
#define ACIDIC_BITE 36796
//#define BLOODY_EXPLOSION 36588
/*class ProteanSpawnAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ProteanSpawnAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    ProteanSpawnAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(ACIDIC_BITE);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 8.0f;
		spells[0].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Entropic EyeAI
#define CN_ENTROPIC_EYE 20868
#define WAVERING_WILL 36699			// not sure if this is right one (I mean spell, not ID)
#define PIERCING_SHADOW 36698		// this "smaller" list must be rechecked =S
#define HEX 36700
#define TANTACLE_CLEAVE_EYE 36664
/*#define TANTACLE_CLEAVE_EYE 36664
#define FIREBALL_EYE 36711
#define FROSTBOLT_EYE 36710
#define WITHERED_TOUCH_EYE 36696
#define HEX_EYE 36700
#define PIERCING_SHADOW_EYE 36698
#define CHAOS_BREATH_EYE 36677	// SSS
#define POISON_BOLT_EYE 36713				// DBC List :O
#define NECROTIC_POISON_EYE 36693
#define SHRINK_EYE 36697
#define SHADOW_BOLT_EYE 36714
#define FEVERED_FATIGUE_EYE 36695
#define WAVERING_WILL_EYE 36699
#define CORROSIVE_POISON_EYE 36694
#define ARCANE_BOLT_EYE 36712*/
/*class EntropicEyeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EntropicEyeAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    EntropicEyeAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(WAVERING_WILL);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(PIERCING_SHADOW);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(HEX);
		spells[2].targettype = TARGET_VARIOUS;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 5.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(TANTACLE_CLEAVE_EYE);
		spells[3].targettype = TARGET_ATTACKING;	// changed from VAR. to prevent crashes
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 12.0f;
		spells[3].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Eredar DeathbringerAI
#define CN_EREDAR_DEATHBRINGER 20880
#define UNHOLY_AURA 27987	// DBC: 27988, 27987
#define DIMINISH_SOUL 36789	// DBC: 36789, 36791 (SSS)
#define FORCEFUL_CLEAVE 36787
/*class EredarDeathbringerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EredarDeathbringerAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    EredarDeathbringerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(UNHOLY_AURA);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(DIMINISH_SOUL);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 7.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(FORCEFUL_CLEAVE);
		spells[2].targettype = TARGET_ATTACKING;	// to prevent crashes changed
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 13.0f;
		spells[2].attackstoptimer = 1000;

		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Eredar Soul-EaterAI
#define CN_EREDAR_SOUL_EATER 20879
#define SOUL_CHILL 36786
#define SOUL_STEAL1 36778	// this on target, another on self
#define SOUL_STEAL2 36782	// DBC: 36782, 36778
/*class EredarSoulEaterAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EredarSoulEaterAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    EredarSoulEaterAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(SOUL_CHILL);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(SOUL_STEAL1);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 7.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(SOUL_STEAL2);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(m_spellcheck[1] == true)
						_unit->CastSpell(_unit, spells[2].info, spells[2].instant);

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Ethereum Life-BinderAI
#define CN_ETHEREUM_LIFE_BINDER 21702
#define BIND 37480
#define SHADOW_WORD_PAIN 15654
/*class EthereumLifeBinderAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EthereumLifeBinderAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    EthereumLifeBinderAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(BIND);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 8.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(SHADOW_WORD_PAIN);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 7.0f;
		spells[1].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Ethereum SlayerAI
#define CN_ETHEREUM_SLAYER 20896
#define IMPARING_POISON 36839
#define SLAYER_STRIKE 36838
#define EVASION 15087
/*class EthereumSlayerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EthereumSlayerAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    EthereumSlayerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(IMPARING_POISON);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(SLAYER_STRIKE);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 12.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(EVASION);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 6.0f;
		spells[2].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Ethereum Wave-CasterAI
#define CN_ETHEREUM_WAVE_CASTER 20897
#define POLYMORPH 36840
#define ARCANE_HASTE 32693
#define SONIC_BOMB 36841	// should counter spell so I must code it a bit more
// KNOCKBACK ?
/*class EthereumWaveCasterAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(EthereumWaveCasterAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    EthereumWaveCasterAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(POLYMORPH);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(ARCANE_HASTE);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(SONIC_BOMB);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 11.0f;
		spells[2].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
		CastTime();
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
		CastTime();
    }

    void OnDied(Unit * mKiller)
    {
		RemoveAIUpdateEvent();
		CastTime();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Gargantuan AbyssalAI
#define CN_GARGANTUAN_ABYSSAL 20898
#define FIRE_SHIELD_ABY 38855	// DBC: 38855, 38893
#define METEOR 36837
/*class GargantuanAbyssalAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(GargantuanAbyssalAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    GargantuanAbyssalAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(FIRE_SHIELD_ABY);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(METEOR);
		spells[1].targettype = TARGET_DESTINATION;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 8.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Greater Fire ElementalAI
// FIX ME: Mark of death
#define CN_GREATER_FIRE_ELEMENTAL 15438
#define FIRE_SHIELD_GFE 13376
#define FIRE_NOVA 12470
#define FIRE_BLAST 13339
#define MARK_OF_DEATH 37128	// SSS	// should be applied on target
/*class GreaterFireElementalAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(GreaterFireElementalAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    GreaterFireElementalAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(FIRE_SHIELD_GFE);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(FIRE_NOVA);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 9.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(FIRE_BLAST);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 9.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(MARK_OF_DEATH);
		spells[3].targettype = TARGET_ATTACKING;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 5.0f;
		spells[3].attackstoptimer = 1000;

		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// IronjawAI	// spells verification, cause some of those are for sure pet spells?
#define CN_IRONJAW 18670
// I couldn't force Ironjaw to cast spells with "?"
#define FURIOUS_HOWL 24597	// ?
#define DASH 23110
#define BITE 27050
#define GROWL 14921			// ?
#define FEROCIOUS_INSPIRATION 34456	// ?
#define FRENZY_EFFECT 19615
#define KILL_COMMAND 34027
#define BESTIAL_WRATH 24395	// DBC: 24395, 24396, 24397, 26592 (all are diffrent)	// ?
#define SNARL 32919
#define CHILLING_HOWL 32918
/*class IronjawAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(IronjawAI);
	SP_AI_Spell spells[10];
	bool m_spellcheck[10];

    IronjawAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 10;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(FURIOUS_HOWL);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 3.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(DASH);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 3.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(BITE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 8.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(GROWL);
		spells[3].targettype = TARGET_ATTACKING;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 5.0f;
		spells[3].attackstoptimer = 1000;

		spells[4].info = dbcSpell.LookupEntry(FEROCIOUS_INSPIRATION);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = true;
		spells[4].cooldown = -1;
		spells[4].perctrigger = 3.0f;
		spells[4].attackstoptimer = 1000;

		spells[5].info = dbcSpell.LookupEntry(FRENZY_EFFECT);
		spells[5].targettype = TARGET_SELF;
		spells[5].instant = true;
		spells[5].cooldown = -1;
		spells[5].perctrigger = 4.0f;
		spells[5].attackstoptimer = 1000;

		spells[6].info = dbcSpell.LookupEntry(KILL_COMMAND);
		spells[6].targettype = TARGET_ATTACKING;
		spells[6].instant = true;
		spells[6].cooldown = -1;
		spells[6].perctrigger = 6.0f;
		spells[6].attackstoptimer = 1000;

		spells[7].info = dbcSpell.LookupEntry(BESTIAL_WRATH);
		spells[7].targettype = TARGET_ATTACKING;
		spells[7].instant = true;
		spells[7].cooldown = -1;
		spells[7].perctrigger = 4.0f;
		spells[7].attackstoptimer = 1000;

		spells[8].info = dbcSpell.LookupEntry(SNARL);
		spells[8].targettype = TARGET_ATTACKING;
		spells[8].instant = true;
		spells[8].cooldown = -1;
		spells[8].perctrigger = 8.0f;
		spells[8].attackstoptimer = 1000;

		spells[9].info = dbcSpell.LookupEntry(CHILLING_HOWL);
		spells[9].targettype = TARGET_ATTACKING;
		spells[9].instant = true;
		spells[9].cooldown = -1;
		spells[9].perctrigger = 5.0f;
		spells[9].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Millhouse ManastormAI
// Probably should be rewritten and is part of Skyriss encounter 
#define CN_MILLHOUSE_MANASTORM 20977
#define SIMPLE_TELEPORT_MM 12980
#define CONJURE_WATER 36879	// SSS
#define ARCANE_INTELLECT 36880
#define ICE_ARMOR 36881
#define DRINK 30024
#define FIREBALL_MM 14034
#define FROSTBOLT_MM 15497
#define FIRE_BLAST_MM 13341
#define CONE_OF_COLD 12611
#define ARCANE_MISSILES 33832	// DBC: 33832, 33833
#define PYROBLAST 33975
//#define CHILLED 7321 effect of ICE_ARMOR 36881
/*class MillhouseManastormAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(MillhouseManastormAI);
	SP_AI_Spell spells[11];
	bool m_spellcheck[11];

    MillhouseManastormAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 11;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(SIMPLE_TELEPORT_MM);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(CONJURE_WATER);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(ARCANE_INTELLECT);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 3.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(ICE_ARMOR);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 3.0f;
		spells[3].attackstoptimer = 1000;

		spells[4].info = dbcSpell.LookupEntry(DRINK);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = true;
		spells[4].cooldown = -1;
		spells[4].perctrigger = 0.0f;
		spells[4].attackstoptimer = 1000;

		spells[5].info = dbcSpell.LookupEntry(FIREBALL_MM);
		spells[5].targettype = TARGET_ATTACKING;
		spells[5].instant = false;
		spells[5].cooldown = -1;
		spells[5].perctrigger = 5.0f;
		spells[5].attackstoptimer = 1000;

		spells[6].info = dbcSpell.LookupEntry(FROSTBOLT_MM);
		spells[6].targettype = TARGET_ATTACKING;
		spells[6].instant = false;
		spells[6].cooldown = -1;
		spells[6].perctrigger = 5.0f;
		spells[6].attackstoptimer = 1000;

		spells[7].info = dbcSpell.LookupEntry(FIRE_BLAST_MM);
		spells[7].targettype = TARGET_ATTACKING;
		spells[7].instant = true;
		spells[7].cooldown = -1;
		spells[7].perctrigger = 5.0f;
		spells[7].attackstoptimer = 1000;

		spells[8].info = dbcSpell.LookupEntry(CONE_OF_COLD);
		spells[8].targettype = TARGET_VARIOUS;
		spells[8].instant = true;
		spells[8].cooldown = -1;
		spells[8].perctrigger = 4.0f;
		spells[8].attackstoptimer = 1000;

		spells[9].info = dbcSpell.LookupEntry(ARCANE_MISSILES);
		spells[9].targettype = TARGET_ATTACKING;
		spells[9].instant = false;
		spells[9].cooldown = -1;
		spells[9].perctrigger = 5.0f;
		spells[9].attackstoptimer = 1000;

		spells[10].info = dbcSpell.LookupEntry(PYROBLAST);
		spells[10].targettype = TARGET_ATTACKING;
		spells[10].instant = false;
		spells[10].cooldown = -1;
		spells[10].perctrigger = 2.0f;
		spells[10].attackstoptimer = 1000;

		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		//CastTime();
		//if(_unit->GetUInt32Value(UNIT_FIELD_POWER1) < _unit->GetUInt32Value(UNIT_FIELD_BASE_MANA))
		//{
		//	_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
		//	_unit->CastSpell(_unit, spells[4].info, spells[4].instant);
		//}
		_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
		_unit->CastSpell(_unit, spells[4].info, spells[4].instant);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Negaton ScreamerAI	// this one needs some more work for dmg taken dmg type, but I don't have time for it...
// Add missing function ------------------------------ look below
#define CN_NEGATON_SCREAMER 20875		// I need to add missing about 15 mobs (w00t? More? =() and to this script
										// OnDamageTaken function with check of spell dmg type and correct spell casts in diff cases
#define PSYCHIC_SCREAM 13704
#define DAMAGE_REDUCTION_SHADOW 34338
#define DAMAGE_REDUCTION_FROST 34334
#define DAMAGE_REDUCTION_ARCANE 34331
#define DAMAGE_REDUCTION_FIRE 34333
#define DAMAGE_REDUCTION_HOLY 34336
#define DAMAGE_REDUCTION_NATURE 34335
//#define DAMAGE_REDUCTION_PHYSICAL 34337
#define SHADOW_ENERGY 34399 // Energy SSS-s (I am sure only to spells shadow-frost-arcane-fire)
#define FROST_ENERGY 34404
#define ARCANE_ENERGY 34401
#define FIRE_ENERGY 34398
#define HOLY_ENERGY 34403
#define NATURE_ENERGY 34402
//#define PHYSICAL_ENERGY 
#define SHADOW_BOLT_VOLLEY 36736
#define FROSTBOLT_VOLLEY 36741
#define ARCANE_VOLLEY 36738
#define FIREBALL_VOLLEY 36742
#define HOLY_VOLLEY 36743
#define LIGHTNING_BOLT_VOLLEY	36740
//#define _VOLLEY
/*class NegatonScreamerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(NegatonScreamerAI);
	SP_AI_Spell spells[19];
	bool m_spellcheck[19];

    NegatonScreamerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 19;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(PSYCHIC_SCREAM);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 5.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_SHADOW);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_FROST);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_ARCANE);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;

		spells[4].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_FIRE);
		spells[4].targettype = TARGET_SELF;
		spells[4].instant = true;
		spells[4].cooldown = -1;
		spells[4].perctrigger = 0.0f;
		spells[4].attackstoptimer = 1000;

		spells[5].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_HOLY);
		spells[5].targettype = TARGET_SELF;
		spells[5].instant = true;
		spells[5].cooldown = -1;
		spells[5].perctrigger = 0.0f;
		spells[5].attackstoptimer = 1000;

		spells[6].info = dbcSpell.LookupEntry(DAMAGE_REDUCTION_NATURE);
		spells[6].targettype = TARGET_SELF;
		spells[6].instant = true;
		spells[6].cooldown = -1;
		spells[6].perctrigger = 0.0f;
		spells[6].attackstoptimer = 1000;

		spells[7].info = dbcSpell.LookupEntry(SHADOW_ENERGY);
		spells[7].targettype = TARGET_SELF;
		spells[7].instant = true;
		spells[7].cooldown = -1;
		spells[7].perctrigger = 0.0f;
		spells[7].attackstoptimer = 1000;

		spells[8].info = dbcSpell.LookupEntry(FROST_ENERGY);
		spells[8].targettype = TARGET_SELF;
		spells[8].instant = true;
		spells[8].cooldown = -1;
		spells[8].perctrigger = 0.0f;
		spells[8].attackstoptimer = 1000;

		spells[9].info = dbcSpell.LookupEntry(ARCANE_ENERGY);
		spells[9].targettype = TARGET_SELF;
		spells[9].instant = true;
		spells[9].cooldown = -1;
		spells[9].perctrigger = 0.0f;
		spells[9].attackstoptimer = 1000;

		spells[10].info = dbcSpell.LookupEntry(FIRE_ENERGY);
		spells[10].targettype = TARGET_SELF;
		spells[10].instant = true;
		spells[10].cooldown = -1;
		spells[10].perctrigger = 0.0f;
		spells[10].attackstoptimer = 1000;

		spells[11].info = dbcSpell.LookupEntry(HOLY_ENERGY);
		spells[11].targettype = TARGET_SELF;
		spells[11].instant = true;
		spells[11].cooldown = -1;
		spells[11].perctrigger = 0.0f;
		spells[11].attackstoptimer = 1000;

		spells[12].info = dbcSpell.LookupEntry(NATURE_ENERGY);
		spells[12].targettype = TARGET_SELF;
		spells[12].instant = true;
		spells[12].cooldown = -1;
		spells[12].perctrigger = 0.0f;
		spells[12].attackstoptimer = 1000;

		spells[13].info = dbcSpell.LookupEntry(SHADOW_BOLT_VOLLEY);
		spells[13].targettype = TARGET_VARIOUS;
		spells[13].instant = false;
		spells[13].cooldown = -1;
		spells[13].perctrigger = 0.0f;
		spells[13].attackstoptimer = 1000;

		spells[14].info = dbcSpell.LookupEntry(FROSTBOLT_VOLLEY);
		spells[14].targettype = TARGET_VARIOUS;
		spells[14].instant = false;
		spells[14].cooldown = -1;
		spells[14].perctrigger = 0.0f;
		spells[14].attackstoptimer = 1000;

		spells[15].info = dbcSpell.LookupEntry(ARCANE_VOLLEY);
		spells[15].targettype = TARGET_VARIOUS;
		spells[15].instant = false;
		spells[15].cooldown = -1;
		spells[15].perctrigger = 0.0f;
		spells[15].attackstoptimer = 1000;

		spells[16].info = dbcSpell.LookupEntry(FIREBALL_VOLLEY);
		spells[16].targettype = TARGET_VARIOUS;
		spells[16].instant = false;
		spells[16].cooldown = -1;
		spells[16].perctrigger = 0.0f;
		spells[16].attackstoptimer = 1000;

		spells[17].info = dbcSpell.LookupEntry(HOLY_VOLLEY);
		spells[17].targettype = TARGET_VARIOUS;
		spells[17].instant = false;
		spells[17].cooldown = -1;
		spells[17].perctrigger = 0.0f;
		spells[17].attackstoptimer = 1000;

		spells[18].info = dbcSpell.LookupEntry(LIGHTNING_BOLT_VOLLEY);
		spells[18].targettype = TARGET_VARIOUS;
		spells[18].instant = false;
		spells[18].cooldown = -1;
		spells[18].perctrigger = 0.0f;
		spells[18].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Negaton Warp-MasterAI
#define CN_NEGATON_WARP_MASTER 20873
#define SUMMON_NEGATION_FIELD 36813
/*class NegatonWarpMasterAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(NegatonWarpMasterAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    NegatonWarpMasterAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(SUMMON_NEGATION_FIELD);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Negaton FieldAI
// Not sure if shouldn't be rewritten.
#define CN_NEGATON_FIELD 21414
#define NEGATION_FIELD 36728 // DBC: 36728, 36729;
/*class NegatonFieldAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(NegatonFieldAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    NegatonFieldAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(NEGATION_FIELD);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;

		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Phase-HunterAI
// This unit is part of Skyriss encounter and it's teleport skill should be used during that encounter
#define CN_PHASE_HUNTER 20906
#define SIMPLE_TELEPORT_PH 12980
#define BACK_ATTACK 36909
#define WARP 36908	// lack of core support?
#define PHASE_BURST 36910
/*class PhaseHunterAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(PhaseHunterAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    PhaseHunterAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(SIMPLE_TELEPORT_PH);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(BACK_ATTACK);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(WARP);
		spells[2].targettype = TARGET_SELF;	//?
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 5.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(PHASE_BURST);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 5.0f;
		spells[3].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(m_spellcheck[2] == true)
					{
						uint32 chance = RandomUInt(100);
						if(chance > 0 && chance <= 30)
							_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
						else return;
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Protean HorrorAI
#define CN_PROTEAN_HORROR 20865
#define TOOTHY_BITE 36612
//#define BLOODY_EXPLOSION 36588
/*class ProteanHorrorAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ProteanHorrorAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    ProteanHorrorAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(TOOTHY_BITE);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Protean NightmareAI
#define CN_PROTEAN_NIGHTMARE 20864
#define INCUBATION 36622
#define INFECTIOUS_POISON 36619
#define GAPIND_MAW 36617
/*class ProteanNightmareAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(ProteanNightmareAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    ProteanNightmareAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(INCUBATION);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 6.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(INFECTIOUS_POISON);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(GAPIND_MAW);
		spells[2].targettype = TARGET_VARIOUS;
		spells[2].instant = false;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 6.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Sulfuron Magma-ThrowerAI
// Part of Skyriss encounter (so same thing to teleport stuff)
#define CN_SULFURON_MAGMA_THROWER 20909
#define SIMPLE_TELEPORT_SMT 12980
#define SHADOW_BOLT_SMT 36986	// DBC: 36987, 36986;
#define MAGMA_THROWERS_CURSE 36917
#define RAIN_OF_FIRE 19717
/*class SulfuronMagmaThrowerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SulfuronMagmaThrowerAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    SulfuronMagmaThrowerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(SIMPLE_TELEPORT_SMT);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(SHADOW_BOLT_SMT);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 12.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(MAGMA_THROWERS_CURSE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 6.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(RAIN_OF_FIRE);
		spells[3].targettype = TARGET_DESTINATION;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 9.0f;
		spells[3].attackstoptimer = 1000;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Spiteful TemptressAI
#define CN_SPITEFUL_TEMPTRESS 20883
#define SHADOW_BOLT_ST 36868
#define DOMINATION_ST 36866
#define SPITEFUL_FURY 36886
#define PRAYER_OF_MENDING 33280	// DBC: 33280, 33110; SSS
/*class SpitefulTemptressAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SpitefulTemptressAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    SpitefulTemptressAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(SHADOW_BOLT_ST);
		spells[0].targettype = TARGET_DESTINATION;	// not sure DESTINATION or ATTACKING
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 12.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(DOMINATION_ST);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 5.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(SPITEFUL_FURY);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 7.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(PRAYER_OF_MENDING);
		spells[3].targettype = TARGET_VARIOUS;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 8.0f;
		spells[3].attackstoptimer = 1000;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Soul DevourerAI
#define CN_SOUL_DEVOURER 20866
#define SIGHTLESS_EYE 36644
#define LAVA_BREATH 21333	// doesn't have animation?
#define FEL_BREATH 36654
#define FRENZY 33958
/*class SoulDevourerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SoulDevourerAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    SoulDevourerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(SIGHTLESS_EYE);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(LAVA_BREATH);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 12.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(FEL_BREATH);
		spells[2].targettype = TARGET_VARIOUS;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 8.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(FRENZY);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 8.0f;
		spells[3].attackstoptimer = 1000;

    }
    
    void OnCombatStart(Unit* mTarget)
    {
		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// SolomonAI
#define CN_SOLOMON 798	// not sure if this boy should be scripted, but he was in DBC and had spells, so I couldn't
						// stop myself to not give little boy deadly skills
#define SLIME_SPRAY 36486
#define SAW_BLADE 32735
#define CRUSADER_STRIKE 35509	// SE (script effect)
/*class SolomonAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SolomonAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    SolomonAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(SLIME_SPRAY);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 8.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(SAW_BLADE);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = false;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 8.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(CRUSADER_STRIKE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 12.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Skulking WitchAI
#define CN_SKULKING_WITCH 20882	// works really cool as assassin :)
#define CHASTISE 36863
#define GOUGE 36862
#define LASH_OF_PAIN 36864
#define GREAT_INVISIBILITY 16380
/*class SkulkingWitchAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SkulkingWitchAI);
	SP_AI_Spell spells[4];
	bool m_spellcheck[4];

    SkulkingWitchAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 4;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;


        spells[0].info = dbcSpell.LookupEntry(CHASTISE);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 12.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(GOUGE);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(LASH_OF_PAIN);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 5.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(GREAT_INVISIBILITY);
		spells[3].targettype = TARGET_SELF;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;

		_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
		FIRST_ATTACK = 1;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		FIRST_ATTACK = 1;
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

	void OnTargetDied(Unit* mTarget)
    {
    }

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
		FIRST_ATTACK = 1;
		_unit->CastSpell(_unit, spells[3].info, spells[3].instant);
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		FIRST_ATTACK = 1;
		CastTime();
		RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(FIRST_ATTACK && _unit->GetAIInterface()->GetNextTarget())
		{
			FIRST_ATTACK = 0;
			Unit * target = NULL;
			target = _unit->GetAIInterface()->GetNextTarget();
			_unit->CastSpell(target, spells[1].info, spells[1].instant);
		}

		else
		{
			float val = (float)RandomFloat(100.0f);
			SpellCast(val);
		}
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	uint32 FIRST_ATTACK;
	int nrspells;
};*/

// Sightless EyeAI
#define CN_SIGHTLESS_EYE 21346	
#define SIGHTLESS_TOUCH 36646
/*class SightlessEyeAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SightlessEyeAI);
	SP_AI_Spell spells[1];
	bool m_spellcheck[1];

    SightlessEyeAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 1;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(SIGHTLESS_TOUCH);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = false;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 10.0f;
		spells[0].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Sargeron HellcallerAI
#define CN_SARGERON_HELLCALLER 20902	
#define HELL_RAIN 36829
#define CURSE_OF_THE_ELEMENTS 36831
#define INCINERATE 36832
/*class SargeronHellcallerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SargeronHellcallerAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    SargeronHellcallerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(HELL_RAIN);
		spells[0].targettype = TARGET_DESTINATION;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 8.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(CURSE_OF_THE_ELEMENTS);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 6.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(INCINERATE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = false;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 11.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Unbound DevastatorAI
#define CN_UNBOUND_DEVASTATOR 20881
#define DEAFENING_ROAR 36887
#define DEVASTATE 36894	// DBC: 36891, 36894;
/*class UnboundDevastatorAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(UnboundDevastatorAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    UnboundDevastatorAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(DEAFENING_ROAR);
		spells[0].targettype = TARGET_VARIOUS;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 7.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(DEVASTATE);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 10.0f;
		spells[1].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Unchained DoombringerAI
// TO DO: Look at charge note
#define CN_UNCHAINED_DOOMBRINGER 20900	
#define AGONIZING_ARMOR 36836
#define WAR_STOMP 36835
#define BERSEKER_CHARGE 36833	// should charge the furthest enemy
/*class UnchainedDoombringerAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(UnchainedDoombringerAI);
	SP_AI_Spell spells[3];
	bool m_spellcheck[3];

    UnchainedDoombringerAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 3;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(AGONIZING_ARMOR);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 9.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(WAR_STOMP);
		spells[1].targettype = TARGET_VARIOUS;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 12.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(BERSEKER_CHARGE);
		spells[2].targettype = TARGET_ATTACKING;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 6.0f;
		spells[2].attackstoptimer = 1000;
	}
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Warder CorpseAI
#define CN_WARDER_CORPSE 21303
#define CORPSE_BURST_WC 36593
#define BLOODY_EXPLOSION_WC 36599
//#define PERMANENT_FEIGN_DEATH_ROOT_WC 31261	// I don't have much infos and I am not sure about how it should work
												// I presume this is just corpse which should cast spell when player is close or attk it
												// so same situation like in Defender Corpse
/*class WarderCorpseAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(WarderCorpseAI);
	SP_AI_Spell spells[2];
	bool m_spellcheck[2];

    WarderCorpseAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 2;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(CORPSE_BURST_WC);
		spells[0].targettype = TARGET_SELF;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

		spells[1].info = dbcSpell.LookupEntry(BLOODY_EXPLOSION_WC);
		spells[1].targettype = TARGET_SELF;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		_unit->CastSpell(_unit, spells[1].info, spells[1].instant);
		_unit->CastSpell(_unit, spells[0].info, spells[0].instant);
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		float val = (float)RandomFloat(100.0f);
		SpellCast(val);
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Sargeron ArcherAI
// Probably to rewrite
#define CN_SARGERON_ARCHER 20901
#define FROST_ARROW	35964 //DBC: 35965, 35964;
#define SHOT_SA 22907
#define RAPID_FIRE 36828
#define SCATTER_SHOT 23601
#define HOOKED_NET 36827
#define IMMOLATION_ARROW 35932	// DBC: 35932, 35935
/*class SargeronArcherAI : public CreatureAIScript
{
public:
    ADD_CREATURE_FACTORY_FUNCTION(SargeronArcherAI);
	SP_AI_Spell spells[6];
	bool m_spellcheck[6];

    SargeronArcherAI(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		nrspells = 6;
		for(int i = 0; i < nrspells; i++)
			m_spellcheck[i] = false;

        spells[0].info = dbcSpell.LookupEntry(FROST_ARROW);
		spells[0].targettype = TARGET_ATTACKING;
		spells[0].instant = true;
		spells[0].cooldown = -1;
		spells[0].perctrigger = 0.0f;
		spells[0].attackstoptimer = 1000;

        spells[1].info = dbcSpell.LookupEntry(SHOT_SA);
		spells[1].targettype = TARGET_ATTACKING;
		spells[1].instant = true;
		spells[1].cooldown = -1;
		spells[1].perctrigger = 0.0f;
		spells[1].attackstoptimer = 1000;

		spells[2].info = dbcSpell.LookupEntry(RAPID_FIRE);
		spells[2].targettype = TARGET_SELF;
		spells[2].instant = true;
		spells[2].cooldown = -1;
		spells[2].perctrigger = 0.0f;
		spells[2].attackstoptimer = 1000;

		spells[3].info = dbcSpell.LookupEntry(SCATTER_SHOT);
		spells[3].targettype = TARGET_ATTACKING;
		spells[3].instant = true;
		spells[3].cooldown = -1;
		spells[3].perctrigger = 0.0f;
		spells[3].attackstoptimer = 1000;

		spells[4].info = dbcSpell.LookupEntry(HOOKED_NET);
		spells[4].targettype = TARGET_VARIOUS;
		spells[4].instant = false;
		spells[4].cooldown = -1;
		spells[4].perctrigger = 6.0f;
		spells[4].attackstoptimer = 1000;

		spells[5].info = dbcSpell.LookupEntry(IMMOLATION_ARROW);
		spells[5].targettype = TARGET_ATTACKING;
		spells[5].instant = false;
		spells[5].cooldown = -1;
		spells[5].perctrigger = 0.0f;
		spells[5].attackstoptimer = 1000;
    }
    
    void OnCombatStart(Unit* mTarget)
    {
		CastTime();
		RegisterAIUpdateEvent(_unit->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME));
    }

	void CastTime()
	{
		for(int i = 0; i < nrspells; i++)
			spells[i].casttime = spells[i].cooldown;
	}

    void OnCombatStop(Unit *mTarget)
    {
		CastTime();
        _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
        _unit->GetAIInterface()->SetAIState(STATE_IDLE);
        RemoveAIUpdateEvent();
    }

    void OnDied(Unit * mKiller)
    {
		CastTime();
       RemoveAIUpdateEvent();
    }

    void AIUpdate()
	{
		if(_unit->GetAIInterface()->GetNextTarget())
		{
			Unit *target = NULL;
			target = _unit->GetAIInterface()->GetNextTarget();
			if(_unit->GetDistance2dSq(target) >= 100.0f && _unit->GetDistanceSq(target) <= 900.0f)
			{
				_unit->GetAIInterface()->m_canMove = false;
				int RangedSpell;
				RandomUInt(1000);
				RangedSpell=rand()%100;
				if(RangedSpell >= 0 && RangedSpell <= 13)
				{
					_unit->CastSpell(target, spells[0].info, spells[0].instant);
					_unit->setAttackTimer(spells[0].attackstoptimer, false);
				}

				if(RangedSpell > 12 && RangedSpell <= 25)
				{
					_unit->CastSpell(target, spells[3].info, spells[3].instant);
					_unit->setAttackTimer(spells[3].attackstoptimer, false);
				}

				if(RangedSpell > 25 && RangedSpell <= 38)
				{
					_unit->CastSpell(target, spells[5].info, spells[5].instant);
					_unit->setAttackTimer(spells[5].attackstoptimer, false);
				}

				if(RangedSpell > 38 && RangedSpell <= 44)
				{
					_unit->CastSpell(target, spells[2].info, spells[2].instant);
					_unit->setAttackTimer(spells[2].attackstoptimer, false);
				}

				if(RangedSpell > 44 && RangedSpell <= 50)
				{
					_unit->CastSpell(target, spells[4].info, spells[4].instant);
					_unit->setAttackTimer(spells[4].attackstoptimer, false);
				}

				else
				{
					_unit->CastSpell(target, spells[1].info, spells[1].instant);
					_unit->setAttackTimer(spells[1].attackstoptimer, false);
				}
			}

			else
			{
				_unit->GetAIInterface()->m_canMove = true;
				if(_unit->GetDistance2dSq(target) < 100.0f)
				{
					float val = (float)RandomFloat(100.0f);
					SpellCast(val);
				}
			}
		}
    }

	void SpellCast(float val)
	{
        if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->GetNextTarget())
        {
			float comulativeperc = 0;
		    Unit *target = NULL;
			for(int i = 0; i < nrspells; i++)
			{
				spells[i].casttime--;
				
				if(m_spellcheck[i])
				{					
					spells[i].casttime = spells[i].cooldown;
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
					}

					if(spells[i].speech != "")
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
						_unit->PlaySoundToSet(spells[i].soundid); 
					}

					m_spellcheck[i] = false;
					return;
				}

				if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
				{
					_unit->setAttackTimer(spells[i].attackstoptimer, false);
					m_spellcheck[i] = true;
				}
				comulativeperc += spells[i].perctrigger;
			}
		}
	}

protected:
	int nrspells;
};*/

// Zereketh the UnboundAI
#define CN_ZEREKETH			20870
#define CN_VOIDZONEARC		21101
#define SEED_OF_C			36123	//32865, 36123
#define SHADOW_NOVA			36127 // 30533, 39005, 36127 (normal mode), 39005 (heroic mode?)
#define SHADOW_NOVA_H		39005
#define CONSUMPTION			30498
#define CONSUMPTION_H		39004
// #define VOID_ZONE 36119	// DBC: 36119; it's not fully functionl without additional core support (for dmg and random place targeting).
class ZerekethAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ZerekethAI, MoonScriptBossAI);

		ZerekethAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(SEED_OF_C, Target_RandomPlayer, 6.0f, 2, 20, 0, 100.0f);

			if(!IsHeroic())
				AddSpell(SHADOW_NOVA, Target_Self, 15, 2, 15);
			else
				AddSpell(SHADOW_NOVA_H, Target_Self, 15, 2, 15);

			AddEmote(Event_OnCombatStart, "Life energy to... consume.", Text_Yell, 11250);
			AddEmote(Event_OnTargetDied, "This vessel...is empty.", Text_Yell, 11251);
			AddEmote(Event_OnTargetDied, "No... more... life.", Text_Yell, 11252);
			AddEmote(Event_OnDied, "The Void... beckons.", Text_Yell, 11255);
		}
		void OnCombatStart(Unit* mTarget)
		{
			VoidTimer = AddTimer((RandomUInt(10) + 30) * 1000);
			SpeechTimer = AddTimer((RandomUInt(10) + 40) * 1000);

			ParentClass::OnCombatStart(mTarget);
		}

		void OnDied(Unit* mKiller)
		{
			//despawn voids
			Creature* creature = NULL;
			for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd();)
			{
				Object* obj = *itr;
				++itr;
				if(obj->IsCreature())
				{
					creature = TO_CREATURE(obj);

					if(creature->GetCreatureInfo()->Id == 21101 && creature->isAlive())
					{
						creature->Despawn(0, 0);
					}
				}
			}

			ParentClass::OnDied(mKiller);
		}

		void Speech()
		{
			switch(RandomUInt(1))
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "The shadow... will engulf you.");
					_unit->PlaySoundToSet(11253);
					break;
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Darkness... consumes all.");
					_unit->PlaySoundToSet(11254);
					break;
			}
			ResetTimer(SpeechTimer, (RandomUInt(10) + 40) * 1000);
		}

		void VoidZoneArc()
		{
			ResetTimer(VoidTimer, (RandomUInt(10) + 30) * 1000);

			std::vector<Player*> TargetTable;
			set< Object* >::iterator Itr = _unit->GetInRangePlayerSetBegin();
			for(; Itr != _unit->GetInRangePlayerSetEnd(); Itr++)
			{
				Player* RandomTarget = NULL;
				if(!(*Itr)->IsPlayer())
					continue;
				RandomTarget = TO< Player* >(*Itr);
				if(RandomTarget && RandomTarget->isAlive() && isHostile(*Itr, _unit))
					TargetTable.push_back(RandomTarget);
			}

			if(!TargetTable.size())
				return;

			size_t RandTarget = rand() % TargetTable.size();

			Player*  RTarget = TargetTable[RandTarget];

			if(!RTarget)
				return;

			float vzX = RandomUInt(5) * cos(RandomFloat(6.28f)) + RTarget->GetPositionX();
			float vzY = RandomUInt(5) * cos(RandomFloat(6.28f)) + RTarget->GetPositionY();
			float vzZ = RTarget->GetPositionZ();
			MoonScriptCreatureAI* VoidZone = SpawnCreature(CN_VOIDZONEARC, vzX, vzY, vzZ);
			VoidZone->GetUnit()->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_2);
			VoidZone->GetUnit()->m_noRespawn = true;
			if(!VoidZone->GetUnit()->IsInWorld())
			{
				VoidZone->Despawn();
				return;
			}
			RTarget = NULL;
			VoidZone->Despawn(60000, 0);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(SpeechTimer))
				Speech();

			if(IsTimerFinished(VoidTimer))
				VoidZoneArc();

			ParentClass::AIUpdate();
		}

	protected:

		int32 SpeechTimer;
		int32 VoidTimer;
};

class VoidZoneARC : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(VoidZoneARC, MoonScriptCreatureAI);
		VoidZoneARC(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			StopMovement();
			SetCanMove(false);
			SetCanEnterCombat(false);
			RegisterAIUpdateEvent(1000);
		};

		void AIUpdate()
		{
			// M4ksiu: I'm not sure if it should be cast once, on start
			uint32 SpellId = CONSUMPTION;
			if(IsHeroic())
				SpellId = CONSUMPTION_H;

			_unit->CastSpell(_unit, SpellId, true);
			RemoveAIUpdateEvent();
		};
};

// Dalliah the DoomsayerAI
#define CN_DALLIAH_THE_DOOMSAYER 20885
#define GIFT_OF_THE_DOOMSAYER 36173 // DBC: 36173
#define WHIRLWIND 36175	// DBC: 36142, 36175
#define HEAL 36144
#define SHADOW_WAVE 39016	// Heroic mode spell
// sounds missing related to Wrath... (look on script below this one)
class DalliahTheDoomsayerAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(DalliahTheDoomsayerAI, MoonScriptBossAI);
		DalliahTheDoomsayerAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(GIFT_OF_THE_DOOMSAYER, Target_Current, 8.0f, 0.0f, -1);

			SpellDesc* WhirlTemp = AddSpell(WHIRLWIND, Target_Self, 15.0f, 0.0f, -1);
			WhirlTemp->AddEmote("Reap the Whirlwind!", Text_Yell, 11089);
			WhirlTemp->AddEmote("I'll cut you to peices!", Text_Yell, 11090);

			SpellDesc* HealTemp = AddSpell(HEAL, Target_Self, 8.0f, 0, -1);
			HealTemp->AddEmote("That is much better.", Text_Yell, 11091);
			HealTemp->AddEmote("Ah, just what I needed.", Text_Yell, 11092);

			if(IsHeroic())
				AddSpell(SHADOW_WAVE, Target_Current, 8.0f, 0, -1);

			AddEmote(Event_OnCombatStart, "It is unwise to anger me.", Text_Yell, 11086);
			AddEmote(Event_OnTargetDied, "Completely ineffective! Just like someone else I know!", Text_Yell, 11087);
			AddEmote(Event_OnTargetDied, "You chose the wrong opponent!", Text_Yell, 11088);
			AddEmote(Event_OnDied, "Now I'm really... angry...", Text_Yell, 11093);
		}

		void OnDied(Unit* mKiller)
		{
			GameObject* door2 = NULL;
			door2 = GetNearestGameObject(184319);
			if(door2 != NULL)
				door2->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

			ParentClass::OnDied(mKiller);
		}

};

// Wrath-Scryer SoccothratesAI
// TO DO: Add moar sounds
#define CN_WRATH_SCRYER_SOCCOTHRATES 20886
#define IMMOLATION 35959 // DBC: 36051, 35959
#define FELFIRE_SHOCK 35759
#define FELFIRE_LINE_UP 35770	// ?
#define KNOCK_AWAY 20686 // DBC: 36512; but it uses it on himself too so changed to other
#define CHARGE 35754 // DBC: 36058, 35754 =( =(
// CHARGE_TARGETING 36038 ?
// There are more sounds connected with Dalliah and some spells, but I don't know situation in which they are used
// so haven't added them.
class WrathScryerSoccothratesAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(WrathScryerSoccothratesAI, MoonScriptBossAI);
		WrathScryerSoccothratesAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(IMMOLATION, Target_Self, 10.0f, 0, -1);
			AddSpell(FELFIRE_SHOCK, Target_Current, 8.0f, 0, -1);
			AddSpell(FELFIRE_LINE_UP, Target_Self, 8.0f, 0, -1);
			AddSpell(KNOCK_AWAY, Target_Destination, 6.0f, 0, -1);
			AddSpell(CHARGE, Target_Current, 4.0f, 0, -1);

			AddEmote(Event_OnCombatStart, "At last, a target for my frustrations!", Text_Yell, 11238);
			AddEmote(Event_OnTargetDied, "Yes, that was quiet... satisfying.", Text_Yell, 11239);
			AddEmote(Event_OnTargetDied, "Ha! Much better!", Text_Yell, 11240);
			AddEmote(Event_OnDied, "Knew this was... the only way out.", Text_Yell, 11243);
		}

		void OnDied(Unit* mKiller)
		{
			GameObject* door1 = NULL;
			door1 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(199.969f, 118.5837f, 22.379f, 184318);
			if(door1 != NULL)
				door1->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

			ParentClass::OnDied(mKiller);
		}

};

// Harbinger SkyrissAI
// Full event must be scripted for this guy.
#define CN_HARBRINGER_SKYRISS 20912
#define MIND_REND 36924 // DBC: 36859, 36924;
#define FEAR 39415
#define DOMINATION 37162
#define SUMMON_ILLUSION_66 36931	// those 2 don't work
#define SUMMON_ILLUSION_33 36932
// BLINK_VISUAL 36937 ?
// SIMPLE_TELEPORT 12980 ?
// Add sounds related to his dialog with mind controlled guy
class HarbringerSkyrissAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(HarbringerSkyrissAI, MoonScriptBossAI);

		HarbringerSkyrissAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(MIND_REND, Target_Current, 15.0f, 0, -1);

			SpellDesc* Fear = AddSpell(FEAR, Target_Current, 8.0f, 0, -1);
			Fear->AddEmote("Flee in terror!", Text_Yell, 11129);
			Fear->AddEmote("I will show you horrors undreamed of.", Text_Yell, 11130);

			SpellDesc* Domination = AddSpell(DOMINATION, Target_Current, 6.0f, 0, -1);
			Domination->AddEmote("You will do my bidding, weakling.", Text_Yell, 11127);
			Domination->AddEmote("Your will is no longer your own.", Text_Yell, 11128);

			Illusion66 = AddSpell(SUMMON_ILLUSION_66, Target_Self, 0, 0, -1, 0, 0, false, "", Text_Yell, 11131);
			Illusion66->mEnabled = false;

			Illusion33 = AddSpell(SUMMON_ILLUSION_33, Target_Self, 0, 0, -1, 0, 0, false, "",  Text_Yell, 11131);
			Illusion33->mEnabled = false;

			AddEmote(Event_OnCombatStart, "Bear witness to the agent of your demise!", Text_Yell, 11123);
			AddEmote(Event_OnTargetDied, "Your fate is written!", Text_Yell, 11124);
			AddEmote(Event_OnTargetDied, "The chaos I have sown here is but a taste....", Text_Yell, 11125);
			AddEmote(Event_OnDied, "I am merely one of... infinite multitudes.", Text_Yell, 11126);

			IllusionCount = 0;
		}

		void OnCombatStart(Unit* mTarget)
		{
			IllusionCount = 0;
			ParentClass::OnCombatStart(mTarget);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 66 && IllusionCount == 0)
			{
				IllusionCount = 1;
				CastSpell(Illusion66);
			}
			else if(GetHealthPercent() <= 33 && IllusionCount == 1)
			{
				IllusionCount = 2;
				CastSpell(Illusion33);
			}
			ParentClass::AIUpdate();
		}


	protected:

		uint32 IllusionCount;
		SpellDesc* Illusion66;
		SpellDesc* Illusion33;
};

// Warden Mellichar
#define CN_WARDEN_MELLICHAR 20904
#define BLAZING_TRICKSTER 20905
#define WARP_STALKER 20906
#define AKKIRIS_LIGHTNING_WAKER 20908
#define SULFURON_MAGMA_THROWER 20909
#define TWILIGHT_DRAKONAAR 20910
#define BLACKWING_DRAKONAAR 20911
#define MILLHOUSE_MANASTORM 20977
class WardenMellicharAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(WardenMellicharAI, MoonScriptBossAI);
		WardenMellicharAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			SetCanMove(false);
			Phase_Timer = -1;
			SetPhase(0);
			Spawncounter = 0;
			NPC_orb1 = NULL;
			NPC_orb2 = NULL;
			NPC_orb3 = NULL;
			NPC_orb4 = NULL;
			NPC_orb5 = NULL;
			shield = NULL;
			orb1 = NULL;
			orb2 = NULL;
			orb3 = NULL;
			orb4 = NULL;
		}

		void OnCombatStart(Unit* mTarget)
		{
			SetPhase(0);
			Phasepart = 0;
			SetCanMove(false);
			Phase_Timer = AddTimer(55000);

			SetCanEnterCombat(false);
			_unit->SetEmoteState(EMOTE_ONESHOT_READY1H); // to be replaced for the standstate

			shield = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(445.786f, -169.263f, 43.0466f, 184802);
			if(shield)
				shield->SetByte(GAMEOBJECT_BYTES_1, 0, 1);

			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "I knew the prince would be angry but, I... I have not been myself. I had to let them out! The great one speaks to me, you see. Wait--outsiders. Kael'thas did not send you! Good... I'll just tell the prince you released the prisoners!");
			_unit->PlaySoundToSet(11222);
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "The naaru kept some of the most dangerous beings in existence here in these cells. Let me introduce you to another...", 27000);
			sEventMgr.AddEvent(TO_OBJECT(_unit), &Object::PlaySoundToSet, (uint32)11223, EVENT_UNK, 27000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

			ParentClass::OnCombatStart(mTarget);
		}

		void OnCombatStop(Unit* mTarget)
		{
			Reset_Event();
			ParentClass::OnCombatStop(mTarget);
		}

		void AIUpdate()
		{
			SetCanEnterCombat(false);
			SetCanMove(false);
			SetAllowMelee(false);
			SetAllowSpell(false);

			// ORB ONE
			if(IsTimerFinished(Phase_Timer) && GetPhase() == 0)
			{
				if(Phasepart == 0)
				{
					Spawncounter = 0;
					orb1 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(482.929f, -151.114f, 43.654f, 183961);
					if(orb1)
						orb1->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

					switch(RandomUInt(1))
					{
							NPC_ID_Spawn = 0;
						case 0:
							NPC_ID_Spawn = BLAZING_TRICKSTER;
							break;
						case 1:
							NPC_ID_Spawn = WARP_STALKER;
							break;
					}
					ResetTimer(Phase_Timer, 8000);
					Phasepart = 1;
					return;
				}

				else if(Phasepart == 1)
				{
					if(!NPC_orb1 && NPC_ID_Spawn != 0 && Spawncounter == 0)
					{
						++Spawncounter;
						NPC_orb1 = SpawnCreature(NPC_ID_Spawn, 475.672f, -147.086f, 42.567f, 3.184015f);
						return;
					}
					else if(NPC_orb1 && !NPC_orb1->IsAlive())
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Yes, yes... another! Your will is mine! Behold another terrifying creature of incomprehensible power!");
						_unit->PlaySoundToSet(11224);
						SetPhase(1);
						Phasepart = 0;
						ResetTimer(Phase_Timer, 6000);
						return;
					}
					else
					{
						return;
					}
					return;
				}
				//return;
			}

			// ORB TWO
			else if(IsTimerFinished(Phase_Timer) && GetPhase() == 1)
			{
				if(Phasepart == 0)
				{
					Spawncounter = 0;
					orb2 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(409.062f, -152.161f, 43.653f, 183963);
					if(orb2)
						orb2->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

					ResetTimer(Phase_Timer, 8000);
					Phasepart = 1;
					return;
				}

				else if(Phasepart == 1)
				{
					if(!NPC_orb2 && Spawncounter == 0)
					{
						++Spawncounter;
						NPC_orb2 = SpawnCreature(MILLHOUSE_MANASTORM, 413.192f, -148.586f, 42.569f, 0.024347f);
						return;
					}
					else if(NPC_orb2 && NPC_orb2->IsAlive())
					{
						Unit* millhouse = TO_UNIT(ForceCreatureFind(MILLHOUSE_MANASTORM));
						if(millhouse)
						{
							millhouse->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Where in Bonzo's brass buttons am I? And who are-- yaaghh, that's one mother of a headache!", 2000);
							sEventMgr.AddEvent(TO_OBJECT(millhouse), &Object::PlaySoundToSet, (uint32)11171, EVENT_UNK, 2000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

							_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "What is this? A lowly gnome? I will do better, oh great one.", 13000);
							sEventMgr.AddEvent(TO_OBJECT(_unit), &Object::PlaySoundToSet, (uint32)11226, EVENT_UNK, 13000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

							millhouse->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Lowly? Nobody refers to the mighty Millhouse Manastorm as lowly! I have no idea what goes on here, but I will gladly join your fight against this impudent imbecile!", 22000);
							sEventMgr.AddEvent(TO_OBJECT(millhouse), &Object::PlaySoundToSet, (uint32)11172, EVENT_UNK, 22000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
						}
						SetPhase(2);
						Phasepart = 0;
						ResetTimer(Phase_Timer, 25000);
						return;
					}
					else
					{
						return;
					}
					return;

				}
				//return;
			}

			// ORB THREE
			else if(IsTimerFinished(Phase_Timer) && GetPhase() == 2)
			{
				if(Phasepart == 0)
				{
					Spawncounter = 0;
					orb3 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(415.167f, -174.338f, 43.654f, 183964);
					if(orb3)
						orb3->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

					switch(RandomUInt(1))
					{
							NPC_ID_Spawn = 0;
						case 0:
							NPC_ID_Spawn = SULFURON_MAGMA_THROWER;
							break;
						case 1:
							NPC_ID_Spawn = AKKIRIS_LIGHTNING_WAKER;
							break;
					}
					ResetTimer(Phase_Timer, 8000);
					Phasepart = 1;
					return;
				}

				else if(Phasepart == 1)
				{
					if(!NPC_orb3 && NPC_ID_Spawn != 0 && Spawncounter == 0)
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "1");
						++Spawncounter;
						NPC_orb3 = SpawnCreature(NPC_ID_Spawn, 420.050f, -173.500f, 42.580f, 6.110f);
						return;
					}
					else if(!NPC_orb3)
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "2");
						NPC_orb3 = GetNearestCreature(NPC_ID_Spawn);
					}
					else if(NPC_orb3 && !NPC_orb3->IsAlive())
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Anarchy! Bedlam! Oh, you are so wise! Yes, I see it now, of course!");
						_unit->PlaySoundToSet(11227);
						SetPhase(3);
						Phasepart = 0;
						ResetTimer(Phase_Timer, 8000);
						return;
					}
					else
					{
						return;
					}
					return;
				}
				//return;
			}

			// ORB FOUR
			else if(IsTimerFinished(Phase_Timer) && GetPhase() == 3)
			{
				if(Phasepart == 0)
				{
					Spawncounter = 0;
					orb4 = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(476.422f, -174.517f, 42.748f, 183962);
					if(orb4)
						orb4->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

					switch(RandomUInt(1))
					{
							NPC_ID_Spawn = 0;
						case 0:
							NPC_ID_Spawn = TWILIGHT_DRAKONAAR;
							break;
						case 1:
							NPC_ID_Spawn = BLACKWING_DRAKONAAR;
							break;
					}
					ResetTimer(Phase_Timer, 8000);
					Phasepart = 1;
					return;
				}

				else if(Phasepart == 1)
				{
					if(!NPC_orb4 && NPC_ID_Spawn != 0 && Spawncounter == 0)
					{
						++Spawncounter;
						NPC_orb4 = SpawnCreature(NPC_ID_Spawn, 471.153f, -174.715f, 42.589f, 3.097f);
						return;
					}
					else if(!NPC_orb4)
					{
						NPC_orb4 = GetNearestCreature(NPC_ID_Spawn);
					}
					else if(NPC_orb4 && !NPC_orb4->IsAlive())
					{
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Yes, O great one, right away!");
						_unit->PlaySoundToSet(11228);
						SetPhase(4);
						Phasepart = 0;
						ResetTimer(Phase_Timer, 6000);
						return;
					}
					else
					{
						return;
					}
					return;
				}
				//return;
			}

			else if(IsTimerFinished(Phase_Timer) && GetPhase() == 4)
			{

			}

			ParentClass::AIUpdate();
			SetCanMove(false);
			SetAllowMelee(false);
			SetAllowSpell(false);

		}

		void Reset_Event()
		{
			SetCanMove(true);
			SetAllowMelee(true);
			SetAllowSpell(true);
			_unit->SetEmoteState(8); // to be replaced for the standstate

			if(shield)
				shield->SetByte(GAMEOBJECT_BYTES_1, 0, 0);

			if(orb1)
				orb1->SetByte(GAMEOBJECT_BYTES_1, 0, 1);

			if(orb2)
				orb2->SetByte(GAMEOBJECT_BYTES_1, 0, 1);

			if(orb3)
				orb3->SetByte(GAMEOBJECT_BYTES_1, 0, 1);

			if(orb4)
				orb4->SetByte(GAMEOBJECT_BYTES_1, 0, 1);

			if(NPC_orb1)
			{
				NPC_orb1->Despawn(0);
				NPC_orb1 = NULL;
			}

			if(NPC_orb2)
			{
				NPC_orb2->Despawn(0);
				NPC_orb2 = NULL;
			}

			if(NPC_orb3)
			{
				NPC_orb3->Despawn(0);
				NPC_orb3 = NULL;
			}

			if(NPC_orb4)
			{
				NPC_orb4->Despawn(0);
				NPC_orb4 = NULL;
			}

			if(NPC_orb5)
			{
				NPC_orb5->Despawn(0);
				NPC_orb5 = NULL;
			}

		}

	protected:

		uint32 Phasepart;
		uint32 NPC_ID_Spawn;
		uint32 Spawncounter;
		int32 Phase_Timer;

		MoonScriptCreatureAI*	NPC_orb1;
		MoonScriptCreatureAI*	NPC_orb2;
		MoonScriptCreatureAI*	NPC_orb3;
		MoonScriptCreatureAI*	NPC_orb4;
		MoonScriptCreatureAI*	NPC_orb5;
		GameObject* shield;
		GameObject* orb1;
		GameObject* orb2;
		GameObject* orb3;
		GameObject* orb4;


};

void SetupArcatraz(ScriptMgr* mgr)
{
	//mgr->register_creature_script(CN_ARCATRAZ_DEFENDER, &ArcatrazDefenderAI::Create);
	//mgr->register_creature_script(CN_ARCATRAZ_SENTINEL, &ArcatrazSentinelAI::Create);
	//mgr->register_creature_script(CN_ARCATRAZ_WARDER, &ArcatrazWarderAI::Create);
	//mgr->register_creature_script(CN_BLACKWING_DRAKONAAR, &BlackwingDrakonaarAI::Create);
	//mgr->register_creature_script(CN_BLACKWING_TRICKSTER, &BlackwingTricksterAI::Create);
	//mgr->register_creature_script(CN_DEATH_WATCHER, &DeathWatcherAI::Create);
	//mgr->register_creature_script(CN_DEFENDER_CORPSE, &DefenderCorpseAI::Create);
	//mgr->register_creature_script(CN_PROTEAN_SPAWN, &ProteanSpawnAI::Create);
	//mgr->register_creature_script(CN_ENTROPIC_EYE, &EntropicEyeAI::Create);
	//mgr->register_creature_script(CN_EREDAR_DEATHBRINGER, &EredarDeathbringerAI::Create);
	//mgr->register_creature_script(CN_EREDAR_SOUL_EATER, &EredarSoulEaterAI::Create);
	//mgr->register_creature_script(CN_ETHEREUM_LIFE_BINDER, &EthereumLifeBinderAI::Create);
	//mgr->register_creature_script(CN_ETHEREUM_SLAYER, &EthereumSlayerAI::Create);
	//mgr->register_creature_script(CN_ETHEREUM_WAVE_CASTER, &EthereumWaveCasterAI::Create);
	//mgr->register_creature_script(CN_GARGANTUAN_ABYSSAL, &GargantuanAbyssalAI::Create);
	//mgr->register_creature_script(CN_GREATER_FIRE_ELEMENTAL, &GreaterFireElementalAI::Create);
	//mgr->register_creature_script(CN_IRONJAW, &IronjawAI::Create);
	//mgr->register_creature_script(CN_MILLHOUSE_MANASTORM, &MillhouseManastormAI::Create);
	//mgr->register_creature_script(CN_NEGATON_SCREAMER, &NegatonScreamerAI::Create);
	//mgr->register_creature_script(CN_NEGATON_WARP_MASTER, &NegatonWarpMasterAI::Create);
	//mgr->register_creature_script(CN_NEGATON_FIELD, &NegatonFieldAI::Create);
	//mgr->register_creature_script(CN_PHASE_HUNTER, &PhaseHunterAI::Create);
	//mgr->register_creature_script(CN_PROTEAN_HORROR, &ProteanHorrorAI::Create);
	//mgr->register_creature_script(CN_PROTEAN_NIGHTMARE, &ProteanNightmareAI::Create);

	//mgr->register_creature_script(CN_SULFURON_MAGMA_THROWER, &SulfuronMagmaThrowerAI::Create);
	//mgr->register_creature_script(CN_SPITEFUL_TEMPTRESS, &SpitefulTemptressAI::Create);
	//mgr->register_creature_script(CN_SOUL_DEVOURER, &SoulDevourerAI::Create);
	//mgr->register_creature_script(CN_SOLOMON, &SolomonAI::Create);
	//mgr->register_creature_script(CN_SKULKING_WITCH, &SkulkingWitchAI::Create);
	//mgr->register_creature_script(CN_SIGHTLESS_EYE, &SightlessEyeAI::Create);
	//mgr->register_creature_script(CN_SARGERON_HELLCALLER, &SargeronHellcallerAI::Create);
	//mgr->register_creature_script(CN_UNBOUND_DEVASTATOR, &UnboundDevastatorAI::Create);
	//mgr->register_creature_script(CN_UNCHAINED_DOOMBRINGER, &UnchainedDoombringerAI::Create);
	//mgr->register_creature_script(CN_WARDER_CORPSE, &WarderCorpseAI::Create);
	//mgr->register_creature_script(CN_SARGERON_ARCHER, &SargeronArcherAI::Create);

	mgr->register_creature_script(CN_ZEREKETH, &ZerekethAI::Create);
	mgr->register_creature_script(CN_VOIDZONEARC, &VoidZoneARC::Create);

	mgr->register_creature_script(CN_DALLIAH_THE_DOOMSAYER, &DalliahTheDoomsayerAI::Create);
	mgr->register_creature_script(CN_WRATH_SCRYER_SOCCOTHRATES, &WrathScryerSoccothratesAI::Create);
	mgr->register_creature_script(CN_HARBRINGER_SKYRISS, &HarbringerSkyrissAI::Create);
	//mgr->register_creature_script(CN_WARDEN_MELLICHAR, &WardenMellicharAI::Create);
}