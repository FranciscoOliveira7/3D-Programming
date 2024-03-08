#include <iostream>
#include "stack.h"
#include <string>
using namespace stack;

int main() {
	Stack<float> stack = Stack<float>(3);
	Stack<std::string> sstack = Stack<std::string>(2);

	std::cout << stack.Push(1.2) << std::endl;
	std::cout << stack.Push(2.5) << std::endl;
	std::cout << stack.Push(3.1) << std::endl;
	std::cout << stack.Push(4.3) << std::endl;
	stack.Print();
	float test = stack.Pop();
	float test2 = stack.Pop();
	float test3 = stack.Pop();
	stack.Print();
	float test4 = stack.Pop();

	sstack.Push("Hello");
	sstack.Push("World");
	sstack.Print();
	std::string string = sstack.Pop();
	sstack.Print();

	return 0;
}