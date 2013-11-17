IF( NOT BUILD_ZONESCRIPTS )
	message("\tZoneScripts was skipped because BUILD_ZONESCRIPTS is unchecked.")
	return()
ENDIF( NOT BUILD_ZONESCRIPTS )

PROJECT(ZoneScripts)

SET( prefix ${ROOT_PATH}/src/scripts/src/${PROJECT_NAME} )

#sources -contains source files for our library.
SET( sources
	ArathiHighlands.cpp
	BladeEdgeMountains.cpp
	BlastedLands.cpp
	BloodmystIsle.cpp
	BoreanTundra.cpp
	Durotar.cpp
	HellfirePeninsula.cpp
	Icecrown.cpp
	Misc.cpp
	Orgrimmar.cpp
    Setup.cpp
	ShadowmoonValley.cpp
	SilverpineForest.cpp
	Tanaris.cpp
	TheBarrens.cpp
	TheScarletEnclave.cpp
	WesternPlaguelands.cpp
 )

SET( headers
    Setup.h
 )
 
foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)
foreach(src IN ITEMS ${headers} )
  SET( HEADERS ${HEADERS} ${prefix}/${src} )
endforeach(src)

include_directories( ${GLOBAL_INCLUDE_DIRS} )
add_library( ${PROJECT_NAME} SHARED ${SRCS} ${HEADERS})
add_dependencies( ${PROJECT_NAME} shared world )
add_definitions( -DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING )
target_link_libraries( ${PROJECT_NAME} world )

include(PCHSupport)
IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
ENDIF()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ARCPRO_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ARCPRO_SCRIPTLIB_PATH} )
#Cleap up our variables(Not required.)
unset( prefix )
unset( SRCS )
unset( HEADERS )
unset( headers )
unset( sources )
