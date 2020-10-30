cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
cmake_policy(VERSION 3.10.2)
# cmake_policy(SET CMP0046 OLD)
cmake_policy(SET CMP0057 NEW)

set (REPO_VERSION 0.2.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

set(NAME proxy_vulkan_samples)

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Samples of Proxy Vulkan")

include(CustomLinkLibraries)

include_directories(external)
if(WIN32)

elseif(APPLE)
  include_directories(/usr/local/include/)
  add_compile_definitions(APPLE)
endif()

# Use FindVulkan module added with CMAKE 3.7
find_package(Vulkan REQUIRED FATAL_ERROR)

include_directories(${Vulkan_INCLUDE_DIRS})

find_program(GLSLANG_VALIDATOR NAMES glslangValidator)
if(NOT GLSLANG_VALIDATOR)
  message(FATAL_ERROR "glslangValidator not found!")
else()
  message(STATUS ${GLSLANG_VALIDATOR})
endif()

# Set preprocessor defines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")

# Clang specific stuff
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")
endif()

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wundef")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

# Set the debug or relese mode.
if (CMAKE_BUILD_TYPE MATCHES Debug)
  # Debug level
  add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
  # Optimization level
else ()
  message(FATAL_ERROR "Set the build type with -DCMAKE_BUILD_TYPE=<type>")
endif()

file(GLOB SOURCE *.cpp)

function(link_assets EXAMPLE_NAME)
  if(NOT ARGN)
    return()
  endif()
  # message("ASSETS: ${ARGN}")
  foreach(ASSET ${ARGN})
    set(input_file ${CMAKE_SOURCE_DIR}/data/${ASSET})
    get_filename_component(ASSET_DIR ${ASSET} DIRECTORY)
    get_filename_component(ASSET_NAME ${ASSET} NAME)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/${ASSET})
    # Must do this in two steps to propagate value
    set(all_assets ${all_assets} ${output_file})
    set(all_assets ${all_assets} PARENT_SCOPE)
    # message("Generating: ${input_file} -> ${output_file}")
    add_custom_command(OUTPUT ${output_file} # POST_BUILD
                       COMMAND mkdir -p ${ASSET_DIR}
                               # COMMAND cp ${input_file} ${output_file} DEPENDS
                               # ${input_file}
                       COMMAND ln -s ${input_file} -r -f ${ASSET}
                       DEPENDS ${input_file}
                       COMMENT "Linking ${output_file} to asset ${ASSET}")
  endforeach()
  add_custom_target(linkassets-${EXAMPLE_NAME} ALL DEPENDS ${all_assets})
  add_dependencies(${EXAMPLE_NAME} linkassets-${EXAMPLE_NAME})
  # add_dependencies(${EXAMPLE_NAME} ${all_assets})
endfunction()

function(compile_shaders EXAMPLE_NAME)
  if(NOT ARGN)
    return()
  endif()
  foreach(SHADER ${ARGN})
    get_filename_component(FILE_NAME ${SHADER} NAME)
    set(output_file ${CMAKE_CURRENT_BINARY_DIR}/shaders/${FILE_NAME}.spv)
    set(compiled_shaders ${compiled_shaders} ${output_file})
    set(compiled_shaders ${compiled_shaders} PARENT_SCOPE)
    add_custom_command(OUTPUT ${output_file}
                       COMMAND mkdir -p shaders
                       COMMAND ${GLSLANG_VALIDATOR} -w -V
                               ${CMAKE_SOURCE_DIR}/${SHADER} -o ${output_file}
                       DEPENDS ${CMAKE_SOURCE_DIR}/${SHADER}
                       COMMENT "Compiling shader ${output_file}")
  endforeach()
  add_custom_target(shaders-${EXAMPLE_NAME} ALL DEPENDS ${compiled_shaders})
  add_dependencies(${EXAMPLE_NAME} shaders-${EXAMPLE_NAME})
endfunction()

add_custom_target(run-all)

function(Prepend var prefix)
  # message(STATUS "Prepend(${var}, ${prefix})")
  set(listVar "")
  foreach(f ${ARGN})
    list(APPEND listVar "${prefix}/${f}")
  endforeach(f)
  set(${var} "${listVar}" PARENT_SCOPE)
endfunction()

# Function for building single example
function(buildExample EXAMPLE_NAME)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath='$ORIGIN'")

  list(REMOVE_AT ARGV 0)
  cmake_parse_arguments(ARGS "" "" "ASSETS;SHADERS" ${ARGN})
  string(REPLACE "${CMAKE_SOURCE_DIR}/"
                 ""
                 src_dir
                 "${CMAKE_CURRENT_SOURCE_DIR}")
  prepend(ARGS_SHADERS "${src_dir}" "${ARGS_SHADERS}")
  # message("SHADERS: ${ARGS_SHADERS}")

  if(WIN32)
    add_executable(${EXAMPLE_NAME} WIN32 ${ARGS_UNPARSED_ARGUMENTS}
                   # ${ARGS_ASSETS}
                   # ${ARGS_SHADERS}
                   )
    target_link_libraries(${EXAMPLE_NAME}
                          ${Vulkan_LIBRARY}
                          ${WINLIBS})
  else()
    add_executable(${EXAMPLE_NAME} ${ARGS_UNPARSED_ARGUMENTS}
                   # ${ARGS_ASSETS}
                   # ${ARGS_SHADERS}
                   )
    target_link_libraries(${EXAMPLE_NAME}
                          ${Vulkan_LIBRARY} # VkLayer_api_dump
                          )
  endif()

  # Set the debug or relese mode.
  if (CMAKE_BUILD_TYPE MATCHES Debug)
    # Debug level
    add_definitions(-DDEBUG)
  elseif (CMAKE_BUILD_TYPE MATCHES Release)
    # Optimization level
  else ()
    message(FATAL_ERROR "Set the build type with -DCMAKE_BUILD_TYPE=<type>")
  endif()

  # Gather SHADERS and ASSETS from upstream dependencies
  get_link_dependencies(${EXAMPLE_NAME} deps)
  if(deps)
    foreach(dep IN LISTS deps)
      get_target_property(s ${dep} SHADERS)
      if(s)
        # Note the adjusted path
        get_target_property(src_dir ${dep} SOURCE_DIR)
        string(REPLACE "${CMAKE_SOURCE_DIR}/"
                       ""
                       src_dir
                       "${src_dir}")
        prepend(s "${src_dir}" "${s}")
        list(APPEND ARGS_SHADERS ${s})
      endif()
      get_target_property(a ${dep} ASSETS)
      if(a)
        list(APPEND ARGS_ASSETS ${a})
      endif()
    endforeach()
  endif()

  link_assets(${EXAMPLE_NAME} ${ARGS_ASSETS})
  compile_shaders(${EXAMPLE_NAME} ${ARGS_SHADERS})

  add_custom_target(run-${EXAMPLE_NAME}
                    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXAMPLE_NAME}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXAMPLE_NAME})
  add_dependencies(run-all run-${EXAMPLE_NAME})

endfunction()

# Build all examples
function(buildExamples)
  foreach(EXAMPLE ${EXAMPLES})
    buildexample(${EXAMPLE})
  endforeach(EXAMPLE)
endfunction(buildExamples)

# Compiler specific stuff
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif(MSVC)

if(WIN32)
  # Nothing here (yet)
else(WIN32)
  link_libraries(${XCB_LIBRARIES} Vulkan::Vulkan)
endif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

add_subdirectory(external/angelia)
add_subdirectory(proxy-protos)
add_subdirectory(proxy-vulkan)
add_subdirectory(proxy-vulkan-server)
add_subdirectory(samples)
