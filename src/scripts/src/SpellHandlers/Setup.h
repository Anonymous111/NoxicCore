/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 * Copyright (c) 2008-2013 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (c) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
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

#ifndef SPELL_SCRIPTS_SETUP_H
#define SPELL_SCRIPTS_SETUP_H

#include "StdAfx.h"
#include "../Common/EasyFunctions.h"

// Class spell handlers
void SetupShamanSpells(ScriptMgr* mgr);
void SetupWarlockSpells(ScriptMgr* mgr);
void SetupWarriorSpells(ScriptMgr* mgr);
void SetupHunterSpells(ScriptMgr* mgr);
void SetupMageSpells(ScriptMgr* mgr);
void SetupPaladinSpells(ScriptMgr* mgr);
void SetupRogueSpells(ScriptMgr* mgr);
void SetupPriestSpells(ScriptMgr* mgr);
void SetupDruidSpells(ScriptMgr* mgr);
void SetupDeathKnightSpells(ScriptMgr* mgr);

void SetupHolidaySpells(ScriptMgr* mgr);
void SetupOldSpellCPPSuff(ScriptMgr* mgr);
void SetupPetAISpells(ScriptMgr* mgr);
void SetupQuestItems(ScriptMgr* mgr);
void SetupItemSpells_1(ScriptMgr* mgr);
void SetupMiscSpellhandlers(ScriptMgr* mgr);

//Instance spells (mainly scripted targets)
void SetupRaidBlackTempleSpells(ScriptMgr* mgr);

#endif
