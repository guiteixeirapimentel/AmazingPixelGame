cmake_minimum_required(VERSION 3.15)
project(myproject CXX)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

include_directories(src external/AMGCL)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB SOURCES "src/*.cpp")
file(GLOB GAMEMECHANICS "src/GameMechanics/*.cpp")
file(GLOB CONTROLSSOURCES "src/Controls/*.cpp")
file(GLOB GFXSOURCES "src/GFX/*.cpp")
file(GLOB PHYSICSSOURCES "src/Physics/*.cpp")
add_executable(game ${SOURCES} ${GAMEMECHANICS} ${CONTROLSSOURCES} ${GFXSOURCES} ${PHYSICSSOURCES})


find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})
target_link_libraries(game PRIVATE ${SDL_LIBRARIES})


