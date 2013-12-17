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
//#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	// Eastern Kingdom
	SetupZoneArathiHighlands(mgr);
	SetupZoneBlastedLands(mgr);
	SetupZoneDuskwood(mgr);
	SetupZoneEasternPlaguelands(mgr);
	SetupZoneElwynnForest(mgr);
	SetupZoneEversongWoods(mgr);
	SetupZoneGhostlands(mgr);
	SetupZoneHillsbradFoothills(mgr);
	SetupZoneIronforge(mgr);
	SetupZoneIsleOfQuelDanas(mgr);
	SetupZoneLochModan(mgr);
	SetupZoneRedridgeMountains(mgr);
	SetupZoneSilvermoonCity(mgr);
	SetupZoneSilverpineForest(mgr);
	SetupZoneStormwindCity(mgr);
	SetupZoneStranglethorn(mgr);
	SetupZoneTheScarletEnclave(mgr);
	SetupZoneTirisfalGlades(mgr);
	SetupZoneUndercity(mgr);
	SetupZoneWesternPlaguelands(mgr);
	SetupZoneWestfall(mgr);

	// Kalimdor
	SetupZoneAzshara(mgr);
	SetupZoneAzuremystIsle(mgr);
	SetupZoneBloodmystIsle(mgr);
	SetupZoneDarkshore(mgr);
	SetupZoneDarnassus(mgr);
	SetupZoneDesolace(mgr);
	SetupZoneDurotar(mgr);
	SetupZoneDustwallowMarsh(mgr);
	SetupZoneExodar(mgr);
	SetupZoneMulgore(mgr);
	SetupZoneOrgrimmar(mgr);
	SetupZoneTanaris(mgr);
	SetupZoneTheBarrens(mgr);
	SetupZoneThousandNeedles(mgr);
	SetupZoneThunderBluff(mgr);
	SetupZoneUnGoroCrater(mgr);

	// Outland
	SetupZoneBladeEdgeMountains(mgr);
	SetupZoneHellfirePeninsula(mgr);
	SetupZoneNagrand(mgr);
	SetupZoneShadowmoonValley(mgr);
	SetupZoneTerrokarForest(mgr);

	// Northrend
	SetupZoneBoreanTundra(mgr);
	SetupZoneDragonblight(mgr);
	SetupZoneHowlingFjord(mgr);
	SetupZoneIcecrown(mgr);
	SetupZoneSholazarBasin(mgr);

	// Other
	SetupZoneMisc(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

#endif
