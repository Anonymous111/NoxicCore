/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
 *
 * This program is free software: you can redistribute it and/or modify
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

class Wormhole : public GossipScript
{
public:
    void GossipHello(Object* pObject, Player* plr)
    {
		if(plr->_GetSkillLineCurrent(202, false) >= 415)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 14785, plr);
			Menu->AddItem(0, "Borean Tundra"    , 1);
			Menu->AddItem(0, "Howling Fjord"  , 2);
			Menu->AddItem(0, "Sholazar Basin"    , 3);
			Menu->AddItem(0, "Icecrown"      , 4);
			Menu->AddItem(0, "Storm Peaks"        , 5);
			
			uint8 chance = RandomUInt(1);

			if (chance == 1)
				Menu->AddItem(0, "Underground..."		,6);
			
			Menu->SendTo(plr);
		}
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
	{

		switch(IntId)
		{
			case 0:  
			GossipHello(pObject, Plr);
			return;
				break;
			case 1:
			Plr->CastSpell(Plr, 67834, true);
				break;
			case 2:
			Plr->CastSpell(Plr, 67838, true);
				break;
			case 3:
			Plr->CastSpell(Plr, 67835, true);
				break;
			case 4:
			Plr->CastSpell(Plr, 67836, true);
				break;
			case 5:
			Plr->CastSpell(Plr, 67837, true);
				break;
			case 6:
			Plr->CastSpell(Plr, 68081, true);
				break;
		}
		Plr->Gossip_Complete();
	}
};

/*class OG_UC_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;

		uint32 textid = 1;
		switch(pObject->GetEntry())
		{
			case ZAPETTA: textid = 2644; break;
			case FREZZA: textid = 2642; break;
			case KRAXX: textid = 11234; break;
			case KRIXX: textid = 11189; break;
		}

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, Plr);
		Menu->AddItem(0, "Where is the zeppelin now?", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char *EnteredCode)
	{
		Transporter* pTransporter = objmgr.GetTransporterByEntry(THUNDERCALLER);
		if(!pTransporter)
			return;

		GossipMenu* Menu = NULL;

		uint32 mapid = pTransporter->GetMapId();

		switch(pTransporter->state)
		{
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if(mapid == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11170, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11182, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if(mapid == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11173, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11169, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if(mapid == 1) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11170, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11182, Plr);
			}break;
		}

		if(Menu)
			Menu->SendTo(Plr);
	}
};

class OG_GG_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;

		uint32 textid = 1;
		switch(pObject->GetEntry())
		{
			case SNURK: textid = 4693; break;
			case NEZRAZ: textid = 2644; break;
		}

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, Plr);
		Menu->AddItem(0, "Where is the zeppelin now?", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		Transporter* pTransporter = objmgr.GetTransporterByEntry(IRONEAGLE);
		if(!pTransporter)
			return;

		GossipMenu* Menu = NULL;

		uint32 mapid = pTransporter->GetMapId();

		switch(pTransporter->state)
		{
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if(mapid == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11170, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11172, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if(mapid == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11167, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11169, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if(mapid == 1) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11170, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11172, Plr);
			}break;
		}

		if(Menu)
			Menu->SendTo(Plr);
	}
};

class UC_GG_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;

		uint32 textid = 1;
		switch(pObject->GetEntry())
		{
			case OVERSPECK: textid = 2642; break;
			case HINDENBURG: textid = 2753; break;
		}

		objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, Plr);
		Menu->AddItem(0, "Where is the zeppelin now?", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		Transporter* pTransporter = objmgr.GetTransporterByEntry(PURPLEPRINCESS);
		if(!pTransporter)
			return;

		GossipMenu* Menu = NULL;

		// special case, this transporter is still on 1 map, so we must check by position
		float x = pTransporter->GetPositionX();
		float y = pTransporter->GetPositionY();
		float z = pTransporter->GetPositionZ();

		switch(pTransporter->state)
		{
			
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if(0 == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11175, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11181, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if(0 == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11180, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11179, Plr);
			}break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if(0 == 0) 
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11181, Plr);
				else
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 11175, Plr);
			}break;
		}

		if(Menu)
			Menu->SendTo(Plr);
	}
};*/

void SetupMiscGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(35646, new Wormhole);
	/*mgr->register_gossip_script(ZAPETTA, new OG_UC_Gossip());
	mgr->register_gossip_script(FREZZA, new OG_UC_Gossip());
	mgr->register_gossip_script(KRIXX, new OG_UC_Gossip());
	mgr->register_gossip_script(KRAXX, new OG_UC_Gossip());
	mgr->register_gossip_script(SNURK, new OG_GG_Gossip());
	mgr->register_gossip_script(NEZRAZ, new OG_GG_Gossip());
	mgr->register_gossip_script(OVERSPECK, new UC_GG_Gossip());
	mgr->register_gossip_script(HINDENBURG, new UC_GG_Gossip());*/
}