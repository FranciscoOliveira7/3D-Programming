#include <iostream>
#include "stack.h"
#include <string>

namespace stack {

	template <typename T>
	Stack<T>::Stack(int c) : capacity_{ c }, size_{ 0 } {
		if (capacity_ < 1) throw "negative_size";

		values_ = new T[capacity_]{}; // Heap memory allocated array
		std::cout << "Stack created with size " << capacity_ << std::endl;
	}

	template <typename T>
	Stack<T>::~Stack() {
		delete[] values_;
		std::cout << "Stack destroyed" << std::endl;
	}

	template <typename T>
	bool Stack<T>::Push(T value) {
		if (size_ == capacity_) return false;

		values_[size_++] = value;
		return true;
	}

	template <typename T>
	T Stack<T>::Pop() {
		if (size_ == 0) {
			std::cout << "cannot pop: stack already empty" << std::endl;
			return {};
		}

		T value = values_[--size_];
		return value;
	}

	template <typename T>
	void Stack<T>::Print() {
		using namespace std;

		// Example: stack: { 1, 2, 3 }

		if (size_ == 0) {
			cout << "stack: empty" << endl;
			return;
		}

		// If not empty
		cout << "stack: { ";
		for (int i = 0; i < size_ - 1; i++) {
			cout << values_[i] << ", ";
		}
		cout << values_[size_ - 1] << " }" << endl;
	}

	template class Stack<int>;
	template class Stack<float>;
	template class Stack<std::string>;
}