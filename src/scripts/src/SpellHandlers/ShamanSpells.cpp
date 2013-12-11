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

#include "Setup.h"

/************************************************************************/
/* Spell Defs                                                           */
/************************************************************************/

bool FlametongueWeaponPassive(uint32 i, Aura* pAura, bool apply)
{
	Unit* target = pAura->GetTarget();

	if(apply)
	{
		// target is always a player
		Item* item = TO_PLAYER(target)->GetItemInterface()->GetItemByGUID(pAura->itemCasterGUID);
		target->AddProcTriggerSpell(10444, pAura->GetSpellProto()->Id, pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_MELEE_ATTACK, 0, NULL, NULL, item);
	}
	else
		target->RemoveProcTriggerSpell(10444, pAura->m_casterGuid, pAura->itemCasterGUID);

	return true;
}

bool SkyShatterRegalia(uint32 i, Spell* s)
{
	// Shaman - Skyshatter Regalia - Two Piece Bonus
	// it checks for earth, air, water, fire totems and triggers Totemic Mastery spell 38437.

	if(!s->p_caster)
		return false;

	if(s->p_caster->summonhandler.HasSummonInSlot(0) &&
	        s->p_caster->summonhandler.HasSummonInSlot(1) &&
	        s->p_caster->summonhandler.HasSummonInSlot(2) &&
	        s->p_caster->summonhandler.HasSummonInSlot(3))
	{
		Aura* aur = sSpellFactoryMgr.NewAura(dbcSpell.LookupEntry(38437), 5000, s->p_caster, s->p_caster, true);

		for(uint32 j = 0; j < 3; j++)
			aur->AddMod(aur->GetSpellProto()->EffectApplyAuraName[j], aur->GetSpellProto()->EffectBasePoints[j] + 1, aur->GetSpellProto()->EffectMiscValue[j], j);

		s->p_caster->AddAura(aur);
	}

	return true;
}

bool ManaTide(uint32 i, Spell* s)
{
	Unit* unitTarget = s->GetUnitTarget();

	if(unitTarget == NULL || unitTarget->IsDead() || unitTarget->getClass() == WARRIOR || unitTarget->getClass() == ROGUE)
		return false;

	uint32 gain = (uint32)(unitTarget->GetMaxPower(POWER_TYPE_MANA) * 0.06);
	unitTarget->Energize(unitTarget, 16191, gain, POWER_TYPE_MANA);

	return true;
}

bool EarthShieldDummyAura(uint32 i, Aura* pAura, bool apply)
{
	Unit* m_target = pAura->GetTarget();

	if(apply)
		m_target->AddProcTriggerSpell(379, pAura->GetSpellId(), pAura->m_casterGuid, pAura->GetSpellProto()->procChance, pAura->GetSpellProto()->procFlags & ~PROC_ON_SPELL_LAND_VICTIM, pAura->GetSpellProto()->procCharges, NULL, NULL);
	else if(m_target->GetAuraStackCount(pAura->GetSpellId()) == 1)
		m_target->RemoveProcTriggerSpell(379, pAura->m_casterGuid);

	return true;
}

bool Reincarnation(uint32 i, Aura* a, bool apply)
{
	Unit* u_target = a->GetTarget();

	if(!u_target->IsPlayer())
		return true;

	Player* p_target = TO_PLAYER(u_target);

	if(apply)
		p_target->bReincarnation = true;
	else
		p_target->bReincarnation = false;

	return true;
}

bool RockbiterWeapon(uint32 i, Spell* pSpell)
{
	uint32 enchantment_entry = 0;
	switch(pSpell->m_spellInfo->RankNumber)
	{
		case 1:
			enchantment_entry = 3021;
		break;
		case 2:
			enchantment_entry = 3024;
		break;
		case 3:
			enchantment_entry = 3027;
		break;
		case 4:
			enchantment_entry = 3030;
		break;
		case 5:
			enchantment_entry = 3033;
		break;
		case 6:
			enchantment_entry = 3036;
		break;
		case 7:
			enchantment_entry = 3039;
		break;
		case 8:
			enchantment_entry = 3042;
		break;
		case 9:
			enchantment_entry = 3018;
		break;
	}

	if(!enchantment_entry || !pSpell->p_caster)
		return true;

	Item* item = pSpell->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
	EnchantEntry* enchant = dbcEnchant.LookupEntry(enchantment_entry);
	if(!item || !enchant)
		return true;

	int32 Slot = item->HasEnchantment(enchant->Id);
	if(Slot >= 0)
		item->ModifyEnchantmentTime(Slot, 1800);
	else
	{
		//check if enchantment slot 1 is taken. If there was no enchantment there function will quit
		item->RemoveEnchantment(1);
		//this will also apply bonuses for us
		Slot = item->AddEnchantment(enchant, 1800, false, true, false, 1);   // 5min
		if(Slot < 0)
			return true;
	}

	sLog.outDebug("ShamanSpells.cpp :: Rockbiter Weapon Rank %u, enchant %u, slot %u", pSpell->m_spellInfo->RankNumber, enchantment_entry, Slot);

	return true;
}

void SetupShamanSpells(ScriptMgr* mgr)
{
	uint32 FlametongueWeaponPassiveIds[] = { 10400, 15567, 15568, 15569, 16311, 16312, 16313, 58784, 58791, 58792, 0 };
	mgr->register_dummy_aura(FlametongueWeaponPassiveIds, &FlametongueWeaponPassive);
	mgr->register_dummy_spell(38443, &SkyShatterRegalia);
	mgr->register_dummy_spell(39610, &ManaTide);
	uint32 earthshielddummyauraids[] = { 974, 32593, 32594, 49283, 49284, 0 };
	mgr->register_dummy_aura(earthshielddummyauraids, &EarthShieldDummyAura);
	mgr->register_dummy_aura(20608, &Reincarnation);
	uint32 rockbiterweaponspellids[] = { 8017, 8018, 8019, 10399, 16314, 16315, 16316, 25479, 25485, 0 };
	mgr->register_dummy_spell(rockbiterweaponspellids, &RockbiterWeapon);
}