# CMakeList.txt : CMake project for first_raylib_game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("first_raylib_game")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RAYLIB_INCLUDE "C:/Side_Projects/raylib")
set(RAYLIB_LIB "C:/Side_Projects/first_raylib_game/first_raylib_game/libs/raylib")


# Add source to this project's executable.
include_directories(first_raylib_game PRIVATE ${RAYLIB_INCLUDE}/src)
add_executable(first_raylib_game "first_raylib_game.cpp" "first_raylib_game.h")


find_library(found_library raylib PATH ${RAYLIB_LIB}/Debug)    
target_link_libraries(first_raylib_game PRIVATE ${found_library} winmm)

#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#    find_library(${RAYLIB_DIR} raylib PATH ${RAYLIB_DIR}/Debug)    
#    # Add source to this project's executable.
#    add_executable(raylib "first_raylib_game.cpp" "first_raylib_game.h")
#    include_directories(first_raylib_game PRIVATE ${RAYLIB_DIR}/src)
#    target_link_libraries(first_raylib_game PRIVATE ${raylib})
##else()
#    target_link_directories(first_raylib_game PRIVATE ${RAYLIB_DIR}/Release)
#    target_link_libraries(first_raylib_game PRIVATE ${RAYLIB_DIR}/Release/raylib)
#endif()



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET first_raylib_game PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
