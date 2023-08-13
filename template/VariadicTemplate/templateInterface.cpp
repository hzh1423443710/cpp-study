#include <iostream>
#include <vector>
#include <functional>

template<class ObjectType, class ReturnType, class... Args>
class Interface
{
	using MemberFunctionPtr = ReturnType(ObjectType::*)(Args...);
public:
	Interface() = default;
	Interface(ObjectType* pObj, MemberFunctionPtr ptr)
		: pObj_(pObj), pFun_(ptr)
	{}
	ReturnType operator()(Args... args)
	{
		return (pObj_->*pFun_)(args...);
	}
private:
	ObjectType* pObj_{};
	MemberFunctionPtr pFun_{};
};

template<class ObjectType, class ReturnType, class... Args>
auto createCallableObject(ObjectType* objPtr, ReturnType(ObjectType::*pFun)(Args...))
{
	return Interface<ObjectType, ReturnType, Args...>{objPtr,pFun};
}

struct MM
{
	int add(int a, int b)
	{
		return a+b;
	}
	void print(std::string_view str)
	{
		std::cout << str << "\n";
	}
};

int main(int argc, char* argv[])
{
	MM m;
	auto addObj = createCallableObject(&m, &MM::add);
	std::cout << addObj(1,2) << "\n";

	auto printObj = createCallableObject(&m, &MM::print);
	printObj("Hello World");


	return 0;
}
