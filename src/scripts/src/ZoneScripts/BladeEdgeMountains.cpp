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

class WyrmcultBlackwhelp : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WyrmcultBlackwhelp);
		WyrmcultBlackwhelp(Creature* c) : CreatureAIScript(c) {}

		void OnLoad()
		{
			RegisterAIUpdateEvent(1000);
		}

		void AIUpdate()
		{
			// Let's see if we are netted
			Aura* a = _unit->FindAura(38177);
			if(a != NULL)
			{
				Unit* Caster = a->GetUnitCaster();
				if(Caster->IsPlayer())
				{

					QuestLogEntry* qle = TO_PLAYER(Caster)->GetQuestLogForEntry(10747);
					if(qle != NULL)
					{
						// casting the spell that will create the item for the player
						_unit->CastSpell(Caster, 38178, true);
						_unit->Despawn(1000, 360000);
					}
				}
			}
		}
};

// The Bladespire Threat Quest
class BladespireQAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BladespireQAI);
		BladespireQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* en = (TO_PLAYER(mKiller))->GetQuestLogForEntry(10503);
				if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = en->GetMobCount(0) + 1;
					en->SetMobCount(0, newcount);
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
					return;
				}
			}
		}
};

class MagnetoAura : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MagnetoAura);
		MagnetoAura(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->CastSpell(_unit, 37136, true);
		}
};

class FunnyDragon : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(FunnyDragon);
		FunnyDragon(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			RegisterAIUpdateEvent(5000);
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->SetEmoteState(0);
			_unit->GetAIInterface()->m_canMove = false;
			i = 1;
		}

		void AIUpdate()
		{
			switch(i)
			{
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Muahahahahaha! You fool! you've released me from my banishment in the interstices between space and time!");
					break;
				case 2:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "All of Draenor shall quake beneath my feet! i Will destroy this world and reshape it in my immage!");
					break;
				case 3:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Where shall i Begin? i cannot bother myself with a worm such as yourself. Theres a World to be Conquered!");
					break;
				case 4:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "No doubt the fools that banished me are long dead. i shall take the wing and survey my new demense, Pray to whatever gods you hold dear that we do not meet again.");
					_unit->Despawn(5000, 0);
					break;
			}

			++i;
		}

		uint32 i;
};

class BloodmaulQAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(BloodmaulQAI);
	BloodmaulQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

	void OnDied(Unit* mKiller)
	{
		if(!mKiller->IsPlayer())
			return;

		Player* pPlayer = TO_PLAYER(mKiller);
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10502);
		if(pQuest == NULL)
		{
			pQuest = pPlayer->GetQuestLogForEntry(10505);
			if(pQuest == NULL)
				return;
		}

		if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
		{
			pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
			pQuest->SendUpdateAddKill(0);
			pQuest->UpdatePlayerFields();
		}
	}
};

class Thuk_the_DefiantAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Thuk_the_DefiantAI);

		Thuk_the_DefiantAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
		}
		void OnLoad()
		{
			_unit->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
		}
		void OnTargetDied(Unit* mTarget)
		{
			_unit->SetFaction(35);
			_unit->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
		}
};

//////////////////////////////////////////////////////////////////////////
/////// Bladespire Brute/Shaman/Cook
#define CN_BLADESPIRE_OGRE_1				19995
#define CN_BLADESPIRE_OGRE_2				19998
#define CN_BLADESPIRE_OGRE_3				20756

//////////////////////////////////////////////////////////////////////////
/////// Bloodmaul Brutebane Stout Trigger
#define CN_BLOODMAUL_BRUTEBANE_STOUT_TRIGGER    21241

/*class BrutebaneStoutTriggerAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BrutebaneStoutTriggerAI);
		BrutebaneStoutTriggerAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			_unit->SetFaction(35);

			SetCanMove(false);

			plr = _unit->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());
			Ogre = GetNearestCreature(CN_BLADESPIRE_OGRE_1);
			if(Ogre == NULL)
			{
				Ogre = GetNearestCreature(CN_BLADESPIRE_OGRE_2);
				if(Ogre == NULL)
				{
					Ogre = GetNearestCreature(CN_BLADESPIRE_OGRE_3);
					if(Ogre == NULL)
					{
						return;
					}
				}
			}
			Ogre->MoveTo(_unit);
			RegisterAIUpdateEvent(1000);
		}

		void AIUpdate()
		{
			if(Ogre == NULL)
				return;
			if(GetRange(Ogre) <= 5)
			{
				Ogre->SetDisplayWeaponIds(28562, 0);
				Ogre->GetUnit()->SetEmoteState(92);
				Ogre->GetUnit()->SetFaction(35);
				Ogre->GetUnit()->SetStandState(STANDSTATE_SIT);
				NdGo = GetNearestGameObject(184315);
				if(NdGo == NULL)
					return;

				NdGo->Despawn(0, 0);
				Ogre->Despawn(60 * 1000, 3 * 60 * 1000);
				if(plr == NULL)
					return;

				QuestLogEntry* qle = plr->GetQuestLogForEntry(10512);

				if(qle != NULL && qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[0])
				{
					qle->SetMobCount(0, qle->GetMobCount(0) + 1);
					qle->SendUpdateAddKill(0);
					qle->UpdatePlayerFields();
				}

				Despawn(0, 0);
				return;
			}
			ParentClass::AIUpdate();
		}

		Player*					plr;
		GameObject*				Keg;
		GameObject*				NdGo;
		MoonScriptCreatureAI*	Ogre;
};*/

void SetupZoneBladeEdgeMountains(ScriptMgr* mgr)
{
	mgr->register_creature_script(21823, &NihilTheBanished::Create); // Nihil the Banished
	mgr->register_creature_script(22920, &ThukTheDefiant::Create); // Thuk the Defiant
	mgr->register_creature_script(21241, &BrutebaneStoutTrigger::Create); // Bloodmaul Brutebane Stout Trigger
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_1, &BladespireQAI::Create);
	mgr->register_creature_script(21296, &BladespireQAI::Create);
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_3, &BladespireQAI::Create);
	mgr->register_creature_script(20766, &BladespireQAI::Create);
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_2, &BladespireQAI::Create);
	mgr->register_creature_script(21731, &MagnetoAura::Create);
	mgr->register_creature_script(21823, &FunnyDragon::Create);
	mgr->register_creature_script(19957, &BloodmaulQAI::Create);
	mgr->register_creature_script(19991, &BloodmaulQAI::Create);
	mgr->register_creature_script(21238, &BloodmaulQAI::Create);
	mgr->register_creature_script(19952, &BloodmaulQAI::Create);
	mgr->register_creature_script(21294, &BloodmaulQAI::Create);
	mgr->register_creature_script(19956, &BloodmaulQAI::Create);
	mgr->register_creature_script(19993, &BloodmaulQAI::Create);
	mgr->register_creature_script(19992, &BloodmaulQAI::Create);
	mgr->register_creature_script(19948, &BloodmaulQAI::Create);
	mgr->register_creature_script(22384, &BloodmaulQAI::Create);
	mgr->register_creature_script(22160, &BloodmaulQAI::Create);
	mgr->register_creature_script(19994, &BloodmaulQAI::Create);
	mgr->register_creature_script(22920, &Thuk_the_DefiantAI::Create);
	mgr->register_creature_script(21387, &WyrmcultBlackwhelp::Create);
	//mgr->register_creature_script(CN_BLOODMAUL_BRUTEBANE_STOUT_TRIGGER, &BrutebaneStoutTriggerAI::Create);
}