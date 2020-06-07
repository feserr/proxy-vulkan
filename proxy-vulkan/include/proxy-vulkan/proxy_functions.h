/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#ifndef PROXY_VULKAN_PROXY_FUNCTIONS_H_
#define PROXY_VULKAN_PROXY_FUNCTIONS_H_

#include <inttypes.h>
#include <vulkan/vulkan.h>

#include "proxy-vulkan/proxy_headers.h"

struct ProxyFunction {
  enum VulkanFunctions vk_function;
  uint32_t data_size;
};

struct ProxyLayerProperties {
  VkLayerProperties layer_properties;
};

#endif  // PROXY_VULKAN_PROXY_FUNCTIONS_H_
