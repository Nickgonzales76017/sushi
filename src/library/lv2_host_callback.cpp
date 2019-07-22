#include "twine/twine.h"

#include "lv2_host_callback.h"
#include "lv2_wrapper.h"
#include "logging.h"

namespace sushi {
namespace lv2 {

MIND_GET_LOGGER_WITH_MODULE_NAME("lv2");

// Disable unused variable warnings as the host callback just print debug info atm
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
VstIntPtr LVC2ALLBACK host_callback(AEffect* effect,
                                    VstInt32 opcode, VstInt32 index,
                                    VstIntPtr value, void* ptr, float opt)
{
    VstIntPtr result = 0;

    MIND_LOG_DEBUG("PLUG> HostCallback (opcode {})\n index = {}, value = {}, ptr = {}, opt = {}\n", opcode, index, FromVstPtr<void> (value), ptr, opt);

    switch (opcode)
    {
    case audioMasterAutomate:
    {
        auto wrapper_instance = reinterpret_cast<Lv2Wrapper*>(effect->user);
        if (twine::is_current_thread_realtime())
        {
            wrapper_instance->notify_parameter_change_rt(index, opt);
        }
        else
        {
            wrapper_instance->notify_parameter_change(index, opt);
            MIND_LOG_DEBUG("Plugin {} sending parameter change notification: param: {}, value: {}",
                           wrapper_instance->name(), index, opt);
        }

        break;
    }
    case audioMasterVersion :
        result = kVstVersion;
        break;

    case  audioMasterGetTime:
    {
        // Pass a pointer to a VstTimeInfo populated with updated data to the plugin
        auto wrapper_instance = reinterpret_cast<Lv2Wrapper*>(effect->user);
        result = reinterpret_cast<VstIntPtr>(wrapper_instance->time_info());
    }
    default:
        break;
    }

    return result;

}
*/

#pragma GCC diagnostic pop

} // namespace lv2
} // namespace sushi