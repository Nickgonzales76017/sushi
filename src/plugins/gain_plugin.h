/**
 * @brief Gain plugin example
 * @copyright MIND Music Labs AB, Stockholm
 */
#ifndef GAIN_PLUGIN_H
#define GAIN_PLUGIN_H

#include "library/internal_plugin.h"

namespace sushi {
namespace gain_plugin {

static const std::string DEFAULT_NAME = "sushi.testing.gain";
static const std::string DEFAULT_LABEL = "Gain";

class GainPlugin : public InternalPlugin
{
public:
    GainPlugin();

    ~GainPlugin();

    void process_audio(const ChunkSampleBuffer &in_buffer, ChunkSampleBuffer &out_buffer) override;

private:
    FloatParameterValue* _gain_parameter;
};

}// namespace gain_plugin
}// namespace sushi
#endif // GAIN_PLUGIN_H