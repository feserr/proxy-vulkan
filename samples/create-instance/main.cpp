/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include <vulkan/vulkan.h>

#include <iostream>
#include <memory>

int main(int argc, const char* argv[]) {
  uint32_t instance_layer_count;
  if (vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr) !=
      VK_SUCCESS) {
    std::cerr << "Failed to get the number of instance layers.\n";
    return 1;
  }

  std::cout << instance_layer_count << " layers found!\n";

  if (instance_layer_count > 0) {
    std::unique_ptr<VkLayerProperties[]> instance_layers(
        new VkLayerProperties[instance_layer_count]);
    if (vkEnumerateInstanceLayerProperties(
            &instance_layer_count, instance_layers.get()) != VK_SUCCESS) {
      std::cerr << "Failed to get the instance layers.\n";
      return 2;
    }
    for (uint32_t i = 0; i < instance_layer_count; ++i) {
      std::cout << instance_layers[i].layerName << "\n";
    }
  }

  return 0;
}
