/*
	enable_shared_from_this<T>类模板
	前提: 该对象由 shared_ptr 管理
	用途: 类内部安全地获取 this 指针, 确保 this 的生命周期由 shared_ptr 管理
	可以避免在异步处理中lambda捕获的this对象不会失效导致崩溃
		如果lambda捕获this后,进行异步处理时this对象已经释放,就导致了悬垂指针
		如果lambda通过shared_from_this()与类外shared_ptr<T>共同管理同一个对象(引用计数为2),所以不会导致悬垂指针,结果是安全的

	https://zh.cppreference.com/w/cpp/memory/enable_shared_from_this
	https://zhuanlan.zhihu.com/p/638029004
*/

#include <iostream>
#include <memory>

class Good : public std::enable_shared_from_this<Good> {
public:
	std::shared_ptr<Good> getptr() { return shared_from_this(); }
};

class Best : public std::enable_shared_from_this<Best> {
	struct Private {};

public:
	// 构造函数私有化
	Best(Private) {}
	// 工厂方法:类内调用构造函数 创建对象
	static std::shared_ptr<Best> create() {
		return std::make_shared<Best>(Private{});
	}
	std::shared_ptr<Best> getptr() { return shared_from_this(); }
};

class Bad {
public:
	// 从原始指针构造
	std::shared_ptr<Bad> getptr() { return std::shared_ptr<Bad>(this); }
	~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

// Good的正确用法
void test_Good() {
	// 2个shared_ptr共享同一对象
	std::shared_ptr<Good> good = std::make_shared<Good>();
	auto ptr = good->getptr();
	std::cout << "good.use_count = " << ptr.use_count() << "\n";
}

// Good的错误用法
void misuseGood() {
	try {
		// 错误: 调用者必须由shared_ptr管理
		Good* good = new Good;
		std::shared_ptr<Good> ptr = good->getptr();
	} catch (const std::bad_weak_ptr& e) {
		std::cout << e.what() << '\n';
	}
}

// 最佳的用法
void test_Best() {
	// 类外无法构造对象
	// Best b1;
	// Best* pb = new Best;

	// 确保了getptr调用者 一定由 shared_ptr 管理, 2个shared_ptr共享一个对象
	std::shared_ptr<Best> best = Best::create();
	auto ptr = best->getptr();
	std::cout << "Best.use_count = " << ptr.use_count() << "\n";
}

// 错误用法
void test_Bad() {
	// 每个shared_ptr认为自己 独占对象
	std::shared_ptr<Bad> bad0 = std::make_shared<Bad>();
	// 因为bad1是从原始指针this构造出来的
	auto bad1 = bad0->getptr();
	std::cout << "bad0.user_count = " << bad0.use_count() << "\n";
	std::cout << "bad1.user_count = " << bad1.use_count() << "\n";
	// 会析构2次 导致程序崩溃
}

int main(int argc, char* argv[]) {
	test_Good();
	misuseGood();
	test_Best();
	test_Bad();
	std::shared_ptr<int> x;
	std::weak_ptr<int> p;

	return 0;
}

/*
	shared_ptr的实现中,只包含两个指针
	1.get()返回的对象指针
	2.指向控制块的指针
	控制块是一个动态分配的对象，其中包含：
		指向被管理对象的指针或被管理对象本身
		删除器（类型擦除）
		分配器（类型擦除）
		占有被管理对象的 shared_ptr 的数量
		涉及被管理对象的 weak_ptr 的数量

	T对象必须由shared_ptr管理的原因(私有化构造函数可以类外避免裸指针或申请到栈上):
	enable_shared_from_this<T>类模板有一个weak_ptr<T>类型的成员变量weak_this
	weak_this是在shared_ptr<T>的构造函数中初始化的!!!
		shared_ptr<T>的构造函数中会判断enable_shared_from_this<T>是不是T的基类
		如果是,就会初始化weak_this
	而shared_from_this()从weak_this构造出一个shared_ptr
	shared_ptr<_Tp> shared_from_this() {
		 return shared_ptr<_Tp>(this->_M_weak_this);
	}

*/