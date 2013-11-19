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

class MidsummerRibbonPoleAI : public GameObjectAIScript
{
public:
	MidsummerRibbonPoleAI(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	/*void OnActivate(Player* pPlayer)
	{
		SpellCastTargets ct;
		Spell* pSpell;
		SpellEntry* sp = dbcSpell.LookupEntryForced(29727);
		if(sp == NULL)
			return;

		ct.m_unitTarget = _gameobject->GetGUID();
		ct.m_targetMask = TARGET_FLAG_OBJECT;
		pSpell = (new Spell(pPlayer, sp, false, NULLAURA));
		pSpell->prepare(&ct);
	}*/
};

bool TestRibbonPoleChannel(uint32 i, Aura* pAura, bool apply)
{
	if(i == 0)
	{
		Unit* pTarget = (Unit*)pAura->GetTarget();
		if(pTarget != NULL)
		{
			if(apply)
				pTarget->CastSpell(pTarget, 45406, true);
			else
				pTarget->RemoveAura(45406);
		}
	}

	return true;
}

/*bool TriggerRibbonDance(uint32 i, Spell* pSpell)
{
	if(pSpell->u_caster != NULL && i == 0)
	{
		Aura* pAura = pSpell->u_caster->FindAura(29175);
		if(pAura != NULL)
		{
			// increase duration by 3 minutes, capping at 60 minutes
			uint32 dur = pAura->GetDuration() / 1000;
			if(dur < (TIME_MINUTE * 60))
			{
				dur += (TIME_MINUTE * 3);
				if(dur >= (TIME_MINUTE * 60))
					dur = (TIME_MINUTE * 60);

				pAura->SetTimeLeft(dur * 1000);
			}
		}
		else
		{
			// add the aura (default 3 mins)
			pSpell->u_caster->CastSpell(pSpell->u_caster, 29175, true);
		}
	}

	return true;
}*/

void SetupEventMidsummerFireFestival(ScriptMgr* mgr)
{
	//mgr->register_gameobject_script(181605, &MidsummerRibbonPoleAI::Create);
	mgr->register_dummy_aura(29727, &TestRibbonPoleChannel);
	//mgr->register_dummy_spell(29715, &TriggerRibbonDance);

	// hackfix this
	SpellEntry* sp = dbcSpell.LookupEntryForced(29715);
	if(sp != NULL)
	{
		sp->EffectImplicitTargetA[0] = 1;
		sp->EffectImplicitTargetA[1] = 0;
		sp->EffectImplicitTargetA[2] = 0;

		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}
}