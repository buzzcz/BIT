#ifndef SP_STEG_H
#define SP_STEG_H

#include <iostream>

using namespace std;

class steg {
public:
	static string get_bits(string text, size_t text_size);

	static void write_to_file(string output, string text);
};


#endif
