/*
 * ArcPro MMORPG Server
 * Copyright (c) 2011-2013 ArcPro Speculation <http://arcpro.info/>
 *
 * This program is free software: you can redistribute it and/or modify
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
 
class DedicationOfHonorAI : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(DedicationOfHonorAI)
		DedicationOfHonorAI(GameObject* go) : GameObjectAIScript(go){}
		~DedicationOfHonorAI() {}

		void OnActivate(Player* player)
		{
			Arcpro::Gossip::Menu::SendQuickMenu(_gameobject->GetGUID(), 15921, player, 1, Arcpro::Gossip::ICON_CHAT, "See the fall of the Lich King.");
		}
};

void SetupDalaranGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(202443, &DedicationOfHonorAI::Create);
}