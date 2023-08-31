#include "impl.h"
#include <iostream>

class Widget::Impl {
public:
	Impl(int m_num = 0) : m_num(m_num) {}
	void fun() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	int num() const { return m_num; }
    void increase() {
        m_num++;
    }
private:
	int m_num;
};

Widget::Widget() : m_pImpl(std::make_unique<Impl>()) {}

Widget::~Widget() = default;

void Widget::fun() { m_pImpl->fun(); }

int Widget::num() const { return m_pImpl->num(); }

void Widget::increase()
{
    m_pImpl->increase();
}

Widget &Widget::operator=(Widget &&) = default;

Widget::Widget(Widget &&) = default;
