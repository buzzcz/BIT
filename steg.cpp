#include <bitset>
#include "steg.h"

string steg::get_bits(string text, size_t text_size) {
	string bits = "";

	bitset<32> size(text_size);
	bits += size.to_string();

	for (unsigned int i = 0; i < text_size; i++) {
		bitset<8> chars((unsigned long long int) text[i]);
		bits += chars.to_string();
	}
	return bits;
}

void steg::write_to_file(string output, string text) {
	FILE *f = fopen(output.c_str(), "w");
	if (f == NULL) {
		cout << "Cannot write into output file" << endl;
		exit(1);
	}
	fwrite(text.c_str(), 1, text.length(), f);
	fclose(f);
}