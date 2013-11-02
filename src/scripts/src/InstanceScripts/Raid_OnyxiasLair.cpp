/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
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
/* Raid_OnyxiasLair.cpp Script by DK			                        */
/************************************************************************/

/* TODO: Deepbreath; Eggs go 176511 */

#define WALK 0
#define RUN 256
#define FLY 768
//0 = walk, 256 = run, 768 = fly

#define MAP_LAIR 249

enum LairGO
{
	GO_EGG			= 176511,
	GO_LAVA			= 176912
};

enum LairBosses
{
	ONY_BOSS		= 10184,
	ONY_WHELP		= 11262,
	ONY_GUARD		= 36561
};

enum LairSpells
{
	FLAME_BREATH				= 18435, // Corrected http://www.wowhead.com/?spell=18435
	ONY_FLAME_BREATH25			= 68970,
	WING_BUFFET					= 18500, // Self
	ONY_WING_BUFFET25			= 69293,
	TAIL_SWEEP					= 68867,
	ONY_TAIL_SWEEP25 			= 69286,
	ONY_ERUPTION 				= 17731,
	ONY_ERUPTION25 				= 69294,
	CLEAVE 						= 68868, // 15579,16044,19642,29832 //target Corrected
	AOE_FEAR		 			= 18431, // With Activate Object
	SCRIPTABLE_FIREBALL 		= 18392, // Corrected http://www.wowhead.com/?spell=18392
	ONY_FIREBALL25 				= 68926,
	DEEP_BREATH 				= 17086,
	GUARD_BLAST_NOVA			= 68958,
	GUARD_CLEAVE				= 15284,
	GUARD_IGNITE_WEAPON			= 68960,
	KNOCK_AWAY					= 19633, // Reduce thread script effect main target
	ENTANGLING_FLAMES			= 20019
};

enum LairAchives
{	
	ACHIEV_BREATH_N			= 4404, 
	ACHIEV_BREATH_H			= 4407,
	ACHIEV_DEFEAT_N			= 4396,
	ACHIEV_DEFEAT_H			= 4397,
	ACHIEV_DOTS_N			= 4402,
	ACHIEV_DOTS_H			= 4405,
	ACHIEV_WHELPS_N			= 4403,
	ACHIEV_WHELPS_H			= 4406
};

static Location coords[] =
{
	{ 0, 0, 0, 0 },
	{ -75.945f, -219.245f, -83.375f, 0.004947f },
	{ -72.945f, -219.245f, -80.779f, 0.004947f },
	{ 42.621f, -217.195f, -66.056f, 3.014011f },
	{ 12.270f, -254.694f, -67.997f, 2.395585f },
	{ -79.020f, -252.374f, -68.965f, 0.885179f },
	{ -80.257f, -174.240f, -69.293f, 5.695741f },
	{ 27.875f, -178.547f, -66.041f, 3.908957f },
	{ -4.868f, -217.171f, -86.710f, M_PI_FLOAT }
};

static Location whelpCoords[] =
{
	{ -30.812f, -166.395f, -89.000f, 5.160f },
	{ -30.233f, -264.158f, -89.896f, 1.129f },
	{ -35.813f, -169.427f, -90.000f, 5.384f },
	{ -36.104f, -260.961f, -90.600f, 1.111f },
	{ -34.643f, -164.080f, -90.000f, 5.364f },
	{ -35.377f, -267.320f, -91.000f, 1.111f }
};

class OnyxiaAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(OnyxiaAI);
		OnyxiaAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			m_phase = 1;
			m_entry = pCreature->GetEntry();
			m_useSpell = true;
			m_eFlamesCooldown = 1;
			m_whelpCooldown = 7;
			m_aoeFearCooldown = 30;
			m_fCastCount = 5;
			_unit->GetAIInterface()->setMoveType(4);
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(1, 2000, RUN));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(2, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(3, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(4, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(5, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(6, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(7, 0, FLY));
			_unit->GetAIInterface()->addWayPoint(CreateWaypoint(8, 0, FLY));

			infoFear = dbcSpell.LookupEntry(AOE_FEAR);
			infoCleave = dbcSpell.LookupEntry(CLEAVE);
			infoFBreath = dbcSpell.LookupEntry(FLAME_BREATH);
			infoKAway = dbcSpell.LookupEntry(KNOCK_AWAY);
			infoSFireball = dbcSpell.LookupEntry(SCRIPTABLE_FIREBALL);
			infoWBuffet = dbcSpell.LookupEntry(WING_BUFFET);
			infoDeepBreath = dbcSpell.LookupEntry(DEEP_BREATH);

			if(!infoFear || !infoCleave || !infoFBreath
			        || !infoKAway || !infoSFireball || !infoWBuffet || !infoDeepBreath)
				m_useSpell = false;

			_unit->GetAIInterface()->setOutOfCombatRange(200000);

			m_fBreath = false;
			m_kAway = false;
			m_wBuffet = false;
			m_Cleave = false;
		}

		void OnCombatStart(Unit* mTarget)
		{
			m_phase = 1;
			m_eFlamesCooldown = 1;
			m_whelpCooldown = 7;
			_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
			_unit->SetStandState(0);
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "How fortuitous, usually I must leave my lair to feed!");
			if(m_useSpell)
				RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));

			m_fBreath = false;
			m_kAway = false;
			m_wBuffet = false;
			m_Cleave = false;
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setMoveType(0);
			_unit->GetAIInterface()->setWaypointToMove(0);
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
			_unit->GetAIInterface()->StopFlying();
			_unit->GetAIInterface()->m_canMove = true;
			_unit->SetStandState(STANDSTATE_SLEEP);
			/*if(_unit->m_pacified > 0)
			    _unit->m_pacified--;*/
			if(m_useSpell)
				RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			if(m_useSpell)
				RemoveAIUpdateEvent();

			m_phase = 1;
			m_eFlamesCooldown = 1;
			m_whelpCooldown = 7;

			/*Add Loot?
			mKiller->
			*/
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			switch(iWaypointId)
			{
				case 1:
					{
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(2);
						Fly();
					}
					break;
				case 2:
					{
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
						_unit->GetAIInterface()->setWaypointToMove(3);
					}
					break;
				case 3:
					{
						_unit->GetAIInterface()->m_canMove = false;
						_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAIInterface()->setCurrentAgent(AGENT_SPELL);
						//_unit->m_pacified--;
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
						WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						m_currentWP = 3;
					}
					break;
				case 8:
					{
						_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
						/*_unit->m_pacified--;
						if(_unit->m_pacified > 0)
						    _unit->m_pacified--;*/
						WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						Land();
					}
					break;
				default:
					{
						_unit->GetAIInterface()->m_canMove = false;
						_unit->GetAIInterface()->SetAllowedToEnterCombat(true);
						_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
						_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
						_unit->GetAIInterface()->setWaypointToMove(0);
						WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
						data << _unit->GetNewGUID();
						data << uint32(0);
						_unit->SendMessageToSet(&data, false);
						//_unit->m_pacified--;
					}
					break;
			};
		}

		void AIUpdate()
		{
			switch(m_phase)
			{
				case 1:
					{
						PhaseOne();
					}
					break;
				case 2:
					{
						PhaseTwo();
					}
					break;
				case 3:
					{
						PhaseThree();
					}
					break;
				default:
					{
						m_phase = 1;
					};
			};
		}

		void PhaseOne()
		{
			if(_unit->GetHealthPct() <= 65)
			{
				m_phase = 2;
				_unit->SetCastSpeedMod(0.01f);
				if(_unit->GetCurrentSpell() != NULL)
					_unit->GetCurrentSpell()->cancel();

				_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
				//_unit->m_pacified++;
				_unit->GetAIInterface()->StopMovement(0);
				_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(1);

				return;
			}
			uint32 val = RandomUInt(1000);
			SpellCast(val);
		}

		void PhaseTwo()
		{
			if(_unit->GetHealthPct() <= 40)
			{
				m_phase = 3;
				_unit->SetCastSpeedMod(1.0f);
				if(_unit->GetCurrentSpell() != NULL)
					_unit->GetCurrentSpell()->cancel();
				_unit->GetAIInterface()->m_canMove = true;
				_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
				//_unit->m_pacified++;
				_unit->GetAIInterface()->StopMovement(0);
				_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
				_unit->GetAIInterface()->setWaypointToMove(8);

				return;
			}
			if(_unit->GetAIInterface()->getMoveType() == MOVEMENTTYPE_WANTEDWP)
				return;
			m_eFlamesCooldown--;
			if(!m_eFlamesCooldown && _unit->GetAIInterface()->getNextTarget())//_unit->getAttackTarget())
			{
				_unit->CastSpell(_unit->GetAIInterface()->getNextTarget(), infoSFireball, false);//(_unit->getAttackTarget(),
				m_eFlamesCooldown = 4;
				m_fCastCount--;
			}
			if(!m_fCastCount)
			{
				uint32 val = RandomUInt(1250);
				if(val < 250)//Move left
				{
					m_currentWP++;
					if(m_currentWP >= 8)
						m_currentWP = 3;

					_unit->GetAIInterface()->m_canMove = true;
					_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
					//_unit->m_pacified++;
					_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
					_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
					_unit->GetAIInterface()->setWaypointToMove(m_currentWP);
					m_fCastCount = 5;
				}
				else if(val > 1000)//Move right
				{
					m_currentWP--;
					if(m_currentWP < 3)
						m_currentWP = 7;

					_unit->GetAIInterface()->m_canMove = true;
					_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
					//_unit->m_pacified++;
					_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
					_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP);
					_unit->GetAIInterface()->setWaypointToMove(m_currentWP);
					m_fCastCount = 5;
				}
				else if(val < 350)
				{
					//Deep breath
					_unit->CastSpell(_unit, infoDeepBreath, false);
					m_fCastCount = 5;
				}
				else
					m_fCastCount = 5;
			}
			m_whelpCooldown--;
			if(!m_whelpCooldown)
			{
				Creature* cre = NULL;
				for(int i = 0; i < 6; i++)
				{
					cre = _unit->GetMapMgr()->GetInterface()->SpawnCreature(11262,
					        whelpCoords[i].x, whelpCoords[i].y,
					        whelpCoords[i].z, whelpCoords[i].o,
					        true, false, 0, 0);
					if(cre)
					{
						cre->GetAIInterface()->MoveTo(14.161f, -177.874f, -85.649f, 0.23f);
						cre->GetAIInterface()->setOutOfCombatRange(100000);
					}
					cre = _unit->GetMapMgr()->GetInterface()->SpawnCreature(11262,
					        whelpCoords[5 - i].x, whelpCoords[5 - i].y,
					        whelpCoords[5 - i].z, whelpCoords[5 - i].o,
					        true, false, 0, 0);
					if(cre)
					{
						cre->GetAIInterface()->MoveTo(27.133f, -232.030f, -84.188f, 0.44f);
						cre->GetAIInterface()->setOutOfCombatRange(100000);
					}
				}
				m_whelpCooldown = 30;
			}
		}

		void PhaseThree()
		{
			if(!m_aoeFearCooldown)
			{
				_unit->CastSpell(_unit, infoFear, false);//(_unit->getAttackTarget(),
				m_aoeFearCooldown = 30;
				return;
			}
			uint32 val = RandomUInt(1000);
			SpellCast(val);
			m_whelpCooldown--;
			m_aoeFearCooldown--;
			if(!m_whelpCooldown)
			{
				Creature* cre = NULL;
				for(int i = 0; i < 6; i++)
				{
					cre = _unit->GetMapMgr()->GetInterface()->SpawnCreature(11262,
					        whelpCoords[i].x, whelpCoords[i].y,
					        whelpCoords[i].z, whelpCoords[i].o,
					        true, false, 0, 0);
					if(cre)
					{
						cre->GetAIInterface()->MoveTo(14.161f, -177.874f, -85.649f, 0.23f);
						cre->GetAIInterface()->setOutOfCombatRange(100000);
					}
					cre = _unit->GetMapMgr()->GetInterface()->SpawnCreature(11262,
					        whelpCoords[5 - i].x, whelpCoords[5 - i].y,
					        whelpCoords[5 - i].z, whelpCoords[5 - i].o,
					        true, false, 0, 0);
					if(cre)
					{
						cre->GetAIInterface()->MoveTo(27.133f, -232.030f, -84.188f, 0.44f);
						cre->GetAIInterface()->setOutOfCombatRange(100000);
					}
				}
				m_whelpCooldown = 300;
			}
		}

		inline WayPoint* CreateWaypoint(int id, uint32 waittime, uint32 flags)
		{
			//WayPoint* wp = new WayPoint;
			//WayPoint * wp = _unit->GetMapMgr()->GetInterface()->CreateWaypoint();
			//WayPoint * wp = sStructFactory.CreateWaypoint();
			WayPoint* wp = _unit->CreateWaypointStruct();
			wp->id = id;
			wp->x = coords[id].x;
			wp->y = coords[id].y;
			wp->z = coords[id].z;
			wp->o = coords[id].o;
			wp->waittime = waittime;
			wp->flags = flags;
			wp->forwardemoteoneshot = false;
			wp->forwardemoteid = 0;
			wp->backwardemoteoneshot = false;
			wp->backwardemoteid = 0;
			wp->forwardskinid = 0;
			wp->backwardskinid = 0;
			return wp;
		}

		void Fly()
		{
			_unit->Emote(EMOTE_ONESHOT_LIFTOFF);
			//Do we need hover really? Check it :D
			/*WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
			data << _unit->GetNewGUID();
			data << uint32(0);
			_unit->SendMessageToSet(&data, false);*/
			_unit->GetAIInterface()->SetFly();
		}

		void Land()
		{
			_unit->Emote(EMOTE_ONESHOT_LAND);
			//Do we need hover really? Check it :D
			/*WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
			data << _unit->GetNewGUID();
			data << uint32(0);
			_unit->SendMessageToSet(&data, false);*/
			_unit->GetAIInterface()->StopFlying();
		}

		void SpellCast(uint32 val)
		{
			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())//_unit->getAttackTarget())
			{
				if(m_fBreath)
				{
					_unit->CastSpell(_unit, infoFBreath, false);
					m_fBreath = false;
					return;
				}
				else if(m_kAway)
				{
					_unit->CastSpell(_unit->GetAIInterface()->getNextTarget(), infoKAway, false);
					m_kAway = false;
					return;
				}
				else if(m_wBuffet)
				{
					_unit->CastSpell(_unit, infoWBuffet, false);
					m_wBuffet = false;
					return;
				}
				else if(m_Cleave)
				{
					_unit->CastSpell(_unit->GetAIInterface()->getNextTarget(), infoCleave, false);
					m_Cleave = false;
					return;
				}

				if(val >= 100 && val <= 225)
				{
					_unit->setAttackTimer(6000, false);//6000
					m_fBreath = true;
					//_unit->CastSpell(_unit, infoFBreath, false);
				}
				else if(val > 225 && val <= 300)
				{
					_unit->setAttackTimer(4000, false);//2000
					m_kAway = true;
					//_unit->CastSpell(_unit->GetAIInterface()->GetNextTarget(), infoKAway, false);
				}
				else if(val > 300 && val <= 375)
				{
					_unit->setAttackTimer(4000, false);//3000
					m_wBuffet = true;
					//_unit->CastSpell(_unit, infoWBuffet, false);
				}
				else if(val > 375 && val < 450)
				{
					_unit->setAttackTimer(4000, false);//2000
					m_Cleave = true;
					// _unit->CastSpell(_unit->GetAIInterface()->GetNextTarget(), infoCleave, false);
				}
			}
		}

		inline bool HasEntry() { return (m_entry != 0) ? true : false; }

	protected:

		bool m_fBreath;
		bool m_kAway;
		bool m_wBuffet;
		bool m_Cleave;
		uint32 m_entry;
		uint32 m_phase;
		bool m_useSpell;
		uint32 m_eFlamesCooldown;
		uint32 m_whelpCooldown;
		uint32 m_aoeFearCooldown;
		uint32 m_fCastCount;
		uint32 m_currentWP;
		SpellEntry* infoFear, *infoWBuffet, *infoCleave, *infoFBreath, *infoKAway, *infoSFireball, *infoDeepBreath;
};

