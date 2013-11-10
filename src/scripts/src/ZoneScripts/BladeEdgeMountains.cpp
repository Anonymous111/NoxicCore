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
#include "../Common/EasyFunctions.h"

class NihilTheBanished : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(NihilTheBanished)
	NihilTheBanished(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		RegisterAIUpdateEvent(5000);
		_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
		_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		_unit->GetAIInterface()->disable_melee = true;
		_unit->GetAIInterface()->m_canMove = false;

		sEAS.EventSay(_unit, "Muahahahahaha! You fool! you've released me from my banishment in the interstices between space and time!", 5000);
		sEAS.EventSay(_unit, "All of Draenor shall quake beneath my feet! I Will destroy this world and reshape it in my image!", 10000);
		sEAS.EventSay(_unit, "Where shall I Begin? I cannot bother myself with a worm such as yourself. There's a World to be Conquered!", 15000);
		sEAS.EventSay(_unit, "No doubt the fools that banished me are long dead. I shall take the wing and survey my new demesne, Pray to whatever gods you hold dear that we do not meet again.", 20000);

		_unit->Despawn(25000, 0);
	}
};

class ThukTheDefiant : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ThukTheDefiant)
	ThukTheDefiant(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->SetScale(0.4f);
	}

	void OnTargetDied(Unit* mTarget)
	{
		_unit->SetFaction(35);
		_unit->SetScale(0.4f);
	}
};

class BrutebaneStoutTrigger : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BrutebaneStoutTrigger)
	BrutebaneStoutTrigger(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->Root();
		Plr = sEAS.GetNearestPlayer(_unit);

		uint32 BladespireOgres[] = { 19995, 19998, 20756, 0 };
		Ogre = sEAS.GetNearestCreature(_unit, BladespireOgres);
		if(Ogre != NULL)
			Ogre->GetAIInterface()->_CalcDestinationAndMove(_unit, 0.3f);

		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		if(Ogre == NULL)
			return;

		if(_unit->CalcDistance(Ogre) <= 5)
		{
			Ogre->SetEquippedItem(MELEE, 28562);
			Ogre->SetEmoteState(EMOTE_ONESHOT_EAT_NOSHEATHE);
			Ogre->SetFaction(35);
			Ogre->SetStandState(STANDSTATE_SIT);
			Ogre->Despawn(60000, 3*60*1000);

			GameObject *Mug = sEAS.GetNearestGameObject(_unit, 184315);
			if(Mug != NULL)
				Mug->Despawn(0, 0);

			if(Plr != NULL)
				sEAS.KillMobForQuest(Plr, 10512, 0);

			_unit->Despawn(0, 0);
		}
	}

protected:
	Player* Plr;
	Creature* Ogre;
};

void SetupZoneBladeEdgeMountains(ScriptMgr* mgr)
{
	mgr->register_creature_script(21823, &NihilTheBanished::Create); // Nihil the Banished
	mgr->register_creature_script(22920, &ThukTheDefiant::Create); // Thuk the Defiant
	mgr->register_creature_script(21241, &BrutebaneStoutTrigger::Create); // Bloodmaul Brutebane Stout Trigger
}