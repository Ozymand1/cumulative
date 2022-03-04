cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(cumulative)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

find_package(ROOT REQUIRED)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include ${ROOT_INCLUDE_DIR})

message(STATUS "${ROOT_USE_FILE}=${${ROOT_USE_FILE}}")

add_definitions(${ROOT_CXX_FLAGS})
include(${ROOT_USE_FILE})

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(cumulative main.cc ${sources})
target_link_libraries(cumulative ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})