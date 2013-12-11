if(NOT BUILD_GOSSIPSCRIPTS )
  message("\tGossipScripts was skipped because BUILD_GOSSIPSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_GOSSIPSCRIPTS)

PROJECT(GossipScripts)

SET( prefix ${SCRIPTS_PATH}/GossipScripts )

#SRCS - contains the source files that compose this project.

set( sources
	Gossip_AlteracMountains.cpp
	Gossip_ArgentTournament.cpp
	Gossip_Azshara.cpp
	Gossip_AzuremystIsle.cpp
	Gossip_Battlemaster.cpp
	Gossip_BlastedLands.cpp
	Gossip_BloodmystIsle.cpp
	Gossip_BoreanTundra.cpp
	Gossip_CrystalsongForest.cpp
	Gossip_Dalaran.cpp
	Gossip_Darkshore.cpp
	Gossip_Dragonblight.cpp
	Gossip_DustwallowMarsh.cpp
	Gossip_EasternPlaguelands.cpp
	Gossip_EversongWoods.cpp
	Gossip_Ghostlands.cpp
	Gossip_Guard.cpp
	Gossip_HellfirePeninsula.cpp
	Gossip_HowlingFjord.cpp
	Gossip_Innkeepers.cpp
	Gossip_IsleOfQuelDanas.cpp
	Gossip_Locksmiths.cpp
	Gossip_Misc.cpp
	Gossip_Moonglade.cpp
	Gossip_Mulgore.cpp
	Gossip_Nagrand.cpp
	Gossip_Netherstorm.cpp
	Gossip_ShadowmoonValley.cpp
	Gossip_Shattrath.cpp
	Gossip_SholazarBasin.cpp
	Gossip_Silithus.cpp
	Gossip_SilvermoonCity.cpp
	Gossip_Stormwind.cpp
	Gossip_StranglethornVale.cpp
	Gossip_Tanaris.cpp
	Gossip_Teldrassil.cpp
	Gossip_TerrokarForest.cpp
	Gossip_TheBarrens.cpp
	Gossip_Theramore.cpp
	Gossip_TheScarletEnclave.cpp
	Gossip_TheStormPeaks.cpp
	Gossip_Trainer.cpp
	Gossip_WyrmrestTemple.cpp
	Gossip_XpEliminator.cpp
	Gossip_Zangarmarsh.cpp
	Setup.cpp
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
unset( prefix)
unset( SRCS )
unset( sources )
