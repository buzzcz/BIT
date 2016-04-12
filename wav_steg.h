#ifndef SP_WAV_H
#define SP_WAV_H

#include <iostream>

using namespace std;

class wav_steg {
public:
	void encode_steg(string source, string dest, string text);

	void decode_steg(string source);

private:
	char *sound;
	long len;
	unsigned int data_size;

	void read_sound(string path);

	void save_sound(string dest);

	void encode_bits(string bits, unsigned int bits_size);

	void decode_bits();
};


#endif
