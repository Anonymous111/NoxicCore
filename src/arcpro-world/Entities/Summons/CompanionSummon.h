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

#ifndef COMPANIONSUMMON_HPP_
#define COMPANIONSUMMON_HPP_

//////////////////////////////////////////////////////////
//class CompanionSummon
//  Class implementing companions/vanity pets/critterpets
//  These are totally passive and inattackable,
//  they only serve iCandy purposes
//
//////////////////////////////////////////////////////////
class CompanionSummon : public Summon
{
public:
	CompanionSummon(uint64 GUID);
	~CompanionSummon();

	virtual void Load(CreatureProto* proto, Unit* owner, LocationVector & position, uint32 spellid, int32 summonslot);
	void OnPushToWorld();
	void OnPreRemoveFromWorld();

private:
};

#endif
