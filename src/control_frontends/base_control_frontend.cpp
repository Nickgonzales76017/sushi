#include <thread>

#include "logging.h"

#include "control_frontends/base_control_frontend.h"

namespace sushi {
namespace control_frontend {

MIND_GET_LOGGER;

constexpr int STOP_RETRIES = 200;
constexpr auto RETRY_INTERVAL = std::chrono::milliseconds(2);

void BaseControlFrontend::send_parameter_change_event(ObjectId processor,
                                                      ObjectId parameter,
                                                      float value)
{
    _queue->push(RtEvent::make_parameter_change_event(processor, 0, parameter, value));
}

void BaseControlFrontend::send_string_parameter_change_event(ObjectId processor,
                                                             ObjectId parameter,
                                                             const std::string& value)
{
    auto str = new std::string(value);
    _queue->push(RtEvent::make_string_parameter_change_event(processor, 0, parameter, str));
}


void BaseControlFrontend::send_keyboard_event(ObjectId processor,
                                              RtEventType type,
                                              int note,
                                              float value)
{
    _queue->push(RtEvent::make_keyboard_event(type, processor, 0, note, value));
}

void BaseControlFrontend::add_chain(const std::string &name, int channels)
{
    auto status = _engine->create_plugin_chain(name, channels);
    if (status != engine::EngineReturnStatus::OK)
    {
        MIND_LOG_ERROR("Failed to create chain {}", name);
    }
}

void BaseControlFrontend::delete_chain(const std::string &name)
{
    auto status = _engine->delete_plugin_chain(name);
    if (status != engine::EngineReturnStatus::OK)
    {
        MIND_LOG_ERROR("Failed to delete chain {}", name);
    }
    MIND_LOG_ERROR("Succesfully deleted chain {}", name);
}

void BaseControlFrontend::add_processor(const std::string& chain, const std::string& uid, const std::string& name,
                                        const std::string& file, engine::PluginType type)
{
    auto status = _engine->add_plugin_to_chain(chain, uid, name, file, type);
    if (status != engine::EngineReturnStatus::OK)
    {
        MIND_LOG_ERROR("Failed to add plugin {} ({}) to {}", name, uid, chain);
    }
}

void BaseControlFrontend::delete_processor(const std::string& chain, const std::string& name)
{
    auto status = _engine->remove_plugin_from_chain(chain, name);
    if (status != engine::EngineReturnStatus::OK)
    {
        MIND_LOG_ERROR("Failed to delete processor {}", name);
    }
}

} // end namespace control_frontend
} // end namespace sushi