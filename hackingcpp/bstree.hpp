#pragma once

#include <memory>
#include <iostream>
#include <initializer_list>

template<class T>
class BSTree
{
public:
	using value_type = T;
	using size_type = std::size_t;

private:
	class Node
	{
	public:
		explicit Node() = default;
		explicit Node(const T& val);
		Node(const Node &);
		Node& operator=(const Node &);
		Node(Node &&) noexcept;
		Node& operator=(Node &&) noexcept;

	public:
		T val_{};
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};

public:
	explicit BSTree() = default;
	BSTree(const BSTree &);
	BSTree(std::initializer_list<T> list);
	BSTree& operator=(const BSTree&);
	BSTree(BSTree &&) noexcept;
	BSTree& operator=(BSTree&&) noexcept;

	void insert(const value_type& val);
	void printTree() const;
	size_type size() const;
	bool empty() const;

private:
	void _insert(std::unique_ptr<Node>& cur, const value_type& val);
	void _printTree(const std::unique_ptr<Node>& cur) const;

private:
	std::unique_ptr<Node> root_{};
	size_type size_{};
};

template<class T>
void BSTree<T>::printTree() const
{
	std::cout << "tree: {";
	if (root_)
		_printTree(root_);
	std::cout << "}\n";
}

template<class T>
typename BSTree<T>::size_type BSTree<T>::size() const
{
	return size_;
}

template<class T>
bool BSTree<T>::empty() const
{
	return size_ == 0;
}

template<class T>
void BSTree<T>::_printTree(const std::unique_ptr<Node>& cur) const
{
	if (cur->left_)
		_printTree(cur->left_);
	std::cout << cur->val_ << ",";
	if (cur->right_)
		_printTree(cur->right_);
}

template<class T>
BSTree<T>::BSTree(const BSTree& other) : root_(nullptr)
{
	if (other.root_) {
		root_ = std::make_unique<Node>(*other.root_);
		size_ = other.size_;
	}
}

template<class T>
BSTree<T>::BSTree(std::initializer_list<T> list)
{
	for (auto&& v : list)
		insert(v);
}

template<class T>
BSTree<T>& BSTree<T>::operator=(const BSTree& other)
{
	if (&other == this)
		return *this;

	BSTree<T> tmp(other);
	root_.swap(tmp.root_);
	size_ = other.size_;

	return *this;
}

template<class T>
BSTree<T>::BSTree(BSTree&& other) noexcept
	: root_(std::move(other.root_))
{
	std::swap(size_, other.size_);
}

template<class T>
BSTree<T>& BSTree<T>::operator=(BSTree&& other) noexcept
{
	if (&other == this)
		return *this;

	root_ = std::move(other.root_);
	std::swap(size_, other.size_);

	return *this;
}

template<class T>
void BSTree<T>::insert(const value_type& val)
{
	if (!root_) {
		root_ = std::make_unique<Node>(val);
	}
	else {
		_insert(root_, val);
	}
	++size_;
}

template<class T>
void BSTree<T>::_insert(std::unique_ptr<Node>& cur, const value_type& val)
{
	if (val < cur->val_) {
		if (cur->left_)
			_insert(cur->left_, val);
		else
			cur->left_ = std::make_unique<Node>(val);
	}
	else {
		if (cur->right_)
			_insert(cur->right_, val);
		else
			cur->right_ = std::make_unique<Node>(val);
	}
}

template<class T>
BSTree<T>::Node::Node(const T& val)
 : val_(val)
{
}

template<class T>
BSTree<T>::Node::Node(const Node& other)
 : val_(other.val_), left_(nullptr), right_(nullptr)
{
	if (other.left_)
		left_ = std::make_unique<Node>(*other.left_);
	if (other.right_)
		right_ = std::make_unique<Node>(*other.right_);
}


template<class T>
typename BSTree<T>::Node& BSTree<T>::Node::operator=(const Node& other)
{
	if (&other == this)
		return *this;

	Node tmp(other);
	std::swap(tmp.val_, val_);
	left_.swap(tmp.left_);
	right_.swap(tmp.right_);

	return *this;
}

template<class T>
BSTree<T>::Node::Node(Node&& other) noexcept
	: val_(std::move(other.val_)), left_(std::move(other.left_)), right_(std::move(other.right_))
{

}

template<class T>
typename BSTree<T>::Node& BSTree<T>::Node::operator=(Node&& other) noexcept
{
	if (&other == this)
		return *this;

	val_ = std::move(other.val_);
	left_ = std::move(other.left_);
	right_ = std::move(other.right_);

	return *this;
}
