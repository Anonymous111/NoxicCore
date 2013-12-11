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

#include "../Setup.h"

/*class ChampionVranesh : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ChampionVranesh);
	ChampionVranesh(Creature* pCreature) : CreatureAIScript(pCreature) {}

    //Just before taking off to patrol the Royal Exchange, Vranesh walks up to Champion Bachi and bows before him. He then leaves the building and mounts up.

    //Emote: Champion Vranesh inclines his head slightly to the pair of guardians in greeting.

    //Upon arriving at the guards in front of the bank:

    //Emote: Champion Vranesh arches a sculpted brow at the guards, a disapproving scowl on his face.

    //Upon arriving at the guards in front of the jewelcrafters:

    //Emote: Champion Vranesh glances from guard to guard.

    //Upon arriving at Farstrider ranger practice grounds:

    //Emote: Champion Vranesh surveys the small ranger practice ground with a condescending smirk.

    //The guards will respond with some of the following after each of his emotes:

    //Silvermoon City Guardian says: Our lives are yours, Blood Knight.
    //Silvermoon City Guardian says: Glory to the Sun K-- ah... Silvermoon!
    //Silvermoon City Guardian says: Your power strengthens us all.

	//He is also known to be mounted on a blood elf paladin's charger

};*/

class BloodKnightStillblade : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BloodKnightStillblade);
	BloodKnightStillblade(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void Reset()
	{
		if(active)
		{
			_unit->SetPosition(_unit->GetSpawnX(), _unit->GetSpawnY(), _unit->GetSpawnZ(), _unit->GetSpawnO(), true);
			lifetimer = 120000;
			timediff = UNIXTIME;
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
			_unit->SetStandState(STANDSTATE_DEAD);
			_unit->setDeathState(CORPSE);
			_unit->GetAIInterface()->setCanMove(false);
		}
	}

	void OnLoad()
	{
		if(unit->m_spawn)
		{
			active = true;
			Reset();
		}
	}

	void AIUpdate(MapManagerScript* MMScript, uint32 p_time)
	{
		if(active)
		{
			uint32 diff = UNIXTIME - timediff;
			if(_unit->GetStandState() == STANDSTATE_STAND)
			{
				if(lifetimer < diff)
					Reset();
			}
		}
	}

protected:
	Creature* BKStillblade
	uint32 lifetimer;
	uint32 timediff;
	bool active;
};

class LordDawnstar : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(LordDawnstar);
		LordDawnstar(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
			_unit->SetStandState(7);
			_unit->setDeathState(CORPSE);
			_unit->GetAIInterface()->m_canMove = false;
		}
};

void SetupZoneSilvermoonCity(ScriptMgr* mgr)
{
	mgr->register_creature_script(18146, &ChampionVranesh::Create);
	mgr->register_creature_script(17768, &BloodKnightStillblade::Create);
	mgr->register_creature_script(17832, &LordDawnstar::Create);
}