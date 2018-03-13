# 3.1 required for CMAKE_CXX_STANDARD
cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
include(CheckCXXCompilerFlag)

project (free.simd CXX)
add_library(free.simd INTERFACE)

# Set free.simd version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# Get the current working git branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE PAW_GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated SHA commit hash of the working git branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_SHORT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest SHA commit hash of the working git branch
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_LONG_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest SHA commit hash of the working git branch
execute_process(
  COMMAND git diff-files COMMAND wc -l
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_NUM_DIRTY_FILES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)


# Pass information of paw to the source
configure_file(${PROJECT_SOURCE_DIR}/include/boost/simd/detail/internal/_config.hpp
               ${PROJECT_BINARY_DIR}/include/boost/simd/detail/internal/config.hpp
               @ONLY)

## Set to release by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RELEASE" CACHE STRING "Choose the type of build." FORCE)
endif()

message(STATUS "CMAKE_BUILD_TYPE is set to ${CMAKE_BUILD_TYPE}")

# Find Boost
find_package(Boost 1.61.0 REQUIRED)

message(STATUS "Including boost directory: ${Boost_INCLUDE_DIRS}")

target_include_directories(free.simd INTERFACE
    ${Boost_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}/include # config only
    ${PROJECT_SOURCE_DIR}/include # entire library
    )

# Check which compiler flags are supported
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

# Use highest CXX compiler flag available
#if (COMPILER_SUPPORTS_CXX17)
  ## Compilation fails on GCC 7.3 with c++17.
  #set (CMAKE_CXX_STANDARD 17)
if (COMPILER_SUPPORTS_CXX14)
  set (CMAKE_CXX_STANDARD 14)
elseif (COMPILER_SUPPORTS_CXX11)
  set (CMAKE_CXX_STANDARD 11)
else()
  message(FATAL_ERROR "Your compiler version does not seem to support C++11. Aborting.")
endif()

## Setup other compiler flags
set(CMAKE_CXX_FLAGS_COMMON "${CMAKE_CXX_FLAGS_COMMON} -Wall -Wfatal-errors")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_COMMON} -O0 -Wextra -pedantic -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS_COMMON}")

## Build libraries in /lib and binaries in /bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Documentation
## Adds a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${doxyfile_in} ${doxyfile} @ONLY)

  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

  #install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()

## Install
install(DIRECTORY include/ DESTINATION include PATTERN include/boost/simd/detail/internal EXCLUDE)
install(DIRECTORY ${CMAKE_BINARY_DIR}/include/boost/simd/detail/internal/ DESTINATION include/paw/internal)

## Testing
enable_testing()
add_subdirectory(test)