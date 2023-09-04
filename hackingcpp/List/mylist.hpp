#include <iostream>
#include <memory>

namespace hzh {

template <class T>
struct Node {
	Node* prev{};
	std::unique_ptr<Node> next;
	T val{};

public:
	Node(const T& val) : val(val) {}
	~Node() {
		static int cnt{};
		std::cout << ++cnt << " " << __FUNCTION__ << "\n";
	}
};

template <class T>
class List {
public:
	using value_type = T;
	using size_type = size_t;
	using node_type = Node<T>;
	using const_reference = const T&;
	using reference = T&;
	class Iterator;
	using const_iterator = const Iterator;

	class Iterator {
		friend class List<T>;

	public:
		Iterator(node_type* ptr = nullptr) : cur(ptr) {}
		Iterator operator++() {
			cur = cur->next.get();
			return *this;
		}
		Iterator operator++(int) {
			auto tmp = cur;
			cur = cur->next.get();
			return Iterator(tmp);
		}
		Iterator operator--() {
			cur = cur->prev;
			return *this;
		}
		Iterator operator--(int) {
			auto tmp = cur;
			cur = cur->prev;
			return Iterator(tmp);
		}
		Iterator operator+(int n) {
			node_type* tmp = cur;
			for (int i{}; i < n; ++i) {
				if (!tmp) {
					throw std::runtime_error("Exception: Invalid iterator plus operator");
				}
				tmp = tmp->next.get();
			}
			return Iterator(tmp);
		}
		Iterator operator+=(int n) {
			Iterator it = (*this) + n;
			cur = it.cur;
			return *this;
		}

		T& operator*() { return cur->val; }
		node_type* operator->() { return &cur->val; }
		bool operator!=(const Iterator& other) const { return cur != other.cur; }
		bool operator==(const Iterator& other) const { return !(cur != other.cur); }

	private:
		node_type* cur;
	};

public:
	List() = default;
	List(const List& other) {
		for (auto it = other.cbegin(); it != other.cend(); ++it) {
			push_back(*it);
		}
	}
	List& operator=(const List& other) {
		List tmp(other);
		m_pHead.swap(tmp.m_pHead);
		m_size = tmp.m_size;
		m_pTail = tmp.m_pTail;
		return *this;
	}
	List(List&& other) : m_pHead(std::move(other.m_pHead)) {
		std::swap(m_pTail, other.m_pTail);
		std::swap(m_size, other.m_size);
	}
	List& operator=(List&& other) {
		m_pHead.swap(other.m_pHead);
		std::swap(m_pTail, other.m_pTail);
		std::swap(m_size, other.m_size);
		return *this;
	}

	Iterator insert(const_iterator pos, const T& val) {
		auto pNew = std::make_unique<Node<T>>(val);
		Iterator it{};
		if (m_size == 0) {
			m_pHead = std::move(pNew);
			m_pTail = m_pHead.get();
			it = Iterator(m_pHead.get());
		} else if (pos == begin()) {
			m_pHead->prev = pNew.get();
			pNew->next = std::move(m_pHead);
			m_pHead = std::move(pNew);
			it = Iterator(m_pHead.get());

		} else if (pos == end()) {
			pNew->prev = m_pTail;
			m_pTail->next = std::move(pNew);
			m_pTail = m_pTail->next.get();
			it = Iterator(m_pTail);
		} else {
			pNew->next = std::move(pos.cur->prev->next);
			pNew->prev = pos.cur->prev;
			pos.cur->prev = pNew.get();
			it = Iterator(pNew.get());
			pNew->prev->next.reset(pNew.release());
		}
		++m_size;
		return it;
	}
	Iterator erase(const_iterator pos) {
		if (empty()) return end();
		Iterator ret{};
		if (pos == begin()) {
			auto pDel = std::move(m_pHead);
			m_pHead = std::move(pDel->next);
			if (m_pHead) m_pHead->prev = pDel->prev;
			ret = m_pHead.get();
		} else {
			auto pDel = std::move(pos.cur->prev->next);
			if (!pos.cur->next) {
				m_pTail = pDel->prev;
				ret = Iterator(m_pTail);
			} else {
				pDel->next->prev = pDel->prev;
				ret = Iterator(pDel->next.get());
				pDel->prev->next = std::move(pDel->next);
			}
		}
		--m_size;
		return ret;
	}

	void push_front(const value_type& val) { insert(begin(), val); }
	void push_back(const value_type& val) { insert(end(), val); }
	void pop_front() { erase(begin()); }
	void pop_back() { erase(Iterator(m_pTail)); }
	size_type size() const { return m_size; }
	bool empty() const { return size() == 0; }
	const_reference front() const { return m_pHead->val; }
	const_reference back() const { return m_pTail->val; }
	reference front() { return m_pHead->val; }
	reference back() { return m_pTail->val; }

	Iterator begin() { return Iterator(m_pHead.get()); }
	const_iterator cbegin() const { return Iterator(m_pHead.get()); }
	Iterator end() { return Iterator(nullptr); }
	const_iterator cend() const { return Iterator(nullptr); }
	Iterator rbegin() { return Iterator(m_pTail); }
	Iterator rend() { return Iterator(nullptr); }

private:
	std::unique_ptr<Node<T>> m_pHead;
	size_type m_size{};
	Node<T>* m_pTail{};
};

}  // namespace hzh