/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include "proxy-vulkan/lib_main.h"

#include <angelia/client.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <hephaestus/log.h>
#include <proxy-protos/protos/function.capnp.h>
#include <stdlib.h>

#include "proxy-vulkan/globals.h"
#include "proxy-vulkan/proto_utils.h"

int socket_desc;

void ConstructorLib() {
  Log(info, "Constructor\n");

  if (AngeliaClient("127.0.0.1", 7000, &socket_desc)) {
    Log(error, "Failed to create Angelia client.");
  }
}

void DestructorLib() {
  Log(info, "Destructor\n");

  OutputStream out(socket_desc);
  ::capnp::MallocMessageBuilder message_builder;
  ProxyFunction::Builder function_end =
      message_builder.initRoot<ProxyFunction>();
  function_end.setFunction(VkType::PROXY_END);
  capnp::writeMessage(out, message_builder);

  if (AngeliaClientClose(&socket_desc)) {
    Log(error, "Failed to close Angelia client.");
  }
}
