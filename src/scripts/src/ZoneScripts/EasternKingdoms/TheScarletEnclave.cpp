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

class SalanarTheHorseman : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SalanarTheHorseman);
	SalanarTheHorseman(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->SendChatMessage(CHAT_MSG_SAY, LANG_UNIVERSAL, "Impressive, death knight. Return to me in the world of living for your reward.");
		_unit->Despawn(10000, 0); // despawn after 10 seconds
	}
};

class CitizenAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CitizenAI);
	CitizenAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->GetAIInterface()->m_canCallForHelp = false;
	}

	void OnCombatStart(Unit* mTarget)
	{
		float chance = 40.0f; // base chance set as 30 %
		if(_unit->getGender() == 1) // women
			chance *= 2; // double chance

		// cover only if its player, they fight with other npcs normally
		if(Rand(chance) && mTarget->GetTypeId() == TYPEID_PLAYER)
		{
			if(mTarget->GetPhase() == 1) // LK voices can be only in phase 1
			{
				uint8 msg = RandomUInt(15);
				uint32 sound = 14771+msg;
				string whisp;

				switch(msg)
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

				/* this is probably best way around
				   it spawns invisible lich king near you for 1 sec */
				Creature* pCreature = sEAS.SpawnCreature(TO_PLAYER(mTarget), 16980, mTarget->GetPositionX(), mTarget->GetPositionY(), mTarget->GetPositionZ(), 0.0f, 1000, 1);
			
				if(pCreature)
				{
					pCreature->SendChatMessage(CHAT_MSG_MONSTER_WHISPER, LANG_UNIVERSAL, whisp.c_str());
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
			_unit->SetEmoteState(431);
		}
		else
		{
			uint8 say = RandomUInt(1);

			switch(say)
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Come then, death knight!");
				break;
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You may take my life, but you won't take my freedom!");
				break;
			}

			// Enrage! :P
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
	ADD_CREATURE_FACTORY_FUNCTION(PeasantAI);
	PeasantAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit* mTarget)
	{
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		if(_unit->GetHealthPct() < 75) // they covered around 75% of HP
		{
			uint8 msg = RandomUInt(4);
			string say;

			switch(msg)
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

			Unit* pUnit = _unit->GetAIInterface()->GetMostHated();
			if(pUnit)
				_unit->smsg_AttackStop(pUnit);

			_unit->GetAIInterface()->disable_melee = true;
			_unit->GetAIInterface()->_UpdateCombat(0);

			RemoveAIUpdateEvent();
			_unit->Root();
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, say.c_str());
			_unit->WipeHateList();
			_unit->SetEmoteState(431);
		}
	}
};

class MinerAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(MinerAI);
	MinerAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnReachWP(uint32 WPId, bool bForwards)
	{
		Creature* pCreature = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 28821);
		// Despawn them when they reach their last WP, they are not running backwards
		if(WPId == _unit->GetAIInterface()->GetWayPointsCount())
		{
			_unit->Despawn(0, 10000);
			if(pCreature != NULL)
				pCreature->Despawn(0, 9000);
		}
	}
};

class CanonAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CanonAI);
	CanonAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		_unit->GetAIInterface()->m_canMove = false;
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
		Player* pPlayer = TO_PLAYER(_unit->GetAIInterface()->getNextTarget());
		if(pPlayer == NULL || (pPlayer->GetHealthPct() > 10 && _unit->GetHealthPct() > 10))
			return;

		RemoveAIUpdateEvent();
		// pPlayer stuff (stop attacking etc.)
		pPlayer->smsg_AttackStop(_unit);
		pPlayer->GetSession()->OutPacket(SMSG_CANCEL_COMBAT);
		pPlayer->EventAttackStop();

		// NPC stuff (stop attacking, despawn)
		if(_unit->isAlive())
		{
			_unit->Root();
			_unit->smsg_AttackStop(pPlayer);
			_unit->SetFaction(2084);
			_unit->Despawn(3000, 30000);
		}

		// duel arbiter
		GameObject* arbiter = pPlayer->GetMapMgr()->GetGameObject(GET_LOWGUID_PART(pPlayer->GetDuelArbiter()));
		if(arbiter != NULL)
		{
			arbiter->RemoveFromWorld(true);
			delete arbiter;
		}
		pPlayer->SetDuelArbiter(0); // reset players arbiter

		if(_unit->GetHealthPct() < 10) // Player is winner
		{
			sEAS.KillMobForQuest(pPlayer, 12733, 0);
			if(_unit->isAlive())
				_unit->Emote(EMOTE_ONESHOT_BEG);
		}
		else
			pPlayer->Emote(EMOTE_ONESHOT_BEG);
	}
};

void SetupZoneTheScarletEnclave(ScriptMgr* mgr)
{
	mgr->register_creature_script(28788, &SalanarTheHorseman::Create); // called by spell 52363 which is used in Q 12687 (spell is from vehicle)
	mgr->register_creature_script(28576, &CitizenAI::Create);
	mgr->register_creature_script(28577, &CitizenAI::Create);
	mgr->register_creature_script(28557, &PeasantAI::Create);
	mgr->register_creature_script(28850, &CanonAI::Create);
	mgr->register_creature_script(28822, &MinerAI::Create);
	mgr->register_creature_script(28406, &DKInitiateAI::Create);
}