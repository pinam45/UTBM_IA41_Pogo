project(UTBM_IA41_Pogo)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

set(CMAKE_CXX_STANDARD 14)

include(cmake/config.cmake)
if(CMAKE_COMPILER_IS_GNUCXX)
	include(cmake/macros/gcc-settings.cmake)
elseif(CMAKE_COMPILER MATCHES "clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	include(cmake/macros/clang-settings.cmake)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D\"DEBUG\"")
	message(STATUS "Debug mode: DEBUG macro defined")
endif()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/PFC_C/ConsoleControl/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/PFC_C/Logger/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/PFC_Cpp/Dispatcher/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/PFC_Cpp/Logger/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Pogo/include/
)

message(STATUS "Sources preparation")
file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/PFC_C/ConsoleControl/src/*"
  "${CMAKE_CURRENT_SOURCE_DIR}/Pogo/src/*"
  )
message("-> Sources prepared")

add_executable(
  UTBM_IA41_Pogo
  ${SOURCE_FILES}
)
