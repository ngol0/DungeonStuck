#ifndef EVENTTYPE_H
#define EVENTTYPE_H

enum class EventType
{
    //collision event type
    OnCollisionEnter,
    OnCollisionStay,
    OnCollisionExit,

    //trigger event type
    OnTriggerEnter,
    
    
    //entity event
    OnEntityDestroy,

    //input event
    OnKeyPressed,
    OnMousePressed,
};

#endif