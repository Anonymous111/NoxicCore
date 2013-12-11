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
 
#include "../Setup.h"
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)	// Comment any script to disable it
{
	// Eastern Kingdom
	SetupArathiBasinGameobjects(mgr);
	SetupArathiHighlandsGameobjects(mgr);
	SetupBlackrockMountainGameobjects(mgr);
	SetupBlastedLandsGameobjects(mgr);
	SetupBurningSteppesGameobjects(mgr);
	SetupDeadwindPassGameobjects(mgr);
	SetupDeeprunTramGameobjects(mgr);
	SetupDunMoroghGameobjects(mgr);
	SetupDuskwoodGameobjects(mgr);
	SetupElwynnForestGameobjects(mgr);
	SetupEversongWoodsGameobjects(mgr);
	SetupGhostlandsGameobjects(mgr);
	SetupHillsbradFoothillsGameobjects(mgr);
	SetupHinterlandsGameobjects(mgr);
	SetupIronforgeGameobjects(mgr);
	SetupIsleofQuelDanasGameobjects(mgr);
	SetupLochModanGameobjects(mgr);
	SetupOldHillsbradGameObjects(mgr);
	SetupRedridgeMountainsGameobjects(mgr);
	SetupSearingGorgeGameobjects(mgr);
	SetupSilvermoonCityGameobjects(mgr);
	SetupSilverpineForestGameobjects(mgr);
	SetupStormwindCityGameobjects(mgr);
	SetupStranglethornGameobjects(mgr);
	SetupSwampofSorrowsGameobjects(mgr);
	SetupTheHinterlandsGameobjects(mgr);
	SetupTheScarletEnclaveGameObject(mgr);
	SetupTirisfalGladesGameobjects(mgr);
	SetupUndercityGameobjects(mgr);
	SetupWesternPlaguelandsGameobjects(mgr);
	SetupWestfallGameobjects(mgr);

	// Kalimdor
	SetupAshenvaleGameobjects(mgr);
	SetupAzsharaGameobjects(mgr);
	SetupAzuremystIsleGameobjects(mgr);
	SetupBarrensGameobjects(mgr);
	SetupBloodmystIsleGameobjects(mgr);
	SetupDarkshoreGameobjects(mgr);
	SetupDarnassusGameobjects(mgr);
	SetupDesolaceGameobjects(mgr);
	SetupDurotarGameobjects(mgr);
	SetupDustwallowMarshGameobjects(mgr);
	SetupExodarGameobjects(mgr);
	SetupFelwoodGameobjects(mgr);
	SetupFeralasGameobjects(mgr);
	SetupMoongladeGameobjects(mgr);
	SetupMulgoreGameobjects(mgr);
	SetupOrgrimmarGameobjects(mgr);
	SetupSilithusGameobjects(mgr);
	SetupStonetalonMountainsGameobjects(mgr);
	SetupTanarisGameobjects(mgr);
	SetupTeldrassilGameobjects(mgr);
	SetupTheFallenKingdomGameobjects(mgr);
	SetupThousandNeedlesGameobjects(mgr);
	SetupThunderBluffGameobjects(mgr);
	SetupUnGoroCraterGameobjects(mgr);
	SetupWinterspringGameobjects(mgr);

	// Outland
	SetupBladeEdgeMountainsGameobjects(mgr);
	SetupHellfirePeninsulaGameobjects(mgr);
	SetupNagrandGameobjects(mgr);
	SetupNetherstormGameobjects(mgr);
	SetupShattrathCityGameobjects(mgr);
	SetupTerokkarForestGameobjects(mgr);

	// Northrend
	SetupBoreanTundraGameobjects(mgr);
	SetupCrystalsongForestGameobjects(mgr);
	SetupDalaranGameobjects(mgr);
	SetupStormPeaksGameobjects(mgr);
	SetupWintergraspGameobjects(mgr);
	SetupZulDrakGameobjects(mgr);

	// Other
	SetupMiscGameobjects(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

#endif
