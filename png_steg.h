#ifndef SP_HIDE_IN_PNG_H
#define SP_HIDE_IN_PNG_H

#include <iostream>
#include <png.h>

using namespace std;

class png_steg {
public:
	void encode_steg(string source, string dest, string text);

	void decode_steg(string source, string output = "");

private:
	png_bytep *rows;
	png_infop info;
	png_structp read;
	png_structp write;

	void read_img(string path);

	void save_img(string dest);

	void encode_bits(string bits, unsigned int bits_size);

	void decode_bits(string output);
};


#endif
