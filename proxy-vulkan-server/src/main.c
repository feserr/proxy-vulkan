/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include <angelia/server.h>
#include <hephaestus/log.h>
#include <proxy-vulkan/proxy_functions.h>
#include <proxy-vulkan/proxy_headers.h>
#include <proxy-vulkan/proxy_results.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

int main() {
  int socket = -1;
  if (AngeliaServer(7000, &socket)) {
    Log(error, "Failed to create Angelia server.\n");
  }

  while (1) {
    uint32_t size = sizeof(struct ProxyFunction);
    void* buffer = malloc(size);
    if (AngeliaRecv(socket, size, &buffer) <= 0) {
      Log(error, "Failed to receive data.\n");
    }
    struct ProxyFunction function = {};
    memcpy(&function, buffer, size);
    free(buffer);

    if (function.vk_function == proxy_end) {
      break;
    } else if (function.vk_function ==
               proxy_vkEnumerateInstanceLayerProperties) {
      VkResult result;
      uint32_t instance_layer_count;
      VkLayerProperties* properties;

      if (function.data_size == 0) {
        result = vkEnumerateInstanceLayerProperties(&instance_layer_count,
                                                    VK_NULL_HANDLE);
      } else {
        size = sizeof(struct ProxyUInt32);
        buffer = malloc(size);
        if (AngeliaRecv(socket, size, &buffer) <= 0) {
          Log(error, "Failed to receive data.\n");
        }
        struct ProxyUInt32 data = {};
        memcpy(&data, buffer, size);
        free(buffer);

        instance_layer_count = data.num;
        properties = malloc(sizeof(VkLayerProperties) * instance_layer_count);
        result = vkEnumerateInstanceLayerProperties(&instance_layer_count,
                                                    properties);
      }

      struct ProxyUInt32 res_data = {instance_layer_count};
      struct ProxyResult res = {result, sizeof(res_data)};

      size = sizeof(res);
      buffer = malloc(size);
      memcpy(buffer, &res, size);
      if (AngeliaSend(socket, buffer, size) <= 0) {
        Log(error, "Failed to send the result.\n");
      }
      free(buffer);

      size = res.data_size;
      buffer = malloc(size);
      memcpy(buffer, &res_data, size);
      if (AngeliaSend(socket, buffer, size) <= 0) {
        Log(error, "Failed to send the result.\n");
      }
      free(buffer);

      if (function.data_size == 1) {
        size = sizeof(VkLayerProperties) * instance_layer_count;
        buffer = malloc(size);
        memcpy(buffer, properties, size);
        if (AngeliaSend(socket, buffer, size) <= 0) {
          Log(error, "Failed to send the properties.\n");
        }
        free(buffer);
      }
    }
  }

  if (AngeliaServerClose(&socket)) {
    Log(error, "Failed to close Angelia server.\n");
  }

  return 0;
}