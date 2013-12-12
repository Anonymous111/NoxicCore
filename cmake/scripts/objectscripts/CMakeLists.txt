if(NOT BUILD_OBJECTSCRIPTS )
  message("\tObjectScripts was skipped because BUILD_OBJECTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_OBJECTSCRIPTS)

PROJECT(ObjectScripts)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

#sources -contains source files for our library.
SET( sources
	Setup.cpp
	EasternKingdoms/ArathiBasin.cpp
	EasternKingdoms/ArathiHighlands.cpp
	EasternKingdoms/BlackrockMountain.cpp
	EasternKingdoms/BlastedLands.cpp
	EasternKingdoms/BurningSteppes.cpp
	EasternKingdoms/DeadwindPass.cpp
	EasternKingdoms/DeeprunTram.cpp
	EasternKingdoms/DunMorogh.cpp
	EasternKingdoms/Duskwood.cpp
	EasternKingdoms/ElwynnForest.cpp
	EasternKingdoms/EversongWoods.cpp
	EasternKingdoms/Ghostlands.cpp
	EasternKingdoms/HillsbradFoothills.cpp
	EasternKingdoms/Hinterlands.cpp
	EasternKingdoms/Ironforge.cpp
	EasternKingdoms/IsleofQuelDanas.cpp
	EasternKingdoms/LochModan.cpp
	EasternKingdoms/OldHillsbrad.cpp
	EasternKingdoms/RedridgeMountains.cpp
	EasternKingdoms/SearingGorge.cpp
	EasternKingdoms/SilvermoonCity.cpp
	EasternKingdoms/SilverpineForest.cpp
	EasternKingdoms/StormwindCity.cpp
	EasternKingdoms/Stranglethorn.cpp
	EasternKingdoms/SwampofSorrows.cpp
	EasternKingdoms/TheHinterlands.cpp
	EasternKingdoms/TheScarletEnclave.cpp
	EasternKingdoms/TirisfalGlades.cpp
	EasternKingdoms/Undercity.cpp
	EasternKingdoms/WesternPlaguelands.cpp
	EasternKingdoms/Westfall.cpp
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