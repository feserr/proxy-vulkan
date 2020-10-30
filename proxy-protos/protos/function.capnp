# Copyright 2020 feserr. All rights reserved.
# License: https://github.com/feserr/proxy-vulkan#license

@0xd838357daca11376;

enum VkType {
  proxyEnd @0;
  proxyVkEnumerateInstanceLayerProperties @1;
}

struct ProxyFunction {
  function @0 : VkType;
  retrieve @1 : Bool;
}