//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

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
	void read(vector<char> &buffer, size_t length);
	void seek(streamoff off, ios_base::seekdir way);
	int eof();
	streamoff tell();
private:
	ifstream mIfs;
	size_t mBinSize;
};

}