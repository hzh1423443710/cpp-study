#pragma once

#include <iostream>
#include <memory>

class MyAny {
public:
	explicit MyAny() : m_ptr(nullptr) {}
	explicit MyAny(const MyAny &other) : m_ptr(other.m_ptr->clone()) {
		// 通过基类指针创建拷贝
	}
	MyAny &operator=(const MyAny &other) {
		MyAny tmp(other);
		std::swap(m_ptr, tmp.m_ptr);
		return *this;
	}

	explicit MyAny(MyAny &&) = default;
	MyAny &operator=(MyAny &&) = default;

	template <class T>
	MyAny &operator=(const T &val) {
		if (auto pHolder = dynamic_cast<Holder<T>*>(m_ptr.get())) {
			pHolder->val = val;
		} else {
			MyAny tmp(val);
			std::swap(m_ptr, tmp.m_ptr);
		}
		return *this;
	}

	template <class T>
	MyAny(const T &val) : m_ptr(std::make_unique<Holder<T>>(val)) {
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}

	template <class T>
	T &value() {
		if (auto pHolder = dynamic_cast<Holder<T> *>(m_ptr.get())) {
			return pHolder->val;
		}
		throw std::runtime_error("type cast error!");
	}

	bool has_value() const { return m_ptr.get() != nullptr; }

private:
	struct HolderBase {
		virtual ~HolderBase() = default;
		virtual std::unique_ptr<HolderBase> clone() = 0;
	};
	template <class T>
	struct Holder : public HolderBase {
		T val;
		Holder(T val) : val(val) {}
		std::unique_ptr<HolderBase> clone() override { return std::make_unique<Holder<T>>(val); }
	};

private:
	std::unique_ptr<HolderBase> m_ptr;
};