set(NAME vulkan)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 2)
set(PATCH_VERSION 135)
set(VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Proxy Vulkan library")

set(SOURCE_FILES
  src/lib_main.c
  src/instance.c)

set(HEADER_PATHS include)
set(HEADER_FILES
  include/proxy-vulkan/globals.h
  include/proxy-vulkan/proxy_headers.h
  include/proxy-vulkan/proxy_functions.h
  include/proxy-vulkan/proxy_results.h
  include/proxy-vulkan/lib_main.h
  include/proxy-vulkan/instance.h)

include_directories(
  ${HEADER_PATHS}
  ${hephaestus_SOURCE_DIR}/include
  ${angelia_SOURCE_DIR}/include
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
  PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

target_link_libraries(${NAME}
  hephaestus::hephaestus
  angelia::angelia)