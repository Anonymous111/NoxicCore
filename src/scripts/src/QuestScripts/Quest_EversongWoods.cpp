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

// Whitebark's Memory Quest 10166
/*bool Whitebark_Memory(uint32 i, Spell* pSpell)
{
	Player *pPlayer = (Player*)pSpell->u_caster;
	if(!pPlayer)
		return true;

	if(!pSpell->u_caster->IsPlayer())
		return true;

	QuestLogEntry *en = pPlayer->GetQuestLogForEntry(10166);
	if(en == NULL)
		return true;

	Creature * WhitebarkSprit= pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(8187.786, -6337.986, 64.51,19456);
	if (WhitebarkSprit==NULL )
	{
		Creature * WhitebarkSpawn= sEAS.SpawnCreature(pPlayer, 19456, 8187.786, -6337.986, 64.51, 3.369,120000);
		WhitebarkSpawn->SetUInt32Value(UNIT_NPC_FLAGS, 0);
		WhitebarkSpawn->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 14);
		WhitebarkSpawn->_setFaction();
	}
	return true;
};

class WhitebarkSpirit : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WhitebarkSpirit);
		WhitebarkSpirit(Creature* pCreature) : CreatureAIScript(pCreature) {}
		void OnCombatStart(Unit* mTarget)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You've returned. Haven't you done enough?");
			RegisterAIUpdateEvent(1000);
		}
		void AIUpdate()
		{
			if(_unit->GetHealthPct() < 35)
			{
				RemoveAIUpdateEvent();
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Very well...I admit defeat");
				_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
				_unit->_setFaction();
				_unit->GetAIInterface()->disable_combat = true;
				_unit->setDeathState(CORPSE);
				_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
				_unit->Despawn(30000, 0);
			}
		}
		void OnCombatStop(Unit* mTarget)
		{
			RemoveAIUpdateEvent();
		}
		void OnTargetDied(Unit* mTarget)
		{
			RemoveAIUpdateEvent();
		}
		void OnDied(Unit *mKiller)
		{
			RemoveAIUpdateEvent();
		}
};

// Unexpected Results Quest 8488
class SCRIPT_DECL UnexpectedResults : public QuestScript
{
	public:
		void OnQuestStart(Player* pPlayer, QuestLogEntry *qLogEntry)
		{
			if( pPlayer == NULL || pPlayer->GetMapMgr() == NULL)
				return;

			Creature *Mirveda = pPlayer->GetMapMgr()->GetSqlIdCreature(40436);
			if(Mirveda == NULL)
				return;

			Creature * RotlimbA=  sEAS.SpawnCreature(pPlayer, 15658, 8732.59, -7144.96, 35.22, 3.56, 48000);
			Creature * RotlimbB=  sEAS.SpawnCreature(pPlayer, 15658, 8726.72, -7137.34, 35.22, 3.98, 48000);
			Creature * RotlimbC=  sEAS.SpawnCreature(pPlayer, 15658, 8718.37, -7132.00, 35.22, 4.30, 48000);
			RotlimbA->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbA->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbA->m_noRespawn=true;
			RotlimbB->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbB->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbB->m_noRespawn=true;
			RotlimbC->GetAIInterface()->SetNextTarget(Mirveda);
			RotlimbC->GetAIInterface()->MoveTo(Mirveda->GetPositionX(), Mirveda->GetPositionY(), Mirveda->GetPositionZ(), Mirveda->GetOrientation());
			RotlimbC->m_noRespawn=true;
			Mirveda->SetUInt32Value(UNIT_NPC_FLAGS, 0);
			Mirveda->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, pPlayer->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
			Mirveda->_setFaction();
			TimedEvent *te1 = TimedEvent::Allocate(this, new CallbackP1<UnexpectedResults, Player*>(this, &UnexpectedResults::QuestComplete, pPlayer), 0, 60000, 1);  
			pPlayer->event_AddEvent(te1);
			TimedEvent *te2 = TimedEvent::Allocate(this, new CallbackP1<UnexpectedResults, Creature*>(this, &UnexpectedResults::MirvedaReset, Mirveda), 0, 63000, 1);  
			Mirveda->event_AddEvent(te2);
		}
  
		void QuestComplete(Player * pPlayer)
		{
			Creature *Mirveda = pPlayer->GetMapMgr()->GetSqlIdCreature(40436);
			QuestLogEntry *en = pPlayer->GetQuestLogForEntry(8488);
			if(en && Mirveda->isAlive())
			{
				Mirveda->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "We made it!...thanks for protecting me");
				Mirveda->Emote(EMOTE_ONESHOT_LAUGH);
				en->SetMobCount(0, 1);
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
				en->SendQuestComplete();
				return;
			}
		}

		void MirvedaReset(Creature * AMirveda)
        {
			AMirveda->GetAIInterface()->SetAIState(STATE_IDLE);
			AMirveda->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 1604);
			AMirveda->_setFaction();
			AMirveda->SetUInt32Value(UNIT_NPC_FLAGS, 2);
		}
};

class ApprenticeMirveda : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ApprenticeMirveda);
		ApprenticeMirveda(Creature* pCreature) : CreatureAIScript(pCreature) {}
		void OnLoad()
		{
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 1604);
			_unit->_setFaction();
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 2);
		}
};

// The Dwarven Spy Quest 8483
class SCRIPT_DECL DwarvenSpy : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer, bool AutoSend)
		{
			if(!pPlayer)
				return;

			GossipMenu *Menu;
			Creature *DwarvenSpy = (Creature*)(pObject);
			if(DwarvenSpy == NULL)
				return;

			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 8239, pPlayer);
			if(pPlayer->GetQuestLogForEntry(8483) && pPlayer->GetItemInterface()->GetItemCount(20764) < 1)
				Menu->AddItem( 0, "I need a moment of your time, sir.", 1);

			if(AutoSend)
				Menu->SendTo(pPlayer);
		}
		void GossipSelectOption(Object* pObject, Player* pPlayer, uint32 Id, uint32 IntId, const char * EnteredCode)
		{
			if(!pPlayer)
				return;

			Creature *DwarvenSpy = (Creature*)(pObject);
			if(DwarvenSpy == NULL)
				return;

			switch (IntId)
			{
				case 0:
					GossipHello(pObject, pPlayer, true);
				break;
				case 1:
				{
					GossipMenu *Menu;
					if(pPlayer->GetItemInterface()->GetItemCount(20764) < 1)
					{
						if(!DwarvenSpy)
							return;

						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 8240, pPlayer);
						Menu->AddItem( 0, "Why... yes, of course. I've something to show you right inside this building, Mr. Anvilward.", 2);
						Menu->SendTo(pPlayer);
					}
					return;
				}break;
				case 2:
				{
					if(pPlayer->GetItemInterface()->GetItemCount(20764) < 1)
					{
						if(!DwarvenSpy)
							return;

						DwarvenSpy->SetUInt32Value(UNIT_NPC_FLAGS, 0);
						DwarvenSpy->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Very well. Let's see what you have to show me");
						DwarvenSpy->GetAIInterface()->setMoveType(2);
						DwarvenSpy->GetAIInterface()->StopMovement(3000);
						sEAS.WaypointCreate(DwarvenSpy,9290.84f, -6683.41f, 22.423f, 5.983f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9294.61f, -6682.60f, 22.424f, 1.340f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9297.54f, -6670.08f, 22.399f, 0.307f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9306.00f, -6667.38f, 22.429f, 1.123f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9309.392, -6659.37f, 22.432f, 1.748f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9307.65f, -6652.02f, 24.712f, 2.648f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9299.86f, -6648.17f, 28.341f, 3.403f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9293.33f, -6649.84f, 30.444f, 4.068f, 0, 0, 15426);
						sEAS.WaypointCreate(DwarvenSpy,9288.21f, -6657.44f, 31.829f, 1.208f, 0, 0, 15426);
					}
					return;
				}break;
			}
		}
		void Destroy()
		{
			delete this;
		}
};

class DwarvenSpyState : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DwarvenSpyState);
		DwarvenSpyState(Creature* pCreature) : CreatureAIScript(pCreature) {}
		void OnLoad()
		{
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
			_unit->_setFaction();
			_unit->SetUInt32Value(UNIT_NPC_FLAGS, 1);
		}
		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			switch(iWaypointId)
			{
				case 9:
				{
					sEAS.DeleteWaypoints(_unit);
					_unit->Despawn(120000,1000);
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "What manner of trick is this? If you seek to ambush me, I warn you I will not go down quietly!");
					_unit->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 14);
					_unit->_setFaction();
				}break;
			}
		}
};*/

