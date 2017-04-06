message(STATUS "Found CLang ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -pedantic-errors -Wall -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion -Wextra -Wformat -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wpointer-arith -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wuninitialized -Wunreachable-code -Wwrite-strings")
message(STATUS "CLang: Enabled warnings")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -s -Os")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O2")
