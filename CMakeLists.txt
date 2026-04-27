cmake_minimum_required(VERSION 3.23)

set(version 0.1.0)

option(CAMELLIA_REGISTER_PACKAGE
       "Register camellia in the CMake user package registry." OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  camellia
  VERSION ${version}
  LANGUAGES C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(camellia)

target_sources(
  camellia
  PRIVATE src/camellia/camellia.c src/camellia/test/test.c
          src/camellia/err/err.c src/camellia/type/dynamic_array.c
  PUBLIC FILE_SET
         HEADERS
         BASE_DIRS
         include
         FILES
         include/camellia/type/dynamic_array.h
         include/camellia/type/int.h
         include/camellia/err/err.h
         include/camellia/err/err_codes.inc
         include/camellia/test/test.h
         include/camellia/camellia.h)

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

# Package version file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/camelliaConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion)

# Installing
install(
  TARGETS camellia
  EXPORT camelliaTargets
  FILE_SET HEADERS
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/camelliaConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/camelliaConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/camellia)

install(
  EXPORT camelliaTargets
  FILE camelliaTargets.cmake
  NAMESPACE camellia::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/camellia)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/camelliaConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/camelliaConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/camellia)

# Export if(CAMELLIA_REGISTER_PACKAGE) export( EXPORT camelliaTargets NAMESPACE
# camellia:: FILE "${CMAKE_CURRENT_BINARY_DIR}/camelliaTargets.cmake")
# export(PACKAGE camellia) endif()

# Testing
enable_testing()

add_subdirectory(tests)
