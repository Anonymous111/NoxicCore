/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (c) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(mgr);
{
	SetupAlteracMountainsGossip(mgr);
	SetupArgentTournamentGossip(mgr);
	SetupAzsharaGossip(mgr);
	SetupAzuremystIsleGossip(mgr);
	SetupBattlemasterGossip(mgr);
	SetupBlastedLandsGossip(mgr);
	SetupBloodmystIsleGossip(mgr);
	SetupBoreanTundraGossip(mgr);
	SetupCrystalsongForestGossip(mgr);
	SetupDalaranGossip(mgr);
	SetupDarkshoreGossip(mgr);
	SetupDragonblightGossip(mgr);
	SetupDustwallowMarshGossip(mgr);
	SetupEasternPlaguelandsGossip(mgr);
	SetupEversongWoodsGossip(mgr);
	SetupGhostlandsGossip(mgr);
	SetupGuardGossip(mgr);
	SetupHellfirePeninsulaGossip(mgr);
	SetupHowlingFjordGossip(mgr);
	SetupInnkeepers(mgr);
	SetupIsleOfQuelDanasGossip(mgr);
	SetupLocksmiths(mgr);
	SetupMiscGossip(mgr);
	SetupMoongladeGossip(mgr);
	SetupMulgoreGossip(mgr);
	SetupNagrandGossip(mgr);
	SetupNetherstormGossip(mgr);
	SetupShadowmoonValleyGossip(mgr);
	SetupShattrathGossip(mgr);
	SetupSholazarBasinGossip(mgr);
	SetupSilithusGossip(mgr);
	SetupSilvermoonCityGossip(mgr);
	SetupStormwindGossip(mgr);
	SetupStranglethornValeGossip(mgr);
	SetupTanarisGossip(mgr);
	SetupTeldrassilGossip(mgr);
	SetupTerrokarForestGossip(mgr);
	SetupTheBarrensGossip(mgr);
	SetupTheramoreGossip(mgr);
	SetupTheScarletEnclaveGossip(mgr);
	SetupTheStormPeaksGossip(mgr);
	SetupTrainerScript(mgr);
	SetupWyrmrestTempleGossip(mgr);
	SetupXpEliminatorGossip(mgr);
	SetupZangarmarshGossip(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

#endif
