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

bool SpiritofKirith(uint32 i, Spell* pSpell)
{
	if(!pSpell->p_caster || i != 1)
		return true;

	Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(7729, _unit->GetPositionX() + 2, _unit->GetPositionY() + 2, _unit->GetPositionZ(), _unit->GetOrientation(), true, false, 0, 0);
	if(NewCreature != NULL)
		NewCreature->Despawn(3*6*1000, 0);

	return true;
}

bool Otherstuff(uint32 i, Spell* pSpell)
{
	if(!pSpell->p_caster || i != 1)
		return true;

	float SSX = pSpell->p_caster->GetPositionX();
	float SSY = pSpell->p_caster->GetPositionY();
	float SSZ = pSpell->p_caster->GetPositionZ();
	float SSO = pSpell->p_caster->GetOrientation();

	pSpell->p_caster->GetMapMgr()->GetInterface()->SpawnCreature(3475, SSX, SSY, SSZ, SSO, true, false, 0, 0);

	return true;
}

bool EmblazonRuneblade(uint32 i, Spell* pSpell)
{
	if(pSpell->p_caster == NULL)
		return true;

	Player* pPlayer = pSpell->p_caster;
	pPlayer->SendChatMessageToPlayer(CHAT_MSG_SYSTEM, LANG_UNIVERSAL, "Player check", pPlayer);

	QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(12619);
	if(pQuest == NULL)
		return true;

	sEAS.AddItem(38631, pPlayer, 1);
	pPlayer->GetItemInterface()->RemoveItemAmt(38607, 1);
	return true;
}

void SetupSummonSpells(ScriptMgr* mgr)
{
	mgr->register_dummy_spell(10853, &SpiritofKirith);
	//mgr->register_dummy_spell(000000, &Otherstuff);
	//mgr->register_script_effect(000000, &EmblazonRuneblade);
}