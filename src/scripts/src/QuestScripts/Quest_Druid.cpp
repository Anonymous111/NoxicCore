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

/**********************
Edits by : FenixGman
**********************/
#include "Setup.h"

/*bool CenarionMoondust(uint32 i, Spell* pSpell) // Body And Heart (Alliance)
{
	const float pos[] = {6348.540039f, 128.124176f, 22.024008f, 4.172032f}; // x, y, z, o
	PlayerPointer p_caster = pSpell->p_caster;
		if(!pSpell->p_caster)
			return true;

	CreaturePointer lunaclaw = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pos[0], pos[1], pos[2], 12138);
	if(lunaclaw != NULL)
		if!pSpell->p_caster->IsInWorld())
			return true;

	const float pos[] = {6335.2329f, 144.0811f, 24.0068f, 5.701f}; // x, y, z, o
	Player * p_caster = pSpell->p_caster;

	// Moonkin Stone Aura
	GameObject * Msa = sEAS.SpawnGameobject(p_caster, 177644, 6331.01, 88.245, 22.6522, 2.01455, 1.0, 0.0, 0.0, 0.0, 0.0);

	// It don't delete lunaclaw if he is here
	Creature * lunaclaw; //p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords([pos[0], pos[1], pos[2], 12138);
	//if(lunaclaw != NULL)
	//{
		//if(!lunaclaw->isAlive())
			//lunaclaw->Delete;
		//else
			//return true;
	//}

	lunaclaw = sEAS.SpawnCreature(p_caster, 12138, pos[0], pos[1], pos[2], pos[3], 0);
	//lunaclaw->GetAIInterface()->SetNextTarget(p_caster);

	sEAS.CreatureCustomWaypointMap(lunaclaw);
	uint32 md = lunaclaw->GetUInt32Value(UNIT_FIELD_DISPLAYID);

	// Waypoints
	sEAS.WaypointCreate(lunaclaw, 6348.3833, 132.5197, 21.6042, 4.19, 200, 256, md);
	// Make sure that player don't cheat speed or something
	if(lunaclaw->GetDistance2dSq(p_caster) < 200) // Can be more? - he can speed hack or teleport hack
	{
		float x = p_caster->GetPositionX();
		float y = p_caster->GetPositionY();
		float z = p_caster->GetPositionZ();
		float o = p_caster->GetOrientation();
		sEAS.WaypointCreate(lunaclaw, x, y, z, o, 200, 256, md);
	}
	else
	{
		sEAS.WaypointCreate(lunaclaw, 5328.2148, 94.5505, 21.4547, 4.2489, 200, 256, md);
	}

	// Make sure that creature will attack player
	if(!lunaclaw->CombatStatus.IsInCombat())
	{
		lunaclaw->GetAIInterface()->SetNextTarget(p_caster);
		sEAS.MoveToPlayer(p_caster, lunaclaw);
	}

	return true;
}*/

class Lunaclaw : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Lunaclaw);

		Lunaclaw(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnDied(Unit* mKiller)
		{
			if(!mKiller->IsPlayer())
				return;

			Player* plr = TO_PLAYER(mKiller);

			sEAS.SpawnCreature(plr, 12144, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 0, 1 * 60 * 1000);
		}
};

// Lunaclaw ghost gossip
#define GOSSIP_GHOST_MOONKIN    "You have fought well, spirit. I ask you to grand me the strenght of your body and the strenght of your heart."

class SCRIPT_DECL MoonkinGhost_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4714, plr);

			if(plr->HasQuest(6002))
			{
				Menu->AddItem(0, GOSSIP_GHOST_MOONKIN, 1);  //Horde
			}
			else if(plr->HasQuest(6001))
			{
				Menu->AddItem(0, GOSSIP_GHOST_MOONKIN, 2);  //Ally
			}

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			if(!pObject->IsCreature())
				return;
			Creature* pCreature = TO_CREATURE(pObject);

			GossipMenu* Menu;
			switch(IntId)
			{
				case 0: // Return to start
					GossipHello(pCreature, plr);
					break;

				case 1: //Horde
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4715, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(6002);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();

						pCreature->Emote(EMOTE_ONESHOT_WAVE);
						pCreature->Despawn(240000, 0);
					}
					break;

				case 2: //Ally
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4715, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(6001);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();

						pCreature->Emote(EMOTE_ONESHOT_WAVE);
						pCreature->Despawn(240000, 0);
					}
					break;

			}
		}
};

// bear ghost gossip
#define GOSSIP_GHOST_BEAR_A    "What do you represent, spirit?"
#define GOSSIP_GHOST_BEAR_B    "I seek to understand the importance of strength of the body."
#define GOSSIP_GHOST_BEAR_C    "I seek to understand the importance of strength of the heart."
#define GOSSIP_GHOST_BEAR_D    "I have heard your words, Great Bear Spirit, and I understand. I now seek your blessings to fully learn the way of the Claw."

class SCRIPT_DECL BearGhost_Gossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4719, plr);

			if(plr->HasQuest(5930)) // horde
			{
				Menu->AddItem(0, GOSSIP_GHOST_BEAR_A, 1);
			}
			else if(plr->HasQuest(5929)) // ally
			{
				Menu->AddItem(0, GOSSIP_GHOST_BEAR_A, 5);
			}

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature*  pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(!pObject->IsCreature())
				return;

			GossipMenu* Menu;
			switch(IntId)
			{
				case 0: // Return to start
					GossipHello(pCreature, plr);
					break;
				case 1:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4721, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_B, 2);
						Menu->SendTo(plr);
						break;
					}
				case 2:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4733, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_C, 3);
						Menu->SendTo(plr);
						break;
					}
				case 3:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4734, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_D, 4);
						Menu->SendTo(plr);
						break;
					}
				case 4:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4735, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(5930);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();
						break;
					}
				case 5:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4721, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_B, 6);
						Menu->SendTo(plr);
						break;
					}
				case 6:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4733, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_C, 7);
						Menu->SendTo(plr);
						break;
					}
				case 7:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4734, plr);
						Menu->AddItem(0, GOSSIP_GHOST_BEAR_D, 8);
						Menu->SendTo(plr);
						break;
					}
				case 8:
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4735, plr);
						Menu->SendTo(plr);

						QuestLogEntry* qle = plr->GetQuestLogForEntry(5929);
						if(qle == NULL)
							return;

						if(qle->CanBeFinished())
							return;

						qle->Complete();
						qle->SendQuestComplete();
						qle->UpdatePlayerFields();
						break;
					}
			}
		}
};

class MoongladeQuest : public QuestScript
{
	public:
		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			if(!mTarget->HasSpell(19027))
				mTarget->CastSpell(mTarget, dbcSpell.LookupEntry(19027), true);
		}
};



void SetupDruid(ScriptMgr* mgr)
{

	GossipScript* MoonkinGhostGossip = new MoonkinGhost_Gossip;
	GossipScript* BearGhostGossip = new BearGhost_Gossip;
	QuestScript* Moonglade = new MoongladeQuest();
	mgr->register_quest_script(5921, Moonglade);
	mgr->register_quest_script(5922, Moonglade);
	mgr->register_creature_script(12138, &Lunaclaw::Create);

	//Register gossip scripts
	mgr->register_gossip_script(12144, MoonkinGhostGossip); // Ghost of Lunaclaw
	mgr->register_gossip_script(11956, BearGhostGossip); // Great Bear Spirit

}

