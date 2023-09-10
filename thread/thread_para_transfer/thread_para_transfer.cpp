#include <iostream>
#include <thread>

#if defined(_MSC_VER)
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif

class Parameter {
public:
	Parameter() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	Parameter(const Parameter&) { std::cout << __PRETTY_FUNCTION__ << "\n"; };
	Parameter(Parameter&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; };
};

// 1. 临时对象
void test_temp_obj() {
	std::thread([](Parameter para) {}, Parameter{}).join();	 // 构造1次 移动2次
}

// 2. 有名对象
void test_name_obj() {
	Parameter para;
	std::thread([](Parameter para) {}, para).join();  // 构造1次 拷贝1次 移动一次
}
// 3. 引用传参
void test_ref_transfer() {
	Parameter para;
	std::thread([](Parameter& para) {}, std::ref(para)).join();	 // 只构造1次
}

/*
std::thread 构造函数
thread(_Callable&& __f, _Args&&... __args) {
    ...
	第1次参数构造: 根据实参是左值还是右值 对_State_impl进行 拷贝构造 or 移动构造
	_M_start_thread(_State_ptr (new _State_impl<_Wrapper>(std::forward<_Callable>(__f),
							std::forward<_Args>(__args)...)), __depend);
	第2次参数构造: 启动线程后 将 args 拷贝到线程入口 
}
*/

int main(int argc, char* argv[]) {
	std::cout << "----------------------------------------test_temp_obj" << "\n";
	test_temp_obj();
	std::cout << "----------------------------------------test_name_obj" << "\n";
	test_name_obj();
	std::cout << "----------------------------------------test_ref_transfer" << "\n";
	test_ref_transfer();

	return 0;
}