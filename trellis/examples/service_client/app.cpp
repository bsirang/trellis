#include "app.hpp"

namespace trellis {
namespace examples {
namespace service_client {

using namespace trellis::core;
using namespace trellis::examples::proto;

App::App(const Node& node, const Config& config)
    : client_{node.CreateServiceClient<AdditionService>()},
      timer_{node.CreateTimer(config["examples"]["service"]["interval_ms"].as<unsigned>(), [this]() { Tick(); })} {}

void App::HandleResponse(const AdditionResponse* resp) {
  if (!resp) {
    Log::Error("Request failed!");
    return;
  }

  Log::Info("Received response {}", resp->sum());
}

void App::Tick() {
  ++request_count_;

  AdditionRequest req;
  unsigned arg1 = request_count_ * 2;
  unsigned arg2 = request_count_ * 3;

  req.set_arg1(arg1);
  req.set_arg2(arg2);

  Log::Info("Sending request for {} + {}", arg1, arg2);
  arg1 += 2;
  arg2 += 3;
  client_->CallAsync<AdditionRequest, AdditionResponse>("Add", req,
                                                        [this](const AdditionResponse* resp) { HandleResponse(resp); });
}

}  // namespace service_client
}  // namespace examples
}  // namespace trellis
