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

class ThreatFromAboveQAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ThreatFromAboveQAI);
		ThreatFromAboveQAI(Creature* pCreature) : CreatureAIScript(pCreature)	{}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(11096);
				if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = pQuest->GetMobCount(0) + 1;
					pQuest->SetMobCount(0, newcount);
					pQuest->SendUpdateAddKill(0);
					pQuest->UpdatePlayerFields();
					return;
				}
			}
		}
};

class TheInfestedProtectorsQAI : public CreatureAIScript
{
	public:

		ADD_CREATURE_FACTORY_FUNCTION(TheInfestedProtectorsQAI);
		TheInfestedProtectorsQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				Player * plr = TO_PLAYER(mKiller);
				if(plr->GetQuestLogForEntry(10896))
				{
					if(Rand(90))
					{
						uint32 min,max,finall;
						switch(_unit->GetEntry())
						{
							case 22307:
								min = 4; max = 11;
								break;
							case 22095:
								min = 2; max = 5;
								break;
						}

						finall = min + RandomUInt(max - min);

						float SSX = _unit->GetPositionX();
						float SSY = _unit->GetPositionY();
						float SSZ = _unit->GetPositionZ();
						float SSO = _unit->GetOrientation();

						for(uint8 i = 0; i < finall; i++)
						{
							Creature * NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(22419, SSX + RandomFloat(3.0f), SSY + RandomFloat(3.0f), SSZ, SSO + RandomFloat(1.0f), true, false, 0, 0);
							if ( NewCreature != NULL )
								NewCreature->Despawn(120000, 0);
						}
					}
				}
			}
		}
};

class TakenInTheNight : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(TakenInTheNight);

		TakenInTheNight(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->GetAIInterface()->m_canMove = false;
			_unit->GetAIInterface()->disable_combat = true;
		}

		void OnDied(Unit* mKiller)
		{
			if(!mKiller->IsPlayer())
				return;

			Player* plr = TO_PLAYER(mKiller);
			uint8 chance = (uint8)RandomUInt(5);
			uint32 spawn = 0;

			switch(chance)
			{
				case 0:
				case 1:
					spawn = 22459; //Freed Shat'ar Warrior
					break;

				case 2:
					spawn = 21661; //Cabal Skirmisher
					break;

				case 3:
					spawn = 16805; //Broken Skeleton
					break;

				case 4:
					spawn = 18470; //Bonelasher
					break;

				case 5:
					spawn = 22045; //Vengeful Husk
					break;
			}

			Creature* creat = sEAS.SpawnCreature(plr, spawn, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 1 * 60 * 1000);

			if(spawn != 22459)
				return;

			creat->GetAIInterface()->m_canMove = false;
			creat->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Finally! I'm free!");

			QuestLogEntry* pQuest = plr->GetQuestLogForEntry(10873);
			if(pQuest == NULL)
				return;

			if(pQuest->GetMobCount(0) == pQuest->GetQuest()->required_mobcount[0])
				return;

			pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
			pQuest->SendUpdateAddKill(0);
			pQuest->UpdatePlayerFields();
		}
};

class AnImproperBurial : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(AnImproperBurial);

		AnImproperBurial(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->SetStandState(7);
			_unit->setDeathState(CORPSE);
			_unit->GetAIInterface()->m_canMove = false;
		}
};

void SetupZoneTerrokarForest(ScriptMgr* mgr)
{
	mgr->register_creature_script(22144, &ThreatFromAboveQAI::Create);
	mgr->register_creature_script(22143, &ThreatFromAboveQAI::Create);
	mgr->register_creature_script(22148, &ThreatFromAboveQAI::Create);
	mgr->register_creature_script(22355, &TakenInTheNight::Create);
	mgr->register_creature_script(21859, &AnImproperBurial::Create);
	mgr->register_creature_script(21846, &AnImproperBurial::Create);
	mgr->register_creature_script(22307, &TheInfestedProtectorsQAI::Create);
	mgr->register_creature_script(22095, &TheInfestedProtectorsQAI::Create);
}