/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#ifndef PROXY_VULKAN_PROTO_UTILS_H_
#define PROXY_VULKAN_PROTO_UTILS_H_

#include <capnp/serialize-packed.h>

#ifdef _WIN32
typedef kj::HandleInputStream InputStream;
typedef kj::HandleOutputStream OutputStream;
#else
typedef kj::FdInputStream InputStream;
typedef kj::FdOutputStream OutputStream;
#endif

#endif  // PROXY_VULKAN_PROTO_UTILS_H_
