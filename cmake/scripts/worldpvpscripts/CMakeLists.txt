IF( NOT BUILD_WORLDPVPSCRIPTS )
	message("\tWorldPvPScripts was skipped because BUILD_WORLDPVPSCRIPTS is unchecked.")
	return()
ENDIF( NOT BUILD_WORLDPVPSCRIPTS )

PROJECT(WorldPvPScripts)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

set( sources
	ZoneHellfirePeninsula.cpp
	ZoneSilithus.cpp
	ZoneZangarmarsh.cpp
	ZoneTerokkarForest.cpp
	ZoneNagrand.cpp
	Setup.cpp )

SET( headers
	Setup.h
)

FOREACH( src IN ITEMS ${sources} )
	SET( SRCS ${SRCS} ${prefix}/${src} )
ENDFOREACH(src)

include_directories( ${include_dirs} ${prefix} )
add_library( ${PROJECT_NAME} SHARED ${SRCS} )
add_dependencies( ${PROJECT_NAME} ${dependancies} )
target_link_libraries( ${PROJECT_NAME} ${linkages} )
install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ARCPRO_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ARCPRO_SCRIPTLIB_PATH} )
#Clean up our variables(Not required.)
unset( prefix )
unset( SRCS )
unset( sources )