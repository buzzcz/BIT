#include <iostream>
#include "png_steg.h"
#include "wav_steg.h"

using namespace std;

void help(char *name) {
	cout << "Usage: " << name <<
	" {-e {-png | -wav} path-to-a-source-file path-to-a-destination-file | -d {-png | -wav} path-to-a-source-file} " <<
	endl << "-e = encode" << endl << "-d = decode" << endl;
	exit(1);
}

void check_args(int argc, char *argv[]) {
	if (argc == 1) {
		help(argv[0]);
	} else {
		if (strcmp(argv[1], "-e") == 0) {
			if (argc != 5) {
				cout << "Wrong number of arguments" << endl;
				help(argv[0]);
			}
			if (strcmp(argv[2], "-png") != 0 && strcmp(argv[2], "-wav") != 0) {
				cout << "Unknown parameter " << argv[2] << endl;
				help(argv[0]);
			}
		} else if (strcmp(argv[1], "-d") == 0) {
			if (argc != 4) {
				cout << "Wrong number of arguments" << endl;
				help(argv[0]);
			}
			if (strcmp(argv[2], "-png") != 0 && strcmp(argv[2], "-wav") != 0) {
				cout << "Unknown parameter " << argv[2] << endl;
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

int main(int argc, char *argv[]) {
	check_args(argc, argv);

	if (strcmp(argv[1], "-e") == 0) {
		string text;
		if (strcmp(argv[2], "-png") == 0) {
			text = get_text();
			png_steg img;
			img.encode_steg(argv[3], argv[4], text);
		} else if (strcmp(argv[2], "-wav") == 0) {
			text = get_text();
			wav_steg snd;
			snd.encode_steg(argv[3], argv[4], text);
		}
	} else if (strcmp(argv[1], "-d") == 0) {
		if (strcmp(argv[2], "-png") == 0) {
			png_steg img;
			img.decode_steg(argv[3]);
		} else if (strcmp(argv[2], "-wav") == 0) {
			wav_steg snd;
			snd.decode_steg(argv[3]);
		}
	}
	return 0;
}