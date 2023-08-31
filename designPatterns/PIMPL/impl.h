#pragma once

#include <memory>

class Widget {
public:
    Widget();
	~Widget();
	void fun();
	int num() const;
	void increase();
	Widget &operator=(Widget &&);
	Widget(Widget &&);

private:
	Widget &operator=(const Widget &) = delete;
	Widget(const Widget &) = delete;
	class Impl;
    std::unique_ptr<Impl> m_pImpl;
};
