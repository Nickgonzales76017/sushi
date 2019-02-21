#include <algorithm>

#include "plugins/transposer_plugin.h"
#include "library/midi_decoder.h"
#include "library/midi_encoder.h"
#include "logging.h"

namespace sushi {
namespace transposer_plugin {

MIND_GET_LOGGER_WITH_MODULE_NAME("transposer");

static const std::string DEFAULT_NAME = "sushi.testing.transposer";
static const std::string DEFAULT_LABEL = "Transposer";

constexpr int MAX_NOTE = 127;
constexpr int MIN_NOTE = 0;

TransposerPlugin::TransposerPlugin(HostControl host_control) : InternalPlugin(host_control)
{
    Processor::set_name(DEFAULT_NAME);
    Processor::set_label(DEFAULT_LABEL);
    _transpose_parameter = register_float_parameter("transpose", "Transpose", 0,-24, 24, new FloatParameterPreProcessor(-24, 24) );
    assert(_transpose_parameter);
    _max_input_channels = 0;
    _max_output_channels = 0;
}

ProcessorReturnCode TransposerPlugin::init(float /*sample_rate*/)
{
    return ProcessorReturnCode::OK;
}

void TransposerPlugin::process_event(RtEvent event)
{
    switch (event.type())
    {
        case RtEventType::NOTE_ON:
        {
            auto typed_event = event.keyboard_event();
            _queue.push(RtEvent::make_note_on_event(typed_event->processor_id(),
                                                    typed_event->sample_offset(),
                                                    typed_event->channel(),
                                                    _transpose_note(typed_event->note()),
                                                    typed_event->velocity()));
            break;
        }

        case RtEventType::NOTE_OFF:
        {
            auto typed_event = event.keyboard_event();
            _queue.push(RtEvent::make_note_off_event(typed_event->processor_id(),
                                                     typed_event->sample_offset(),
                                                     typed_event->channel(),
                                                     _transpose_note(typed_event->note()),
                                                     typed_event->velocity()));
            break;
        }

        case RtEventType::WRAPPED_MIDI_EVENT:
        {
            auto typed_event = event.wrapped_midi_event();
            _queue.push(RtEvent::make_wrapped_midi_event(typed_event->processor_id(),
                                                         typed_event->sample_offset(),
                                                         _transpose_midi(typed_event->midi_data())));
            break;
        }

        default:
            // Parameter changes are handled by the default implementation
            InternalPlugin::process_event(event);
            break;
    }
}

int TransposerPlugin::_transpose_note(int note)
{
    int steps = _transpose_parameter->value();
    return std::clamp(note + steps, MIN_NOTE, MAX_NOTE);
}

MidiDataByte TransposerPlugin::_transpose_midi(MidiDataByte midi_msg)
{
    auto type = midi::decode_message_type(midi_msg);
    switch (type)
    {
        case midi::MessageType::NOTE_ON:
        {
            auto note_on_msg = midi::decode_note_on(midi_msg);
            return midi::encode_note_on(note_on_msg.channel, _transpose_note(note_on_msg.note), note_on_msg.velocity);
        }
        case midi::MessageType::NOTE_OFF:
        {
            auto note_off_msg = midi::decode_note_off(midi_msg);
            return midi::encode_note_off(note_off_msg.channel, _transpose_note(note_off_msg.note), note_off_msg.velocity);
        }
        default:
            return midi_msg;
    }
}

void TransposerPlugin::process_audio(const ChunkSampleBuffer&, ChunkSampleBuffer&)
{
    while (_queue.empty() == false)
    {
        RtEvent e;
        _queue.pop(e);
        output_event(e);
    }
}

}// namespace transposer_plugin
}// namespace sushi