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

class AllianceGryphon : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AllianceGryphon);
	AllianceGryphon(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		if(!mTarget->IsPlayer())
			return;

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9526, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);

		NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9526, _unit->GetPositionX() - RandomFloat(5.0f), _unit->GetPositionY() - RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);
	}
};

class AllianceHippogryph : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AllianceHippogryph);
	AllianceHippogryph(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		if(!mTarget->IsPlayer())
			return;

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9527, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);

		NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9527, _unit->GetPositionX() - RandomFloat(5.0f), _unit->GetPositionY() - RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);
	}
};

class HordeWyvern : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(HordeWyvern);
	HordeWyvern(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		if(!mTarget->IsPlayer())
			return;

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9297, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);

		NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9297, _unit->GetPositionX() - RandomFloat(5.0f), _unit->GetPositionY() - RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);
	}
};

class HordeBat : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(HordeBat);
	HordeBat(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		if(!mTarget->IsPlayer())
			return;

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9521, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);

		NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9521, _unit->GetPositionX() - RandomFloat(5.0f), _unit->GetPositionY() - RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(360000, 0);
	}
};

class DragonhawkMasters : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(DragonhawkMasters)
	DragonhawkMasters(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		LocationVector vect(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
		for(int i = 0; i < 2; ++i)
		{
			vect.x += RandomFloat(2.0f);
			vect.y += RandomFloat(2.0f);
			Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(27946, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(360000, 0);
		}
	}
};

class NeutralMasters : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(NeutralMasters)
	NeutralMasters(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		LocationVector vect(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
		for(int i = 0; i < 2; ++i)
		{
			vect.x += RandomFloat(2.0f);
			vect.y += RandomFloat(2.0f);
			Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(9526+i, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
			if(NewCreature != NULL)
				NewCreature->Despawn(360000, 0);
		}
	}
};

///////////////////////////////////////////////////////////
//D.I.S.C.O AI Script ( entry 27989 )
//"Dancer's Integrated Sonic Celebration Oscillator"
//
//Behavior
//  On spawn it casts 2 spells, which
//  - summon the dancefloor
//  - applies a periodic aura that plays the music
//
//
//////////////////////////////////////////////////////////
class DISCO : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DISCO);
		DISCO(Creature* c) : CreatureAIScript(c) {}

		void OnLoad()
		{
			_unit->CastSpell(_unit, 50487, false); // summon disco dancefloor
			_unit->CastSpell(_unit, 50314, false); // play the music
		}
};

void SetupMiscCreatures(ScriptMgr* mgr)
{
	// Gryphon Master
	uint32 GryphonMasterIds[] = { 352, 523, 931, 1571, 1572, 1573, 2299, 2409, 2432, 2835, 2859,
	2941, 4321, 7823, 8018, 8609, 12596, 12617, 16822, 17209, 18809, 18931, 18939, 19181, 20234,
	21107, 6326, 6327, 24366, 23704, 26879, 23736, 23859, 24061, 26876, 26877, 226878, 26880, 0 };
	mgr->register_creature_script(GryphonMasterIds, &AllianceGryphon::Create);

	// Hippogryph Master
	uint32 HippogryphMasterIds[] = { 3838, 3841, 4267, 4319, 4407, 6706, 8019, 10897, 11138, 11800, 12577, 12578,
	15177, 17554, 17555, 18785, 18788, 18789, 18937, 22485, 22935, 22936, 22937, 26881, 30271, 0 };
	mgr->register_creature_script(HippogryphMasterIds, &AllianceHippogryph::Create);

	// Wyvern Master
	uint32 WyvernMasterIds[] = { 1387, 2851, 2858, 2861, 2995, 3305, 3310, 3615, 4312, 4314, 4317, 6026, 6726,
	7824, 8020, 8610, 10378, 11139, 11899, 11900, 11901, 12616, 12740, 13177,
	15178, 16587, 18791, 18807, 18808, 18930, 18942, 18953, 19317, 19558, 20762,
	24032, 25288, 26566, 26846, 26847, 26848, 26850, 26852, 26853, 29762, 31426, 0 };
	mgr->register_creature_script(WyvernMasterIds, &HordeWyvern::Create);

	// Bat Master
	uint32 BatMasterIds[] = { 2226, 2389, 4551, 12636, 3575, 23816, 24155, 26844, 26845, 27344, 27842, 37915, 0 };
	mgr->register_creature_script(BatMasterIds, &HordeBat::Create);

	// Dragonhawk Masters
	uint32 DragonhawkMasterIds[] = { 16189, 16192, 26560, 30269, 0 };
	mgr->register_creature_script(DragonhawkMasterIds, &DragonhawkMasters::Create);

	// Neutral Masters
	uint32 NeutralMasterIds[] = { 10583, 11798, 11800, 16227, 18938, 18940, 19581, 19583, 20515,
	21766, 22216, 22455, 22931, 23612, 24851, 29480, 26851, 27046, 28037, 28195, 28196, 28197,
	28574, 28615, 28618, 28621, 28623, 28624, 28674, 29137, 29721, 29749, 29750, 29757, 29950,
	29951, 29952, 30314, 30433, 30569, 30869, 30870, 31069, 31078, 32571, 33849, 37888, 0 };
	mgr->register_creature_script(NeutralMasterIds, &NeutralMasters::Create);

	mgr->register_creature_script(27989, &DISCO::Create);
}