/*void SpellFunc_Deep_Breath(SpellDesc* pThis, CreatureAIScript* pCreatureAI, Unit *pTarget, TargetType pType)
{
	OnyxiaAI *pOnyxia = (pCreatureAI != NULL) ? (OnyxiaAI*)(pCreatureAI) : NULL;
	if(pOnyxia != NULL)
	{
		Spell *dbspell = new Spell(TO_OBJECT(pOnyxia), dbcSpell.LookupEntry(ONY_BREATH), false, NULLAURA);
		dbspell->SetUnitTarget(pTarget);
		for (unordered_set<Player *>::iterator itr = pOnyxia->GetUnit()->GetInRangePlayerSetBegin(); itr != pOnyxia->GetUnit()->GetInRangePlayerSetEnd(); ++itr) 
		{
			Player *pPlayer = TO_PLAYER(*itr);
			pPlayer->GetSession()->SystemMessage("Lady Onyxia takes in a deep breath...");
		}
		pOnyxia->GetUnit()->CastSpell(dbspell);
		//if(dbspell->_DidHit(dbspell->GetUnitTarget())) // Need to somehow return hit state
			//pOnyxia->mDidHit = true;
	}
}

void SpellFunc_Eruption(SpellDesc* pThis, CreatureAIScript* pCreatureAI, Unit *pTarget, TargetType pType)
{
	if(pCreatureAI != NULL)
	{
		for(unordered_set<Object* >::iterator itr = pCreatureAI->GetUnit()->GetInRangeSetBegin(); itr != pCreatureAI->GetUnit()->GetInRangeSetEnd(); ++itr)
		{
			if((*itr)->GetEntry() == GO_LAVA)
			{
				(*itr)->Activate(pCreatureAI->GetUnit()->GetMapMgr());
				(*itr)->CastSpell(pTarget->GetGUID(), (pCreatureAI->GetInstanceMode() == MODE_10PLAYER_NORMAL) ? ONY_ERUPTION : ONY_ERUPTION25, false);
				(*itr)->Deactivate(pCreatureAI->GetUnit()->GetMapMgr());
			}				
		}
	}
}

class GuardAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(GuardAI);
	GuardAI(Creature *pCreature) : CreatureAIScript(pCreature)
    {	
		AddSpell(GUARD_BLAST_NOVA, Target_Current, 15, 0, 10, 0.0f, 15.0f);
		AddSpell(GUARD_CLEAVE, Target_Current, 15, 0, 10);
	    mIgniteWeapon = AddSpell(GUARD_IGNITE_WEAPON, Target_Self, 0, 0, 0, 0.0f, 0.0f);
		AddSpellFunc(&SpellFunc_Ignite_Weapon, Target_Self, 15, 0, 40, 0.0f, 5.0f);
	}
	SpellDesc *mIgniteWeapon;
};

void SpellFunc_Ignite_Weapon(SpellDesc* pThis, CreatureAIScriptAI* pCreatureAI, Unit *pTarget, TargetType pType)
{
	GuardAI *pGuard = (pCreatureAI != NULL) ? (GuardAI*)pCreatureAI : NULL;
	if (pGuard != NULL)
	{
		if(!pGuard->GetUnit()->disarmed)
			pGuard->CastSpell(pGuard->mIgniteWeapon);
	}
}

class OnyxiasLair : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(OnyxiasLair);
	OnyxiasLair( MapMgr *pMapMgr ) : CreatureAIScript( pMapMgr )
	{
		mWhelpCount = 0;
	};

	void OnCreaturePushToWorld( Creature *pCreature )
	{
		if(pCreature!=NULLCREATURE)
		{
			if(pCreature->GetEntry() == ONY_BOSS)
				mOnyxiaDots = AddTimer(300000);
			if(pCreature->GetEntry() == ONY_WHELP)
				mWhelpCount++;
		}
	};

	void OnCreatureDeath( Creature *pVictim, Unit *pKiller )
	{
		if(pKiller != NULLUNIT && )
		if(pVictim->GetEntry() == ONY_BOSS)
		{
			(GetInstanceMode() == MODE_10PLAYER_NORMAL) ? HandleLairAchievements(ACHIEV_DEFEAT_N) : HandleLairAchievements(ACHIEV_DEFEAT_H);
			if(!IsTimerFinished(mOnyxiaDots))
			{
				RemoveTimer(mOnyxiaDots);
				(GetInstanceMode() == MODE_10PLAYER_NORMAL) ? HandleLairAchievements(ACHIEV_DOTS_N) : HandleLairAchievements(ACHIEV_DOTS_H);
			}
			if(!((OnyxiaAI*)pOnyxia)->mDidHit)
				(GetInstanceMode() == MODE_10PLAYER_NORMAL) ? HandleLairAchievements(ACHIEV_BREATH_N) : HandleLairAchievements(ACHIEV_BREATH_H);
		}
	};

	void UpdateEvent()
	{
		if(pOnyxia->GetAIInterface()->m_moveFly)
			mOnyxiaFly = AddTimer(10000);
		if(!IsTimerFinished(mOnyxiaFly) && mWhelpCount >=50)
		{
			RemoveTimer(mOnyxiaFly);
			(GetInstanceMode() == MODE_10PLAYER_NORMAL) ? HandleLairAchievements(ACHIEV_WHELPS_N) : HandleLairAchievements(ACHIEV_WHELPS_H);
		}	
	};

	void HandleLairAchievements(uint32 pEntry)
	{
		if(pOnyxia == NULL || pOnyxia->GetMapMgr() == NULL)
			return;
		Player *Jerk = NULLPLR;
		for (PlayerStorageMap::iterator itr = pOnyxia->GetMapMgr()->m_PlayerStorage.begin(); itr != pOnyxia->GetMapMgr()->m_PlayerStorage.end(); ++itr) 
		{
			Jerk = itr->second;
			if(Jerk)
				Jerk->GetAchievementInterface()->HandleAchievementCreature(pEntry);
		}
	};

	void Destroy()
	{
		delete this;
	};

private:
	int32 mWhelpCount, mOnyxiaFly, mOnyxiaDots;
	Creature *pOnyxia; // Don't know why, but it crashes when used OnyxiaAI*
};*/

void SetupOnyxiasLair(ScriptMgr* mgr)
{
	//mgr->register_instance_script(MAP_LAIR, &OnyxiasLair::Create);
	mgr->register_creature_script(ONY_BOSS, &OnyxiaAI::Create);
	//mgr->register_creature_script(ONY_GUARD, &GuardAI::Create);
}
