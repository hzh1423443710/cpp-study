#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>

template <class FunSig>
class Function {
	static_assert(!std::is_same_v<FunSig, FunSig>, "should pass function sigature");
};

template <class Ret, class... Args>
class Function<Ret(Args...)> {
private:
	class Callable {
	public:
		virtual Ret call(Args... arg) = 0;
		virtual ~Callable() {}
	};

	template <class Functor>
	class ConcreteCallable : public Callable {
	public:
		ConcreteCallable(const Functor& fn) : m_f(fn) {}
		Ret call(Args... arg) override { return m_f(arg...); }

	private:
		Functor m_f;
	};

public:
	// 构造
	Function() = default;
	template <class Functor>
	Function(Functor&& f)
		: m_ptr(std::make_unique<ConcreteCallable<Functor>>(std::forward<Functor>(f))) {}

	// 调用
	template <class... T>
	Ret operator()(T... args) const {
		if (!m_ptr) throw std::runtime_error("Uninitialized Function");
		return m_ptr->call(std::forward<T>(args)...);
	}

	// 赋值
	template <class Functor>
	Function& operator=(Functor&& f) {
		Function{f}.m_ptr.swap(this->m_ptr);
		return *this;
	}

	Function& operator=(std::nullptr_t) {
		m_ptr.reset();
		return *this;
	}

private:
	std::unique_ptr<Callable> m_ptr;
};

void print1(const char* str) { std::cout << str << "\n"; }
void print2(const char* str) { std::cout << "#" << str << "\n"; }

struct D {
	void operator()(const char* str) { std::cout << __PRETTY_FUNCTION__ << ":" << str << "\n"; }
};

int main() {
	Function<void(const char*)> f = print1;
	f("1212");

	f = D{};
	f("HHHH");

	try {
		f = nullptr;
		f("12345");
	} catch (const std::exception& e) {
		std::cout << "exception:" << e.what() << "\n";
	}

	f = [](const char* str) { std::cout << __PRETTY_FUNCTION__ << "\n"; };
	f("Lambda");

	return 0;
}