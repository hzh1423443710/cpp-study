#include "impl.h"

#include <iostream>

class WW::Impl {
public:
	void doSomething() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

WW::WW() : m_ptr(std::make_unique<Impl>()) {}

WW::~WW() = default;

void WW::doSomething() { m_ptr->doSomething(); }