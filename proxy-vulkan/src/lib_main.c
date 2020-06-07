/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include "proxy-vulkan/lib_main.h"

#include <angelia/client.h>
#include <hephaestus/log.h>
#include <stdlib.h>

#include "proxy-vulkan/globals.h"
#include "proxy-vulkan/proxy_functions.h"

void ConstructorLib() {
  Log(info, "Constructor\n");

  if (AngeliaClient("127.0.0.1", 7000, &socket_desc)) {
    Log(error, "Failed to create Angelia client.");
  }
}

void DestructorLib() {
  Log(info, "Destructor\n");

  uint32_t size = sizeof(struct ProxyFunction);
  void* buffer = malloc(size);
  struct ProxyFunction function = {proxy_end, 0};
  memcpy(buffer, &function, size);

  if (AngeliaSend(socket_desc, buffer, size) <= 0) {
    Log(error, "Failed to send data.\n");
  }
  free(buffer);

  if (AngeliaClientClose(&socket_desc)) {
    Log(error, "Failed to close Angelia client.");
  }
}
