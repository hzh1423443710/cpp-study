#include <iostream>
#include <memory>
#include <functional>
#include <type_traits>

template <class Signature>
class Function {
	static_assert(!std::is_same_v<Signature, Signature>,
				  "incorret function signature");
};

template <class Ret, class... Args>
class Function<Ret(Args...)> {
private:
	class FunctorBase {
	public:
		virtual FunctorBase* clone() const noexcept = 0;
		virtual Ret call(Args...) = 0;
		virtual ~FunctorBase() {}
	};

	template <class Fn>
	class FunctorImpl : public FunctorBase {
	public:
		FunctorImpl(const Fn& fn) : m_fn(fn) {}
		FunctorImpl* clone() const noexcept override {
			return new FunctorImpl<Fn>(m_fn);
		}
		Ret call(Args... args) override { m_fn(args...); }

	private:
		Fn m_fn;
	};

public:
	// 默认构造
	Function() = default;

	// 构造空的Funciton
	Function(std::nullptr_t) : Function() {
		std::cout << "Function(std::nullptr_t)\n";
	}

	// 构造Callable Object
	template <class Fn, class = std::enable_if_t<
							std::is_invocable_r_v<Ret, Fn, Args...> &&
								!std::is_same_v<std::decay_t<Fn>, Function>,
							void>>
	Function(Fn&& fn)
		: m_ptr(std::make_unique<FunctorImpl<Fn>>(std::forward<Fn>(fn))) {
		std::cout << "Function(Fn&&)\n";
	}

	// 拷贝构造
	Function(const Function& other) {
		std::cout << "Function(const Function&)\n";
		// 从基类拷贝一个实体
		if (other) m_ptr.reset(other.m_ptr->clone());
	}

	// 移动构造
	Function(Function&& other) noexcept {
		std::cout << "Function(Function&&)\n";
		if (other) m_ptr.swap(other.m_ptr);
	}

	// 调用
	Ret operator()(Args... args) const {
		if (m_ptr)
			return m_ptr->call(std::forward<Args>(args)...);
		else
			throw std::runtime_error("Uninitialized Function");
	}

	// 拷贝赋值
	Function& operator=(const Function& rhs) {
		if (this != &rhs) Function(rhs).m_ptr.swap(m_ptr);
		return *this;
	}

	// 移动赋值
	Function& operator=(Function&& rhs) noexcept {
		if (this != &rhs) Function(std::move(rhs)).m_ptr.swap(m_ptr);
		return *this;
	}

	// 存储functor
	template <class Fn>
	std::enable_if_t<std::is_invocable_r_v<Ret, Fn, Args...> &&
						 !std::is_same_v<std::decay_t<Fn>, Function>,
					 Function&>
	operator=(Fn&& fn) {
		std::cout << "operator=(Fn&&)\n";
		this->m_ptr.reset(new FunctorImpl<Fn>(std::forward<Fn>(fn)));
		return *this;
	}

	// 置空
	Function& operator=(std::nullptr_t) {
		m_ptr.reset();
		return *this;
	}

	// operator bool
	explicit operator bool() const noexcept { return m_ptr != nullptr; }

	bool empty() const noexcept { return m_ptr == nullptr; }

private:
	std::unique_ptr<FunctorBase> m_ptr;
};

void printMsg(const std::string& msg) { std::cout << "PRINT: " << msg << "\n"; }

void test_Function() {
	using Signature = void(const std::string&);
	Function<Signature> f0 = nullptr;		// nullptr构造
	Function<Signature> f1 = f0;			// 拷贝构造
	Function<Signature> f2 = std::move(f1); // 移动构造

	// 可调用对象构造
	Function<Signature> f = printMsg;
	f("Callable object construct: f is printMsg");

	// 可调用对象赋值
	f = [](const std::string& str) { std::cout << "Lambda: " << str << "\n"; };
	f("Callable object assigment: f is Lambda");

	// 空赋值
	f = nullptr;
	if (f.empty()) std::cout << "nullptr assignment: f is nullptr";

	// 拷贝赋值
	f = f0;
	if (f.empty()) std::cout << "copy assignment: f is empty function";

	// 移动赋值
	f = std::move(f0);
	if (f.empty()) std::cout << "move assignment: f is empty function";
}

void test_contravariant() {
	// std::function
	std::function<void(const char*)> f0;
	std::function<void(const std::string&)> f1;
	f0 = f1; // correct		f1的Callable object可以调用void(const char*)
	// f1 = f0; // incorrect	f0的Callable object不能调用void(const string&)

	// my function
	Function<void(const char*)> ff0;
	Function<void(const std::string&)> ff1;
	ff0 = ff1; // correct		ff1的Callable object可以调用void(const char*)
	// ff1 = ff0; // incorrect	ff0的Callable object不能调用void(conststring&)
}

int main(int argc, char* argv[]) {
	test_Function();
	test_contravariant(); // 逆变

	return 0;
}