#pragma once

namespace stack {

	template <typename T>

	class Stack {
	private:
		int size_, capacity_;
		T *values_;

	public:
		Stack(int c);
		~Stack();

		bool Push(T value);
		T Pop();
		
		void Print();
	};
}