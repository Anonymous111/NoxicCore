/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
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

#define BUFF_RESPAWN_TIME 90000
#define WSG_MAX_MATCH_TIME 25

class WarsongGulch : public CBattleground
{
		GameObject* m_buffs[6];
		GameObject* m_homeFlags[2];
		GameObject* m_dropFlags[2];
		uint32 m_flagHolders[2];
		list<GameObject*> m_gates;
		uint8 m_scores[2];
		uint32 m_lgroup;
		uint8 m_timeElapsed;
	public:
		WarsongGulch(MapMgr* mgr, uint32 id, uint32 lgroup, uint32 t);
		~WarsongGulch();

		void HookOnPlayerDeath(Player* plr);
		void HookFlagDrop(Player* plr, GameObject* obj);
		void HookFlagStand(Player* plr, GameObject* obj);
		void HookOnMount(Player* plr);
		void HookOnAreaTrigger(Player* plr, uint32 id);
		bool HookHandleRepop(Player* plr);
		void OnAddPlayer(Player* plr);
		void OnRemovePlayer(Player* plr);
		void OnCreate();
		void HookOnPlayerKill(Player* plr, Player* pVictim);
		void HookOnUnitKill(Player* plr, Unit* pVictim);
		void HookOnHK(Player* plr);
		void HookOnShadowSight();
		void HookGenerateLoot(Player* plr, Object* pCorpse);
		void SpawnBuff(uint32 x);
		LocationVector GetStartingCoords(uint32 Team);
		void HookOnFlagDrop(Player* plr);
		void ReturnFlag(uint8 team);

		void EventReturnFlags();

		static CBattleground* Create(MapMgr* m, uint32 i, uint32 l, uint32 t) { return new WarsongGulch(m, i, l, t); }

		uint32 GetNameID() { return 39; }
		uint64 GetFlagHolderGUID( uint32 faction ) const{ return m_flagHolders[ faction ]; }
		void OnStart();

		void SetIsWeekend(bool isweekend);
		void DespawnGates(uint32 delay);
		void WarsongGulch::TimerTick();
};
