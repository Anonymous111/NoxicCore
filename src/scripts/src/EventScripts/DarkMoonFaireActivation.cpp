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

#include "StdAfx.h"
#include "Setup.h"

/*enum DARKMOONFAIRE_LOCATIONS
{
	MULGORE = 1,
	TEROKKAR_FOREST = 530,
	ELWYN_FOREST = 0
};

enum DARKMOONFAIRE_STATES
{
	NOTHING = 0,
	BUILDING = 1,
	ACTIVE = 2
};

struct DarkmoonFaireType
{
	uint32 MapId;
	uint32 State;
};

#define BUILDING_DURATION 3 // days
#define ACTIVE_DURATION 7 // days

typedef std::pair<uint32, uint32> DarkmoonFaireTypePair;
typedef std::map<DarkmoonFaireTypePair, std::set<CreatureSpawn >> CreatureSpawnsMap;
typedef std::map<uint32, WayPointMap*> CreatureWaypointsMap;
typedef std::map<DarkmoonFaireTypePair, std::set<GOSpawn*>> GameObjectSpawnsMap;
typedef std::map<uint32, uint32> CreatureSQLIdMap;

class DarkmoonFaire : public Singleton<DarkmoonFaire>, public EventableObject
{
	public:
		DarkmoonFaire() {}
		~DarkmoonFaire() { delete this; }

		void Init();
	private:
		CreatureSQLIdMap CreatureSQLId;
		CreatureSpawnsMap CreatureSpawns;
		CreatureWaypointsMap CreatureWaypoints;
		GameObjectSpawnsMap GameObjectSpawns;
		set< Creature * > Creatures;
		set< GameObject * > GameObjects;

		DarkmoonFaireTypePair Type;
		uint32 start;

		inline void SetMapId(uint32 i) { Type.first = i; }
		inline void SetState(uint32 i) { Type.second = i; }

		inline uint32 GetMapId() { return Type.first; }
		inline uint32 GetState() { return Type.second; }

		void LoadDB();
		void Update();
		void Spawn();
		void DeleteSpawns();
};

#define sDarkmoonFaire DarkmoonFaire::getSingleton()

initialiseSingleton(DarkmoonFaire);

void DarkmoonFaire::Init()
{
	start = 0;
	Type = make_pair(0, NOTHING);

	LoadDB();
	Update();
}

void DarkmoonFaire::LoadDB()
{
	char* tables[] = { "darkmoonfaire_creature_spawns", "darkmoonfaire_creature_formations", "darkmoonfaire_gameobject_spawns" };
	for(uint32 i = 0; i < 3; i++)
	{
		QueryResult * result = WorldDatabase.Query("SELECT * FROM %s", tables[i]);
		if(result == NULL)
			return;
		do
		{
			Field* f = result->Fetch();
			if(tables[i] == "darkmoonfaire_creature_spawns" && result->GetFieldCount() == 21)
			{
				CreatureSpawn* cs = new CreatureSpawn;
				cs->id = objmgr.GenerateCreatureSpawnID();
				cs->form = NULL;
				cs->entry = f[1].GetUInt32();
				cs->x = f[3].GetFloat();
				cs->y = f[4].GetFloat();
				cs->z = f[5].GetFloat();
				cs->o = f[6].GetFloat();
				cs->movetype = f[7].GetUInt8();
				cs->displayid = f[8].GetUInt32();
				cs->factionid = f[9].GetUInt32();
				cs->flags = f[10].GetUInt32();
				cs->bytes0 = f[11].GetUInt32();
				cs->bytes1 = f[13].GetUInt32();
				cs->bytes2 = f[14].GetUInt32();
				cs->emote_state = f[15].GetUInt32();
				cs->channel_spell = f[16].GetUInt16();
				cs->channel_target_go = f[17].GetUInt32();
				cs->channel_target_creature = f[18].GetUInt32();
				cs->stand_state = f[19].GetUInt16();

				QueryResult* r2 = WorldDatabase.Query("SELECT * FROM darkmoonfaire_creature_waypoints WHERE spawnid = %u", f[0].GetUInt32());
				if(r2 != NULL)
				{
					do
					{
						Field* f2 = r2->Fetch();
						WayPoint* wp = new WayPoint;
						wp->id = f2[1].GetUInt32();
						wp->x = f2[2].GetFloat();
						wp->y = f2[3].GetFloat();
						wp->z = f2[4].GetFloat();
						wp->waittime = f2[5].GetUInt32();
						wp->flags = f2[6].GetUInt32();
						wp->forwardemoteoneshot = f2[7].GetBool();
						wp->forwardemoteid = f2[8].GetUInt32();
						wp->backwardemoteoneshot = f2[9].GetBool();
						wp->backwardemoteid = f2[10].GetUInt32();
						wp->forwardskinid = f2[11].GetUInt32();
						wp->backwardskinid = f2[12].GetUInt32();

						CreatureWaypointsMap::const_iterator wit = CreatureWaypoints.find(cs->id);
						if(wit == CreatureWaypoints.end())
						{
							WayPointMap* m = new WayPointMap;
							if(m->size() <= wp->id)
							{
								m->resize(wp->id + 1);
							}
							(*m)[wp->id] = wp;
							CreatureWaypoints.insert(make_pair(cs->id, m));
						}
						else
						{
							if(wit->second->size() <= wp->id)
							{
								wit->second->resize(wp->id + 1);
							}
							(*(wit->second))[wp->id] = wp;
						}
					}while(r2->NextRow());
					delete r2;
				}

				DarkmoonFaireTypePair t = make_pair(f[2].GetUInt32(), f[20].GetUInt32());
				CreatureSpawnsMap::iterator it = CreatureSpawns.find(t);
				if(it == CreatureSpawns.end())
				{
					set< CreatureSpawn * > s;
					s.insert(cs);
					CreatureSpawns.insert(make_pair(t, s));
				}
				else
					it->second.insert(cs);
				CreatureSQLId.insert(make_pair(f[0].GetUInt32(), cs->id));
			}
			else if(tables[i] == "darkmoonfaire_creature_formations" && result->GetFieldCount() == 4)
			{
						Formation * form = new Formation;
						form->fol = CreatureSQLId.find(f[1].GetUInt32())->second;
						form->ang = f[2].GetFloat();
						form->dist = f[3].GetFloat();

						bool b;
						for(CreatureSpawnsMap::const_iterator it = CreatureSpawns.begin(); it != CreatureSpawns.end(); it++)
						{
							b = false;
							uint32 sqlid = CreatureSQLId.find(f[0].GetUInt32())->second;
							for(set< CreatureSpawn * >::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
							{
								if((*it2)->id == sqlid)
								{
									(*it2)->form = form;
									b = true;
									break;
								}
							}
							if(b)
								break;
						}
			}
			else if(tables[i] == "darkmoonfaire_gameobject_spawns" && result->GetFieldCount() == 17)
			{
				GOSpawn* gs = new GOSpawn;
				gs->id = objmgr.GenerateGameObjectSpawnID();
				gs->entry = f[1].GetUInt32();
				gs->x=f[3].GetFloat();
				gs->y=f[4].GetFloat();
				gs->z=f[5].GetFloat();
				gs->facing=f[6].GetFloat();
				gs->o =f[7].GetFloat();
				gs->o1=f[8].GetFloat();
				gs->o2=f[9].GetFloat();
				gs->o3=f[10].GetFloat();
				gs->state=f[11].GetUInt32();
				gs->flags=f[12].GetUInt32();
				gs->faction=f[13].GetUInt32();
				gs->scale = f[14].GetFloat();

				DarkmoonFaireTypePair t = make_pair(f[2].GetUInt32(), f[16].GetUInt32());
				GameObjectSpawnsMap::iterator it = GameObjectSpawns.find(t);
				if(it == GameObjectSpawns.end())
				{
					set<GOSpawn*> s;
					s.insert(gs);
					GameObjectSpawns.insert(make_pair(t, s));
				}
				else
					it->second.insert(gs);
			}
		}
		while(result->NextRow());
		delete result;
	}
}

void DarkmoonFaire::Spawn()
{
	sLog.outString("Spawn: MapId = %u, State = %u", GetMapId(), GetState());
	MapMgr* pMapMgr = sInstanceMgr.GetMapMgr(GetMapId());
	if(pMapMgr == NULL)
		return;

	CreatureSpawnsMap::const_iterator cit = CreatureSpawns.find(Type);
	if(cit != CreatureSpawns.end())
	{
		for(set<CreatureSpawn*>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); cit2++)
		{
			Creature * c = pMapMgr->CreateCreature((*cit2)->entry);
			ASSERT(c);
			c->Load((*cit2), 0, NULL);
			CreatureWaypointsMap::const_iterator wit = CreatureWaypoints.find((*cit2)->id);
			if(wit != CreatureWaypoints.end())
				c->GetAIInterface()->SetWaypointMap(wit->second);
			c->PushToWorld(pMapMgr);

			Creatures.insert(c);
		}
	}

	GameObjectSpawnsMap::const_iterator git = GameObjectSpawns.find(Type);
	if(git != GameObjectSpawns.end())
	{
		for(set<GOSpawn*>::const_iterator git2 = git->second.begin(); git2 != git->second.end(); git2++)
		{
			GameObject* g = pMapMgr->CreateGameObject((*git2)->entry);
			ASSERT(g);
			g->Load((*git2));
			g->PushToWorld(pMapMgr);
			GameObjects.insert(g);
		}
	}
}

void DarkmoonFaire::Update()
{
	if(start == 0 || start + ACTIVE_DURATION * 24 * 60 * 60 <= UNIXTIME)
	{
		time_t now;
		struct tm * ts;

		time(&now);
		ts = localtime(&now);

		int today = ts->tm_mday, tomon = ts->tm_mon;
		ts->tm_sec = 0;
		ts->tm_min = 0;
		ts->tm_hour = 0;
		ts->tm_mday = 1;
		mktime(ts);

		// find start of carneval week :P
		while(ts->tm_wday % 7 != 1 || ts->tm_mday < BUILDING_DURATION + 1)
		{
				ts->tm_wday++;
				ts->tm_mday++;
				if(tomon == ts->tm_mon && today > ts->tm_mday + ACTIVE_DURATION)
				{
						ts->tm_mday = 1;
						if(ts->tm_mon == 11)
								ts->tm_mon = 0;
						else
								ts->tm_mon++;
						mktime(ts);
				}
		}

		start = mktime(ts);
		switch((ts->tm_mon + 1) % 3)
		{
			case 0:
				SetMapId(ELWYN_FOREST);
			break;
			case 1:
				SetMapId(MULGORE);
			break;
			case 2:
				SetMapId(TEROKKAR_FOREST); 
			break;
		}
	}

	if(GetState() != NOTHING)
		DeleteSpawns();

	uint32 next_update;
	if(start > UNIXTIME && UNIXTIME >= start - BUILDING_DURATION * 24 * 60 * 60)
	{
		SetState(BUILDING);
		next_update = (start - UNIXTIME) * 1000;
	}
	else if(start <= UNIXTIME && UNIXTIME < start + ACTIVE_DURATION * 24 * 60 * 60)
	{
		SetState(ACTIVE);
		next_update = (start + ACTIVE_DURATION * 24 * 60 * 60 - UNIXTIME) * 1000;
	}
	else
		next_update = (start - BUILDING_DURATION * 24 * 60 * 60 - UNIXTIME) * 1000;

	sEventMgr.AddEvent(this, &DarkmoonFaire::Update, 0, next_update, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	if(GetState() != NOTHING)
		Spawn();
}

void DarkmoonFaire::DeleteSpawns()
{
	if(!Creatures.empty())
	{
		for(set< Creature * >::iterator it = Creatures.begin(); it != Creatures.end(); it++)
			(*it)->Despawn(0, 0);
		Creatures.clear();
	}
	if(!GameObjects.empty())
	{
		for(set< GameObject * >::iterator it = GameObjects.begin(); it != GameObjects.end(); it++)
			(*it)->Despawn(0 , 0);
		GameObjects.clear();
	}
}
*/
void SetupDarkmoonFaireBuild(ScriptMgr * mgr)
{
	/*if(!DarkmoonFaire::getSingletonPtr())
		new DarkmoonFaire;

	sDarkmoonFaire.Init();*/
}