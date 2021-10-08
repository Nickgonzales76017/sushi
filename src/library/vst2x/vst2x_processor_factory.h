/*
 * Copyright 2017-2021 Modern Ancient Instruments Networked AB, dba Elk
 *
 * SUSHI is free software: you can redistribute it and/or modify it under the terms of
 * the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * SUSHI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with
 * SUSHI. If not, see http://www.gnu.org/licenses/
 */

/**
 * @brief Factory for VST2 processors.
 */

#ifndef SUSHI_VST2X_PROCESSOR_FACTORY_H
#define SUSHI_VST2X_PROCESSOR_FACTORY_H

#include "library/base_processor_factory.h"
#include "library/vst2x/vst2x_wrapper.h"

#ifdef SUSHI_BUILD_WITH_VST2

namespace sushi {

class Vst2xProcessorFactory : public BaseProcessorFactory
{
public:
    Vst2xProcessorFactory() = default;

    std::pair<ProcessorReturnCode, std::shared_ptr<Processor>> new_instance(const sushi::engine::PluginInfo &plugin_info,
                                                                            HostControl& host_control,
                                                                            float sample_rate) override
    {
        auto processor = std::make_shared<vst2::Vst2xWrapper>(host_control, plugin_info.path);
        auto processor_status = processor->init(sample_rate);
        return {processor_status, processor};
    }
};

} // end namespace sushi

#endif //SUSHI_BUILD_WITH_VST2
#ifndef SUSHI_BUILD_WITH_VST2

namespace sushi {

    class Vst2xProcessorFactory : public BaseProcessorFactory
    {
    public:
        Vst2xProcessorFactory() = default;

        std::pair<ProcessorReturnCode, std::shared_ptr<Processor>> new_instance(const sushi::engine::PluginInfo&,
                                                                                HostControl&,
                                                                                float) override
        {
            return {ProcessorReturnCode::UNSUPPORTED_OPERATION, nullptr};
        }
    };

} // end namespace sushi

#endif

#endif //SUSHI_VST2X_PROCESSOR_FACTORY_H