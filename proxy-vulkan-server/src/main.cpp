/*
 * Copyright 2020 feserr. All rights reserved.
 * License: https://github.com/feserr/proxy-vulkan#license
 */

#include <angelia/server.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <hephaestus/log.h>
#include <proxy-protos/protos/function.capnp.h>
#include <proxy-protos/protos/instance.capnp.h>
#include <proxy-protos/protos/result.capnp.h>
#include <proxy-vulkan/proto_utils.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#include <memory>

int main() {
  // Open the server.
  int socket = -1;
  if (AngeliaServer(7000, &socket)) {
    Log(error, "Failed to create Angelia server.\n");
  }

  // Set input and output stream.
  InputStream input_stream(socket);
  OutputStream out_stream(socket);

  // Set input stream reader.
  capnp::InputStreamMessageReader message(input_stream);

  while (1) {
    auto proxy_function = message.getRoot<ProxyFunction>();
    auto function = proxy_function.getFunction();

    if (function == VkType::PROXY_END) {
      break;
    } else if (function ==
               VkType::PROXY_VK_ENUMERATE_INSTANCE_LAYER_PROPERTIES) {
      VkResult result;
      uint32_t instance_layer_count;
      VkLayerProperties* properties;

      if (proxy_function.getRetrieve()) {
        // Get the number of layer properties.
        capnp::InputStreamMessageReader data_message(input_stream);
        instance_layer_count = message.getRoot<ProxyUInt32>().getNum();
        properties = new VkLayerProperties[instance_layer_count];

        result = vkEnumerateInstanceLayerProperties(&instance_layer_count,
                                                    properties);
      } else {
        result = vkEnumerateInstanceLayerProperties(&instance_layer_count,
                                                    VK_NULL_HANDLE);
      }

      // Send the function result.
      ::capnp::MallocMessageBuilder message_builder;
      ProxyResult::Builder result_proto =
          message_builder.initRoot<ProxyResult>();
      result_proto.setResult(result);
      capnp::writeMessage(out_stream, message_builder);

      // Send the number of layer properties.
      ProxyUInt32::Builder layers_proto =
          message_builder.initRoot<ProxyUInt32>();
      layers_proto.setNum(instance_layer_count);
      capnp::writeMessage(out_stream, message_builder);

      if (proxy_function.getRetrieve()) {
        // Prepare the layer properties to be send.
        uint32_t size = sizeof(VkLayerProperties) * instance_layer_count;
        std::unique_ptr<kj::byte> test_buffer =
            std::make_unique<kj::byte>(size);
        memcpy(test_buffer.get(), properties, size);

        // Send the layer properties.
        ProxyLayerProperties::Builder layer_properties =
            message_builder.initRoot<ProxyLayerProperties>();
        layer_properties.setLayerProperties(
            kj::arrayPtr(test_buffer.get(), size));
        capnp::writeMessage(out_stream, message_builder);
      }
    }
  }

  // Close the server.
  if (AngeliaServerClose(&socket)) {
    Log(error, "Failed to close Angelia server.\n");
  }

  return 0;
}
