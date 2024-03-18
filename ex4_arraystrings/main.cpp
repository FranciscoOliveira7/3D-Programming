#include <iostream>
#include <string>
#include <array>

using namespace std;

typedef array<string, 5> StringArray;

StringArray readStringArray(StringArray strings) {
	
	for (int i = 0; i < strings.size(); i++) {
		cout << "Insira uma frase: ";
		getline(cin, strings[i]);
	}

	return strings;
}

StringArray sortStringArray(StringArray strings) {
	
	// Bubble sort

	bool sorted = false;

	while (!sorted) {
		sorted = true;
		for (int i = 0; i < strings.size() - 1; i++) {
			if (strings[i] > strings[i + 1]) {
				sorted = false;
				strings[i].swap(strings[i+1]);
			}
		}
	}

	return strings;
}

void printStringArray(StringArray strings) {
	cout << "\n---Frases---" << endl;

	for (StringArray::iterator p = strings.begin(); p != strings.end(); p++) {
		cout << *p << endl;
	}
}

int main() {
	StringArray sentences = {};

	sentences = readStringArray(sentences);
	sentences = sortStringArray(sentences);
	printStringArray(sentences);

	return 0;
}