// itickable.h
//
// The interface definition of an item that is updated by the scene during the
// tick cycle.
//
#ifndef NGE_WORLD_ITICKABLE_H
#define NGE_WORLD_ITICKABLE_H

namespace nge
{

namespace world
{

class ITickable
{
  public:
    // CONSTRUCTORS
    /**
     * Destructs the tickable.
     */
    virtual ~ITickable() = 0;

    // MEMBER FUNCTIONS
    /**
     * Prepares for the next tick cycle.
     */
    virtual void pretick() = 0;

    /**
     * Performs the tick cycle for the given elapsed time in seconds.
     */
    virtual void tick( float dtS ) = 0;

    /**
     * Cleans up after the tick cycle.
     */
    virtual void postick() = 0;
};

inline
ITickable::~ITickable()
{
}

} // End nspc world

} // End nspc nge

#endif // NGE_WORLD_ITICKABLE_H
