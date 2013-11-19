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

class Blastenheimer5000 : public GameObjectAIScript
{
public:
	Blastenheimer5000(GameObject* pGameObject) : GameObjectAIScript(pGameObject)
	{
		mPlayerGuid = 0;
	};

	static GameObjectAIScript* Create(GameObject* pGameObject)
	{
		return new Blastenheimer5000(pGameObject);
	};

	void OnActivate(Player* pPlayer)
	{
		if(mPlayerGuid != 0)
			return;

		// Do you think we should look for AI owner ?
		/*GameObject* BlastCannon = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 180515);
		if(BlastCannon != NULL)
			BlastCannon->SetUInt32Value(GAMEOBJECT_FLAGS, 33);*/

		pPlayer->CastSpell(pPlayer, 24832, true);
		pPlayer->SetMovement(MOVE_ROOT, 1);
		_gameobject->PlaySoundToSet(8476);
		mPlayerGuid = static_cast<uint32>(pPlayer->GetGUID());
		RegisterAIUpdateEvent(2200);
	};

	void AIUpdate()
	{
		Player* pPlayer = objmgr.GetPlayer(mPlayerGuid);
		if(pPlayer == NULL)
		{
			RemoveAIUpdateEvent();
			mPlayerGuid = 0;
			return;
		};

		if(pPlayer->GetMapId() == 530) // Shattrath
			pPlayer->SafeTeleport(530, 0, -1742.640869f, 5454.712402f, -7.928009f, 4.606363f);
		else if(pPlayer->GetMapId() == 0) // Elwynn Forest
			pPlayer->SafeTeleport(0, 0, -9569.150391f, -14.753426f, 68.051422f, 4.874008f);
		else if(pPlayer->GetMapId() == 1) // Mulgore
			pPlayer->SafeTeleport(1, 0, -1326.711914f, 86.301125f, 133.093918f, 3.510725f);

		pPlayer->SetMovement(MOVE_UNROOT, 1);
		pPlayer->CastSpell(pPlayer, 42867, true); // 24742
		_gameobject->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
		mPlayerGuid = 0;
		RemoveAIUpdateEvent();
	};

protected:
	uint32	mPlayerGuid;
};

/*
Spells:
=====================
Cannon - 24933
Mortor - 25003
Drop Mine - 39685, 25024
Nitrous Boost - 27746

class TonkControlConsole : public GameObjectAIScript
{
public:
	TonkControlConsole(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new TonkControlConsole(GO); }

	// Click the Console
	void OnActivate(Player* pPlayer)
	{
		// Pre-flight checks
		GameObject* tonkConsole = NULL;
		tonkConsole = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 180524);

		// Open and disable the Tonk Console
		tonkConsole->SetUInt32Value(GAMEOBJECT_FLAGS, 1);
		tonkConsole->SetState(0);

		// Spawn Steam Tonk
		pPlayer->GetMapMgr()->GetInterface()->SpawnCreature(19405, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), true, false, 0, 0)->Despawn(310000, 0);;

		// Store the tonk just spawned
		Creature* pTonk = NULL;
		pTonk = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 19405);

		// Cast the tonk control spell on the tonk
		pPlayer->CastSpell(pTonk, 33849, false);

		// Start checks to see if player still has aura
		RegisterAIUpdateEvent(1000);

		Tonk = pTonk;
		Console = tonkConsole;
	}

	void AIUpdate()
	{
		if(!pPlayer->HasAura(33849) || Tonk->isDead())
		{
			// Kill then Despawn Tonk after 10 seconds
			pPlayer->CastSpell(Tonk, 5, false); // Kill spell
			pPlayer->CastSpell(pPlayer, 2880, false); // Stun Player
			pPlayer->RemoveAura(33849);
			Tonk->Despawn(10000,0);

			// Close the console so others can access it
			Console->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
			Console->SetState(1);
			RemoveAIUpdateEvent();
		}
	}

protected:
	Player* pPlayer;
	Creature* Tonk;
	GameObject* Console;
};
*/

class DMF_MusicDoodad : public GameObjectAIScript
{
public:
	DMF_MusicDoodad(GameObject* goinstance) : GameObjectAIScript(goinstance){RegisterAIUpdateEvent(1000);}
	static GameObjectAIScript* Create(GameObject* pGameObject) { return new DMF_MusicDoodad(pGameObject); }
	
	void AIUpdate()
	{
		_gameobject->PlaySoundToSet(8440); // Play Darkmoon Faire Music
	}
};

void SetupDarkmoonFaireObjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(180515, &Blastenheimer5000::Create);
	mgr->register_gameobject_script(186560, &Blastenheimer5000::Create);
	mgr->register_gameobject_script(180452, &Blastenheimer5000::Create);
	//mgr->register_gameobject_script(180524, &TonkControlConsole::Create);
	mgr->register_gameobject_script(180335, &DMF_MusicDoodad::Create);
}