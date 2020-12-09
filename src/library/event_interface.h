/*
 * Copyright 2017-2019 Modern Ancient Instruments Networked AB, dba Elk
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
 * SUSHI.  If not, see http://www.gnu.org/licenses/
 */

/**
 * @brief Abstract interface for adding event and notification functionality
 *        to a class.
 * @copyright 2017-2019 Modern Ancient Instruments Networked AB, dba Elk, Stockholm
 */

#ifndef SUSHI_EVENT_INTERFACE_H
#define SUSHI_EVENT_INTERFACE_H

#include "event.h"

namespace sushi {

enum EventPosterId : int
{
    AUDIO_ENGINE = 0,
    MIDI_DISPATCHER,
    OSC_FRONTEND,
    WORKER,
    CONTROLLER,
    MAX_POSTERS
};

class EventPoster
{
public:
    /**
     * @brief Function called when the poster receives an event
     * @param event The event received
     * @return An EventStatus or int code signaling how the event was handled.
     *         This will be returned to the completion callback, if the event
     *         does not have a completion callback, the return value will be
     *         ignored
     */
    virtual int process(Event* /*event*/) {return EventStatus::UNRECOGNIZED_EVENT;};

    /**
     * @brief The unique id of this poster.
     * @return
     */
    virtual int poster_id() = 0;
};

} // end namespace sushi
#endif //SUSHI_EVENT_INTERFACE_H
