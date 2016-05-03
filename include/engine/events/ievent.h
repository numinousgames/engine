// event.h
#ifndef NGE_EVENT_IEVENT_H
#define NGE_EVENT_IEVENT_H

#include <string>

#include "engine/intdef.h"
#include "engine/strdef.h"

namespace nge
{

namespace event
{

class IEvent
{
  public:
    // CONSTRUCTORS
    /**
     * Destructs the event.
     */
    virtual ~IEvent() = 0;

    // TODO: decide how an object registers for events (what options?)
    // ACCESSOR FUNCTIONS
    /**
     * Gets the event type.
     */
    virtual const String type() const = 0;
};

// CONSTRUCTORS
inline
IEvent::~IEvent()
{
}

} // End nspc event

} // End nspc nge

#endif // NGE_EVENT_IEVENT_H
