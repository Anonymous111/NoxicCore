#child CMakeLists use this variable to access the source file directories. 
#e.g ${SCRIPTS_PATH}/LuaEngine to access the source files for LuaEngine.

if( NOT BUILD_ARCPROSCRIPTS )
  message( WARNING, "BUILD_ARCPROSCRIPTS option is set to false. Script libraries will not be built." )
  return()
endif(NOT BUILD_ARCPROSCRIPTS)
message("Configuring scripts")
SET( SCRIPTS_PATH ${ROOT_PATH}/src/scripts/src )
#common include directories that script libraries might include.
SET( include_dirs ${GLOBAL_INCLUDE_DIRS} )
SET( dependancies shared world )
SET( linkages world)

#All script libraries have SCRIPTLIB defined.
add_definitions(-DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING)
SET( BUILD_EVENTSCRIPTS TRUE CACHE BOOL "Build EventScripts.")
SET( BUILD_INSTANCESCRIPTS TRUE CACHE BOOL "Build InstanceScripts.")
SET( BUILD_EXTRASCRIPTS TRUE CACHE BOOL "Build ExtraScripts.")
SET( BUILD_GOSSIPSCRIPTS TRUE CACHE BOOL "Build GossipScripts.")
SET( BUILD_QUESTSCRIPTS TRUE CACHE BOOL "Build QuestScripts.")
SET( BUILD_MISCSCRIPTS TRUE CACHE BOOL "Build MiscScripts." )
SET( BUILD_SERVERSTATUSPLUGIN TRUE CACHE BOOL "Build ServerStatusPlugin.")
SET( BUILD_LUAENGINE TRUE CACHE BOOL "Build ArcPro Lua Engine ( ALE ).")
SET( BUILD_SPELLHANDLERS TRUE CACHE BOOL "Build SpellHandlers.")
SET( BUILD_BATTLEGROUNDS TRUE CACHE BOOL "Build Battlegrounds.")
SET( BUILD_WORLDPVPSCRIPTS TRUE CACHE BOOL "Build WorldPvPScripts.")
SET( BUILD_ZONESCRIPTS TRUE CACHE BOOL "Build ZoneScripts.")

add_subdirectory( eventscripts)
add_subdirectory( instancescripts )
add_subdirectory( extrascripts )
add_subdirectory( gossipscripts )
add_subdirectory( questscripts )
add_subdirectory( miscscripts )
add_subdirectory( serverstatusplugin )
add_subdirectory( lualib ) #Used by LuaEngine modules.
add_subdirectory( luaengine )
add_subdirectory( spellhandlers )
add_subdirectory( battlegrounds )
#add_subdirectory( worldpvpscripts )
#add_subdirectory( zonescripts )

unset(SCRIPTS_PATH)
unset(include_dirs)