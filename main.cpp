#include <iostream>
#include "png_steg.h"
#include "wav_steg.h"

using namespace std;

void help(char *name) {
	cout << "Usage: " << name <<
	" {{-e | --encode} {-png | -wav} path-to-a-source-file path-to-a-destination-file [{-f | --file} path_to_input] | {-d | --decode} {-png | -wav} path-to-a-source-file [{-f | --file} path_to_output]}" <<
	endl;
	exit(1);
}

void check_args(int argc, char *argv[]) {
	if (argc == 1) {
		help(argv[0]);
	} else {
		if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encode") == 0) {
			if (argc != 5 && argc != 7) {
				cout << "Wrong number of arguments" << endl;
				help(argv[0]);
			}
			if (strcmp(argv[2], "-png") != 0 && strcmp(argv[2], "-wav") != 0) {
				cout << "Unknown parameter " << argv[2] << endl;
				help(argv[0]);
			}
			if (argc == 7 && strcmp(argv[5], "-f") != 0 && strcmp(argv[5], "--file") != 0) {
				cout << "Unknown parameter " << argv[5] << endl;
				help(argv[0]);
			}
		} else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decode") == 0) {
			if (argc != 4 && argc != 6) {
				cout << "Wrong number of arguments" << endl;
				help(argv[0]);
			}
			if (strcmp(argv[2], "-png") != 0 && strcmp(argv[2], "-wav") != 0) {
				cout << "Unknown parameter " << argv[2] << endl;
				help(argv[0]);
			}
			if (argc == 6 && strcmp(argv[4], "-f") != 0 && strcmp(argv[4], "--file") != 0) {
				cout << "Unknown parameter " << argv[4] << endl;
				help(argv[0]);
			}
		} else {
			cout << "Unknown parameter " << argv[1] << endl;
			help(argv[0]);
		}
	}
}

string get_text() {
	string text;
	cout << "Enter text to hide:" << endl;
	getline(cin, text);
	return text;
}

string read_file(string filename) {
	FILE *f = fopen(filename.c_str(), "r");
	if (f == NULL) {
		cout << "Cannot open input file" << endl;
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *text = (char *) malloc(len * sizeof(char));
	fread(text, 1, len, f);
	fclose(f);
	string t(text);
	free(text);
	return t;
}

int main(int argc, char *argv[]) {
	check_args(argc, argv);

	if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encode") == 0) {
		string text;
		if (strcmp(argv[2], "-png") == 0) {
			if (argc == 5) text = get_text();
			else text = read_file(argv[6]);
			png_steg img;
			img.encode_steg(argv[3], argv[4], text);
		} else if (strcmp(argv[2], "-wav") == 0) {
			if (argc == 5) text = get_text();
			else text = read_file(argv[6]);
			wav_steg snd;
			snd.encode_steg(argv[3], argv[4], text);
		}
	} else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decode") == 0) {
		if (strcmp(argv[2], "-png") == 0) {
			png_steg img;
			if (argc == 4) img.decode_steg(argv[3]);
			else img.decode_steg(argv[3], argv[5]);
		} else if (strcmp(argv[2], "-wav") == 0) {
			wav_steg snd;
			if (argc == 4) snd.decode_steg(argv[3]);
			else snd.decode_steg(argv[3], argv[5]);
		}
	}
	return 0;
}