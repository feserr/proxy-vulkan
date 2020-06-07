/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#ifndef PROXY_VULKAN_PROXY_RESULTS_H_
#define PROXY_VULKAN_PROXY_RESULTS_H_

#include <inttypes.h>

#include "proxy-vulkan/proxy_headers.h"

struct ProxyResult {
  VkResult result;
  uint32_t data_size;
};

struct ProxyUInt32 {
  uint32_t num;
};

#endif  // PROXY_VULKAN_PROXY_RESULTS_H_
