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

#include "../Setup.h"

class ShrineOfDathRemar : public GameObjectAIScript
{
public:
	ShrineOfDathRemar(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO) { return new ShrineOfDathRemar(GO); }

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* qle = pPlayer->GetQuestLogForEntry(8345);
		if(qle)
			qle->SendQuestComplete();
	}
};

class duskwitherspirebottom : public GameObjectAIScript
{
public:
	duskwitherspirebottom(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new duskwitherspirebottom(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, 9334.352f, -7880.743f, 74.910f, 4.724170f);
	}
};

class duskwitherspiretop : public GameObjectAIScript
{
public:
	duskwitherspiretop(GameObject *goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript *Create(GameObject *GO) { return new duskwitherspiretop(GO); }

	void OnActivate(Player *pPlayer)
	{
		pPlayer->SafeTeleport(530, 0, 9291.155f, -7913.556f, 176.130f, 4.724170f);
	}
};

void SetupEversongWoodsGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(180516, &ShrineOfDathRemar::Create);
	mgr->register_gameobject_script(180912, &duskwitherspirebottom::Create);
	mgr->register_gameobject_script(180911, &duskwitherspiretop::Create);
}