#pragma once

namespace stack {

	template <typename T>

	class Stack {
	private:
		int size_, capacity_;
		T *values_;

	public:
		Stack(int c) : capacity_{ c }, size_{ 0 } {
			if (capacity_ < 1) throw "negative_size";

			values_ = new T[capacity_]{}; // Heap memory allocated array
			std::cout << "Stack created with size " << capacity_ << std::endl;
		}
		~Stack() {
			delete[] values_;
			std::cout << "Stack destroyed" << std::endl;
		}

		bool Push(T value) {
			if (size_ == capacity_) return false;

			values_[size_++] = value;
			return true;
		}
		T Pop() {
			if (size_ == 0) {
				std::cout << "cannot pop: stack already empty" << std::endl;
				return {};
			}

			T value = values_[--size_];
			values_[size_] = {};
			return value;
		}
		
		void Print() {
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
	};

	// Specialization for std::string
	using StringStack = Stack<std::string>;
}