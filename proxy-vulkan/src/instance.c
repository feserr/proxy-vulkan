/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include "proxy-vulkan/instance.h"

#include <angelia/client.h>
#include <hephaestus/log.h>
#include <stdlib.h>

#include "proxy-vulkan/globals.h"
#include "proxy-vulkan/proxy_functions.h"
#include "proxy-vulkan/proxy_headers.h"
#include "proxy-vulkan/proxy_results.h"

VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount,
                                            VkLayerProperties* pProperties) {
  Log(info, "vkEnumerateInstanceLayerProperties start\n");

  uint32_t size = sizeof(struct ProxyFunction);
  void* buffer = malloc(size);
  struct ProxyFunction function = {proxy_vkEnumerateInstanceLayerProperties, 0};
  if (pProperties) {
    function.data_size = 1;
  }
  memcpy(buffer, &function, size);

  if (AngeliaSend(socket_desc, buffer, size) <= 0) {
    Log(error, "Failed to send data.\n");
  }
  free(buffer);

  if (pProperties) {
    struct ProxyUInt32 data = {*pPropertyCount};
    size = sizeof(data);
    buffer = malloc(size);
    memcpy(buffer, &data, size);
    if (AngeliaSend(socket_desc, buffer, size) <= 0) {
      Log(error, "Failed to send data.\n");
    }
    free(buffer);
  }

  struct ProxyResult result = {};
  size = sizeof(result);
  buffer = malloc(size);
  if (AngeliaRecv(socket_desc, size, &buffer) <= 0) {
    Log(error, "Failed to receive the result.\n");
  }
  memcpy(&result, buffer, size);
  free(buffer);

  struct ProxyUInt32 res_data = {};
  size = sizeof(res_data);
  buffer = malloc(size);
  if (AngeliaRecv(socket_desc, size, &buffer) <= 0) {
    Log(error, "Failed to receive the data.\n");
  }
  memcpy(&res_data, buffer, size);
  free(buffer);

  if (pProperties) {
    size = sizeof(VkLayerProperties) * res_data.num;
    buffer = malloc(size);
    if (AngeliaRecv(socket_desc, size, &buffer) <= 0) {
      Log(error, "Failed to receive the properties.\n");
    }
    memcpy(pProperties, buffer, size);
    free(buffer);
  }

  *pPropertyCount = res_data.num;

  return result.result;
}
