#pragma once

#include <memory>

class WW
{
public:
    WW();
    ~WW();
    void doSomething();
private:
    class Impl;
    std::unique_ptr<Impl> m_ptr;
};