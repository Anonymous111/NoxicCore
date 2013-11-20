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

#ifndef ZONE_SCRIPTS_SETUP_H
#define ZONE_SCRIPTS_SETUP_H

#include "StdAfx.h"
#include "../Common/EasyFunctions.h"

// Northrend
void SetupZoneIcecrown(ScriptMgr* mgr);
void SetupZoneBoreanTundra(ScriptMgr* mgr);

// Eastern Kingdom
void SetupZoneArathiHighlands(ScriptMgr* mgr);
void SetupZoneBlastedLands(ScriptMgr* mgr);
void SetupZoneIronforge(ScriptMgr* mgr);
void SetupZoneSilvermoonCity(ScriptMgr* mgr);
void SetupZoneSilverpineForest(ScriptMgr* mgr);
void SetupZoneTheScarletEnclave(ScriptMgr* mgr);
void SetupZoneTirisfalGlades(ScriptMgr* mgr);
void SetupZoneUndercity(ScriptMgr* mgr);
void SetupZoneWesternPlaguelands(ScriptMgr* mgr);
void SetupZoneWestfall(ScriptMgr* mgr);

// Kalimdor
void SetupZoneBloodmystIsle(ScriptMgr* mgr);
void SetupZoneDarnassus(ScriptMgr* mgr);
void SetupZoneDurotar(ScriptMgr* mgr);
void SetupZoneExodar(ScriptMgr* mgr);
void SetupZoneOrgrimmar(ScriptMgr* mgr);
void SetupZoneTanaris(ScriptMgr* mgr);
void SetupZoneTheBarrens(ScriptMgr* mgr);
void SetupZoneThousandNeedles(ScriptMgr* mgr);
void SetupZoneThunderBluff(ScriptMgr* mgr);
void SetupZoneUnGoroCrater(ScriptMgr* mgr);

// Outland
void SetupAzuremystIsle(ScriptMgr* mgr);
void SetupZoneBladeEdgeMountains(ScriptMgr* mgr);
void SetupZoneHellfirePeninsula(ScriptMgr* mgr);
void SetupZoneShadowmoonValley(ScriptMgr* mgr);

// Other
void SetupZoneMisc(ScriptMgr* mgr);

#endif
