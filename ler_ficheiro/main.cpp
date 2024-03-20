#include <iostream>
#include <string>
#include <fstream>

int main() {
	using namespace std;

	//ifstream ficheiro("teste.txt");
	//if (ficheiro.is_open()) {
	//	string msg;
	//	while (getline(ficheiro, msg, '|'))
	//		cout << msg << endl;
	//	ficheiro.close();
	//}

	//ifstream shader_file("shader.vert");
	//if (shader_file.is_open()) {
	//	string line;
	//	while (getline(shader_file, line)) cout << line << endl;
	//	shader_file.close();
	//}

	streampos start, end;

	ifstream shader_file("shader.vert");
	if (shader_file.is_open()) {
		start = shader_file.tellg();
		shader_file.seekg(0, ios::end);
		end = shader_file.tellg();

		int file_size = end - start;

		char* shader = new char[file_size];
		delete[] shader;
		shader_file.close();
	}

	return 0;
}