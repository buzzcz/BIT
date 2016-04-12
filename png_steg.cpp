#include <netinet/in.h>
#include <cstring>
#include <bitset>
#include "png_steg.h"
#include "steg.h"

void png_steg::encode_steg(string source, string dest, string text) {
	read_img(source);

	unsigned int bits_size = (unsigned int) strlen(text.c_str());
	string bits = steg::get_bits(text, bits_size);
	bits_size = bits_size * 8 + 32;
	if (bits_size > info->height * (info->width * info->color_type)) {
		cout << "Text is too long to be hidden in this image" << endl;
		png_destroy_read_struct(&read, &info, NULL);
		exit(0);
	}
	encode_bits(bits, bits_size);
	save_img(dest);
	cout << "Done" << endl;
}

void png_steg::decode_steg(string source) {
	read_img(source);
	decode_bits();
}

void png_steg::read_img(string path) {
	FILE *f = fopen(path.c_str(), "rb");
	if (!f) {
		cout << "File not found" << endl;
		exit(1);
	}

	unsigned char header[8];
	fread(header, 1, 8, f);
	if (png_sig_cmp(header, 0, 8)) {
		cout << "File is not PNG" << endl;
		exit(1);
	}

	read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!read) {
		cout << "Read error" << endl;
		exit(1);
	}
	info = png_create_info_struct(read);
	if (!info) {
		png_destroy_read_struct(&read, NULL, NULL);
		cout << "Info error" << endl;
		exit(1);
	}
	png_infop end_info = png_create_info_struct(read);
	if (!end_info) {
		png_destroy_read_struct(&read, &info, NULL);
		cout << "End info error" << endl;
		exit(1);
	}

	png_init_io(read, f);
	png_set_sig_bytes(read, 8);
	png_read_png(read, info, PNG_TRANSFORM_IDENTITY, NULL);
	rows = png_get_rows(read, info);

	fclose(f);
	free(end_info);
}

void png_steg::save_img(string dest) {
	FILE *f = fopen(dest.c_str(), "wb");
	if (!f) {
		cout << "Cannot create/open output file" << endl;
		exit(1);
	}
	write = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!write) {
		cout << "Write error" << endl;
		exit(1);
	}
	png_init_io(write, f);
	png_set_rows(write, info, rows);
	png_write_png(write, info, PNG_TRANSFORM_IDENTITY, NULL);
	fclose(f);
	png_destroy_read_struct(&read, &info, NULL);
	png_destroy_write_struct(&write, NULL);
}

void png_steg::encode_bits(string bits, unsigned int bits_size) {
	unsigned int i = 0, j = 0;
	for (unsigned int count = 0; count < bits_size; count++) {
		bits[count] == '1' ? (*(rows[i] + j) |= 0b1) : (*(rows[i] + j) &= 0b0);
		j++;
		if (j == info->width * info->color_type) {
			i++;
			j = 0;
		}
	}
}

void png_steg::decode_bits() {
	unsigned int i = 0, j = 0;
	unsigned int size = 0;
	for (unsigned int count = 0; count < 32; count++) {
		size = size << 1;
		size += (*(rows[i] + j)) & 0b1;
		j++;
		if (j == info->width * info->color_type) {
			i++;
			j = 0;
		}
	}

	char c = 0;
	unsigned int n = 0;
	for (unsigned int count = 0; count < size * 8; count++) {
		c = c << 1;
		c += (*(rows[i] + j)) & 0b1;
		j++;
		n++;
		if (n == 8) {
			cout << c;
			n = 0;
			c = 0;
		}
		if (j == info->width * info->color_type) {
			i++;
			j = 0;
		}
	}
	cout << endl << "Done" << endl;

	png_destroy_read_struct(&read, &info, NULL);
}