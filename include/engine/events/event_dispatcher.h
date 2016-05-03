// event_dispatcher.h
#ifndef NGE_EVENT_EVENT_DISPATCHER_H
#define NGE_EVENT_EVENT_DISPATCHER_H

#include <functional>

#include "engine/containers/dynamic_array.h"
#include "engine/events/ievent.h"
#include "engine/strdef.h"

namespace nge
{

namespace event
{

class EventDispatcher
{
  public:
    // TYPES
    /**
     * Defines an event listener.
     */
    typedef std::function<void( const IEvent* )> EventListener;

  private:
    // TYPES
    typedef std::pair<String, RegisteredListener>

    // MEMBERS
    /**
     * The registered listeners.
     */
    cntr::Map<String, cntr::DynamicArray<EventListener>> _listeners;

    cntr::DynamicArray<

};

} // End nspc event

} // End nspc nge

#endif // NGE_EVENT_EVENT_DISPATCHER_H
