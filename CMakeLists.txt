#CMakeLists file for CaliopeAnalysis

#This Block removes the capability to build in source
#--------------------------------------------------------------------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS "CaliopeAnalysis requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()
#--------------------------------------------------------------------------------

#Setup project and dependencies
#--------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
project(CaliopeAnalysis)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(cmake/FindROOT.cmake)
find_package(OrcaRoot REQUIRED)
#find_library(ORCAROOT_LIBRARY)
mark_as_advanced(FORCE ORCAROOT_INCLUDE_DIR)
mark_as_advanced(FORCE ORCAROOT_LIB)
#This is for what happens if you can't find the orcaroot library
MESSAGE("$ENV{ORDIR}")

# CaliopeAnalysis Version
set(MODULE_VERSION_MAJOR 1)
set(MODULE_VERSION_MINOR 1)
set(MODULE_VERSION_PATCH 1)
set(MODULE_VERSION "${MODULE_VERSION_MAJOR}.${MODULE_VERSION_MINOR}.${MODULE_VERSION_PATCH}")
#--------------------------------------------------------------------------------

include_directories(
	$ENV{ORDIR}/include
	${OrcaRoot_INCLUDE_DIRS}
	${ORCAROOT_INCLUDE_DIRS}
	/Users/kwierman/Dev/Install/external_software/include/root
)

FILE(GLOB ANALYSIS_HEADERS Analysis/*.hh)
FILE(GLOB ANALYSIS_SOURCE Analysis/*.cc)

install(FILES ${ANALYSIS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

add_library(Analysis SHARED
${ANALYSIS_HEADERS}
${ANALYSIS_SOURCE}
)
target_include_directories (Analysis PUBLIC include)
target_link_libraries(Analysis  ${ORCAROOT_LIBRARIES} $ENV{ORDIR}/lib/libOrcaRoot.dylib ${ROOT_LIBRARIES} )
install(TARGETS Analysis LIBRARY DESTINATION lib)
#--------------------------------------------------------------------------------

add_executable(caliopeanalysis Applications/caliopeanalysis.cc)
target_include_directories(caliopeanalysis PUBLIC Analysis)
message("ORCAROOT_LIBRARIES:"${OrcaRoot_LIBRARIES})
target_link_libraries(caliopeanalysis Analysis ${ORCAROOT_LIBRARIES} $ENV{ORDIR}/lib/libOrcaRoot.dylib ${ROOT_LIBRARIES} )
install(TARGETS caliopeanalysis DESTINATION bin)


  
