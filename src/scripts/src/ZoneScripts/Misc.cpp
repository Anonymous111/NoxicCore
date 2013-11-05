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

void GuardsOnEmote(Player* pPlayer, Unit* pUnit, uint32 Emote)
{
	if(Emote == EMOTE_ONESHOT_KISS)
		Emote = EMOTE_ONESHOT_BOW;

	if(RandomUInt(100) <= 33 && pPlayer->GetStandingRank(pUnit->m_factionDBC->ID) >= STANDING_FRIENDLY)
		pUnit->Emote(static_cast<EmoteType>(Emote));
}

void OnEmote(Player* pPlayer, Unit* pUnit, uint32 Emote)
{
	if(!pUnit || pUnit->IsDead() || pUnit->CombatStatus.IsInCombat() || !pUnit->GetAIInterface())
		return;

	switch(Emote)
	{
		case EMOTE_ONESHOT_SALUTE:
		case EMOTE_ONESHOT_WAVE:
		case EMOTE_ONESHOT_KISS:
			if(pUnit->GetAIInterface()->m_isGuard)
				GuardsOnEmote(pPlayer, pUnit, Emote);
			break;
	}
}

void SetupZoneMisc(ScriptMgr* mgr)
{
	mgr->register_hook(SERVER_HOOK_EVENT_ON_EMOTE, (void*)&OnEmote);
}