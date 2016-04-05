#include <iostream>
#include "png.h"

using namespace std;

void help(char *name) {
	cout << "Usage: " << name << " {-e | -d} {-p | -w} path-to-a-file" << endl;
}

void check_args(int argc, char *argv[]) {
	if (argc == 1) {
		help(argv[0]);
	} else if (argc < 4) {
		cout << "Too few arguments" << endl;
		help(argv[0]);
	} else if (argc > 4) {
		cout << "Too many arguments" << endl;
		help(argv[0]);
	}
	exit(1);
}

int main(int argc, char *argv[]) {
	//check_args(argc, argv);
	string text;
	cout << "Enter text to hide:" << endl;
	cin >> text;
	png img;
	img.hide("Bug.png", text);
	return 0;
}