static LocationExtra ProspectorAnvilwardWaypoints[] =
{
	{ 9294.834f, -6681.092f, 22.428f, 1.284f, 0 },
	{ 9297.834f, -6671.092f, 22.387f, 0.793f, 0 },
	{ 9310.375f, -6658.936f, 22.43f,  2.046f, 0 },
	{ 9306.596f, -6650.905f, 25.222f, 2.666f, 0 },
	{ 9299.666f, -6648.099f, 28.39f,  3.468f, 0 },
	{ 9292.345f, -6650.509f, 30.908f, 4.249f, 0 },
	{ 9289.426f, -6657.825f, 31.829f, 6.154f, 0 },
	{ 9294.095f, -6658.863f, 34.482f, 6.063f, 0 },
};

class ProspectorAnvilwardGossip : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* Plr);
		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode);
		void GossipEnd(Object* pObject, Player* Plr) { Plr->CloseGossip(); }
};

void ProspectorAnvilwardGossip::GossipHello(Object* pObject, Player* Plr)
{
	GossipMenu* Menu;
	objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2, Plr);

	Menu->AddItem(0, "Show me...", 1);

	Menu->SendTo(Plr);
}

void ProspectorAnvilwardGossip::GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
{
	if(!pObject->IsCreature())
		return;
	Creature* _unit = TO< Creature* >(pObject);
	switch(IntId)
	{
		case 1:
			{
				QuestLogEntry* qLogEntry = Plr->GetQuestLogForEntry(8483);
				if(qLogEntry != NULL)
				{
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Follow me!");
					_unit->m_custom_waypoint_map = new WayPointMap;
					_unit->GetAIInterface()->SetWaypointMap(_unit->m_custom_waypoint_map);
					WayPoint* wp = new WayPoint;
					wp->id = 1;
					wp->x = _unit->GetSpawnX();
					wp->y = _unit->GetSpawnY();
					wp->z = _unit->GetSpawnZ() + 2.05f;
					wp->o = _unit->GetSpawnO();
					wp->flags = 256;
					wp->backwardskinid = wp->forwardskinid = _unit->GetDisplayId();
					wp->backwardemoteid = wp->forwardemoteid = 0;
					wp->backwardemoteoneshot = wp->forwardemoteoneshot = false;
					wp->waittime = 0;
					_unit->m_custom_waypoint_map->push_back(wp);
					for(uint32 i = 0; i < sizeof(ProspectorAnvilwardWaypoints) / sizeof(LocationExtra); i++)
					{
						wp = new WayPoint;
						wp->id = i + 2;
						wp->x = ProspectorAnvilwardWaypoints[i].x;
						wp->y = ProspectorAnvilwardWaypoints[i].y;
						wp->z = ProspectorAnvilwardWaypoints[i].z;
						wp->o = ProspectorAnvilwardWaypoints[i].o;
						wp->flags = 256;
						wp->backwardskinid = wp->forwardskinid = _unit->GetDisplayId();
						wp->backwardemoteid = wp->forwardemoteid = 0;
						wp->backwardemoteoneshot = wp->forwardemoteoneshot = false;
						wp->waittime = 0;
						_unit->m_custom_waypoint_map->push_back(wp);
					}
				}
				else
				{
					_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I have nothing for you. Go away!");
				}
				GossipEnd(pObject, Plr);
			}
			break;
	}
}

class ProspectorAnvilwardAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ProspectorAnvilwardAI);
		ProspectorAnvilwardAI(Creature* c) : CreatureAIScript(c)
		{
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == sizeof(ProspectorAnvilwardWaypoints) / sizeof(LocationExtra) && bForwards)
			{
				_unit->GetAIInterface()->SetWaypointMap(NULL, false);
				_unit->SetFaction(14);
				RegisterAIUpdateEvent(10000);
			}
			else if(iWaypointId == 2 && !bForwards)
			{
				_unit->GetAIInterface()->SetWaypointMap(NULL);
				_unit->m_custom_waypoint_map = NULL;
				_unit->GetAIInterface()->MoveTo(_unit->GetSpawnX(), _unit->GetSpawnY(), _unit->GetSpawnZ() + 2.05f, _unit->GetSpawnO());
				_unit->SetFaction(35);
			}
		}

		void AIUpdate()
		{
			if(!_unit->CombatStatus.IsInCombat())
			{
				RemoveAIUpdateEvent();
				_unit->GetAIInterface()->SetWaypointMap(_unit->m_custom_waypoint_map);
			}
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
			if(_unit->GetAIInterface()->GetWaypointMap() != NULL)
				_unit->GetAIInterface()->SetWaypointMap(NULL);
			else if(_unit->m_custom_waypoint_map != NULL)
			{
				for(WayPointMap::iterator itr = _unit->m_custom_waypoint_map->begin(); itr != _unit->m_custom_waypoint_map->end(); ++itr)
					delete(*itr);
				delete _unit->m_custom_waypoint_map;
			}
			_unit->m_custom_waypoint_map = NULL;

			_unit->SetFaction(35);
		}
};

class ThirstUnending : public QuestScript
{
public:
	Player* pPlayer;
	Creature* pCreature = _unit->GetEntry(15274);
	if(pCreature->GetSpellEntry(28730 || 25046 || 50613))
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(8346);
		//pCreature->KillMob() // Should kill the mob, what is that damn command?!
		pQuest->SendQuestComplete();
	}
};

void SetupEversongWoods(ScriptMgr* mgr)
{
	mgr->register_gossip_script(15420, new ProspectorAnvilwardGossip);
	mgr->register_creature_script(15420, &ProspectorAnvilwardAI::Create);
	/*GossipScript* DwarvenSpyGossip = (GossipScript*) new DwarvenSpy();
	mgr->register_gossip_script(15420, DwarvenSpyGossip);
	mgr->register_creature_script(15420, &DwarvenSpyState::Create);
	mgr->register_dummy_spell(33980, &Whitebark_Memory);
	mgr->register_creature_script(19456, &WhitebarkSpirit::Create);
	mgr->register_quest_script(8488, CREATE_QUESTSCRIPT(UnexpectedResults));
	mgr->register_creature_script(15402, &ApprenticeMirveda::Create);*/
	mgr->register_quest_script(8346, new ThirstUnending());
}