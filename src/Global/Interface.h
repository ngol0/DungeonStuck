#ifndef INTERFACE_H
#define INTERFACE_H

class IData
{
public:
    virtual ~IData() = default;
};

class ICallback
{
public:
    virtual ~ICallback() = default;

    virtual void Call() {}
    virtual void Call(IData& data) {}
};

#endif