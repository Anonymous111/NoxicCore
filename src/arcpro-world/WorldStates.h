/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://www.arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __WORLDSTATES_H
#define __WORLDSTATES_H

enum WorldStates
{
	WORLDSTATE_AV_STONEHEARTH_GRAVE_HORDE_CONTROLLED		= 1301,
	WORLDSTATE_AV_STONEHEARTH_GRAVE_ALLIANCE_CONTROLLED		= 1302,
	WORLDSTATE_AV_STONEHEARTH_GRAVE_HORDE_ASSAULTING		= 1303,
	WORLDSTATE_AV_STONEHEARTH_GRAVE_ALLIANCE_ASSAULTING		= 1304,
	WORLDSTATE_AV_STORMPIKE_AID_STATION_ALLIANCE_CONTROLLED	= 1325,
	WORLDSTATE_AV_STORMPIKE_AID_STATION_ALLIANCE_ASSAULTING	= 1326,
	WORLDSTATE_AV_STORMPIKE_AID_STATION_HORDE_CONTROLLED	= 1327,
	WORLDSTATE_AV_STORMPIKE_AID_STATION_HORDE_ASSAULTING	= 1328,
	WORLDSTATE_AV_FROSTWOLF_RELIEF_HUT_ALLIANCE_CONTROLLED	= 1329,
	WORLDSTATE_AV_FROSTWOLF_RELIEF_HUT_HORDE_CONTROLLED		= 1330,
	WORLDSTATE_AV_FROSTWOLF_RELIEF_HUT_ALLIANCE_ASSAULTING	= 1331,
	WORLDSTATE_AV_FROSTWOLF_RELIEF_HUT_HORDE_ASSAULTING		= 1332,
	WORLDSTATE_AV_STORMPIKE_GRAVE_ALLIANCE_CONTROLLED		= 1333,
	WORLDSTATE_AV_STORMPIKE_GRAVE_HORDE_CONTROLLED			= 1334,
	WORLDSTATE_AV_STORMPIKE_GRAVE_ALLIANCE_ASSAULTING		= 1335,
	WORLDSTATE_AV_STORMPIKE_GRAVE_HORDE_ASSAULTING			= 1336,
	WORLDSTATE_AV_FROSTWOLF_GRAVE_ALLIANCE_CONTROLLED		= 1337,
	WORLDSTATE_AV_FROSTWOLF_GRAVE_HORDE_CONTROLLED			= 1338,
	WORLDSTATE_AV_FROSTWOLF_GRAVE_ALLIANCE_ASSAULTING		= 1339,
	WORLDSTATE_AV_FROSTWOLF_GRAVE_HORDE_ASSAULTING			= 1340,
	WORLDSTATE_AV_SNOWFALL_GRAVE_ALLIANCE_CONTROLLED		= 1341,
	WORLDSTATE_AV_SNOWFALL_GRAVE_HORDE_CONTROLLED			= 1342,
	WORLDSTATE_AV_SNOWFALL_GRAVE_ALLIANCE_ASSAULTING		= 1343,
	WORLDSTATE_AV_SNOWFALL_GRAVE_HORDE_ASSAULTING			= 1344,
	WORLDSTATE_AV_ICEBLOOD_GRAVE_ALLIANCE_CONTROLLED		= 1346,
	WORLDSTATE_AV_ICEBLOOD_GRAVE_HORDE_CONTROLLED			= 1347,
	WORLDSTATE_AV_ICEBLOOD_GRAVE_ALLIANCE_ASSAULTING		= 1348,
	WORLDSTATE_AV_ICEBLOOD_GRAVE_HORDE_ASSAULTING			= 1349,
	WORLDSTATE_AV_COLDTOOTH_MINE_ALLIANCE_CONTROLLED		= 1355,
	WORLDSTATE_AV_COLDTOOTH_MINE_HORDE_CONTROLLED			= 1356,
	WORLDSTATE_AV_COLDTOOTH_MINE_KOBOLD_CONTROLLED			= 1357,
	WORLDSTATE_AV_IRONDEEP_MINE_ALLIANCE_CONTROLLED			= 1358,
	WORLDSTATE_AV_IRONDEEP_MINE_HORDE_CONTROLLED			= 1359,
	WORLDSTATE_AV_IRONDEEP_MINE_TROGG_CONTROLLED			= 1360,
	WORLDSTATE_AV_DUN_BALDAR_NORTH_BUNKER_CONTROLLED		= 1361,
	WORLDSTATE_AV_DUN_BALDAR_SOUTH_BUNKER_CONTROLLED		= 1362,
	WORLDSTATE_AV_ICEWING_BUNKER_CONTROLLED					= 1363,
	WORLDSTATE_AV_STONEHEARTH_BUNKER_CONTROLLED				= 1364,
	WORLDSTATE_AV_FROSTWOLF_WEST_TOWER_DESTROYED			= 1365,
	WORLDSTATE_AV_FROSTWOLF_EAST_TOWER_DESTROYED			= 1366,
	WORLDSTATE_AV_TOWERPOINT_DESTROYED						= 1367,
	WORLDSTATE_AV_ICEBLOOD_TOWER_DESTROYED					= 1368,
	WORLDSTATE_AV_DUN_BALDAR_NORTH_BUNKER_DESTROYED			= 1370,
	WORLDSTATE_AV_DUN_BALDAR_SOUTH_BUNKER_DESTROYED			= 1371,
	WORLDSTATE_AV_ICEWING_BUNKER_DESTROYED					= 1372,
	WORLDSTATE_AV_STONEHEARTH_BUNKER_DESTROYED				= 1373,
	WORLDSTATE_AV_DUN_BALDAR_NORTH_BUNKER_ASSAULTING		= 1378,
	WORLDSTATE_AV_DUN_BALDAR_SOUTH_BUNKER_ASSAULTING		= 1379,
	WORLDSTATE_AV_ICEWING_BUNKER_ASSAULTING					= 1380,
	WORLDSTATE_AV_STONEHEARTH_BUNKER_ASSAULTING				= 1381,
	WORLDSTATE_AV_FROSTWOLF_WEST_TOWER_CONTROLLED			= 1382,
	WORLDSTATE_AV_FROSTWOLF_EAST_TOWER_CONTROLLED			= 1383,
	WORLDSTATE_AV_TOWERPOINT_CONTROLLED						= 1384,
	WORLDSTATE_AV_ICEBLOOD_TOWER_CONTROLLED					= 1385,
	WORLDSTATE_AV_FROSTWOLF_WEST_TOWER_ASSAULTING			= 1387,
	WORLDSTATE_AV_FROSTWOLF_EAST_TOWER_ASSAULTING			= 1388,
	WORLDSTATE_AV_TOWERPOINT_ASSAULTING						= 1389,
	WORLDSTATE_AV_ICEBLOOD_TOWER_ASSAULTING					= 1390,
	WORLDSTATE_WSG_ALLIANCE_SCORE							= 1581,
	WORLDSTATE_WSG_HORDE_SCORE								= 1582,
	WORLDSTATE_WSG_MAX_SCORE								= 1601,
	WORLDSTATE_AB_CAPTURED_STABLES_ALLIANCE					= 1767,
	WORLDSTATE_AB_CAPTURED_STABLES_HORDE					= 1768,
	WORLDSTATE_AB_CAPTURING_STABLES_ALLIANCE				= 1769,
	WORLDSTATE_AB_CAPTURING_STABLES_HORDE					= 1770,
	WORLDSTATE_AB_CAPTURED_FARM_ALLIANCE					= 1772,
	WORLDSTATE_AB_CAPTURED_FARM_HORDE						= 1773,
	WORLDSTATE_AB_CAPTURING_FARM_ALLIANCE					= 1774,
	WORLDSTATE_AB_CAPTURING_FARM_HORDE						= 1775,
	WORLDSTATE_AB_ALLIANCE_RESOURCES						= 1776,
	WORLDSTATE_AB_HORDE_RESOURCES							= 1777,
	WORLDSTATE_AB_HORDE_CAPTUREBASE							= 1778,
	WORLDSTATE_AB_ALLIANCE_CAPTUREBASE						= 1779,
	WORLDSTATE_AB_MAX_SCORE									= 1780,
	WORLDSTATE_AB_CAPTURED_BLACKSMITH_ALLIANCE				= 1782,
	WORLDSTATE_AB_CAPTURED_BLACKSMITH_HORDE					= 1783,
	WORLDSTATE_AB_CAPTURING_BLACKSMITH_ALLIANCE				= 1784,
	WORLDSTATE_AB_CAPTURING_BLACKSMITH_HORDE				= 1785,
	WORLDSTATE_AB_CAPTURED_GOLDMINE_ALLIANCE				= 1787,
	WORLDSTATE_AB_CAPTURED_GOLDMINE_HORDE					= 1788,
	WORLDSTATE_AB_CAPTURING_GOLDMINE_ALLIANCE				= 1789,
	WORLDSTATE_AB_CAPTURING_GOLDMINE_HORDE					= 1790,
	WORLDSTATE_AB_CAPTURED_LUMBERMILL_ALLIANCE				= 1792,
	WORLDSTATE_AB_CAPTURED_LUMBERMILL_HORDE					= 1793,
	WORLDSTATE_AB_CAPTURING_LUMBERMILL_ALLIANCE				= 1794,
	WORLDSTATE_AB_CAPTURING_LUMBERMILL_HORDE				= 1795,
	WORLDSTATE_AB_SHOW_STABLE_ICON							= 1842,
	WORLDSTATE_AB_SHOW_GOLDMINE_ICON						= 1843,
	WORLDSTATE_AB_SHOW_LUMBERMILL_ICON						= 1844,
	WORLDSTATE_AB_SHOW_FARM_ICON							= 1845,
	WORLDSTATE_AB_SHOW_BACKSMITH_ICON						= 1846,
	WORLDSTATE_AV_SNOWFALL_GRAVE_NEUTRAL_CONTROLLED			= 1966,
	WORLDSTATE_WSG_ALLIANCE_FLAG_DISPLAY					= 2338,
	WORLDSTATE_WSG_HORDE_FLAG_DISPLAY						= 2339,
	WORLDSTATE_OLD_HILLSBRAD_BARRELS						= 2436,
	WORLDSTATE_ARENA_BLADESEDGE_SCORE_SHOW					= 2547,
	WORLDSTATE_ARENA_NAGRAND_SCORE_SHOW						= 2577,
	WORLDSTATE_EOTS_DISPLAYON								= 2718,
	WORLDSTATE_EOTS_DISPLAYVALUE							= 2719,
	WORLDSTATE_EOTS_BLOODELF_TOWER_NEUTRAL_DISPLAY			= 2722,
	WORLDSTATE_EOTS_BLOODELF_TOWER_ALLIANCE_DISPLAY			= 2723,
	WORLDSTATE_EOTS_BLOODELF_TOWER_HORDE_DISPLAY			= 2724,
	WORLDSTATE_EOTS_FELREAVER_RUINS_NETURAL_DISPLAY			= 2725,
	WORLDSTATE_EOTS_FELREAVER_RUINS_ALLIANCE_DISPLAY		= 2726,
	WORLDSTATE_EOTS_FELREAVER_RUINS_HORDE_DISPLAY			= 2727,
	WORLDSTATE_EOTS_MAGE_TOWER_NETURAL_DISPLAY				= 2728,
	WORLDSTATE_EOTS_MAGE_TOWER_HORDE_DISPLAY				= 2729,
	WORLDSTATE_EOTS_MAGE_TOWER_ALLIANCE_DISPLAY				= 2730,
	WORLDSTATE_EOTS_DRAENEI_RUINS_NETURAL_DISPLAY			= 2731,
	WORLDSTATE_EOTS_DRAENEI_RUINS_ALLIANCE_DISPLAY			= 2732,
	WORLDSTATE_EOTS_DRAENEI_RUINS_HORDE_DISPLAY				= 2733,
	WORLDSTATE_EOTS_ALLIANCE_VICTORYPOINTS					= 2749,
	WORLDSTATE_EOTS_HORDE_VICTORYPOINTS						= 2750,
	WORLDSTATE_EOTS_ALLIANCE_BASES							= 2752,
	WORLDSTATE_EOTS_HORDE_BASES								= 2753,
	WORLDSTATE_EOTS_FLAG_NEUTRAL_DISPLAY					= 2757,
	WORLDSTATE_EOTS_ALLIANCE_VICTORY_POINTS_DISPLAY			= 2769,
	WORLDSTATE_EOTS_HORDE_VICTORY_POINTS_DISPLAY			= 2770,
	WORLDSTATE_AV_ALLIANCE_SCORE							= 3127,
	WORLDSTATE_AV_HORDE_SCORE								= 3128,
	WORLDSTATE_AV_ALLIANCE_SCORE_DISPLAY					= 3133,
	WORLDSTATE_AV_HORDE_SCORE_DISPLAY						= 3134,
	WORLDSTATE_WG_HORDE_VEHICLES							= 3490, // current horde vehicles
	WORLDSTATE_WG_MAX_HORDE_VEHICLES						= 3491, // max horde vehicles
	WORLDSTATE_SOTA_CAPTURE_BAR_DISPLAY						= 3536, // displays the node capture bar(GY for example)
	WORLDSTATE_SOTA_CAPTURE_BAR_VALUE						= 3537, // 0 - horde, 100 - alliance
	WORLDSTATE_SOTA_TIMER_1									= 3559, // remaining/bonustime minutes
	WORLDSTATE_SOTA_TIMER_2									= 3560, // remaining/bonustime seconds first digit
	WORLDSTATE_SOTA_TIMER_3									= 3561, // remaining/bonustime seconds second digit
	WORLDSTATE_SOTA_ALLIANCE_ATTACKER						= 3564, // show remaining time 1
	WORLDSTATE_SOTA_HORDE_ATTACKER							= 3565, // show remaining time 2
	WORLDSTATE_SOTA_BONUS_TIME								= 3571, // show bonus timer
	WORLDSTATE_ARENA__GREEN_PLAYER_COUNT					= 3600,
	WORLDSTATE_ARENA__GOLD_PLAYER_COUNT						= 3601,
	WORLDSTATE_ARENA_LORDAERON_SCORE_SHOW					= 3002,
	WORLDSTATE_ARENA_WOTLK_SCORE_SHOW						= 3610,
	WORLDSTATE_SOTA_SHOW_PURPLE_GATE						= 3614, // Gate of Purple Amethyst
	WORLDSTATE_SOTA_SHOW_RED_GATE							= 3617, // Gate of Red Sun
	WORLDSTATE_SOTA_SHOW_BLUE_GATE							= 3620, // Gate of Blue Sapphire
	WORLDSTATE_SOTA_SHOW_GREEN_GATE							= 3623, // Gate of Green Emerald
	WORLDSTATE_SOTA_SHOW_ALLY_BEACHHEAD1					= 3626, // alliance offense 1
	WORLDSTATE_SOTA_SHOW_ALLY_BEACHHEAD2					= 3627, // alliance offense 2
	WORLDSTATE_SOTA_SHOW_HORDE_BEACHHEAD1					= 3628, // horde offense 2
	WORLDSTATE_SOTA_SHOW_HORDE_BEACHHEAD2					= 3629, // horde offense 1
	WORLDSTATE_SOTA_SHOW_ALLY_DEFENSE						= 3630, // alliance defense
	WORLDSTATE_SOTA_SHOW_HORDE_DEFENSE						= 3631, // horde defense
	WORLDSTATE_SOTA_GY_E_H									= 3632, // East GY horde control
	WORLDSTATE_SOTA_GY_W_H									= 3633, // West GY horde control
	WORLDSTATE_SOTA_GY_S_H									= 3634, // South GY horde control
	WORLDSTATE_SOTA_GY_W_A									= 3635, // West GY alliance control
	WORLDSTATE_SOTA_GY_E_A									= 3636, // East GY alliance control
	WORLDSTATE_SOTA_GY_S_A									= 3637, // South GY alliance control
	WORLDSTATE_SOTA_SHOW_YELLOW_GATE						= 3638, // Gate of the Yellow Moon
	WORLDSTATE_WG_ALLIANCE_VEHICLES							= 3680, // current alliance vehicles
	WORLDSTATE_WG_MAX_ALLIANCE_VEHICLES						= 3681, // max alliance vehicles
	WORLDSTATE_WG_SHOW_W_FORTRESS_WORKSHOP					= 3698, // Fortress(W) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_E_FORTRESS_WORKSHOP					= 3699, // Fortress(E) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_BT_WORKSHOP							= 3700, // Broken Temple(W) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_SR_WORKSHOP							= 3701, // Sunken Ring(E) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_WS_WORKSHOP							= 3702, // West Spark(SW) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_ES_WORKSHOP							= 3703, // East Spark(SE) vehicle workshop 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_SS_WORKSHOP							= 3704, // Shadow Sight(SW) tower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_WE_TOWER								= 3705, // Winter's Edge(S) tower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FW_TOWER								= 3706, // Flame Watch(SE) tower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_BATTLE_UI							= 3710, // shows battle timer, and vehicle counters
	WORLDSTATE_WG_SHOW_NW_TOWER								= 3711, // NWFortresstower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_NE_TOWER								= 3712, // NEFortresstower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_SW_TOWER								= 3713, // SWFortresstower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_SE_TOWER								= 3714, // SEFortresstower 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_PVP_MAIN_GATE0						= 3723, // pvp activity detected Crossroad Infront of the fortress gates
	WORLDSTATE_WG_SHOW_PVP_WE0								= 3724, // pvp activity detected Infront of winter' sedge tower
	WORLDSTATE_WG_SHOW_PVP_CENTRAL_BRIDGE					= 3725, // pvp activity detected central bridge to fortress
	WORLDSTATE_WG_SHOW_PVP_SR0								= 3726, // pvp activity detected fortress to Sunkenring
	WORLDSTATE_WG_SHOW_PVP_EAST_BRIDGE_N					= 3727, // pvp activity detected North ofEastbridge
	WORLDSTATE_WG_SHOW_PVP_EAST_BRIDGE_S					= 3728, // pvp activity detected South ofEastBridge
	WORLDSTATE_WG_SHOW_PVP_BT_E								= 3729, // pvp activity detected Easton the road from Brokentemple
	WORLDSTATE_WG_SHOW_PVP_WEST_BRIDGE_N					= 3730, // pvp activity detected North of West bridge
	WORLDSTATE_WG_SHOW_PVP_WEST_BRIDGE_S					= 3731, // pvp activity detected South of West bridge
	WORLDSTATE_WG_SHOW_PVP_GF_S								= 3737, // pvp activity detected SouthofGlacialfalls
	WORLDSTATE_WG_SHOW_PVP_FT_W								= 3738, // pvp activity detected WestontheroadfromFlamewatchTower
	WORLDSTATE_WG_SHOW_PVP_GATE_W							= 3739, // pvp activity detected Westfromthefortressgateontheroadforsunkenringvehicleworkshop
	WORLDSTATE_WG_SHOW_PVP_SR_SW							= 3740, // pvp activity detected SouthwestfromSunkenringvehicleworkshop
	WORLDSTATE_WG_SHOW_PVP_ES_W								= 3741, // pvp activity detected WestfromEastsparkWorkshopontheroadtoWinter'segetower
	WORLDSTATE_WG_SHOW_PVP_ES_E								= 3742, // pvp activity detected EastofWestsparkWorkshopontheroadforWinter'sEdgeTower
	WORLDSTATE_WG_SHOW_PVP_BT_SE							= 3743, // pvp activity detected SoutheastofBrokenTempleVehicleWorkshop
	WORLDSTATE_WG_SHOW_PVP_BT_W								= 3744, // pvp activity detected WestfromthefortressontheroadtoBrokenTempleVehicleWorkshop
	WORLDSTATE_WG_SHOW_PVP_WS_NW							= 3745, // pvp activity detected NorthwestfromWestsparkWorkshopontheroadtoShadowsightTower
	WORLDSTATE_WG_SHOW_PVP_ST_E								= 3746, // pvp activity detected EastfromShaowsightTowerontheraodtoWestbrige
	WORLDSTATE_WG_SHOW_PVP_BT_SW							= 3747, // pvp activity detected BrokenTemplesouthwestlake
	WORLDSTATE_WG_SHOW_PVP_BT_GY							= 3748, // pvp activity detected ThechilledquagmirerightnexttoBrokenTempleGraveyard
	WORLDSTATE_WG_SHOW_FORTRESS_WALL1						= 3749, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL2						= 3750, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL3						= 3751, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL4						= 3752, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL5						= 3753, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL6						= 3754, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL7						= 3755, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL8						= 3756, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL9						= 3757, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL10						= 3758, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL11						= 3759, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL12						= 3760, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL13						= 3761, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL14						= 3762, // Wintergrasp Fortress wall 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_MAIN_GATE					= 3763, // Wintergrasp Fortress main gate 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL15						= 3763, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL16						= 3764, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL17						= 3765, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL18						= 3766, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL19						= 3767, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL20						= 3768, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL21						= 3769, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL22						= 3770, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL23						= 3771, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_WALL24						= 3772, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_FORTRESS_INNER_GATE					= 3773, // Wintergrasp Fortress inner gate and graveyard 0 - don't show, 1, 2, 3 Neutral (intact, damaged, destroyed), 4, 5, 6 (Horde), 7, 8, 9 (Ally)
	WORLDSTATE_WG_SHOW_PVP_MAIN_GATE						= 3774, // pvp activity detected atmaingate
	WORLDSTATE_WG_SHOW_PVP_SW								= 3775, // pvp activity detected SW
	WORLDSTATE_WG_SHOW_PVP_SE								= 3776, // pvp activity detected SE
	WORLDSTATE_WG_SHOW_PVP_NE								= 3777, // pvp activity detected NE
	WORLDSTATE_WG_SHOW_PVP_N								= 3778, // pvp activity detected N
	WORLDSTATE_WG_SHOW_PVP_NW								= 3779, // pvp activity detected NW
	WORLDSTATE_WG_END_TIME									= 3781, // unixtime of the end of battle(showsitastimeleftintheUI)
	WORLDSTATE_WG_SHOW_PVP_BT								= 3788, // pvp activity detected near Broken Temple vehicle shop
	WORLDSTATE_WG_SHOW_PVP_SR								= 3790, // pvp activity detected near Sunken Ring vehicle shop
	WORLDSTATE_WG_SHOW_PVP_ES								= 3791, // pvp activity detected near East Spark vehicle shop
	WORLDSTATE_WG_SHOW_PVP_WS								= 3792, // pvp activity detected near West Spark vehicle shop
	WORLDSTATE_WG_SHOW_PVP_SS								= 3793, // pvp activity detected near Shadow Sight tower
	WORLDSTATE_WG_SHOW_PVP_FW								= 3794, // pvp activity detected near Flamewatch tower
	WORLDSTATE_WG_SHOW_PVP_WE								= 3795, // pvp activity detected near Winter's Edgetower
	WORLDSTATE_WG_SHOW_PVP_FS								= 3796, // pvp activity detected near Forest of Shadows
	WORLDSTATE_WG_SHOW_PVP_GF								= 3797, // pvp activity detected near Glacial Falls
	WORLDSTATE_WG_SHOW_PVP_CF								= 3798, // pvp activitydetectednearCauldronofFlames
	WORLDSTATE_WG_SHOW_PVP_SL								= 3799, // pvp activity detected near Steppe of Life
	WORLDSTATE_WG_NEXT_BATTLE_TIME							= 3801, // timer until next battle
	WORLDSTATE_WG_HORDE_CONTROL								= 3802, // horde control
	WORLDSTATE_WG_ALLY_CONTROL								= 3803, // alliance control
	WORLDSTATE_SOTA_CHAMBER_GATE							= 3849, // Chamber of the ancient relics gate
	WORLDSTATE_IOC_ALLIANCE_SCORE							= 4221,
	WORLDSTATE_IOC_HORDE_SCORE								= 4222,
	WORLDSTATE_IOC_ALLY_SCORE_VALUE							= 4226,
	WORLDSTATE_IOC_HORDE_SCORE_VALUE						= 4227,
	WORLDSTATE_IOC_WORKSHOP_ALLIANCE_ASSAULTED				= 4228,
	WORLDSTATE_IOC_WORKSHOP_ALLIANCE_CONTROLLED				= 4229,
	WORLDSTATE_IOC_WORKSHOP_HORDE_CONTROLLED				= 4230,
	WORLDSTATE_WSG_TIME_ENABLED								= 4247,
	WORLDSTATE_WSG_TIME_REMAINING							= 4248,
	WORLDSTATE_IOC_WORKSHOP_HORDE_ASSAULTED					= 4293,
	WORLDSTATE_IOC_WORKSHOP_NETURAL							= 4294,
	WORLDSTATE_IOC_HANGAR_NETURAL							= 4296,
	WORLDSTATE_IOC_HANGAR_HORDE_ASSAULTED					= 4297,
	WORLDSTATE_IOC_HANGAR_HORDE_CONTROLLED					= 4298,
	WORLDSTATE_IOC_HANGAR_ALLIANCE_CONTROLLED				= 4299,
	WORLDSTATE_IOC_HANGAR_ALLIANCE_ASSAULTED				= 4300,
	WORLDSTATE_IOC_DOCKS_NETURAL							= 4301,
	WORLDSTATE_IOC_DOCKS_HORDE_ASSAULTED					= 4302,
	WORLDSTATE_IOC_DOCKS_HORDE_CONTROLLED					= 4303,
	WORLDSTATE_IOC_DOCKS_ALLIANCE_CONTROLLED				= 4304,
	WORLDSTATE_IOC_DOCKS_ALLIANCE_ASSAULTED					= 4305,
	WORLDSTATE_IOC_QUARRY_NETURAL							= 4306,
	WORLDSTATE_IOC_QUARRY_HORDE_ASSAULTED					= 4307,
	WORLDSTATE_IOC_QUARRY_HORDE_CONTROLLED					= 4308,
	WORLDSTATE_IOC_QUARRY_ALLIANCE_CONTROLLED				= 4309,
	WORLDSTATE_IOC_QUARRY_ALLIANCE_ASSAULTED				= 4310,
	WORLDSTATE_IOC_REFINERY_NETURAL							= 4311,
	WORLDSTATE_IOC_REFINERY_HORDE_ASSAULTED					= 4312,
	WORLDSTATE_IOC_REFINERY_HORDE_CONTROLLED				= 4313,
	WORLDSTATE_IOC_REFINERY_ALLIANCE_CONTROLLED				= 4314,
	WORLDSTATE_IOC_REFINERY_ALLIANCE_ASSAULTED				= 4315,
	WORLDSTATE_IOC_HORDE_FRONT_GATE							= 4317,
	WORLDSTATE_IOC_HORDE_WEST_GATE							= 4318,
	WORLDSTATE_IOC_HORDE_EAST_GATE							= 4319,
	WORLDSTATE_IOC_HORDE_GATE_DESTROYED_2					= 4320,
	WORLDSTATE_IOC_HORDE_GATE_DESTROYED_3					= 4321,
	WORLDSTATE_IOC_HORDE_GATE_DESTROYED_1					= 4322,
	WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_1				= 4323,
	WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_3				= 4324,
	WORLDSTATE_IOC_ALLIANCE_GATE_DESTROYED_2				= 4325,
	WORLDSTATE_IOC_ALLIANCE_EAST_GATE						= 4326,
	WORLDSTATE_IOC_ALLIANCE_WEST_GATE						= 4327,
	WORLDSTATE_IOC_ALLIANCE_FRONT_GATE						= 4328,
	WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_CONTROLLED		= 4339,
	WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_CONTROLLED			= 4340,
	WORLDSTATE_IOC_ALLIANCE_KEEP_NETURAL					= 4341,
	WORLDSTATE_IOC_ALLIANCE_KEEP_ALLIANCE_ASSAULTED			= 4342,
	WORLDSTATE_IOC_ALLIANCE_KEEP_HORDE_ASSAULTED			= 4343,
	WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_CONTROLLED			= 4344,
	WORLDSTATE_IOC_HORDE_KEEP_HORDE_CONTROLLED				= 4345,
	WORLDSTATE_IOC_HORDE_KEEP_NETURAL						= 4346,
	WORLDSTATE_IOC_HORDE_KEEP_ALLIANCE_ASSAULTED			= 4347,
	WORLDSTATE_IOC_HORDE_KEEP_HORDE_ASSAULTED				= 4348,
	WORLDSTATE_SOTA_SHOW_ALLY_ROUND							= 4352, // Alliance attacks, Horde defends
	WORLDSTATE_SOTA_SHOW_HORDE_ROUND						= 4353, // Horde attacks, Alliance defends
	WORLDSTATE_WG_SHOW_NEXT_BATTLE							= 4354, // unixtime of next battle(showsitastimeleftintheUI)
};

#endif // __WORLDSTATES_H
