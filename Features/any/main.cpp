#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>

class Any {
private:
	class HolderBase {
	public:
		virtual HolderBase* clone() = 0;
		virtual ~HolderBase() noexcept {}
		virtual const std::type_info& type() const noexcept = 0;
	};

	template <class T>
	class HolderImpl : public HolderBase {
	public:
		HolderImpl<T>* clone() override { return new HolderImpl<T>(m_val); }
		const std::type_info& type() const noexcept override { return typeid(T); }
		HolderImpl(const T& val) : m_val(val) {}
		T m_val;
	};

public:
	// 默认构造
	Any() = default;
	// 拷贝构造
	Any(const Any& other) {
		if (other.m_ptr) {
			m_ptr.reset(other.m_ptr->clone());
		} else {
			m_ptr = nullptr;
		}
	}
	// 移动构造
	Any(Any&& other) noexcept { m_ptr.swap(other.m_ptr); }

	// SFINAE:避免需要拷贝,移动构造时 调用这个万能匹配
	// 有参构造
	template <class T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, Any>, int> = 0>
	Any(T&& val) : m_ptr(std::make_unique<HolderImpl<T>>(std::forward<T>(val))) {}

	// 转换
	template <class T>
	T cast() {
		if (!m_ptr) throw std::runtime_error("Uninitialized any");
		HolderImpl<T>* ptr = dynamic_cast<HolderImpl<T>*>(m_ptr.get());
		if (!ptr) throw std::runtime_error("Wrong type conversion");
		return ptr->m_val;
	}

	// 是否有值
	bool has_value() const noexcept { return m_ptr != nullptr; }

	// 拷贝赋值
	Any& operator=(const Any& rhs) {
		if (this != &rhs) *this = Any(rhs);	 // 复用 拷贝构造
		return *this;
	}

	// 移动赋值
	Any& operator=(Any&& rhs) noexcept {
		Any tmp(std::move(rhs));  // 复用 移动构造
		tmp.m_ptr.swap(m_ptr);
		return *this;
	}

	// 存储对象
	template <class T, std::enable_if_t<!std::is_same_v<std::decay_t<T>, Any>, int> = 0>
	Any& operator=(T&& val) noexcept {
		*this = Any(std::forward<T>(val));	// 复用 移动赋值
		return *this;
	}

	// If not empty, destroy the contained object.
	void reset() noexcept {
		if (has_value()) m_ptr.reset();
	}

	const std::type_info& type() const noexcept {
		if (!has_value()) return typeid(void);
		return m_ptr->type();
	}

private:
	std::unique_ptr<HolderBase> m_ptr;
};

void test_any() {
	// 测试 无参构造
	// 测试 有参构造
	// 测试 拷贝构造
	// 测试 移动构造

	// 测试 拷贝赋值
	// 测试 移动赋值

	// 测试 存储对象
	Any a = 3.14;
	std::cout << "a = " << a.cast<double>() << "\n";
	a = 200;
	std::cout << "a = " << a.cast<int>() << "\n";

	Any a2;
	try {
		std::cout << "a2 = " << a2.cast<int>() << "\n";
		std::cout << "a2 = " << a2.cast<int>() << "\n";
		std::cout << "a = " << a.cast<int>() << "\n";
	} catch (const std::exception& e) {
		std::cout << "EXCEPTION: " << e.what() << "\n";
	}

	std::cout << "a2.type: " << a2.type().name() << "\n";
	a2.reset();
	std::cout << "a2.has_value: " << a2.has_value() << "\n";
}

int main() {
	test_any();

	return 0;
}