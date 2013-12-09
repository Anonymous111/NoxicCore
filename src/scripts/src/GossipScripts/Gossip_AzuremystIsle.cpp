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

class TheKesselRun_Gossip : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* Plr, bool AutoSend)
	{
		GossipMenu* Menu;
		if(pObject->GetEntry() == 17440)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 8997, Plr);
		else if(pObject->GetEntry() == 17240)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9040, Plr);
		else if(pObject->GetEntry() == 17240)
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9038, Plr);

		if(Plr->HasQuest(9663))
			Menu->AddItem(0, "Warn him", 1);
		Menu->SendTo(Plr);
	}

	void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* EnteredCode)
	{
		if(pObject->GetEntry() == 17440)
			sEAS.KillMobForQuest(Plr, 9663, 0);
		else if(pObject->GetEntry() == 17116)
			sEAS.KillMobForQuest(Plr, 9663, 1);
		else if(pObject->GetEntry() == 17240)
			sEAS.KillMobForQuest(Plr, 9663, 2);
	}
};

class DraeneiFishingNet : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* pPlayer)
		{
			if(pObject == NULL || !pObject->IsItem() || pPlayer == NULL)
				return;

			QuestLogEntry* QuestEntry = pPlayer->GetQuestLogForEntry(9452);
			if(QuestEntry == NULL)
				return;

#ifndef BLIZZLIKE
			//if ( QuestEntry->GetMobCount( 0 ) >= QuestEntry->GetQuest()->required_mobcount[ 0 ] )
			//	return;
#endif
			if(pPlayer->GetMapMgr() == NULL)
				return;

			// Meh, double object looking - we should find a way to remove this
			GameObject* School = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 181616);
			if(School == NULL || pPlayer->CalcDistance(School) > 5.0f)
				return;

#ifdef BLIZZLIKE
			sEventMgr.AddEvent(School, &GameObject::Despawn, static_cast< uint32 >(20000), EVENT_GAMEOBJECT_ITEM_SPAWN, 1000, 1, 0);
#else
			School->Despawn(20000, 0);
#endif
			pPlayer->CastSpell(pPlayer, dbcSpell.LookupEntry(TO_ITEM(pObject)->GetProto()->Spells[ 0 ].Id), false);
			uint32 Chance = RandomUInt(10);
			if(Chance <= 3)
			{
				Creature* NewCreature = sEAS.SpawnCreature(pPlayer, 17102, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), 180000);
				if(NewCreature != NULL)
				{
					NewCreature->GetAIInterface()->StopMovement(500);
					NewCreature->setAttackTimer(1000, false);
					NewCreature->m_noRespawn = true;
				};

				return;
			};

			sEAS.AddItem(23614, pPlayer);
			QuestEntry->SendUpdateAddKill(1);
			QuestEntry->UpdatePlayerFields();
			pPlayer->Gossip_Complete();
		};

};

void SetupAzuremystIsleGossip(ScriptMgr* mgr)
{
	mgr->register_gossip_script(17440, new TheKesselRun_Gossip()); // High Chief Stillpine
	mgr->register_gossip_script(17116, new TheKesselRun_Gossip()); // Exarch Menelaous
	mgr->register_gossip_script(17240, new TheKesselRun_Gossip()); // Admiral Odesyus
	//mgr->register_item_gossip_script( 23654, CREATE_GOSSIPSCRIPT( DraeneiFishingNet ) );
}