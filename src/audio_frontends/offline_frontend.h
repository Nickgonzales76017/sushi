/**
 * @brief Offline frontend to process audio files in chunks
 *
 */

#ifndef SUSHI_OFFLINE_FRONTEND_H
#define SUSHI_OFFLINE_FRONTEND_H

#include "base_audio_frontend.h"

#include <string>

#include <sndfile.h>

namespace sushi {

namespace audio_frontend {


struct OfflineFrontendConfiguration : public BaseAudioFrontendConfiguration
{

    OfflineFrontendConfiguration(const unsigned int sample_rate,
                                 const std::string input_filename,
                                 const std::string output_filename) :
            BaseAudioFrontendConfiguration(sample_rate),
            _input_filename(input_filename),
            _output_filename(output_filename)
    {}

    virtual ~OfflineFrontendConfiguration()
    {}

    std::string _input_filename;
    std::string _output_filename;
};

class OfflineFrontend : public BaseAudioFrontend
{
public:
    OfflineFrontend()
    {}

    virtual ~OfflineFrontend();

    AudioFrontendInitStatus init(const BaseAudioFrontendConfiguration* config) override;

    void cleanup() override;

    void run() override;

private:
    SNDFILE*    _input_file;
    SNDFILE*    _output_file;
    SF_INFO     _soundfile_info;

    sushi_engine::SushiBuffer _buffer(AUDIO_CHUNK_SIZE);
    float*  _file_buffer;
};

}; // end namespace audio_frontend

}; // end namespace sushi

#endif //SUSHI_OFFLINE_FRONTEND_H
