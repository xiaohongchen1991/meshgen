cmake_minimum_required (VERSION 2.6)

# The version number.
set (MESHGEN_VERSION_MAJOR 1)
set (MESHGEN_VERSION_MINOR 0)
set (MESHGEN_VERSION_PATCH 0)

set(VERSION ${MESHGEN_VERSION_MAJOR}.${MESHGEN_VERSION_MINOR}.${MESHGEN_VERSION_PATCH})
message(STATUS "meshgen version ${VERSION}")

project(meshgen CXX)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/meshgen_config.hpp.in"
  "${PROJECT_SOURCE_DIR}/include/meshgen_config.hpp"
  )

enable_testing()

option(BUILD_TESTS "Set to ON to build tests" OFF)

# request c++14 without gnu extension for the whole project and enable more warnings
if (CXXOPTS_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${CXXOPTS_CXX_STANDARD})
else()
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wshadow")
endif()

# Install version file
install(FILES ${PROJECT_SOURCE_DIR}/include/meshgen_config.hpp DESTINATION include)

# Install the header file
install(FILES ${PROJECT_SOURCE_DIR}/include/meshgrid.hpp DESTINATION include)


add_subdirectory(test)
