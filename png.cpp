#include <netinet/in.h>
#include <cstring>
#include "png.h"

void png::hide(string source, string text) {
	unsigned int width, height;
	read_img(source);
	read_header(&width, &height);
	unsigned int start = 37;
	int number_of_char = 0;
	size_t text_size = strlen(text.c_str());
	while ((start = find_data(start)) != 0) {
		unsigned int begin = start;
		unsigned int length = *(unsigned int *) &img[begin - 4];
//		TODO if char doesn't fit into data chunk
		if (length % 8 == 0) {
			for (unsigned int i = 0; i < length && number_of_char < text_size; i++) {
				begin += 4;
				hide_char(text[number_of_char++], begin);
			}
		} else {

		}
//		TODO calculate new checksum
		start += length + 8;
	}
	save_img("Bug_steg.png");
	cout << "Done" << endl;
}

void png::read_img(string path) {
	FILE *f = fopen(path.c_str(), "rb");
	if (f == NULL) {
		cout << "File not found" << endl;
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	img = (char *) malloc((len + 1) * sizeof(char));
	fseek(f, 0, SEEK_SET);
	fread(img, 1, len, f);
	fclose(f);
}

void png::save_img(string dest) {
	FILE *f = fopen(dest.c_str(), "wb");
	fwrite(img, 1, len, f);
	fclose(f);
	free(img);
}

void png::read_header(unsigned int *width, unsigned int *height) {
	*width = htonl(*(unsigned int *) &img[16]);
	*height = htonl(*(unsigned int *) &img[20]);
}

unsigned int png::find_data(unsigned int start) {
	for (; start < len - 4; start++) {
		string s = "";
		for (unsigned int i = start; i < start + 4; i++) {
			s += img[i];
		}
		if (strcmp(s.c_str(), "IDAT") == 0) return start;
		else if (strcmp(s.c_str(), "IEND") == 0) return 0;
	}
	return 0;
}

void png::hide_char(char c, unsigned int start) {
	for (int i = 0; i < 8; i++) {
		char bit;
		switch (i) {
			case 0:
				bit = (char) ((c >> 7) & 0b1);
				break;
			case 1:
				bit = (char) ((c >> 6) & 0b1);
				break;
			case 2:
				bit = (char) ((c >> 5) & 0b1);
				break;
			case 3:
				bit = (char) ((c >> 4) & 0b1);
				break;
			case 4:
				bit = (char) ((c >> 3) & 0b1);
				break;
			case 5:
				bit = (char) ((c >> 2) & 0b1);
				break;
			case 6:
				bit = (char) ((c >> 1) & 0b1);
				break;
			default:
				bit = (char) (c & 0b1);
				break;
		}
		bit == 1 ? (img[start + i] |= (1 << 0)) : (img[start + i] &= ~(1 << 2));
	}
}