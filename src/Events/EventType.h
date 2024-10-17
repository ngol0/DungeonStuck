#ifndef EVENTTYPE_H
#define EVENTTYPE_H

enum class EventType
{
    //collision event type
    OnCollisionEnter,
    OnCollisionStay,
    OnCollisionExit,
    
    //entity event
    OnEntityDestroy,

    //input event
    OnKeyPressed,
    OnKeyUp,
    OnMousePressed,
    OnMouseUp,

    // on attack
    OnBeginAnim,
    OnDoneAnim,

    // collect item
    OnItemCollected,
};

#endif