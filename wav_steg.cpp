#include <cstring>
#include "wav_steg.h"
#include "steg.h"

void wav_steg::encode_steg(string source, string dest, string text) {
	read_sound(source);

	unsigned int bits_size = (unsigned int) strlen(text.c_str());
	string bits = steg::get_bits(text, bits_size);
	bits_size = bits_size * 8 + 32;
	if (bits_size > data_size) {
		cout << "Text is too long to be hidden in this sound" << endl;
		exit(0);
	}
	encode_bits(bits, bits_size);
	save_sound(dest);
	cout << "Done" << endl;
}

void wav_steg::decode_steg(string source, string output) {
	read_sound(source);
	decode_bits(output);
}

void wav_steg::read_sound(string path) {
	FILE *f = fopen(path.c_str(), "rb");
	if (f == NULL) {
		cout << "File not found" << endl;
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	sound = (char *) malloc((len + 1) * sizeof(char));
	fseek(f, 0, SEEK_SET);
	fread(sound, 1, len, f);
	fclose(f);

	string format = "";
	for (int i = 8; i < 12; i++) {
		format += sound[i];
	}
	if (strcmp(format.c_str(), "WAVE") != 0) {
		cout << "File is not WAV" << endl;
	}

	data_size = *(unsigned int *) &sound[40];
}

void wav_steg::save_sound(string dest) {
	FILE *f = fopen(dest.c_str(), "wb");
	if (f == NULL) {
		cout << "File could not be created" << endl;
		exit(1);
	}
	fwrite(sound, 1, len, f);
	fclose(f);
	free(sound);
}

void wav_steg::encode_bits(string bits, unsigned int bits_size) {
	for (unsigned int i = 0; i < bits_size; i++) {
		bits[i] == '1' ? (sound[44 + i] |= 0b1) : (sound[44 + i] &= 0b0);
	}
}

void wav_steg::decode_bits(string output) {
	unsigned int size = 0, i;
	for (i = 0; i < 32; i++) {
		size = size << 1;
		size += (sound[44 + i]) & 0b1;
	}

	char c = 0;
	unsigned int n = 0;
	string text;
	for (; i < 32 + (size * 8); i++) {
		c = c << 1;
		c += (sound[44 + i]) & 0b1;
		n++;
		if (n == 8) {
			text += c;
			n = 0;
			c = 0;
		}
	}
	if (!output.empty()) steg::write_to_file(output, text);
	else cout << text << endl;
	cout << "Done" << endl;

	free(sound);
}







