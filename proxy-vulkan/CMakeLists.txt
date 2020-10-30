cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(NAME vulkan)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 2)
set(PATCH_VERSION 135)
set(VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Proxy Vulkan library")

find_package(CapnProto CONFIG REQUIRED)

set(SOURCE_FILES
  src/lib_main.cpp
  src/instance.cpp)

set(HEADER_PATHS include)
set(HEADER_FILES
  include/proxy-vulkan/globals.h
  include/proxy-vulkan/proto_utils.h
  include/proxy-vulkan/lib_main.h
  include/proxy-vulkan/instance.h)

include_directories(
  ${HEADER_PATHS}
  ${hephaestus_SOURCE_DIR}/include
  ${angelia_SOURCE_DIR}/include
  ${CAPNP_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ../external/vulkan)

add_library(${NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

SET_TARGET_PROPERTIES(${NAME}
  PROPERTIES
  SOVERSION ${MAJOR_VERSION}
  VERSION ${VERSION}
)

include(GenerateExportHeader)
generate_export_header(${NAME})

target_include_directories(${NAME}
  PUBLIC
    ${CMAKE_BINARY_DIR}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})

target_link_libraries(${NAME}
  hephaestus::hephaestus
  angelia::angelia
  proxyvulkan::protos
  CapnProto::capnp)