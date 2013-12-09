IF( NOT BUILD_ZONESCRIPTS )
	message("\tZoneScripts was skipped because BUILD_ZONESCRIPTS is unchecked.")
	return()
ENDIF( NOT BUILD_ZONESCRIPTS )

PROJECT(ZoneScripts)

SET( prefix ${ROOT_PATH}/src/scripts/src/${PROJECT_NAME} )

#sources -contains source files for our library.
SET( sources
	Eastern Kingdoms/ArathiHighlands.cpp
	Eastern Kingdoms/BlastedLands.cpp
	Eastern Kingdoms/Duskwood.cpp
	Eastern Kingdoms/EasternPlaguelands.cpp
	Eastern Kingdoms/ElwynnForest.cpp
	Eastern Kingdoms/EversongWoods.cpp
	Eastern Kingdoms/Ghostlands.cpp
	Eastern Kingdoms/HillsbradFoothills.cpp
	Eastern Kingdoms/Ironforge.cpp
	Eastern Kingdoms/IsleOfQuelDanas.cpp
	Eastern Kingdoms/LochModan.cpp
	Eastern Kingdoms/RedridgeMountains.cpp
	Eastern Kingdoms/SilvermoonCity.cpp
	Eastern Kingdoms/SilverpineForest.cpp
	Eastern Kingdoms/StormwindCity.cpp
	Eastern Kingdoms/Stranglethorn.cpp
	Eastern Kingdoms/TheScarletEnclave.cpp
	Eastern Kingdoms/TirisfalGlades.cpp
	Eastern Kingdoms/Undercity.cpp
	Eastern Kingdoms/WesternPlaguelands.cpp
	Eastern Kingdoms/Westfall.cpp
	Kalimdor/Azshara.cpp
	Kalimdor/AzuremystIsle.cpp
	Kalimdor/BloodmystIsle.cpp
	Kalimdor/Darkshore.cpp
	Kalimdor/Darnassus.cpp
	Kalimdor/Desolace.cpp
	Kalimdor/Durotar.cpp
	Kalimdor/DustwallowMarsh.cpp
	Kalimdor/Exodar.cpp
	Kalimdor/Mulgore.cpp
	Kalimdor/Orgrimmar.cpp
	Kalimdor/Tanaris.cpp
	Kalimdor/TheBarrens.cpp
	Kalimdor/ThousandNeedles.cpp
	Kalimdor/ThunderBluff.cpp
	Kalimdor/UnGoroCrater.cpp
	Northrend/BoreanTundra.cpp
	Northrend/Dragonblight.cpp
	Northrend/HowlingFjord.cpp
	Northrend/Icecrown.cpp
	Northrend/SholazarBasin.cpp
	Other/Misc.cpp
	Outland/BladeEdgeMountains.cpp
	Outland/HellfirePeninsula.cpp
	Outland/Nagrand.cpp
	Outland/ShadowmoonValley.cpp
	Outland/TerrokarForest.cpp
)

SET( headers
    Setup.h
	../Common/EasyFunctions.h
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
