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

class YennikuAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(YennikuAI);
	YennikuAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 28);
	}
	/*
    	Ana'thek the Cruel says: You stay back! Da troll is mine!

    	Yenniku says: Zanzil is creating an army that will wash over all of Stranglethorn! Bloodscalps, Skullsplitter, Gurubashi and Horde...all will serve Zanzil!
    */
};

class NegolashAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(NegolashAI);

		NegolashAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
		}
		void OnDied(Unit* mKiller)
		{
			_unit->Despawn(180000, 0);
			RemoveAIUpdateEvent();
		}
};

class Beka : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Beka);
		Beka(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				Player* mPlayer = TO_PLAYER(mKiller);
				Creature*  beka1 = sEAS.SpawnCreature(mPlayer, 1516, -13770.5f, -6.79f, 42.8f, 5.7f , 0);
				beka1->GetAIInterface()->MoveTo(-13727.8f, -26.2f, 46.15f, 4.07f);
				beka1->Despawn(10 * 60 * 1000, 0);
			}
			else
			{
				Player* mPlayer = _unit->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());
				if(mPlayer)
				{
					Creature*  beka1 = sEAS.SpawnCreature(mPlayer, 1516, -13770.5f, -6.79f, 42.8f, 5.7f , 0);
					beka1->GetAIInterface()->MoveTo(-13727.8f, -26.2f, 46.15f, 4.07f);
					beka1->Despawn(10 * 60 * 1000, 0);
				}
			}
		}
};

class Beka1 : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Beka1);
		Beka1(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				Player* mPlayer = TO_PLAYER(mKiller);
				Creature* beka1 = sEAS.SpawnCreature(mPlayer, 1514, -13770.5f, -6.79f, 42.8f, 5.7f, 0);
				beka1->GetAIInterface()->MoveTo(-13727.8f, -26.2f, 46.15f, 4.07f);
				beka1->Despawn(10 * 60 * 1000, 0);
			}
			else
			{
				Player* mPlayer = _unit->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());
				if(mPlayer)
				{
					Creature* beka1 = sEAS.SpawnCreature(mPlayer, 1514, -13770.5f, -6.79f, 42.8f, 5.7f, 0);
					beka1->GetAIInterface()->MoveTo(-13727.8f, -26.2f, 46.15f, 4.07f);
					beka1->Despawn(10 * 60 * 1000, 0);
				}
			}
		}
};

class Beka2 : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Beka2);
		Beka2(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			float SSX = mKiller->GetPositionX();
			float SSY = mKiller->GetPositionY();
			float SSZ = mKiller->GetPositionZ();

			Creature* doctor = mKiller->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 1449);
			if(doctor)
				doctor->Emote(EMOTE_ONESHOT_CHEER);
		}
};

void SetupZoneStranglethorn(ScriptMgr* mgr)
{
	mgr->register_creature_script(2530, &YennikuAI::Create);
	mgr->register_creature_script(1511, &Beka::Create);
	mgr->register_creature_script(1516, &Beka1::Create);
}