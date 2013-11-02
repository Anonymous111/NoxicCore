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

#ifndef _FEATURE_DEFINITIONS_H_
#define _FEATURE_DEFINITIONS_H_

//#define FORCED_GM_TRAINEE_MODE			1 //this means he cannot switch off GM mode. He has fixed DMG and health. Forced faction. No spell casts
#define FORCED_GM_BAN_LIMITATION			2*7*24*60*60 //given in seconds. Noob GMs are not supposed to give bigger bans then this. This is to avoid GM revenges
//#define MINIMIZE_NETWORK_TRAFIC			//this is used for very high player concentrations to send spell packets only to duelling players
//#define GENERATE_CLASS_BALANCING_STATISTICS	1	//used to bust urban legends of QQ players that say that some class is uber imba due to emu bugs
//! you need to search in files and additional enable this !
//#define USE_OLD_EVENT_MANAGER			//the new event manager is using pools for the event lists. Stats say alloc and dealoc eats up 2 GB RAM / 5 minutes

//put 0 to disable this feature, else put a few minute size in milliseconds to monitor when GM goes AFK
#define GM_STATISTICS_UPDATE_INTERVAL		(1*60*1000)

#define USE_PACKET_COMPRESSION				0		//counted in milliseconds. undefine to disable this feature
#define ENABLE_NAGLE_ALGORITHM				0		//nagle can reduce huge overhead for some packets. Might also create a lot of lag in case he has nothing else to group up packets with
#define CLIENT_TIMESPEED_CHEAT_TRIGGER_DC	3		//if ping packets will come with a higher rate then normal then there is a chance that client is using timespeed cheat ?

#define CATACLYSM_SUPPORT					1		//disable this in case i forget about it. This will be used to force emu to try to support basic cataclysm support

//#define USE_HACK_TO_ENABLE_ACHIEVEMENTS		1
#define FORCE_DISABLE_CREATURE_PROTO_PERIODIC_AURAS 1//because i met the case when some fire was casting every few seconds a spell. And there were lots of fires...= doomed
#define SOCIAL_BONUSES_ADDON				1		// when people chat a lot, or get in places with lots of places, they receive buffs. The idea is to award people that socialize a lot
#define SOCIAL_BONUS_DROPRATE_CHANCE_PER_5_MAN	5	//for every 5 man drop rate chance increases by N%

//FAILURE !! Do not ever use this :P
//#define SMALL_ITEM_OBJECT					1		//there are a few million item objects cached. Even if we save a few bytes it might have a considerable impact on mem usage
#endif