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

#include "StdAfx.h"
#include "Setup.h"

#define PARACHUTE 54168
#define SWIFT_SPECTRAL_GRYPHON 55164
#define SWIFT_FLYING_WHISP 55173

#define ZONE_ICECROWN 210
#define ZONE_STORMPEAKS 65
#define ZONE_WYRMREST_TEMPLE 4161

#define MAP_NORTHREND 571

/*bool isSpectralGryphonZone(uint32 zone)
{
	return ( map == MAP_NORTHREND && ( zone == ZONE_ICECROWN || zone == ZONE_STORMPEAKS || zone == ZONE_WYRMREST_TEMPLE ) );
}

void SpectralGryphonHook(Player * plr, uint32 Zone, uint32 OldZone)
{
	if( plr == NULL )
		return;

	if( plr->IsDead() )
	{
		if( plr->GetMapId() == MAP_NORTHREND && isSpectralGryphonZone(Zone) )
		{
			uint32 spellId = SWIFT_SPECTRAL_GRYPHON
			if( plr->getRace() == RACE_NIGHTELF )
				spellId = SWIFT_FLYING_WHISP;

			if( !plr->HasAura(spellId) )
			{
				plr->CastSpell(plr, spellId, true);
			}
		}
		else if( isSpectralGryphonZone(OldZone) )
		{
			uint32 spellId = SWIFT_SPECTRAL_GRYPHON;
			if( plr->getRace() == RACE_NIGHTELF )
				spellId = SWIFT_FLYING_WHISP;

			if( plr->HasAura(spellId) )
			{
				plr->RemoveAura(spellId);
				// The dead don't need a chute, they're already dead
			}
		}
	}
	else
	{
		uint32 spellId = SWIFT_SPECTRAL_GRYPHON
		if( plr->getRace() == RACE_NIGHTELF )
			spellId = SWIFT_FLYING_WHISP;

		if( plr->HasAura(spellId) && !plr->HasAura(PARACHUTE) )
		{
			plr->RemoveAura(spellId);
			plr->CastSpell(plr, PARACHUTE, true);
		}
	}
}*/

void SetupZoneIcecrown(ScriptMgr* mgr)
{
	//SpectralGryphons
	//mgr->register_hook(SERVER_HOOK_EVENT_ON_ZONE, (void*)&SpectralGryphonHook);
}