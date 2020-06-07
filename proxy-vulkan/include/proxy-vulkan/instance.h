/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#ifndef PROXY_VULKAN_INSTANCE_H_
#define PROXY_VULKAN_INSTANCE_H_

#include <vulkan/vulkan.h>

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(
    uint32_t* pPropertyCount, VkLayerProperties* pProperties);

#endif  // PROXY_VULKAN_INSTANCE_H_
