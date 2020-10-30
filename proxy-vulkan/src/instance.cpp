/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include "proxy-vulkan/instance.h"

#include <angelia/client.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <hephaestus/log.h>
#include <kj/io.h>
#include <proxy-protos/protos/function.capnp.h>
#include <proxy-protos/protos/instance.capnp.h>
#include <proxy-protos/protos/result.capnp.h>
#include <stdlib.h>

#include <algorithm>

#include "proxy-vulkan/globals.h"
#include "proxy-vulkan/proto_utils.h"

VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount,
                                            VkLayerProperties* pProperties) {
  Log(info, "vkEnumerateInstanceLayerProperties start\n");

  // Set the output stream.
  OutputStream output_out(socket_desc);

  // Send which function we are going to use.
  ::capnp::MallocMessageBuilder message_builder;
  ProxyFunction::Builder function = message_builder.initRoot<ProxyFunction>();
  function.setFunction(VkType::PROXY_VK_ENUMERATE_INSTANCE_LAYER_PROPERTIES);
  function.setRetrieve(pProperties != VK_NULL_HANDLE);
  capnp::writeMessage(output_out, message_builder);

  // If it want to retrieve the layer properties.
  if (pProperties) {
    ProxyUInt32::Builder properties = message_builder.initRoot<ProxyUInt32>();
    properties.setNum(*pPropertyCount);
    capnp::writeMessage(output_out, message_builder);
  }

  // Set the input stream.
  InputStream input_stream(socket_desc);

  // Get the result of the function.
  capnp::InputStreamMessageReader input_result(input_stream);
  auto result = input_result.getRoot<ProxyResult>();

  // Get the data of the function.
  capnp::InputStreamMessageReader input_data(input_stream);
  auto res_data = input_data.getRoot<ProxyUInt32>();

  // Get the properties if needed.
  if (pProperties) {
    capnp::InputStreamMessageReader input_properties(input_stream);
    auto res_properties = input_properties.getRoot<ProxyLayerProperties>();
    memcpy(pProperties, res_properties.getLayerProperties().begin(),
           res_properties.getLayerProperties().size());
  }

  // Set the out param variable.
  *pPropertyCount = res_data.getNum();

  return static_cast<VkResult>(result.getResult());
}
