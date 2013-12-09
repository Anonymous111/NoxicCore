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

uint32 numBarrel = 0;

struct Coords
{
	float x;
	float y;
	float z;
	float o;
};

static Coords Fires[] =
{
	{2160.68f, 235.382f, 53.8946f, 3.5555f},
	{2162.26f, 237.439f, 56.7303f, 5.97846f},
	{2192.94f, 258.437f, 54.0479f, 4.1799f},
	{2196.59f, 256.212f, 54.5663f, 4.15633f},
	{2207.03f, 259.549f, 62.1383f, 5.43653f},
	{2225.57f, 248.524f, 62.2857f, 5.6643f},
	{2179.05f, 262.558f, 62.2233f, 0.629895f},
	{2071.52f, 108.279f, 54.6802f, 3.91757f},
	{2160.76f, 246.79f, 62.035f, 0.822316f},
	{2195.19f, 257.229f, 58.0637f, 4.13277f},
	{2072.3f, 110.435f, 56.8422f, 2.74732f},
	{2061.12f, 95.2094f, 62.4747f, 2.04439f},
	{2067.92f, 121.267f, 62.7211f, 1.08228f},
	{2110.83f, 46.0729f, 62.0335f, 2.7159f},
	{2118.41f, 52.8182f, 56.0043f, 2.89655f},
	{2120.1f, 51.7093f, 54.6008f, 5.81823f},
	{2082.69f, 71.9957f, 55.8388f, 2.77088f},
	{2087.61f, 57.1432f, 62.1681f, 2.78659f},
	{2083.42f, 70.0828f, 53.7298f, 4.8247f},
	{2077.26f, 140.631f, 62.9179f, 1.05479f},
	{2070.2f, 75.6493f, 61.9173f, 2.12293f}
};

class LodgesAblaze : public GameObjectAIScript
{
public:
	LodgesAblaze(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO)
	{
		return new LodgesAblaze(GO);
	}

	void OnActivate(Player* pPlayer)       
	{
		QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10283);
		if (++numBarrel == 5)
		{
			if(pQuest != NULL)
			{
				pQuest->SetMobCount(0, pQuest->GetMobCount(0)+1);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
			GameObject* obj;
			for(uint8 i = 0; i < 21; i++)
			{
				obj = sEAS.SpawnGameobject(pPlayer, 183816, Fires[i].x, Fires[i].y, Fires[i].z, Fires[i].o, 1, 0, 0, 0, 0);
				sEAS.GameobjectDelete(obj, 10*60*1000);
			}
			sEAS.SpawnCreature(pPlayer, 17848, 2138.8f, 45.4242f, 52.4437f, 0.0f, 0);
			numBarrel = 0;
		}
	}
};

void SetupOldHillsbradGameobjects(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(182589, &LodgesAblaze::Create);
}