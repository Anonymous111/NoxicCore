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
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)
{
	SetupZoneArathiHighlands(mgr);
	SetupAzuremystIsle(mgr);
	SetupZoneBladeEdgeMountains(mgr);
	SetupZoneBlastedLands(mgr);
	SetupZoneBloodmystIsle(mgr);
	SetupZoneBoreanTundra(mgr);
	SetupZoneDarnassus(mgr);
	SetupZoneDurotar(mgr);
	SetupZoneExodar(mgr);
	SetupZoneHellfirePeninsula(mgr);
	SetupZoneIcecrown(mgr);
	SetupZoneIronforge(mgr);
	SetupZoneMisc(mgr);
	SetupZoneOrgrimmar(mgr);
	SetupZoneShadowmoonValley(mgr);
	SetupZoneSilverpineForest(mgr);
	SetupZoneTanaris(mgr);
	SetupZoneTheBarrens(mgr);
	SetupZoneThousandNeedles(mgr);
	SetupZoneTheScarletEnclave(mgr);
	SetupZoneThunderBluff(mgr);
	SetupZoneTirisfalGlades(mgr);
	SetupZoneUndercity(mgr);
	SetupZoneUnGoroCrater(mgr);
	SetupZoneWesternPlaguelands(mgr);
	SetupZoneWestfall(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

#endif
