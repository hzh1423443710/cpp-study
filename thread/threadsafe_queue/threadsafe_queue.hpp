#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

template <class T>
class threadsafe_queue {
public:
	threadsafe_queue() = default;
    // copy constructor
	threadsafe_queue(const threadsafe_queue &other) {
		std::lock_guard<std::mutex> lock(other.m_mtx);	
		m_que = other.m_que;
	}
	threadsafe_queue(threadsafe_queue &&) = delete;
	threadsafe_queue &operator=(const threadsafe_queue &) = delete;
	threadsafe_queue &operator=(threadsafe_queue &&) = delete;

	// push and notify
	void push(const T &val) {
		std::lock_guard<std::mutex> lock(m_mtx);
		m_que.push(val);
		m_cond.notify_one();
	}
	// wait and pop1
	void wait_pop(T &outVal) {
		std::unique_lock<std::mutex> lk(m_mtx);
		while (m_que.empty()) {
			m_cond.wait(lk, [this]() { return !m_que.empty(); });
		}
		outVal = m_que.front();
		m_que.pop();
	}
	// wait and pop2
	std::shared_ptr<T> wait_pop() {
		std::unique_lock<std::mutex> lock(m_mtx);
		while (m_que.empty()) {
			m_cond.wait(lock, [this]() { return !m_que.empty(); });
		}
		auto ret_sp = std::make_shared<T>(std::move(m_que.front()));
		m_que.pop();
	}
	// try_pop1
	bool try_pop(T &outVal) {
		if (empty()) return false;
		std::lock_guard<std::mutex> lock(m_mtx);
		outVal = m_que.front();
		m_que.pop();
		return true;
	}
	// try_pop2
	bool try_pop() {
		if (empty()) return false;
		std::lock_guard<std::mutex> lock(m_mtx);
		auto ret_sp = std::make_shared<T>(std::move(m_que.front()));
		m_que.pop();
		return true;
	}
	// size
	auto size() const {
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_que.size();
	}
	// empty
	bool empty() const {
		std::lock_guard<std::mutex> lock(m_mtx);
		return m_que.empty();
	}

private:
	mutable std::mutex m_mtx;
	std::condition_variable m_cond;
	std::queue<T> m_que;
};