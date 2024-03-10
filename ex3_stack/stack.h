#pragma once

namespace stack {

	template <class T>
	class Stack {
	 private:
		int size_ = 0, capacity_ = 0;
		T *values_;

	 public:
		Stack(int c);
		~Stack();
		bool Push(T value);
		T Pop(void);
		void Print(void);
	};

	// Stack Functions Definitions

	template <class T> Stack<T>::Stack(int c) : capacity_{ c }, size_{ 0 } {
		if (capacity_ < 1) throw "Negative Size Stack";

		values_ = new T[capacity_]{}; // Heap memory allocated array
		std::cout << "Stack created with size " << capacity_ << std::endl;
	}

	template <class T> Stack<T>::~Stack() {
		delete[] values_;
		std::cout << "Stack destroyed" << std::endl;
	}

	template <class T> bool Stack<T>::Push(T value) {
		if (size_ == capacity_) return false;

		values_[size_++] = value;
		return true;
	}	

	template <class T> T Stack<T>::Pop() {
		T value{};

		if (size_ > 0) {
			value = [--size_];
		}

		return value;
	}

	template <class T> void Stack<T>::Print() {
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
}