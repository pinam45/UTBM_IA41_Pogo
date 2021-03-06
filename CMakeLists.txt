project(UTBM_IA41_Pogo)
cmake_minimum_required(VERSION 3.7)

# Don't allow to build in sources otherwise a makefile not generated by CMake can be overridden
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Place generated binaries in build/bin
set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/build/bin
)

# Place generated libs in build/lib
set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/build/lib
)
set(
  CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/build/lib
)

# By default build in Release mode
if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Include config files
include(cmake/config.cmake)
if(CMAKE_COMPILER_IS_GNUCXX)
	include(cmake/gcc-settings.cmake)
endif()

# Disable compiler specific extensions
set(CMAKE_C_EXTENSIONS OFF)

# Define LOGGER_ENABLED macro if in debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOGGER_ENABLED")
	message(STATUS "Debug mode: Logger enabled (LOGGER_ENABLED macro defined)")
endif()

# Add dependencies subdirectories
add_subdirectory(ConsoleControl)

# Set include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleControl/ConsoleControl/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/ConsoleControl/Logger/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Pogo/include/
)

# Set libraries directories
link_directories(
  ${CMAKE_BINARY_DIR}/build/lib/
)

# Use static linking for the libraries
set(CMAKE_EXE_LINKER_FLAGS " -static")
#target_link_libraries(UTBM_IA41_Pogo -static-libgcc -static-libstdc++)

# Set sources
message(STATUS "Sources preparation")
file(GLOB_RECURSE SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/Pogo/src/*"
  )
message(" -> Sources prepared")

# Add executable
add_executable(
  UTBM_IA41_Pogo
  ${SOURCE_FILES}
)
add_dependencies(UTBM_IA41_Pogo ConsoleControl)
target_link_libraries(UTBM_IA41_Pogo ConsoleControl)

set_property(TARGET UTBM_IA41_Pogo PROPERTY CXX_STANDARD 14)
set_property(TARGET UTBM_IA41_Pogo PROPERTY CXX_STANDARD_REQUIRED ON)
message(STATUS "UTBM_IA41_Pogo set standard to use: c++14")
