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

class SalanarTheHorseman : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SalanarTheHorseman)
	SalanarTheHorseman(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->SendChatMessage(CHAT_MSG_SAY, LANG_UNIVERSAL, "Impressive, death knight. Return to me in the world of living for your reward.");
		_unit->Despawn(10000, 0); // despawn after 10 seconds
	}
};

class CitizenAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CitizenAI)
	CitizenAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		float chance = 40.0f;
		if(_unit->getGender() == 1)
			chance *= 2; // double chance for women

		// cover only if its player, they fight with other npcs normally
		if(Rand(chance) && mTarget->IsPlayer())
		{
			if(mTarget->GetPhase() == 1) // LK voices can be only in phase 1
			{
				uint8 Random = RandomUInt(15);
				uint32 sound = 14771 + Random;
				string whisp = "";

				switch(Random)
				{
					case 0:
						whisp = "No mercy.";
						break;
					case 1:
						whisp = "Kill them all.";
						break;
					case 2:
						whisp = "Mercy is for the weak.";
						break;
					case 3:
						whisp = "End it.";
						break;
					case 4:
						whisp = "Finish it.";
						break;
					case 5:
						whisp = "No survivors.";
						break;
					case 6:
					{
						whisp = "Kill or be killed, ";
						whisp += TO_PLAYER(mTarget)->GetName();
						whisp += ".";
					}break;
					case 7:
						whisp = "Do not hesitate.";
						break;
					case 8:
						whisp = "Harness your rage and focus.";
						break;
					case 9:
						whisp = "Strike it down.";
						break;
					case 10:
						whisp = "Suffering to the conquered.";
						break;
					case 11:
						whisp = "Show it the meaning of terror.";
						break;
					case 12:
						whisp = "End it's miserable life.";
						break;
					case 13:
						whisp = "Give into the darkness, Death Knight.";
						break;
					case 14:
						whisp = "Do you think it would hesitate to kill you, a monster like you?";
						break;
					case 15:
						whisp = "Living or dead, you will serve me.";
						break;
				}

				Creature *cr = sEAS.SpawnCreature(TO_PLAYER(mTarget), 16980, mTarget->GetPositionNC());
				if(cr)
				{
					cr->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, whisp.c_str());
					cr->Despawn(0, 0);
					TO_PLAYER(mTarget)->PlaySound(sound);
				}
			}

			// this will make creature stop attacking you and stay at 1 place with emote
			_unit->smsg_AttackStop(mTarget);
			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->_UpdateCombat(0);
			_unit->Root();
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "No! Please! I.. I have children! I... I...");
			_unit->WipeHateList();
			_unit->SetEmoteState(EMOTE_STATE_COWER);
		}
		else
		{
			switch(RandomUInt(1))
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Come then, death knight!");
					break;
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You may take my life, but you won't take my freedom!");
					break;
			}

			_unit->CastSpell(_unit, 52262, false);
		}
	}

	void OnReachWP(uint32 WPId, bool bForwards)
	{
		// Despawn them when they reach their last WP, they are not running backwards
		if(WPId == _unit->GetAIInterface()->GetWayPointsCount())
			_unit->Despawn(0, 10000);
	}
};

class PeasantAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PeasantAI)
	PeasantAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		if(_unit->GetHealthPct() < 75) // they covered around 75% of HP
		{
			string say = "";
			switch(RandomUInt(4))
			{
				case 0:
					say = "I... I got a sick grandma at home... I... I'm all she's got, mister ";
					break;
				case 1:
					say = "I picked the wrong week to quit drinkin'!";
					break;
				case 2:
					say = "You don't have to do this! Nobody has to die!";
					break;
				case 3:
					say = "Ungh... I... I think I pooped...";
					break;
				case 4:
					say = "I've got five kids, man! They'll die without me!";
					break;
			}
			RemoveAIUpdateEvent();

			Unit *u = _unit->GetAIInterface()->getNextTarget();
			if(u)
				_unit->smsg_AttackStop(u);

			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->_UpdateCombat(0);
			_unit->Root();
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, say.c_str());
			_unit->WipeHateList();
			_unit->SetEmoteState(EMOTE_STATE_COWER);
		}
	}
};

class CanonAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CanonAI);
	CanonAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->GetAIInterface()->m_canMove = false;
	}
};

class MinerAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(MinerAI)
	MinerAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 WPId, bool bForwards)
	{
		Creature *car = sEAS.GetNearestCreature(_unit, 28821);
		// Despawn them when they reach their last WP, they are not running backwards
		if(WPId == _unit->GetAIInterface()->GetWayPointsCount())
		{
			_unit->Despawn(0, 10000);
			if(car != NULL)
				car->Despawn(0, 10000);
		}
	}
};

class DKInitiateAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(DKInitiateAI)
	DKInitiateAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		if(mTarget->IsPlayer())
			RegisterAIUpdateEvent(500);
	}

	void AIUpdate()
	{
		Player *plr = TO_PLAYER(_unit->GetAIInterface()->getNextTarget());
		if(plr == NULL || (plr->GetHealthPct() > 10 && _unit->GetHealthPct() > 10))
			return;

		RemoveAIUpdateEvent();
		// plr stuff (stop attacking etc.)
		plr->smsg_AttackStop(_unit);
		plr->GetSession()->OutPacket(SMSG_CANCEL_COMBAT);
		plr->EventAttackStop();

		// NPC stuff (stop attacking, despawn)
		if(_unit->isAlive())
		{
			_unit->Root();
			_unit->smsg_AttackStop(plr);
			_unit->SetFaction(2084);
			_unit->Despawn(3000, 30000);
		}

		// duel arbiter
		GameObject *arbiter = plr->GetMapMgr()->GetGameObject(GET_LOWGUID_PART(plr->GetDuelArbiter()));
		if(arbiter != NULL)
		{
			arbiter->RemoveFromWorld(true);
			delete arbiter;
		}
		plr->SetDuelArbiter(0); // reset players arbiter

		if(_unit->GetHealthPct() < 10) // Player is winner
		{
			sEAS.KillMobForQuest(plr, 12733, 0);
			if(_unit->isAlive())
				_unit->Emote(EMOTE_ONESHOT_BEG);
		}
		else
			plr->Emote(EMOTE_ONESHOT_BEG);
	}
};

void SetupZoneTheScarletEnclave(ScriptMgr* mgr)
{
	mgr->register_creature_script(28788, &SalanarTheHorseman::Create); // Salanar the Horseman
	mgr->register_creature_script(28576, &CitizenAI::Create); // Citizen of Havenshire
	mgr->register_creature_script(28577, &CitizenAI::Create); // Citizen of Havenshire
	mgr->register_creature_script(28557, &PeasantAI::Create); // Scarlet Peasant
	mgr->register_creature_script(28850, &CanonAI::Create); // Scarlet Land Cannon
	mgr->register_creature_script(28822, &MinerAI::Create); // Scarlet Miner
	mgr->register_creature_script(28406, &DKInitiateAI::Create); // Death Knight Initiate
}