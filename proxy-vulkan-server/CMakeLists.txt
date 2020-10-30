cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(NAME proxy-vulkan-server)

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Proxy Vulkan library")

find_package(CapnProto CONFIG REQUIRED)

set(SOURCE_FILES
  src/main.cpp)

set(HEADER_PATH
  include)

include_directories(
  ${HEADER_PATH}
  ${hephaestus_SOURCE_DIR}/include
  ${angelia_SOURCE_DIR}/include
  ${CAPNP_INCLUDE_DIRS}
  ${vulkan_SOURCE_DIR}/include
  ${Vulkan_INCLUDE_DIRS})

if(WIN32)
  add_executable(${NAME} WIN32
    ${SOURCE_FILES}
    # ${ARGS_ASSETS}
    # ${ARGS_SHADERS}
  )
  target_link_libraries(${NAME}
    hephaestus::hephaestus
    angelia::angelia
    proxyvulkan::protos
    CapnProto::capnp
    Vulkan::Vulkan
    ${WINLIBS})
else()
  add_executable(${NAME}
    ${SOURCE_FILES}
    # ${ARGS_ASSETS}
    # ${ARGS_SHADERS}
  )
  target_link_libraries(${NAME}
    hephaestus::hephaestus
    angelia::angelia
    proxyvulkan::protos
    CapnProto::capnp
    Vulkan::Vulkan)
endif()

target_include_directories(${NAME}
  PUBLIC
    ${CMAKE_BINARY_DIR}
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR})
