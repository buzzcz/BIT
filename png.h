#ifndef SP_HIDE_IN_PNG_H
#define SP_HIDE_IN_PNG_H

#include <iostream>

using namespace std;

class png {
public:
	void hide(string source, string text);
private:
	char *img;
	long len;
	void read_img(string path);
	void save_img(string dest);
	void read_header(unsigned int *width, unsigned int *height);
	unsigned int find_data(unsigned int start);
	void hide_char(char c, unsigned int start);
};


#endif
