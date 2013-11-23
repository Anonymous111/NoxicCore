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

class ScourgeGryphonOne : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(Plr->HasQuest(12670))
			{
				TaxiPath* path = sTaxiMgr.GetTaxiPath(1053);
				plr->TaxiStart(path, 26308, 0);
			}
		}
};

class ScourgeGryphonTwo : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(Plr->HasQuest(12670))
			{
				TaxiPath* path = sTaxiMgr.GetTaxiPath(1054);
				plr->TaxiStart(path, 26308, 0);
			}
		}
};

class DKInitiate : public GossipScript
{
public:
	void GossipHello(Object *pObject, Player *Plr, bool AutoSend)
	{
		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 13433, Plr );
		if( Plr->HasQuest(12733) )
			Menu->AddItem( 0, "I Challenge you, death knight!", 1 );

		Menu->SendTo( Plr );
	}

	void GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *EnteredCode)
	{
		Creature *pCreature = TO_CREATURE(pObject);
		Plr->Gossip_Complete();

		// At first change their orientation after gossip ends
		pCreature->SetFacing( Plr->GetOrientation()+float(M_PI) );

		// Spawn duel flag - taken from source from normal duel
		float dist = Plr->CalcDistance( pCreature ) * 0.5f; //half way
		float x = (Plr->GetPositionX() + pCreature->GetPositionX()*dist)/(1+dist) + cos(Plr->GetOrientation()+(float(M_PI)/2))*2;
		float y = (Plr->GetPositionY() + pCreature->GetPositionY()*dist)/(1+dist) + sin(Plr->GetOrientation()+(float(M_PI)/2))*2;
		float z = (Plr->GetPositionZ() + pCreature->GetPositionZ()*dist)/(1+dist);

		//Create flag/arbiter // TODO: SpawnGameObject does not take 6 arguments
		/*GameObject* Flag = sEAS.SpawnGameobject( Plr, 194306, x, y, z, pCreature->GetOrientation() );
		Flag->SetUInt64Value(OBJECT_FIELD_CREATED_BY, Plr->GetGUID());

		Plr->SetDuelArbiter( Flag->GetGUID() );*/

		string say = "";
		switch( RandomUInt(5) )
		{
			case 0:
				say = "Remember this day, ";
				say += Plr->GetName();
				say += ", for it is the day that you will be thoroughly owned.";
				break;
			case 1:
				say = "You have challenged death itself!";
				break;
			case 2:
				say = "Don't make me laugh.";
				break;
			case 3:
				say = "Here come the tears...";
				break;
			case 4:
				say = "No potions!";
				break;
			case 5:
				say = "I'm going to tear your heart out, cupcake!";
				break;
		}
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, say.c_str() );
		// Duel Timer
		WorldPacket *data = sChatHandler.FillMessageData( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL,  "The duel will begin in...", Plr->GetGUID(), 0 );
		Plr->SendPacket( data );
		data = sChatHandler.FillMessageData( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL,  "3...", Plr->GetGUID(), 0 );
		sEventMgr.AddEvent( Plr, &Player::SendPacket, data, EVENT_PLAYER_SEND_PACKET, 1000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		data = sChatHandler.FillMessageData( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL,  "2...", Plr->GetGUID(), 0 );
		sEventMgr.AddEvent( Plr, &Player::SendPacket, data, EVENT_PLAYER_SEND_PACKET, 2000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		data = sChatHandler.FillMessageData( CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL,  "1...", Plr->GetGUID(), 0 );
		sEventMgr.AddEvent( Plr, &Player::SendPacket, data, EVENT_PLAYER_SEND_PACKET, 3000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );


		sEventMgr.AddEvent( TO_UNIT(pCreature), &Unit::SetFaction, uint32(14), EVENT_CREATURE_UPDATE, 3100, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT ); 
	}
};

class Salanar : public GossipScript
{
public:
	void GossipHello(Object *pObject, Player *Plr, bool AutoSend)
	{
		GossipMenu *Menu;
		objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 13355, Plr );
		if( Plr->HasQuest(12687) )
			Menu->AddItem( 0, "Salanar, I must return to the Realm of Shadows.", 1 );
		if(AutoSend)
			Menu->SendTo( Plr );
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(IntId == 1)
		{
			Plr->Gossip_Complete();
			TO_UNIT(pObject)->CastSpell(Plr, 52693, true);
		}
	}
};

void SetupTheScarletEnclaveGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(29488, new ScourgeGryphonOne());
	mgr->register_gossip_script(29501, new ScourgeGryphonTwo());
	mgr->register_gossip_script(28406, new DKInitiate()); // Death Knight Initiate
	mgr->register_gossip_script(28653, new Salanar()); // Salanar the Horseman
}