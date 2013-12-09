if(NOT BUILD_OBJECTSCRIPTS )
  message("\tObjectScripts was skipped because BUILD_OBJECTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_OBJECTSCRIPTS)

PROJECT(ObjectScripts)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

#sources -contains source files for our library.
SET( sources
	Setup.cpp
	Eastern Kingdoms/ArathiBasin.cpp
	Eastern Kingdoms/ArathiHighlands.cpp
	Eastern Kingdoms/BlackrockMountain.cpp
	Eastern Kingdoms/BlastedLands.cpp
	Eastern Kingdoms/BurningSteppes.cpp
	Eastern Kingdoms/DeadwindPass.cpp
	Eastern Kingdoms/DeeprunTram.cpp
	Eastern Kingdoms/DunMorogh.cpp
	Eastern Kingdoms/Duskwood.cpp
	Eastern Kingdoms/ElwynnForest.cpp
	Eastern Kingdoms/EversongWoods.cpp
	Eastern Kingdoms/Ghostlands.cpp
	Eastern Kingdoms/HillsbradFoothills.cpp
	Eastern Kingdoms/Hinterlands.cpp
	Eastern Kingdoms/Ironforge.cpp
	Eastern Kingdoms/IsleofQuelDanas.cpp
	Eastern Kingdoms/LochModan.cpp
	Eastern Kingdoms/OldHillsbrad.cpp
	Eastern Kingdoms/RedridgeMountains.cpp
	Eastern Kingdoms/SearingGorge.cpp
	Eastern Kingdoms/SilvermoonCity.cpp
	Eastern Kingdoms/SilverpineForest.cpp
	Eastern Kingdoms/StormwindCity.cpp
	Eastern Kingdoms/Stranglethorn.cpp
	Eastern Kingdoms/SwampofSorrows.cpp
	Eastern Kingdoms/TheHinterlands.cpp
	Eastern Kingdoms/TheScarletEnclave.cpp
	Eastern Kingdoms/TirisfalGlades.cpp
	Eastern Kingdoms/Undercity.cpp
	Eastern Kingdoms/WesternPlaguelands.cpp
	Eastern Kingdoms/Westfall.cpp
	Kalimdor/Ashenvale.cpp
	Kalimdor/Azshara.cpp
	Kalimdor/AzuremystIsle.cpp
	Kalimdor/BloodmystIsle.cpp
	Kalimdor/Darkshore.cpp
	Kalimdor/Darnassus.cpp
	Kalimdor/Desolace.cpp
	Kalimdor/Durotar.cpp
	Kalimdor/DustwallowMarsh.cpp
	Kalimdor/Exodar.cpp
	Kalimdor/Felwood.cpp
	Kalimdor/Feralas.cpp
	Kalimdor/Moonglade.cpp
	Kalimdor/Mulgore.cpp
	Kalimdor/Orgrimmar.cpp
	Kalimdor/Silithus.cpp
	Kalimdor/StonetalonMountains.cpp
	Kalimdor/Tanaris.cpp
	Kalimdor/Teldrassil.cpp
	Kalimdor/TheBarrens.cpp
	Kalimdor/TheFallenKingdom.cpp
	Kalimdor/ThousandNeedles.cpp
	Kalimdor/ThunderBluff.cpp
	Kalimdor/UnGoroCrater.cpp
	Kalimdor/Winterspring.cpp
	Northrend/BoreanTundra.cpp
	Northrend/CrystalsongForest.cpp
	Northrend/Dalaran.cpp
	Northrend/TheStormPeaks.cpp
	Northrend/Wintergrasp.cpp
	Northrend/ZulDrak.cpp
	Other/Misc.cpp
	Outland/BladeEdgeMountains.cpp
	Outland/HellfirePeninsula.cpp
	Outland/Nagrand.cpp
	Outland/Netherstorm.cpp
	Outland/ShadowmoonValley.cpp
	Outland/ShattrathCity.cpp
	Outland/TerokkarForest.cpp
)

SET( headers
	Setup.h
	../Common/EasyFunctions.h )

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)
foreach(src IN ITEMS ${headers} )
  SET( HEADERS ${HEADERS} ${prefix}/${src} )
endforeach(src)

include_directories( ${include_dirs} )
add_library( ${PROJECT_NAME} SHARED ${SRCS} ${HEADERS} )
add_dependencies( ${PROJECT_NAME} ${dependancies} )
target_link_libraries( ${PROJECT_NAME} ${linkages} )

include(PCHSupport)
IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
ENDIF()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ARCPRO_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ARCPRO_SCRIPTLIB_PATH})
#Cleap up our variables(Not required.)
unset( prefix )
unset( SRCS )
unset( sources )