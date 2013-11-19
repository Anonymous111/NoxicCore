/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation
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

class SCRIPT_DECL PlaguedCritterAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PlaguedCritterAI);
	PlaguedCritterAI(Creature* pCreature) : CreatureAIScript(pCreature) {}

    void OnDied(Unit* mKiller)
    {
		// You're infected now!
        mKiller->CastSpell(mKiller, 43958, true);
    }
};

/*class SCRIPT_DECL ArgentHealerAI : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ArgentHealerAI);
	ArgentHealerAI(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		RegisterAIUpdateEvent(15000);
	}

	void OnDied(Unit* mKiller)
	{
		RemoveAIUpdateEvent();
	}

	void AIUpdate()
	{
		// Loop over in-range players, remove the infection, remove zombie form
		unordered_set<Player*>::iterator itr = _unit->GetInRangePlayerSetBegin();
		for(; itr != _unit->GetInRangePlayerSetEnd(); ++itr)
		{
			Player* pPlayer = (*itr);
			// We've got some plagues to cure, then?
			if(pPlayer && pPlayer->HasActiveAura(43958))
			{
				pPlayer->RemoveNegativeAura(43958);
				continue;
			}

			if(pPlayer && pPlayer->GetShapeShift() == FORM_ZOMBIE)
			{
				pPlayer->RemoveNegativeAura(43869);
				continue;
			}
		}

		// Now cast Holy Nova for the fancy-looking Argent Healer effect
		_unit->CastSpell(_unit, 15237, true);
	}
};*/

void SetupEventZombie(ScriptMgr* mgr)
{ // Uncomment the following for the infection to begin
	/*mgr->register_creature_script(27845, &PlaguedCritterAI::Create); // Plagued Roach
	mgr->register_creature_script(27855, &PlaguedCritterAI::Create); // Plagued Vermin
	mgr->register_creature_script(27305, &ArgentHealerAI::Create); // Argent Healer (Alliance)
	mgr->register_creature_script(31282, &ArgentHealerAI::Create); // Argent Healer (Horde)*/
}