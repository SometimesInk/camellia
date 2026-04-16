cmake_minimum_required(VERSION 3.23)

project(
  camellia
  VERSION 0.0.0
  LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(camellia)

target_sources(
  camellia
  PRIVATE src/camellia/camellia.c
  PUBLIC FILE_SET HEADERS BASE_DIRS include FILES include/camellia/camellia.h)

target_include_directories(
  camellia
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(camellia PUBLIC c_std_11)

add_library(camellia::camellia ALIAS camellia)

# Docs with Doxygen
option(BUILD_DOCUMENTATION "Build API documentation with Doxygen" OFF)

if(BUILD_DOCUMENTATION)
  find_package(Doxygen)

  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is required to build documentation")
  endif()

  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  set(DOXYGEN_CONFIG_FILE ${DOXYGEN_OUT})

  doxygen_add_docs(
    docs ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src
    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()

# Testing
enable_testing()

add_subdirectory(tests)
