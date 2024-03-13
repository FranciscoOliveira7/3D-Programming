#include "list.h"
using namespace my_list;

int main() {

	List<int> list = List<int>();

	list.Add(2);

	std::cout << list[0] << std::endl;

	return 0;
}