set(NAME proxy-vulkan-server)

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Proxy Vulkan library")

set(SOURCE_FILES
  src/main.c)

set(HEADER_PATH
  include)

include_directories(
  ${HEADER_PATH}
  ${hephaestus_SOURCE_DIR}/include
  ${angelia_SOURCE_DIR}/include
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
      Vulkan::Vulkan)
  endif()