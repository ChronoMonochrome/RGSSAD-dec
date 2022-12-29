#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include "helpers.hpp"

namespace rgssad {

using namespace std;

class BinaryReader {
public:
	BinaryReader(string fileName);
	~BinaryReader();
	
	uint32_t readUint32();
	char *read(size_t length);
	void seek(streamoff off);
	streamoff tell();
private:
	ifstream mIfs;
	vector<char> mBuffer;
	size_t mFileSize;
};

}