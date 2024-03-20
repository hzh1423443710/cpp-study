#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// 抽象观察者类
class AbstractObserver {
public:
	virtual ~AbstractObserver() {}
	virtual void update(const std::string& state) = 0;
};

// 抽象主题类
class AbstractSubject {
public:
	virtual ~AbstractSubject() {}
	using AbstractObserverPtr = std::shared_ptr<AbstractObserver>;
	void attach(AbstractObserverPtr obsPtr) {
		if (std::find(_observers.begin(), _observers.end(), obsPtr) ==
			_observers.end()) {
			_observers.push_back(obsPtr);
		}
	}
	void detach(AbstractObserverPtr obsPtr) {
		auto it = std::find(_observers.begin(), _observers.end(), obsPtr);
		if (it != _observers.end()) {
			_observers.erase(it);
		}
	}

protected:
	virtual void notify() = 0;
	std::vector<AbstractObserverPtr> _observers;
};

// 实体主题类
class Bell : public AbstractSubject {
public:
	void setMsg(const std::string& msg) { _msg = msg; }
	virtual void notify() override {
		for (auto& obs : _observers) {
			obs->update(_msg);
		}
	}

private:
	std::string _msg;
};

// 实体观察者
class Teacher : public AbstractObserver {
public:
	virtual void update(const std::string& msg) override {
		std::string str = "...";
		if (msg == "上课铃") str = "准备去讲课";
		std::cout << "The teacher heared the bell \'" << msg << "\', " << str
				  << "\n";
	}
};

// 实体观察者
class Student : public AbstractObserver {
public:
	virtual void update(const std::string& msg) override {
		std::string str = "...";
		if (msg == "上课铃") str = "准备去上课";
		std::cout << "The student heared the bell \'" << msg << "\', " << str
				  << "\n";
	}
};

int main(int argc, char* argv[]) {
	Bell bell;
	auto teacher = std::make_shared<Teacher>();
	auto student = std::make_shared<Student>();

	bell.attach(teacher);
	bell.attach(student);

	bell.setMsg("上课铃");
	bell.notify();

	bell.setMsg("下课铃");
	bell.notify();

	bell.detach(student);
	bell.notify();
	bell.notify();

	return 0;
}