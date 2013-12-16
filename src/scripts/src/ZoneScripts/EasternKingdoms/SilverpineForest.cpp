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

#include "../Setup.h"

class CorruptMinorManifestationWater : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CorruptMinorManifestationWater);
	CorruptMinorManifestationWater(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		float SSX = _unit->GetPositionX();
		float SSY = _unit->GetPositionY();
		float SSZ = _unit->GetPositionZ();
		float SSO = _unit->GetOrientation();

		Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(5895, SSX, SSY + 1, SSZ, SSO, true, false, 0, 0);
		if(NewCreature != NULL)
			NewCreature->Despawn(600000, 0);
	}
};

class Deathstalker_Erland : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Deathstalker_Erland);
		Deathstalker_Erland(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == 9)
			{
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Thanks, you helped me to overcome this obstacle");
				_unit->Despawn(5000, 1000);
				sEAS.DeleteWaypoints(_unit);
				if(_unit->m_escorter == NULL)
					return;
				Player* pPlayer = _unit->m_escorter;
				_unit->m_escorter = NULL;
				pPlayer->GetQuestLogForEntry(435)->SendQuestComplete();
			}
		}
};

class Nightlash : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Nightlash);
	Nightlash(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			Player* mPlayer = TO_PLAYER(mKiller);

			if(!_unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(1069.889404f, 1544.777558f, 28.331335f, 1983) && (rand() % 5 > 2) && mPlayer->GetQuestLogForEntry(437)) //random number I picked between 2-8
			{
				_unit->GetMapMgr()->GetInterface()->SpawnCreature(1983, 1069.889404f, 1544.777558f, 28.331335f, 3.99f, true, false, 0, 0)->Despawn(600000, 0);
				_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Nightlash avenge us!!");//not sure this is 100% blizzlike, but looks nice
			}
		}
	}
};

class ProveYourWorthQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ProveYourWorthQAI);
	ProveYourWorthQAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnDied(Unit* mKiller)
	{
		if(mKiller->IsPlayer())
		{
			QuestLogEntry* pQuest = (TO_PLAYER(mKiller))->GetQuestLogForEntry(421);
			if(pQuest && pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
				return;
			}
		}
	}
};

void SetupZoneSilverpineForest(ScriptMgr* mgr)
{
	mgr->register_creature_script(5894, &CorruptMinorManifestationWater::Create);
	mgr->register_creature_script(1978, &Deathstalker_Erland::Create);
	mgr->register_creature_script(1773, &Nightlash::Create);
	mgr->register_creature_script(1772, &Nightlash::Create);
	mgr->register_creature_script(1769, &ProveYourWorthQAI::Create);
}