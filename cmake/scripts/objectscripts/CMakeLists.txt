if(NOT BUILD_OBJECTSCRIPTS )
  message("\tObjectScripts was skipped because BUILD_OBJECTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_OBJECTSCRIPTS)

PROJECT(ObjectScripts)

SET( prefix ${SCRIPTS_PATH}/${PROJECT_NAME} )

#sources -contains source files for our library.
SET( sources
	Setup.cpp
	ArathiBasin.cpp
	ArathiHighlands.cpp
	Ashenvale.cpp
	Azshara.cpp
	AzuremystIsle.cpp
	BlackrockMountain.cpp
	BladeEdgeMountains.cpp
	BlastedLands.cpp
	BloodmystIsle.cpp
	BoreanTundra.cpp
	BurningSteppes.cpp
	CrystalsongForest.cpp
	Dalaran.cpp
	Darkshore.cpp
	Darnassus.cpp
	DeadwindPass.cpp
	DeeprunTram.cpp
	Desolace.cpp
	DunMorogh.cpp
	Durotar.cpp
	Duskwood.cpp
	DustwallowMarsh.cpp
	ElwynnForest.cpp
	EversongWoods.cpp
	Exodar.cpp
	Felwood.cpp
	Feralas.cpp
	Ghostlands.cpp
	HellfirePeninsula.cpp
	HillsbradFoothills.cpp
	Hinterlands.cpp
	Ironforge.cpp
	IsleofQuelDanas.cpp
	LochModan.cpp
	Misc.cpp
	Moonglade.cpp
	Mulgore.cpp
	Nagrand.cpp
	Netherstorm.cpp
	Orgrimmar.cpp
	RedridgeMountains.cpp
	SearingGorge.cpp
	ShattrathCity.cpp
	Silithus.cpp
	SilvermoonCity.cpp
	SilverpineForest.cpp
	StonetalonMountains.cpp
	StormwindCity.cpp
	Stranglethorn.cpp
	SwampofSorrows.cpp
	Tanaris.cpp
	Teldrassil.cpp
	TerokkarForest.cpp
	TheBarrens.cpp
	TheFallenKingdom.cpp
	TheHinterlands.cpp
	TheScarletEnclave.cpp
	TheStormPeaks.cpp
	ThousandNeedles.cpp
	ThunderBluff.cpp
	TirisfalGlades.cpp
	UnderCity.cpp
	UnGoroCrater.cpp
	WesternPlaguelands.cpp
	Westfall.cpp
	Wintergrasp.cpp
	Winterspring.cpp
	ZulDrak.cpp )

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