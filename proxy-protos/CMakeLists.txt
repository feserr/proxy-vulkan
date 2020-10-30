cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(NAME proxy_protos)

project(${NAME} VERSION ${REPO_VERSION} DESCRIPTION "Proxy Vulkan Protobuffers")

find_package(CapnProto CONFIG REQUIRED)

include_directories(${CAPNP_INCLUDE_DIRS})

capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS
  protos/result.capnp
  protos/function.capnp
  protos/instance.capnp)

add_library(${NAME} ${CAPNP_HDRS} ${CAPNP_SRCS})
add_library(proxyvulkan::protos ALIAS ${NAME})