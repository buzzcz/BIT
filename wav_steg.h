#ifndef SP_WAV_H
#define SP_WAV_H

#include <iostream>

using namespace std;

class wav_steg {
public:
	void encode_steg(string source, string dest, string text);

	void decode_steg(string source);
};


#endif
