/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://www.arcpro.info/>
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

#ifndef POSSESSEDSUMMON_HPP_
#define POSSESSEDSUMMON_HPP_

///////////////////////////////////////////////////////////////////////////////////
//class PossessedSummon
//  Class that implements summons that are possessed by the player after spawning.
//  They despawn when killed or dismissed
//
//////////////////////////////////////////////////////////////////////////////////
class PossessedSummon : public Summon
{
public:
	PossessedSummon(uint64 GUID);
	~PossessedSummon();

	void Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot);
	void OnPushToWorld();
	void OnPreRemoveFromWorld();

private:
};

#endif
