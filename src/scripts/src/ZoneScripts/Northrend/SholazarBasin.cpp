/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://www.arcpro.sexyi.am>
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

#include "../Setup.h"

// -----------------------------------------------------------------------------
// Quest 12532 - Flown the Coop!
// Quest 12702 - Chicken Party! (by bartus

class ChickenEscapee : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ChickenEscapee);
	ChickenEscapee(Creature* pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		// Let's see if we are netted
		Aura* a = _unit->FindAura(51959);
		if(a != NULL)
		{
			Unit* Caster = a->GetUnitCaster();
			if(Caster->IsPlayer())
			{
				QuestLogEntry* pQuest = TO_PLAYER(Caster)->GetQuestLogForEntry(12532);
				if(pQuest == NULL)
					pQuest = TO_PLAYER(Caster)->GetQuestLogForEntry(12702);

				if(pQuest != NULL)
				{
					// casting the spell that will create the item for the player
					_unit->CastSpell(Caster, 51037, true);
					_unit->Despawn(1000, 360000);
				}
			}
		}
	}
};

void SetupZoneSholazarBasin(ScriptMgr* mgr)
{
	mgr->register_creature_script(28161, &ChickenEscapee::Create);
}