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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

void Aura::SpellAuraTransform(bool apply)
{
	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummyAura(GetSpellId(), mod->i, this, apply))
		return;

	uint32 displayId = 0;
	CreatureInfo* ci = CreatureNameStorage.LookupEntry(mod->m_miscValue);

	if(ci)
		displayId = ci->Male_DisplayID;

	if(p_target != NULL)
		p_target->Dismount();

	// SetPositive();
	switch(GetSpellProto()->Id)
	{
		case 30403: // Arcane Infusion
			m_target->SetDisplayId(apply ? 19416 : m_target->GetNativeDisplayId());
		break;
		case 34204: // Arcane Form
			m_target->SetDisplayId(apply ? 19031 : m_target->GetNativeDisplayId());
		break;
		case 45033: // Abyssal Transformation
			m_target->SetDisplayId(apply ? 22810 : m_target->GetNativeDisplayId());
		break;
		case 20584: // Wisp
			m_target->SetDisplayId(apply ? 10045 : m_target->GetNativeDisplayId());
		break;
		case 47133: // Ghost Wolf
			m_target->SetDisplayId(apply ? 23114 : m_target->GetNativeDisplayId());
		break;
		case 28443: // Transform Ghost
			m_target->SetDisplayId(apply ? 16179 : m_target->GetNativeDisplayId());
		break;
		case 39916: // Soulgrinder Ghost Transform
			m_target->SetDisplayId(apply ? 21233 : m_target->GetNativeDisplayId());
		break;
		case 46753: // Borean Tundra - Quest - Transform to Valanar
			m_target->SetDisplayId(apply ? 25514 : m_target->GetNativeDisplayId());
		break;
		case 32745: // Chess: Disabled Square Transform
			m_target->SetDisplayId(apply ? 10045 : m_target->GetNativeDisplayId());
		break;
		case 24721: // Buru Transform
			m_target->SetDisplayId(apply ? 15655 : m_target->GetNativeDisplayId());
		break;
		case 25107: // Blue Dragon Transform DND
			m_target->SetDisplayId(apply ? 15413 : m_target->GetNativeDisplayId());
		break;
		case 64490: // Black Knight Transform
			m_target->SetDisplayId(apply ? 29085 : m_target->GetNativeDisplayId());
		break;
		case 32616: // Barnes Tuxedo Transform
			m_target->SetDisplayId(apply ? 18039 : m_target->GetNativeDisplayId());
		break;
		case 24190: // Arlokk Transform
			m_target->SetDisplayId(apply ? 15013 : m_target->GetNativeDisplayId());
		break;
		case 4063: // Argus Shadow Mage Transform
			m_target->SetDisplayId(apply ? 775 : m_target->GetNativeDisplayId());
		break;
		case 69877: // Alliance Brigadier General Transform (Stormwind)
			m_target->SetDisplayId(apply ? 30509 : m_target->GetNativeDisplayId());
		break;
		case 30473: // Coo Transform Furbolg DND
			m_target->SetDisplayId(apply ? 17019 : m_target->GetNativeDisplayId());
		break;
		case 29489: // Concubine Transform
			m_target->SetDisplayId(apply ? 10926 : m_target->GetNativeDisplayId());
		break;
		case 58986: // Chromie Transform
			m_target->SetDisplayId(apply ? 10008 : m_target->GetNativeDisplayId());
		break;
		case 58668: // Cyanigosa Transform
			m_target->SetDisplayId(apply ? 27340 : m_target->GetNativeDisplayId());
		break;
		case 74667: // Durak's Shield Transform Stage2
			m_target->SetDisplayId(apply ? 23257 : m_target->GetNativeDisplayId());
		break;
		case 51834: // Drakuru Transform
			m_target->SetDisplayId(apply ? 28121 : m_target->GetNativeDisplayId());
		break;
		case 4329: // Drag and Drop: Dark Subjugator Transform
			m_target->SetDisplayId(apply ? 27889 : m_target->GetNativeDisplayId());
		break;
		case 50738: // Don Carlos Hatless Transform
			m_target->SetDisplayId(apply ? 25125 : m_target->GetNativeDisplayId());
		break;
		case 43311: // Halazzi Transform
		case 43272:
		case 43271:
		case 43145:
			m_target->SetDisplayId(apply ? 21632 : m_target->GetNativeDisplayId());
		break;
		case 25105: // Green Dragon Transform DND
			m_target->SetDisplayId(apply ? 15412 : m_target->GetNativeDisplayId());
		break;
		case 33316: // Giselda Transform DND
			m_target->SetDisplayId(apply ? 17543 : m_target->GetNativeDisplayId());
		break;
		case 48304: // Fresh Remounts: Skeletal Warhorse Transform
			m_target->SetDisplayId(apply ? 10719 : m_target->GetNativeDisplayId());
		break;
		case 39158: // Evergrove Druid Transform Druid
			m_target->SetDisplayId(apply ? 20991 : m_target->GetNativeDisplayId());
		break;
		case 38776: // Evergrove Druid Transform Crow
			m_target->SetDisplayId(apply ? 20997 : m_target->GetNativeDisplayId());
		break;
		case 22097: // Eliminate the Competition: Onu'zun's Frog Transform
			m_target->SetDisplayId(apply ? 23311 : m_target->GetNativeDisplayId());
		break;
		case 36658: // Transform
			m_target->SetDisplayId(apply ? 2582 : m_target->GetNativeDisplayId());
		break;
		case 70900: // Dark Transformation
			m_target->SetDisplayId(apply ? 22124 : m_target->GetNativeDisplayId());
		break;
		/*case 24735: // Ghost Costume
		case ??: 
		{
			case 24735:
				m_target->SetDisplayId(10478);
				m_target->SetDisplayId(10479);
			break;
			case ??: //Female
				m_target->SetDisplayId(10481);
				m_target->SetDisplayId(10480);
			break;
		}break;*/
		case 30167: // Red Ogre Costume
		{
			if(apply)
				m_target->SetDisplayId(11549);
			else
				m_target->SetDisplayId(m_target->GetNativeDisplayId());
		}break;
		case 41301: // Time-Lost Figurine
		{
			if(apply)
				m_target->SetDisplayId(18628);
			else
				m_target->SetDisplayId(m_target->GetNativeDisplayId());
		}break;
		case 16739: // Orb of Deception
		{
			if(apply)
			{
				if(m_target->getRace() == RACE_ORC)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10139);
					else
						m_target->SetDisplayId(10140);
				}
				if(m_target->getRace() == RACE_TAUREN)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10136);
					else
						m_target->SetDisplayId(10147);
				}
				if(m_target->getRace() == RACE_TROLL)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10135);
					else
						m_target->SetDisplayId(10134);
				}
				if(m_target->getRace() == RACE_UNDEAD)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10146);
					else
						m_target->SetDisplayId(10145);
				}
				if(m_target->getRace() == RACE_BLOODELF)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(17829);
					else
						m_target->SetDisplayId(17830);
				}
				if(m_target->getRace() == RACE_GNOME)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10148);
					else
						m_target->SetDisplayId(10149);
				}
				if(m_target->getRace() == RACE_DWARF)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10141);
					else
						m_target->SetDisplayId(10142);
				}
				if(m_target->getRace() == RACE_HUMAN)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10137);
					else
						m_target->SetDisplayId(10138);
				}
				if(m_target->getRace() == RACE_NIGHTELF)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(10143);
					else
						m_target->SetDisplayId(10144);
				}
				if(m_target->getRace() == RACE_DRAENEI)
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(17827);
					else
						m_target->SetDisplayId(17828);
				}
			}
			else
				m_target->SetDisplayId(m_target->GetNativeDisplayId());
		}break;
		case 42365:	// murloc costume
			m_target->SetDisplayId(apply ? 21723 : m_target->GetNativeDisplayId());
		break;
		case 50517: // Dread Corsair
		case 51926: // Corsair Costume
		{
			if(apply)
			{
				case RACE_ORC:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25039);
					else
						m_target->SetDisplayId(25050);
				}break;
				case RACE_TAUREN:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25040);
					else
						m_target->SetDisplayId(25051);
				}break;
				case RACE_TROLL:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25041);
					else
						m_target->SetDisplayId(25052);
				}break;
				case RACE_UNDEAD:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25042);
					else
						m_target->SetDisplayId(25053);
				}break;
				case RACE_BLOODELF:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25032);
					else
						m_target->SetDisplayId(25043);
				}break;
				case RACE_GNOME:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25035);
					else
						m_target->SetDisplayId(25046);
				}break;
				case RACE_DWARF:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25034);
					else
						m_target->SetDisplayId(25045);
				}break;
				case RACE_HUMAN:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25037);
					else
						m_target->SetDisplayId(25048);
				}break;
				case RACE_NIGHTELF:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25038);
					else
						m_target->SetDisplayId(25049);
				}break;
				case RACE_DRAENEI:
				{
					if(m_target->getGender() == 0)
						m_target->SetDisplayId(25033);
					else
						m_target->SetDisplayId(25044);
				}break;
			}
			else
				m_target->SetDisplayId(m_target->GetNativeDisplayId());
		}break;
		case 118: // Polymorph
		case 228: // Polymorph: Chicken
		case 851: // Polymorph: Sheep
		case 5254:
		case 12824:
		case 12825:
		case 12826:
		case 13323: // Polymorph
		case 14621: // Polymorph
		case 15534: // Polymorph
		case 22274: // Greater Polymorph
		case 23603: // Wild Polymorph
		case 27760: // Polymorph
		case 28270:  // Polymorph: Cow
		case 28271:  // Polymorph: Turtle
		case 28272:  // Polymorph: Pig
		case 29124: // Polymorph
		case 29848: // Polymorph
		//case 29963: // Mass Polymorph // Forcing all nearby enemies into sheep instead // Only works on beasts, dragons, giants, humanoids, and critters.
		case 30838: // Polymorph: Helboar
		case 33173: // Greater Polymorph
		case 34639: // Polymorph: Lasher
		case 36840: // Polymorph
		case 38245: // Polymorph
		case 38896: // Polymorph
		case 41334: // Polymorph
		case 43309: // Polymorph
		case 46280: // Polymorph
		//case 51514: // Hex
		case 58537: // Polymorph
		case 61025: // Polymorph: Serpent
		case 61305: // Polymorph: Black Cat
		case 61721: // Polymorph: Rabbit
		case 61780: // Polymorph: Turkey
		case 61816: // Polymorph: Sheep // TODO: Right-clicking this will remove the effect
		case 61834: // Manabonked!
		//case 61839: // Polymorph: Sheep // TODO: Triggers spell: Manabonked! 61834
		case 65801: // Polymorph
		case 66043: // Polymorph
		{// http://wotlk.openwow.com/npc=16372
			if(!displayId)
			{
				switch(GetSpellProto()->Id)
				{
					/*case 51514: // Frog
						displayId = ;
					break;*/
					case 28270: // Cow
						displayId = 1060;
					break;
					case 28272: // Pig
						displayId = 16356 + RandomUInt(2);
					break;
					case 28271: // Turtle
						displayId = 16359 + RandomUInt(2);
					break;
					case 61780: // Turkey
						displayId = 32822;
					break;
					case 30838: // Helboar
						displayId = 11410;
					break;
					case 61721: // Rabbit
						displayId = 32789;
					break;
					case 61305: // Black Cat
						displayId = 32570;
					break;
					case 61025: // Serpent
						displayId = 1206;
					break;
					case 34639: // Lasher
						displayId = 11634;
					break;
					case 228: // Chicken
						displayId = 304;
					break;
					case 61834:
						displayId = 16372;
					break;
					default: // Sheep
						displayId = 856;
					break;
				}
			}
			if(apply)
			{
				Unit* caster = GetUnitCaster();
				if(caster != NULL && m_target->IsCreature())
					m_target->GetAIInterface()->AttackReaction(caster, 1, GetSpellId());

				m_target->SetDisplayId(displayId);

				// remove the current spell (for channalers)
				if(m_target->m_currentSpell && m_target->GetGUID() != m_casterGuid && m_target->m_currentSpell->getState() == SPELL_STATE_CASTING)
				{
					m_target->m_currentSpell->cancel();
					m_target->m_currentSpell = 0;
				}
				sEventMgr.AddEvent(this, &Aura::EventPeriodicHeal1, (uint32)1000, EVENT_AURA_PERIODIC_HEAL, 1000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				m_target->polySpell = GetSpellProto()->Id;
			}
			else
			{
				m_target->SetDisplayId(m_target->GetNativeDisplayId());
				m_target->polySpell = 0;
			}
		}break;
		case 19937:
		{
			if(apply)
			{
				// TODO: Sniff the spell / item, we need to know the real displayID
				// guessed this may not be correct
				// human = 7820
				// dwarf = 7819
				// Halfling = 7818
				// maybe 7842 as its from a lesser npc
				m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 7842);
			}
			else
				m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, m_target->GetNativeDisplayId());
		}break;
		default:
		{
			if(!displayId) return;
				if(apply)
					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayId);
				else
					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, m_target->GetNativeDisplayId());
		}break;
	};

	m_target->EventModelChange();
}