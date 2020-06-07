/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#ifndef PROXY_VULKAN_LIB_MAIN_H_
#define PROXY_VULKAN_LIB_MAIN_H_

void ConstructorLib() __attribute__((constructor()));

void DestructorLib() __attribute__((destructor()));

#endif  // PROXY_VULKAN_LIB_MAIN_H_
