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

#include "Setup.h"

#define CN_PURIFYING_TOTEM	25494

class PurifyingTotem : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PurifyingTotem)
	PurifyingTotem(Creature* pCreature ) : CreatureAIScript(pCreature)
	{
		//SetCanEnterCombat(false);
		_unit->GetAIInterface()->m_canMove = false;
		//Despawn(8000, 0);
	}
};

class SeaforiumDepthCharge : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SeaforiumDepthCharge)
	SeaforiumDepthCharge(Creature* pCreature) : CreatureAIScript(pCreature)
	{
		_unit->GetAIInterface()->m_canMove = false;
		//SetCanEnterCombat(false);
		_unit->SetFaction(21);
	}
	
	void OnLoad()
		{
			if(!_unit->IsSummon())
				return;

			Unit* summoner = TO<Summon*>(_unit)->GetOwner();

			if(summoner != NULL)
			{
				if(summoner->IsPlayer())
				{
					Player* pPlayer = TO_PLAYER(summoner);
					if(pPlayer->HasQuest(11608))
					{
						GameObject* pSinkhole = p->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 300171);
						if(pSinkhole != NULL)
						{
							_unit->CastSpell(_unit, 45502, true);

							float posX = pSinkhole->GetPositionX();
							if(posX == 2657.13f)
								sEAS.KillMobForQuest(pPlayer, 11608, 0);

							if(posX == 2716.02f)
								sEAS.KillMobForQuest(pPlayer, 11608, 1);

							if(posX == 2877.96f)
								sEAS.KillMobForQuest(pPlayer, 11608, 2);

							if(posX == 2962.16f)
								sEAS.KillMobForQuest(pPlayer, 11608, 3);

						}
					}
				}
			}
			_unit->Despawn(500, 0);
		}
};

void SetupZoneBoreanTundra(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_PURIFYING_TOTEM, &PurifyingTotem::Create);
	mgr->register_creature_script(25401, &SeaforiumDepthCharge::Create);
}