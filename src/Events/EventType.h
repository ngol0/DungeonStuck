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
    OnMousePressed,

    // on attack
    OnAttack,
};

#endif